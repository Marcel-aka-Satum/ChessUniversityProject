//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include "SchaakStuk.h"

class Game {
// variabelen om de status van het spel/bord te bewaren

public:
    Game();
    ~Game();

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k
    //kijkt of koning met kleur in schaak staat
    bool schaak(zw kleur, vector<pair<int,int>> &killPositions);

    bool schaakmat(zw kleur);

    bool pat(zw kleur);

    void setStartBord();

    SchaakStuk* getPiece(int r, int k);

    void setPiece(int r, int k, SchaakStuk* s);

    SchaakStuk* schaakboord[8][8];

    vector<pair<int, int>> &getBlackKillPositions();

    vector<pair<int, int>> &getWhiteKillPositions();
    //kijkt of een bepaalde schaakstuk op positie r, k in schaak staat
    bool schaak_danger(int r, int k);

    int rijWhiteKing = 0;

    int kolomWhiteKing = 4;

    int rijBlackKing = 7;

    int kolomBlackKing = 4;
    //verwijder geldige zetten van schaakstukken wnr koning in schaak staat
    void update_geldige_zetten();

private:
    // Hier zet jij jouw datastructuur neer om het bord te bewaren ...
    vector<pair<int,int>> blackKillPositions; // vector die bevat alle posities die white kan killen OP HET MOMENT (gebruikt in functei updateBlack())

    vector<pair<int,int>> whiteKillPositions; // vector die bevat alle posities die white kan OP HET MOMENT killen (gebruikt in functie updateWhite())

};


#endif //SCHAKEN_GAME_H
