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

// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    if (!secondClick){
        if(g.schaakboord[r][k] != nullptr){
            s = g.getPiece(r,k);
            v= s->getEigenGeldigeZetten();
        }
    }
    //FIRST CLICK
    if(beginWit == 0 && !secondClick && s != nullptr){ // eerste begint wit dus select wit
        if(s->getKleur() == wit){
            removeAllMarking();
            //setTileSelect + setTileFocus
            if(g.schaakboord[r][k] != nullptr){
                if(dMoves){
                    setTileSelect(r,k, true);
                    for(auto i : v){ // geef dan alle geldige posities waarnaar dit stuk verplaatst kan worden
                        setTileFocus(i.first,i.second, true);
                    }
                }
            }
            //color_red(s) = setTileThreat
            color_red(s);
            r2 = r;
            k2 = k;
            beginWit++;
            secondClick = true;
            update();
            return;
        }
    } else if(beginWit == 1 && !secondClick && s != nullptr) { // na wit moet zwart
        if(s->getKleur() == zwart){
            removeAllMarking();
            //setTileSelect + setTileFocus
            if(g.schaakboord[r][k] != nullptr){
                if(dMoves){
                    setTileSelect(r,k, true);
                    for(auto i : v){ // geef dan alle geldige posities waarnaar dit stuk verplaatst kan worden
                        setTileFocus(i.first,i.second, true);
                    }
                }
            }
            //color_red(s) = setTileThreat
            color_red(s);
            r2 = r;
            k2 = k;
            beginWit--;
            secondClick = true;
            update();
            return;
        }
    }
    if(secondClick){ // SECOND CLICK
        // unselect Schaakstuk
        if(r == r2 && k == k2){
            removeAllMarking();
            //setPieceThreat
            if(dKills){
                if(s->getKleur() == zwart){
                    for(auto move : g.getBlackKillPositions()){
                        setPieceThreat(move.first, move.second, true);
                    }
                } else if(s->getKleur() == wit){
                    for(auto move : g.getWhiteKillPositions()){
                        setPieceThreat(move.first, move.second, true);
                    }
                }
            }
            if(dThreats){
                if(s->getKleur() == wit){
                    for(auto move : g.getBlackKillPositions()){
                        setPieceThreat(move.first, move.second, true);
                    }
                } else if(s->getKleur() == zwart){
                    for(auto move : g.getWhiteKillPositions()){
                        setPieceThreat(move.first, move.second, true);
                    }
                }
            }
            s = nullptr;
            if(beginWit == 1){
                beginWit = 0;
                secondClick = false;
            } else{
                beginWit = 1;
                secondClick= false;
            }
            return;
        }
        // look if it's a valid move
        bool found = false;
        for(auto i : v){
            if(i.first == r && i.second == k){
                found = true;
                break;
            }
        }
        if(found){ // beweging gevonden
            g.move(s,r,k);
            removeAllMarking();
            update();
            updateWhite(g.getWhiteKillPositions());
            updateBlack(g.getBlackKillPositions());
            //setPieceThreat
            if(dKills){
                if(s->getKleur() == zwart){
                    for(auto move : g.getBlackKillPositions()){
                        setPieceThreat(move.first, move.second, true);
                    }
                } else if(s->getKleur() == wit){
                    for(auto move : g.getWhiteKillPositions()){
                        setPieceThreat(move.first, move.second, true);
                    }
                }
            }
            if(dThreats){
                if(s->getKleur() == wit){
                    for(auto move : g.getBlackKillPositions()){
                        setPieceThreat(move.first, move.second, true);
                    }
                } else if(s->getKleur() == zwart){
                    for(auto move : g.getWhiteKillPositions()){
                        setPieceThreat(move.first, move.second, true);
                    }
                }
            }
            //check mate
            if(g.schaakmat(wit, g.getBlackKillPositions())){
                message("Wit heeft gewonnen!");
            } else if(g.schaakmat(zwart, g.getWhiteKillPositions())){
                message("Zwart heeft gewonnen");
            }
            //stalemate
            if(g.pat(wit, g.getBlackKillPositions())){
                message("Pat voor wit");
            } else if(g.pat(zwart, g.getWhiteKillPositions())){
                message("Pat voor zwart");
            }
            //check
            if(g.schaak(wit, g.getBlackKillPositions())){
                message("Schaak wit!");
            } else if(g.schaak(zwart, g.getWhiteKillPositions())){
                message("Schaak zwart!");
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
    if(!displayMoves()){
        dMoves = false;
    } else{
        dMoves = true;
    }
    if(!displayKills()){
        dKills = false;
    } else{
        dKills = true;
    }
    if(!displayThreats()){
        dThreats = false;
    } else{
        dThreats = true;
    }
}


// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {
    clearBoard();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8;j++){
            if(g.schaakboord[i][j] != nullptr){
                setItem(i,j, g.schaakboord[i][j]);
                g.schaakboord[i][j]->setEigenGeldigeZetten(g.schaakboord[i][j]->geldige_zetten(g));
            }
        }
    }
    g.update_geldige_zetten();
}

