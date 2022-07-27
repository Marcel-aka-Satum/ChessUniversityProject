//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"
#include "SchaakGUI.h"
#include "iostream"
#include "guicode/message.h"
Game::Game() {}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de jusite plaats toe
void Game::setStartBord() {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            schaakboord[i][j] = nullptr;
        }
    }

    schaakboord[0][0] = new Toren(zwart);
    schaakboord[0][1] = new Paard(zwart);
    schaakboord[0][2] = new Loper(zwart);
    schaakboord[0][3] = new Koning(zwart);
    schaakboord[0][4] = new Koningin(zwart);
    schaakboord[0][5] = new Loper(zwart);
    schaakboord[0][6] = new Paard(zwart);
    schaakboord[0][7] = new Toren(zwart);

    schaakboord[1][0] = new Pion(zwart);
    schaakboord[1][1] = new Pion(zwart);
    schaakboord[1][2] = new Pion(zwart);
    schaakboord[1][3] = new Pion(zwart);
    schaakboord[1][4] = new Pion(zwart);
    schaakboord[1][5] = new Pion(zwart);
    schaakboord[1][6] = new Pion(zwart);
    schaakboord[1][7] = new Pion(zwart);

    schaakboord[6][0] = new Pion(wit);
    schaakboord[6][1] = new Pion(wit);
    schaakboord[6][2] = new Pion(wit);
    schaakboord[6][3] = new Pion(wit);
    schaakboord[6][4] = new Pion(wit);
    schaakboord[6][5] = new Pion(wit);
    schaakboord[6][6] = new Pion(wit);
    schaakboord[6][7] = new Pion(wit);

    schaakboord[7][0] = new Toren(wit);
    schaakboord[7][1] = new Paard(wit);
    schaakboord[7][2] = new Loper(wit);
    schaakboord[7][3] = new Koning(wit);
    schaakboord[7][4] = new Koningin(wit);
    schaakboord[7][5] = new Loper(wit);
    schaakboord[7][6] = new Paard(wit);
    schaakboord[7][7] = new Toren(wit);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
           if(schaakboord[i][j] != nullptr){
               schaakboord[i][j]->rij = i;
               schaakboord[i][j]->kolom = j;
           }
        }
    }
}

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    vector<pair<int,int>> v= s->geldige_zetten(*this);
    int rij = s->rij;
    int kolom = s->kolom;
    bool canMove = false;

    for(auto i : v){
        if(i.first == r && i.second == k){
            canMove = true;
        }
    }
    if(canMove){
        schaakboord[rij][kolom] = nullptr;
        setPiece(r,k,s);
        schaakboord[r][k]->rij = r;
        schaakboord[r][k]->kolom = k;
        if(s->piece().type() == 0 && s->getKleur() == wit){
            rijWhiteKing = r;
            kolomWhiteKing = k;
        } else if(s->piece().type() == 0 && s->getKleur() == zwart){
            rijBlackKing = r;
            kolomBlackKing = k;
        }
        return true;
    } else{
        return false;
    }
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur, vector<pair<int,int>> &killPositions) {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(schaakboord[i][j] != nullptr){
                if(schaakboord[i][j]->piece().type() == 0 && schaakboord[i][j]->getKleur() == kleur){ // type 0 == King
                    //kijk of enemy de king kan killen
                    for(auto h : killPositions){
                        if(h.first == i && h.second == j){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    return false;
}

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k) {
    // Hier komt jouw code om op te halen welk stuk op rij r, kolom k staat
    return schaakboord[r][k];
}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk* s)
{
    // Hier komt jouw code om een stuk neer te zetten op het bord
    schaakboord[r][k] = s;
    schaakboord[r][k]->rij = r;
    schaakboord[r][k]->kolom = k;
}

vector<pair<int, int>> &Game::getBlackKillPositions(){
    return blackKillPositions;
}

vector<pair<int, int>> &Game::getWhiteKillPositions(){
    return whiteKillPositions;
}

bool Game::schaak_danger(int r, int k){
    if(schaakboord[r][k] == nullptr){
        return false;
    }
    SchaakStuk* s = schaakboord[r][k];
    if(s->getKleur() == zwart){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(schaakboord[i][j] != nullptr && schaakboord[i][j]->getKleur() == wit){
                    for(auto i : schaakboord[i][j]->danger_posities){
                        if(i.first == r && i.second == k){
                            return true;
                        }
                    }
                }
            }
        }
    } else if(s->getKleur() == wit){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(schaakboord[i][j] != nullptr && schaakboord[i][j]->getKleur() == zwart){
                    for(auto i : schaakboord[i][j]->danger_posities){
                        if(i.first == r && i.second == k){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Game::update_geldige_zetten() {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(schaakboord[i][j] != nullptr){
                int position = 0;
                bool remove = false;
                SchaakStuk* s = schaakboord[i][j];
                if(schaakboord[i][j]->geldige_zetten(*this).size() > 0){
                    for(auto h : schaakboord[i][j]->geldige_zetten(*this)){
                        move(schaakboord[i][j], h.first, h.second);
                        if(schaakboord[h.first][h.second]->getKleur() == zwart){
                            if(schaak_danger(rijBlackKing, kolomBlackKing)){
                                remove = true;
                            }
                        } else if(schaakboord[h.first][h.second]->getKleur() == wit){
                            if(schaak_danger(rijWhiteKing, kolomWhiteKing)){
                                remove = true;
                            }
                        }
                        //remove zet in geldige zetten indien de koning nogsteeds in danger is
                        if(remove){
                            schaakboord[i][j]->geldige_zetten(*this).erase(schaakboord[i][j]->geldige_zetten(*this).begin() + position);
                            remove = false;
                        }
                        schaakboord[h.first][h.second] = nullptr;
                        setPiece(i,j, s);
                        position++;
                    }
                }
            }
        }
    }
}



