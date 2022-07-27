//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>
#include <vector>
#include <utility>
using namespace std;
class Game;

enum zw{zwart,wit};

class SchaakStuk {
public:

    SchaakStuk(zw kleur): kleur(kleur) {}

    int rij;

    int kolom;

    vector<pair<int,int>> danger_posities; // positions that SchaakStuk can kill

    virtual vector<pair<int,int>> geldige_zetten(Game& g);

    virtual Piece piece() const=0;      // Verander deze functie niet!
                                        // Deze functie wordt gebruikt door
                                        // setItem(x,y,SchaakStuk*) van
                                        // SchaakGUI

    zw getKleur() const { return kleur; }
private:
    zw kleur;
};

class Pion:public SchaakStuk {
public:

    vector<pair<int,int>> geldige_zetten(Game& g);
    Pion(zw kleur):SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }

};

class Toren:public SchaakStuk {
public:
    vector<pair<int,int>> geldige_zetten(Game& g);
    Toren(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }
};

class Paard:public SchaakStuk {
public:
    vector<pair<int,int>> geldige_zetten(Game& g);
//    int rij;
//    int kolom;
    Paard(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }
};

class Loper:public SchaakStuk {
public:
    vector<pair<int,int>> geldige_zetten(Game& g);
//    int rij;
//    int kolom;
    Loper(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }
};

class Koning:public SchaakStuk {
public:
    vector<pair<int,int>> geldige_zetten(Game& g);
//    int rij;
//    int kolom;
    Koning(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }
};

class Koningin:public SchaakStuk {
public:
    vector<pair<int,int>> geldige_zetten(Game& g);
//    int rij;
//    int kolom;
    Koningin(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }
};

#endif //SCHAKEN_SCHAAKSTUK_H