/*
 * void SchaakGUI::updateWhite(vector<pair<int,int>> &whiteKillPositions2);
 * Loop door de schaakboord en kijk de danger_posities van elke witte schaakstuk vervolgens voeg deze toe in whiteKillPositions vector
 * die gebruikt wordt om te kijken waar witte speler zwarte speler kan killen
 * * */
void SchaakGUI::updateWhite(vector<pair<int,int>> &whiteKillPositions2){
    whiteKillPositions2.clear();
    //alle plekken waar wit kan killen in whiteKillPosition steken
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            //whitekillposition
            if(g.schaakboord[i][j] != nullptr && g.schaakboord[i][j]->getKleur() == wit){
                if(g.schaakboord[i][j]->danger_posities.size() > 0){
                    for(auto b : g.schaakboord[i][j]->danger_posities){
                        bool found = false; // check if there is already same pair
                        for(auto h : whiteKillPositions2){
                            if(h.first == b.first && h.second == b.second){
                                found = true;
                                break;
                            }
                        }
                        if(!found){
                            // kijk ofdat na een kill een schaak is indien wel dan gaat voegt gij deze move niet in de vector
                            bool found2 = false;
                            for(auto move : g.schaakboord[i][j]->getEigenGeldigeZetten()){
                                if(b.first == move.first && b.second == move.second){
                                    found2 = true;
                                    break;
                                }
                            }
                            if(found2){
                                whiteKillPositions2.push_back(make_pair(b.first, b.second));
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
 * void SchaakGUI::updateBlack(vector<pair<int,int>> &blackKillPositions2);
 * Zelfde als functie hierboven maar voor zwarte speler
 * * */
void SchaakGUI::updateBlack(vector<pair<int,int>> &blackKillPositions2){
    blackKillPositions2.clear();
    //alle plekken waar zwart kan killen in blackKillPositions steken
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            //blackKillPositions
            if(g.schaakboord[i][j] != nullptr){
                if(g.schaakboord[i][j]->getKleur() == zwart){
                    for(auto b : g.schaakboord[i][j]->danger_posities){
                        bool found = false; // check if there is already same pair
                        for(auto h : blackKillPositions2){
                            if(h.first == b.first && h.second == b.second){
                                found = true;
                                break;
                            }
                        }
                        if(!found){
                            // kijk ofdat na een kill een schaak is indien wel dan gaat voegt gij deze move niet in de vector
                            bool found2 = false;
                            for(auto move : g.schaakboord[i][j]->getEigenGeldigeZetten()){
                                if(b.first == move.first && b.second == move.second){
                                    found2 = true;
                                    break;
                                }
                            }
                            if(found2){
                                blackKillPositions2.push_back(make_pair(b.first, b.second));
                            }
                        }
                    }
                }
            }
        }
    }
}

void SchaakGUI::color_red(SchaakStuk* s) {
    /*
     * 1) loop through all legal possible moves and then make a move
     * 2) check if the Schaakstuk is in danger
     * 3) if 2) == true then color the red square
     * 4) go back to previous move
     * 5) repeat until you've looped through all legal possible moves
     * */
    if(s == nullptr){
        return;
    }
    int primaryRij = s->rij;
    int primaryKolom = s->kolom;
    //1)
    for(auto i : s->getEigenGeldigeZetten()){
        SchaakStuk* temp = nullptr; // use for storing killed schaakstuk
        if(g.schaakboord[i.first][i.second] != nullptr){
            temp = g.schaakboord[i.first][i.second];
        }
        g.move(s, i.first, i.second);
        //2)
        if(g.schaak_danger(i.first, i.second)){
            //3)
            setTileThreat(i.first, i.second, true);
        }
        //4)
        g.setPiece(primaryRij, primaryKolom, s);
        g.schaakboord[i.first][i.second] = nullptr;
        //fix if a SchaakStuk has been killed
        if(temp != nullptr){
            g.setPiece(i.first, i.second, temp);
        }
    }
}



