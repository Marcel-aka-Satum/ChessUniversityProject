//
// Created by toonc on 12/17/2021.
//

#ifndef SCHAKEN_SCHAAKGUI_H
#define SCHAKEN_SCHAAKGUI_H

#include "guicode/ChessWindow.h"
#include <QMessageBox>
#include <QAction>
#include "vector"
#include "SchaakStuk.h"

class SchaakGUI:public ChessWindow {
public:
    SchaakGUI();

    void update();
    void updateWhite(vector<pair<int,int>> &whiteKillPositions2); //Gaat in vector whiteKillPositions2 alle coordinaten steken die wit kan killen (steekt geen coordinaten wnr er na een kill schaakmat is)
    void updateBlack(vector<pair<int,int>> &blackKillPositions2); //Gaat in vector blackKillPositions2 alle coordinaten steken die black kan killen (steekt geen coordinaten wnr er na een kill schaakmat is)
    void color_red(SchaakStuk* s); // click on a Schaakstuk and then make a move for every legal move for this Schaakstuk and if the move is dangerous (can be killed) color the square red, reset everything to it's primary state

private:
    Game g;


private:
    //bool vars used for displaymoves (updated after visualizationChange!)
    bool dMoves;
    bool dThreats;
    bool dKills;

    void clicked(int x, int y) override;
    void newGame() override;
    void open() override;
    void save() override;
    void undo() override;
    void redo() override;
    void visualizationChange() override;

/*  Overgeerfde functies van ChessWindow:

    void removeAllMarking();
    void clearBoard();
    void setItem(int i,int j,SchaakStuk* p);
    void setPieceThreat(int i,int j,bool b);
    void removeAllPieceThreats();
    void setTileSelect(int i,int j,bool b);
    void setTileFocus(int i,int j,bool b);
    void setTileThreat(int i,int j,bool b);

    bool displayKills();
    bool displayMoves();
    bool displayThreats();
*/
};


#endif //SCHAKEN_SCHAAKGUI_H
