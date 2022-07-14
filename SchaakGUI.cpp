//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"
#include <iostream>
// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr) {
    g.setStartBord();
    update();
}

int beginWit = 0; // een integer om te kijken wie dat er begint
bool secondClick = false; // een bool om te kijken of wij user second click doet
int r2, k2; // bevat rij en kolom van de vorige schaakstuk indien er een nieuwe gekozen word
vector<pair<int,int>> v; // bevat de geldige zetten van schaakstuk s
SchaakStuk* s; // bevat de schaakstuk
vector<pair<int,int>> blackKillPositions; // vector die bevat alle posities die white kan killen OP HET MOMENT (gebruikt in functei updateBlack())
vector<pair<int,int>> whiteKillPositions; // vector die bevat alle posities die white kan OP HET MOMENT killen (gebruikt in functie updateWhite())


// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    if (!secondClick){
        if(g.schaakboord[r][k] != nullptr){
            s = g.getPiece(r,k);
            v=s->geldige_zetten(g);
        }
    }
    if(beginWit == 0 && secondClick == false){ // eerste begint wit dus select wit
        if(s->getKleur() == wit){
            if(SchaakGUI::displayMoves()){
                setTileSelect(r,k, true);
                for(auto i : v){ // geef dan alle geldige posities waarnaar dit stuk verplaatst kan worden
                    setTileFocus(i.first,i.second, true);
                }
            }
            r2 = r;
            k2 = k;
            beginWit++;
            secondClick = true;
            update();
            return;
        }
    } else if(beginWit == 1 && !secondClick) {// na wit moet zwart
        if(s->getKleur() == zwart){
            if(SchaakGUI::displayMoves()){
                setTileSelect(r,k, true);
                for(auto i : v){ // geef dan alle geldige posities waarnaar dit stuk verplaatst kan worden
                    setTileFocus(i.first,i.second, true);
                }
            }

            r2 = r;
            k2 = k;
            beginWit--;
            secondClick = true;
            update();
            return;
        }
    }
    if(secondClick){ // second click
        if(r == r2 && k == k2){ // unselect
            removeAllMarking();
            update();
            // set threat
            if(SchaakGUI::displayThreats()){
                for(auto v : whiteKillPositions){
                    setPieceThreat(v.first, v.second, true);
                }
                for(auto l : blackKillPositions){
                    setPieceThreat(l.first, l.second, true);
                }
            }
            if(beginWit == 1){
                beginWit = 0;
                secondClick = false;
            } else{
                beginWit = 1;
                secondClick= false;
            }
            return;
        }
        bool found = false;
        for(auto i : v){
            if(i.first == r && i.second == k){
                found = true;
                break;
            }
        }
        if(found){
            g.move(s,r,k);
            removeAllMarking();
            update();
            updateWhite(whiteKillPositions);
            updateBlack(blackKillPositions);
            printGeldigWhite(whiteKillPositions);
            // set threat
            if(SchaakGUI::displayThreats()){
                for(auto v : whiteKillPositions){
                    setPieceThreat(v.first, v.second, true);
                }
                for(auto l : blackKillPositions){
                    setPieceThreat(l.first, l.second, true);
                }
            }
            secondClick = false;
            return;
        } else{
            message("Ongeldige zet");
            return;
        }
    }

}

void SchaakGUI::newGame()
{}


void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb") << QString("Hb") << QString("Rb");
        for  (int i=0;i<8;i++) {
            out << QString("Pb");
        }
        for  (int r=3;r<7;r++) {
            for (int k=0;k<8;k++) {
                out << QString(".");
            }
        }
        for  (int i=0;i<8;i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw") << QString("Hw") << QString("Rw");
    }
}

void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r=0;r<8;r++) {
                for (int k=0;k<8;k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Invalid File Format");
                    }
                }
                debugstring += "\n";
            }
            message(debugstring);
        } catch (QString& Q) {
            message(Q);
        }
    }
    update();
}


void SchaakGUI::undo() {
    message("Je hebt undo gekozen");
}

void SchaakGUI::redo() {}


void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves()?"T":"F")+(displayKills()?"T":"F")+(displayThreats()?"T":"F");
    message(QString("Visualization changed : ")+visstring);
}


// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {
    clearBoard();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8;j++){
            if(g.schaakboord[i][j] != nullptr){
                setItem(i,j, g.schaakboord[i][j]);
            }
        }
    }
}


void SchaakGUI::updateWhite(vector<pair<int,int>> &whiteKillPositions2){
    geldigForWhite();
    whiteKillPositions2.clear();
    //alle plekken waar wit kan killen in whiteKillPosition steken
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            //whitekillposition
            if(g.schaakboord[i][j] != nullptr && g.schaakboord[i][j]->getKleur() == wit){
                if(g.schaakboord[i][j]->danger_posities.size() > 0){
                    for(auto b : g.schaakboord[i][j]->danger_posities){
                        whiteKillPositions2.push_back(make_pair(b.first, b.second));
                    }
                }
            }
        }
    }

    // reset danger_posities
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(g.schaakboord[i][j] != nullptr){
                if(g.schaakboord[i][j]->getKleur() == wit && g.schaakboord[i][j]->danger_posities.size() > 0){
                    g.schaakboord[i][j]->danger_posities.clear();
                }
            }
        }
    }
}

void SchaakGUI::updateBlack(vector<pair<int,int>> &blackKillPositions2){
    geldigForBlack();
    blackKillPositions2.clear();
    //alle plekken waar wit kan killen in whiteKillPosition steken
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            //blackKillPositions
            if(g.schaakboord[i][j] != nullptr){
                if(g.schaakboord[i][j]->getKleur() == zwart){
                    for(auto b : g.schaakboord[i][j]->danger_posities){
                        blackKillPositions2.push_back(make_pair(b.first, b.second));
                    }
                }
            }
        }
    }
    // reset danger_posities
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(g.schaakboord[i][j] != nullptr){
                if(g.schaakboord[i][j]->getKleur() == zwart && g.schaakboord[i][j]->danger_posities.size() > 0){
                    g.schaakboord[i][j]->danger_posities.clear();
                }
            }
        }
    }
}


void SchaakGUI::geldigForWhite(){
    vector<pair<int,int>> rr;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(g.schaakboord[i][j] != nullptr){
                if(g.schaakboord[i][j]->getKleur() == wit){
                    rr = g.schaakboord[i][j]->geldige_zetten(g);
                }
            }
        }
    }
}

void SchaakGUI::geldigForBlack(){
    vector<pair<int,int>> rr;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(g.schaakboord[i][j] != nullptr){
                if(g.schaakboord[i][j]->getKleur() == zwart){
                    rr = g.schaakboord[i][j]->geldige_zetten(g);
                }
            }
        }
    }
}

void SchaakGUI::printGeldigWhite(vector<pair<int, int>> killPositions) {

    if(killPositions.size() > 0){
        cout << "POSITIES DIE WHITE KAN KILLEN: " << endl;
        for(auto i :killPositions){
            cout << i.first << ", " << i.second << endl;
        }
    } else{
        cout << "White kan niemand killen " << endl;
    }
}

