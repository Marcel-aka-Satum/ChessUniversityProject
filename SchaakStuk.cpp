//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "game.h"

vector<pair<int,int>> SchaakStuk::geldige_zetten(Game& g){
    vector<pair<int,int>> zetten;

    return zetten;
}

vector<pair<int, int>> &SchaakStuk::getEigenGeldigeZetten() {
    return eigen_geldige_zetten;
}

void SchaakStuk::setEigenGeldigeZetten(vector<pair<int, int>> eigenGeldigeZetten) {
    eigen_geldige_zetten = eigenGeldigeZetten;
}

vector<pair<int,int>> Pion::geldige_zetten(Game& g){
    vector<pair<int,int>> zetten;
    int rij = this->rij;
    int kolom = this->kolom;
    danger_posities.clear();

    if(g.schaakboord[rij][kolom]->getKleur() == zwart){ // check black
        if(g.schaakboord[rij+1][kolom+1] != nullptr && g.schaakboord[rij+1][kolom+1]->getKleur() == wit && g.schaakboord[rij][kolom]->kolom < 7 && rij+1 >= 0 && rij+1 <= 7) {
            zetten.push_back(make_pair(rij + 1, kolom + 1)); // kill schijn rechts indien niet op kolom 7
            danger_posities.push_back(make_pair(rij+1, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
        }
        if(g.schaakboord[rij+1][kolom-1] != nullptr && g.schaakboord[rij+1][kolom-1]->getKleur() == wit && g.schaakboord[rij][kolom]->kolom > 0 && rij+1 >= 0 && rij +1 <= 7){
            zetten.push_back(make_pair(rij+1,kolom-1)); // kill schijn links indien niet op kolom 0
            danger_posities.push_back(make_pair(rij+1, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
        }
        if(g.schaakboord[rij+1][kolom] == nullptr){
            zetten.push_back(make_pair(rij+1, kolom));
        } else{
            return zetten;
        }
        if(g.schaakboord[rij+2][kolom] == nullptr && g.schaakboord[rij][kolom]->rij == 1){
            zetten.push_back(make_pair(rij+2, kolom));
        }
    } else if(g.schaakboord[rij][kolom]->getKleur() == wit){ // check white
        if(g.schaakboord[rij-1][kolom+1] != nullptr && g.schaakboord[rij-1][kolom+1]->getKleur() == zwart && g.schaakboord[rij][kolom]->kolom < 7 && rij-1 >= 0 && rij-1 <= 7) {
            zetten.push_back(make_pair(rij-1, kolom + 1)); // kill schijn rechts idien kolom < 7
            danger_posities.push_back(make_pair(rij-1, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
        }
        if(g.schaakboord[rij-1][kolom-1] != nullptr && g.schaakboord[rij-1][kolom-1]->getKleur() == zwart && g.schaakboord[rij][kolom]->kolom > 0 && rij-1 >= 0 && rij-1 <= 7) {
            zetten.push_back(make_pair(rij-1, kolom - 1)); // kill schijn links idien kolom > 0
            danger_posities.push_back(make_pair(rij-1, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
        }
        if(g.schaakboord[rij-1][kolom] == nullptr){
            zetten.push_back(make_pair(rij-1, kolom));
        } else{
            return zetten;
        }
        if(g.schaakboord[rij-2][kolom] == nullptr && g.schaakboord[rij][kolom]->rij == 6){
            zetten.push_back(make_pair(rij-2, kolom));
        }
    }
    return zetten;
}


vector<pair<int,int>> Toren::geldige_zetten(Game& g){
    vector<pair<int,int>> zetten;
    int rij = this->rij;
    int kolom = this->kolom;
    danger_posities.clear();

    if(g.schaakboord[rij][kolom]->getKleur() == zwart){
        //under for black
        for(int i = 1; i < 8; i++){
            if(rij+i > 7){
                break;
            }
            if(g.schaakboord[rij+i][kolom] == nullptr){
                zetten.push_back(make_pair(rij+i, kolom));
            } else if(g.schaakboord[rij+i][kolom] != nullptr && g.schaakboord[rij+i][kolom]->getKleur() == wit){
                zetten.push_back(make_pair(rij+i, kolom));//stop
                danger_posities.push_back(make_pair(rij+i, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{ //als zwarte pion ervoor is
                break;
            }
        }
        //top for black
        for(int i = 1; i < 8; i++){
            if(rij-i < 0){
                break;
            }
            if(g.schaakboord[rij-i][kolom] == nullptr){
                zetten.push_back(make_pair(rij-i, kolom));
            } else if(g.schaakboord[rij-i][kolom] != nullptr && g.schaakboord[rij-i][kolom]->getKleur() == wit){
                zetten.push_back(make_pair(rij-i, kolom));//stop
                danger_posities.push_back(make_pair(rij-i, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else {
                break;
            }
        }
        // right for black
        for(int i = 1; i < 8; i++){
            if(kolom+i > 7){
                break;
            }
            if(g.schaakboord[rij][kolom+i] == nullptr){
                zetten.push_back(make_pair(rij, kolom+i));
            } else if(g.schaakboord[rij][kolom+i] != nullptr && g.schaakboord[rij][kolom+i]->getKleur() == wit){
                zetten.push_back(make_pair(rij, kolom+i));//stop
                danger_posities.push_back(make_pair(rij, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{
                break;
            }
        }
        //left for black
        for(int i = 1; i < 8; i++){
            if(kolom-i < 0){
                break;
            }
            if(g.schaakboord[rij][kolom-i] == nullptr){
                zetten.push_back(make_pair(rij, kolom-i));
            } else if(g.schaakboord[rij][kolom-i] != nullptr && g.schaakboord[rij][kolom-i]->getKleur() == wit){
                zetten.push_back(make_pair(rij, kolom-i));//stop
                danger_posities.push_back(make_pair(rij, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{
                break;
            }
        }
    } else{
        //under for white
        for(int i = 1; i < 8; i++){
            if(rij+i > 7){
                break;
            }
            if(g.schaakboord[rij+i][kolom] == nullptr){
                zetten.push_back(make_pair(rij+i, kolom));
            } else if(g.schaakboord[rij+i][kolom] != nullptr && g.schaakboord[rij+i][kolom]->getKleur() == zwart){
                zetten.push_back(make_pair(rij+i, kolom));//stop
                danger_posities.push_back(make_pair(rij+i, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{ //als white pion ervoor is
                break;
            }
        }
        //top for white
        for(int i = 1; i < 8; i++){
            if(rij-i < 0){
                break;
            }
            if(g.schaakboord[rij-i][kolom] == nullptr){
                zetten.push_back(make_pair(rij-i, kolom));
            } else if(g.schaakboord[rij-i][kolom] != nullptr && g.schaakboord[rij-i][kolom]->getKleur() == zwart){
                zetten.push_back(make_pair(rij-i, kolom));//stop
                danger_posities.push_back(make_pair(rij-i, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else {
                break;
            }
        }
        // right for white
        for(int i = 1; i < 8; i++){
            if(kolom+i > 7){
                break;
            }
            if(g.schaakboord[rij][kolom+i] == nullptr){
                zetten.push_back(make_pair(rij, kolom+i));
            } else if(g.schaakboord[rij][kolom+i] != nullptr && g.schaakboord[rij][kolom+i]->getKleur() == zwart){
                zetten.push_back(make_pair(rij, kolom+i));//stop
                danger_posities.push_back(make_pair(rij, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{
                break;
            }
        }
        //left for white
        for(int i = 1; i < 8; i++){
            if(kolom-i < 0){
                break;
            }
            if(g.schaakboord[rij][kolom-i] == nullptr){
                zetten.push_back(make_pair(rij, kolom-i));
            } else if(g.schaakboord[rij][kolom-i] != nullptr && g.schaakboord[rij][kolom-i]->getKleur() == zwart){
                zetten.push_back(make_pair(rij, kolom-i));//stop
                danger_posities.push_back(make_pair(rij, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{
                break;
            }
        }
    }
    return zetten;
}

vector<pair<int,int>> Paard::geldige_zetten(Game& g){
    vector<pair<int,int>> zetten;
    int rij = this->rij;
    int kolom = this->kolom;
    danger_posities.clear();
    if(g.schaakboord[rij][kolom]->getKleur() == zwart){
        // boven rechts
        if(rij-2 >= 0){
            if(kolom+1 < 8){
                if(g.schaakboord[rij-2][kolom+1] == nullptr){
                    zetten.push_back(make_pair(rij-2, kolom+1));
                } else if(g.schaakboord[rij-2][kolom+1] != nullptr && g.schaakboord[rij-2][kolom+1]->getKleur() == wit){
                    zetten.push_back(make_pair(rij-2, kolom+1));
                    danger_posities.push_back(make_pair(rij-2, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
            if(kolom-1 >= 0){
                // boven links
                if(g.schaakboord[rij-2][kolom-1] == nullptr){
                    zetten.push_back(make_pair(rij-2, kolom-1));
                } else if(g.schaakboord[rij-2][kolom-1] != nullptr && g.schaakboord[rij-2][kolom-1]->getKleur() == wit){
                    zetten.push_back(make_pair(rij-2, kolom-1));
                    danger_posities.push_back(make_pair(rij-2, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }

        if(rij-1 >= 0){
            if(kolom-2 >= 0){
                // links boven
                if(g.schaakboord[rij-1][kolom-2] == nullptr){
                    zetten.push_back(make_pair(rij-1, kolom-2));
                } else if(g.schaakboord[rij-1][kolom-2] != nullptr && g.schaakboord[rij-1][kolom-2]->getKleur() == wit){
                    zetten.push_back(make_pair(rij-1, kolom-2));
                    danger_posities.push_back(make_pair(rij-1, kolom-2)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
        if(kolom-2 >= 0){
            if(rij+1 < 8){
                //links onder
                if(g.schaakboord[rij+1][kolom-2] == nullptr){
                    zetten.push_back(make_pair(rij+1, kolom-2));
                } else if(g.schaakboord[rij+1][kolom-2] != nullptr && g.schaakboord[rij+1][kolom-2]->getKleur() == wit){
                    zetten.push_back(make_pair(rij+1, kolom-2));
                    danger_posities.push_back(make_pair(rij+1, kolom-2)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }

        if(rij+2 < 8){
            if(kolom-1 >= 0){
                //onder links
                if(g.schaakboord[rij+2][kolom-1] == nullptr){
                    zetten.push_back(make_pair(rij+2, kolom-1));
                } else if(g.schaakboord[rij+2][kolom-1] != nullptr && g.schaakboord[rij+2][kolom-1]->getKleur() == wit){
                    zetten.push_back(make_pair(rij+2, kolom-1));
                    danger_posities.push_back(make_pair(rij+2, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
            if(kolom+1 < 8){
                //onder rechts
                if(g.schaakboord[rij+2][kolom+1] == nullptr){
                    zetten.push_back(make_pair(rij+2, kolom+1));
                } else if(g.schaakboord[rij+2][kolom+1] != nullptr && g.schaakboord[rij+2][kolom+1]->getKleur() == wit){
                    zetten.push_back(make_pair(rij+2, kolom+1));
                    danger_posities.push_back(make_pair(rij+2, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
        if(kolom+2 < 8){
            if(rij-1 >= 0){
                //rechts boven
                if(g.schaakboord[rij-1][kolom+2] == nullptr){
                    zetten.push_back(make_pair(rij-1, kolom+2));
                } else if(g.schaakboord[rij-1][kolom+2] != nullptr && g.schaakboord[rij-1][kolom+2]->getKleur() == wit){
                    zetten.push_back(make_pair(rij-1, kolom+2));
                    danger_posities.push_back(make_pair(rij-1, kolom+2)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
            if(rij+1 < 8){
                //rechts onder
                if(g.schaakboord[rij+1][kolom+2] == nullptr){
                    zetten.push_back(make_pair(rij+1, kolom+2));
                } else if(g.schaakboord[rij+1][kolom+2] != nullptr && g.schaakboord[rij+1][kolom+2]->getKleur() == wit){
                    zetten.push_back(make_pair(rij+1, kolom+2));
                    danger_posities.push_back(make_pair(rij+1, kolom+2)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }

    } else{ // WHITE PAARD
        if(rij-2 >= 0){
            if(kolom+1 < 8){
                if(g.schaakboord[rij-2][kolom+1] == nullptr){
                    zetten.push_back(make_pair(rij-2, kolom+1));
                } else if(g.schaakboord[rij-2][kolom+1] != nullptr && g.schaakboord[rij-2][kolom+1]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij-2, kolom+1));
                    danger_posities.push_back(make_pair(rij-2, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
            if(kolom-1 >= 0){
                // boven links
                if(g.schaakboord[rij-2][kolom-1] == nullptr){
                    zetten.push_back(make_pair(rij-2, kolom-1));
                } else if(g.schaakboord[rij-2][kolom-1] != nullptr && g.schaakboord[rij-2][kolom-1]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij-2, kolom-1));
                    danger_posities.push_back(make_pair(rij-2, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }

        if(rij-1 >= 0){
            if(kolom-2 >= 0){
                // links boven
                if(g.schaakboord[rij-1][kolom-2] == nullptr){
                    zetten.push_back(make_pair(rij-1, kolom-2));
                } else if(g.schaakboord[rij-1][kolom-2] != nullptr && g.schaakboord[rij-1][kolom-2]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij-1, kolom-2));
                    danger_posities.push_back(make_pair(rij-1, kolom-2)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
        if(kolom-2 >= 0){
            if(rij+1 < 8){
                //links onder
                if(g.schaakboord[rij+1][kolom-2] == nullptr){
                    zetten.push_back(make_pair(rij+1, kolom-2));
                } else if(g.schaakboord[rij+1][kolom-2] != nullptr && g.schaakboord[rij+1][kolom-2]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij+1, kolom-2));
                    danger_posities.push_back(make_pair(rij+1, kolom-2)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }

        if(rij+2 < 8){
            if(kolom-1 >= 0){
                //onder links
                if(g.schaakboord[rij+2][kolom-1] == nullptr){
                    zetten.push_back(make_pair(rij+2, kolom-1));
                } else if(g.schaakboord[rij+2][kolom-1] != nullptr && g.schaakboord[rij+2][kolom-1]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij+2, kolom-1));
                    danger_posities.push_back(make_pair(rij+2, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
            if(kolom+1 < 8){
                //onder rechts
                if(g.schaakboord[rij+2][kolom+1] == nullptr){
                    zetten.push_back(make_pair(rij+2, kolom+1));
                } else if(g.schaakboord[rij+2][kolom+1] != nullptr && g.schaakboord[rij+2][kolom+1]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij+2, kolom+1));
                    danger_posities.push_back(make_pair(rij+2, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
        if(kolom+2 < 8){
            if(rij-1 >= 0){
                //rechts boven
                if(g.schaakboord[rij-1][kolom+2] == nullptr){
                    zetten.push_back(make_pair(rij-1, kolom+2));
                } else if(g.schaakboord[rij-1][kolom+2] != nullptr && g.schaakboord[rij-1][kolom+2]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij-1, kolom+2));
                    danger_posities.push_back(make_pair(rij-1, kolom+2)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
            if(rij+1 < 8){
                //rechts onder
                if(g.schaakboord[rij+1][kolom+2] == nullptr){
                    zetten.push_back(make_pair(rij+1, kolom+2));
                } else if(g.schaakboord[rij+1][kolom+2] != nullptr && g.schaakboord[rij+1][kolom+2]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij+1, kolom+2));
                    danger_posities.push_back(make_pair(rij+1, kolom+2)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
    }
    return zetten;
}

vector<pair<int,int>> Loper::geldige_zetten(Game& g){
    vector<pair<int,int>> zetten;
    int rij = this->rij;
    int kolom = this->kolom;
    danger_posities.clear();
    if(g.schaakboord[rij][kolom]->getKleur() == zwart){
        //schijn links boven
        for(int i = 1; i < 8; i++){
            if(rij-i >= 0){
                if(kolom-i >= 0) {
                    if(g.schaakboord[rij-i][kolom-i] == nullptr){
                        zetten.push_back(make_pair(rij - i, kolom - i));
                    } else if (g.schaakboord[rij-i][kolom-i] != nullptr && g.schaakboord[rij-i][kolom-i]->getKleur() == wit){
                        zetten.push_back(make_pair(rij - i, kolom - i));
                        danger_posities.push_back(make_pair(rij-i, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn rechts boven
        for(int i = 1; i < 8; i++){
            if(rij-i >= 0){
                if(kolom+i <= 7) {
                    if(g.schaakboord[rij-i][kolom+i] == nullptr){
                        zetten.push_back(make_pair(rij - i, kolom + i));
                    } else if (g.schaakboord[rij-i][kolom+i] != nullptr && g.schaakboord[rij-i][kolom+i]->getKleur() == wit){
                        zetten.push_back(make_pair(rij - i, kolom + i));
                        danger_posities.push_back(make_pair(rij-i, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn links onder
        for(int i = 1; i < 8; i++){
            if(rij+i <= 7){
                if(kolom-i >= 0) {
                    if(g.schaakboord[rij+i][kolom-i] == nullptr){
                        zetten.push_back(make_pair(rij + i, kolom - i));
                    } else if (g.schaakboord[rij+i][kolom-i] != nullptr && g.schaakboord[rij+i][kolom-i]->getKleur() == wit){
                        zetten.push_back(make_pair(rij + i, kolom - i));
                        danger_posities.push_back(make_pair(rij+i, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn rechts onder
        for(int i = 1; i < 8; i++){
            if(rij+i <= 7){
                if(kolom+i <= 7) {
                    if(g.schaakboord[rij+i][kolom+i] == nullptr){
                        zetten.push_back(make_pair(rij + i, kolom + i));
                    } else if (g.schaakboord[rij+i][kolom+i] != nullptr && g.schaakboord[rij+i][kolom+i]->getKleur() == wit){
                        zetten.push_back(make_pair(rij + i, kolom + i));
                        danger_posities.push_back(make_pair(rij+i, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
    } else{ //WHITE LOPER
        //schijn links boven
        for(int i = 1; i < 8; i++){
            if(rij-i >= 0){
                if(kolom-i >= 0) {
                    if(g.schaakboord[rij-i][kolom-i] == nullptr){
                        zetten.push_back(make_pair(rij - i, kolom - i));
                    } else if (g.schaakboord[rij-i][kolom-i] != nullptr && g.schaakboord[rij-i][kolom-i]->getKleur() == zwart){
                        zetten.push_back(make_pair(rij - i, kolom - i));
                        danger_posities.push_back(make_pair(rij-i, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn rechts boven
        for(int i = 1; i < 8; i++){
            if(rij-i >= 0){
                if(kolom+i <= 7) {
                    if(g.schaakboord[rij-i][kolom+i] == nullptr){
                        zetten.push_back(make_pair(rij - i, kolom + i));
                    } else if (g.schaakboord[rij-i][kolom+i] != nullptr && g.schaakboord[rij-i][kolom+i]->getKleur() == zwart){
                        zetten.push_back(make_pair(rij - i, kolom + i));
                        danger_posities.push_back(make_pair(rij-i, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn links onder
        for(int i = 1; i < 8; i++){
            if(rij+i <= 7){
                if(kolom-i >= 0) {
                    if(g.schaakboord[rij+i][kolom-i] == nullptr){
                        zetten.push_back(make_pair(rij + i, kolom - i));
                    } else if (g.schaakboord[rij+i][kolom-i] != nullptr && g.schaakboord[rij+i][kolom-i]->getKleur() == zwart){
                        zetten.push_back(make_pair(rij + i, kolom - i));
                        danger_posities.push_back(make_pair(rij+i, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn rechts onder
        for(int i = 1; i < 8; i++){
            if(rij+i <= 7){
                if(kolom+i <= 7) {
                    if(g.schaakboord[rij+i][kolom+i] == nullptr){
                        zetten.push_back(make_pair(rij + i, kolom + i));
                    } else if (g.schaakboord[rij+i][kolom+i] != nullptr && g.schaakboord[rij+i][kolom+i]->getKleur() == zwart){
                        zetten.push_back(make_pair(rij + i, kolom + i));
                        danger_posities.push_back(make_pair(rij+i, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
    }
    return zetten;
}

vector<pair<int,int>> Koning::geldige_zetten(Game& g){
    vector<pair<int,int>> zetten;
    int rij = this->rij;
    int kolom = this->kolom;
    danger_posities.clear();

    if(g.schaakboord[rij][kolom]->getKleur() == zwart){ // BLACK KING
        //up
        if(rij-1 >= 0){
            if(g.schaakboord[rij-1][kolom] == nullptr){
                zetten.push_back(make_pair(rij-1,kolom));
            } else if(g.schaakboord[rij-1][kolom] != nullptr && g.schaakboord[rij-1][kolom]->getKleur() == wit){
                zetten.push_back(make_pair(rij-1,kolom));
                danger_posities.push_back(make_pair(rij-1, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
            }
        }
        //upleft
        if(rij-1 >= 0){
            if(kolom-1 >=0){
                if(g.schaakboord[rij-1][kolom-1] == nullptr){
                    zetten.push_back(make_pair(rij-1,kolom-1));
                } else if(g.schaakboord[rij-1][kolom-1] != nullptr && g.schaakboord[rij-1][kolom-1]->getKleur() == wit){
                    zetten.push_back(make_pair(rij-1, kolom-1));
                    danger_posities.push_back(make_pair(rij-1, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
        //upright
        if(rij-1 >= 0){
            if(kolom+1 < 8){
                if(g.schaakboord[rij-1][kolom+1] == nullptr){
                    zetten.push_back(make_pair(rij-1,kolom+1));
                } else if(g.schaakboord[rij-1][kolom+1] != nullptr && g.schaakboord[rij-1][kolom+1]->getKleur() == wit){
                    zetten.push_back(make_pair(rij-1, kolom+1));
                    danger_posities.push_back(make_pair(rij-1, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }

            }
        }
        //left mid
        if(kolom-1 >= 0){
            if(g.schaakboord[rij][kolom-1] == nullptr){
                zetten.push_back(make_pair(rij, kolom-1));
            } else if(g.schaakboord[rij][kolom-1] != nullptr && g.schaakboord[rij][kolom-1]->getKleur() == wit){
                zetten.push_back(make_pair(rij, kolom-1));
                danger_posities.push_back(make_pair(rij, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
            }
        }
        //down left
        if(rij+1 < 8){
            if(kolom-1 >=0){
                if(g.schaakboord[rij+1][kolom-1] == nullptr){
                    zetten.push_back(make_pair(rij+1, kolom-1));
                } else if(g.schaakboord[rij+1][kolom-1] != nullptr && g.schaakboord[rij+1][kolom-1]->getKleur() == wit){
                    zetten.push_back(make_pair(rij+1, kolom-1));
                    danger_posities.push_back(make_pair(rij+1, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
        //down mid
        if(rij+1 < 8){
            if(g.schaakboord[rij+1][kolom] == nullptr){
                zetten.push_back(make_pair(rij+1,kolom));
            } else if(g.schaakboord[rij+1][kolom] != nullptr && g.schaakboord[rij+1][kolom]->getKleur() == wit){
                zetten.push_back(make_pair(rij+1, kolom));
                danger_posities.push_back(make_pair(rij+1, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
            }
        }
        // down right
        if(kolom+1 < 8){
            if(rij+1 < 8){
                if(g.schaakboord[rij+1][kolom+1] == nullptr){
                    zetten.push_back(make_pair(rij+1, kolom+1));
                } else if(g.schaakboord[rij+1][kolom+1] != nullptr && g.schaakboord[rij+1][kolom+1]->getKleur() == wit){
                    zetten.push_back(make_pair(rij+1, kolom+1));
                    danger_posities.push_back(make_pair(rij+1, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
        //right mid
        if(kolom+1 < 8){
            if(g.schaakboord[rij][kolom+1] == nullptr){
                zetten.push_back(make_pair(rij, kolom+1));
            } else if(g.schaakboord[rij][kolom+1] != nullptr && g.schaakboord[rij][kolom+1]->getKleur() == wit){
                zetten.push_back(make_pair(rij, kolom+1));
                danger_posities.push_back(make_pair(rij, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
            }
        }
    } else{ // WHITE KING
        //up
        if(rij-1 >= 0){
            if(g.schaakboord[rij-1][kolom] == nullptr){
                zetten.push_back(make_pair(rij-1,kolom));
            } else if(g.schaakboord[rij-1][kolom] != nullptr && g.schaakboord[rij-1][kolom]->getKleur() == zwart){
                zetten.push_back(make_pair(rij-1,kolom));
                danger_posities.push_back(make_pair(rij-1, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
            }
        }
        //upleft
        if(rij-1 >= 0){
            if(kolom-1 >=0){
                if(g.schaakboord[rij-1][kolom-1] == nullptr){
                    zetten.push_back(make_pair(rij-1,kolom-1));
                } else if(g.schaakboord[rij-1][kolom-1] != nullptr && g.schaakboord[rij-1][kolom-1]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij-1, kolom-1));
                    danger_posities.push_back(make_pair(rij-1, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
        //upright
        if(rij-1 >= 0){
            if(kolom+1 < 8){
                if(g.schaakboord[rij-1][kolom+1] == nullptr){
                    zetten.push_back(make_pair(rij-1,kolom+1));
                } else if(g.schaakboord[rij-1][kolom+1] != nullptr && g.schaakboord[rij-1][kolom+1]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij-1, kolom+1));
                    danger_posities.push_back(make_pair(rij-1, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }

            }
        }
        //left mid
        if(kolom-1 >= 0){
            if(g.schaakboord[rij][kolom-1] == nullptr){
                zetten.push_back(make_pair(rij, kolom-1));
            } else if(g.schaakboord[rij][kolom-1] != nullptr && g.schaakboord[rij][kolom-1]->getKleur() == zwart){
                zetten.push_back(make_pair(rij, kolom-1));
                danger_posities.push_back(make_pair(rij, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
            }
        }
        //down left
        if(rij+1 < 8){
            if(kolom-1 >=0){
                if(g.schaakboord[rij+1][kolom-1] == nullptr){
                    zetten.push_back(make_pair(rij+1, kolom-1));
                } else if(g.schaakboord[rij+1][kolom-1] != nullptr && g.schaakboord[rij+1][kolom-1]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij+1, kolom-1));
                    danger_posities.push_back(make_pair(rij+1, kolom-1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
        //down mid
        if(rij+1 < 8){
            if(g.schaakboord[rij+1][kolom] == nullptr){
                zetten.push_back(make_pair(rij+1, kolom));
            } else if(g.schaakboord[rij+1][kolom] != nullptr && g.schaakboord[rij+1][kolom]->getKleur() == zwart){
                zetten.push_back(make_pair(rij+1, kolom));
                danger_posities.push_back(make_pair(rij+1, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
            }
        }
        // down right
        if(kolom+1 < 8){
            if(rij+1 < 8){
                if(g.schaakboord[rij+1][kolom+1] == nullptr){
                    zetten.push_back(make_pair(rij+1, kolom+1));
                } else if(g.schaakboord[rij+1][kolom+1] != nullptr && g.schaakboord[rij+1][kolom+1]->getKleur() == zwart){
                    zetten.push_back(make_pair(rij+1, kolom+1));
                    danger_posities.push_back(make_pair(rij+1, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
                }
            }
        }
        //right mid
        if(kolom+1 < 8){
            if(g.schaakboord[rij][kolom+1] == nullptr){
                zetten.push_back(make_pair(rij, kolom+1));
            } else if(g.schaakboord[rij][kolom+1] != nullptr && g.schaakboord[rij][kolom+1]->getKleur() == zwart){
                zetten.push_back(make_pair(rij, kolom+1));
                danger_posities.push_back(make_pair(rij, kolom+1)); //DEZE POSITIE KAN GEKILLED WORDEN
            }
        }

    }
    return zetten;
}

vector<pair<int,int>> Koningin::geldige_zetten(Game& g){
    vector<pair<int,int>> zetten;
    int rij = this->rij;
    int kolom = this->kolom;
    danger_posities.clear();

    //LOPER
    if(g.schaakboord[rij][kolom]->getKleur() == zwart){
        //schijn links boven
        for(int i = 1; i < 8; i++){
            if(rij-i >= 0){
                if(kolom-i >= 0) {
                    if(g.schaakboord[rij-i][kolom-i] == nullptr){
                        zetten.push_back(make_pair(rij - i, kolom - i));
                    } else if (g.schaakboord[rij-i][kolom-i] != nullptr && g.schaakboord[rij-i][kolom-i]->getKleur() == wit){
                        zetten.push_back(make_pair(rij - i, kolom - i));
                        danger_posities.push_back(make_pair(rij-i, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn rechts boven
        for(int i = 1; i < 8; i++){
            if(rij-i >= 0){
                if(kolom+i <= 7) {
                    if(g.schaakboord[rij-i][kolom+i] == nullptr){
                        zetten.push_back(make_pair(rij - i, kolom + i));
                    } else if (g.schaakboord[rij-i][kolom+i] != nullptr && g.schaakboord[rij-i][kolom+i]->getKleur() == wit){
                        zetten.push_back(make_pair(rij - i, kolom + i));
                        danger_posities.push_back(make_pair(rij-i, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn links onder
        for(int i = 1; i < 8; i++){
            if(rij+i <= 7){
                if(kolom-i >= 0) {
                    if(g.schaakboord[rij+i][kolom-i] == nullptr){
                        zetten.push_back(make_pair(rij + i, kolom - i));
                    } else if (g.schaakboord[rij+i][kolom-i] != nullptr && g.schaakboord[rij+i][kolom-i]->getKleur() == wit){
                        zetten.push_back(make_pair(rij + i, kolom - i));
                        danger_posities.push_back(make_pair(rij+i, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn rechts onder
        for(int i = 1; i < 8; i++){
            if(rij+i <= 7){
                if(kolom+i <= 7) {
                    if(g.schaakboord[rij+i][kolom+i] == nullptr){
                        zetten.push_back(make_pair(rij + i, kolom + i));
                    } else if (g.schaakboord[rij+i][kolom+i] != nullptr && g.schaakboord[rij+i][kolom+i]->getKleur() == wit){
                        zetten.push_back(make_pair(rij + i, kolom + i));
                        danger_posities.push_back(make_pair(rij+i, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
    } else{ //WHITE LOPER
        //schijn links boven
        for(int i = 1; i < 8; i++){
            if(rij-i >= 0){
                if(kolom-i >= 0) {
                    if(g.schaakboord[rij-i][kolom-i] == nullptr){
                        zetten.push_back(make_pair(rij - i, kolom - i));
                    } else if (g.schaakboord[rij-i][kolom-i] != nullptr && g.schaakboord[rij-i][kolom-i]->getKleur() == zwart){
                        zetten.push_back(make_pair(rij - i, kolom - i));
                        danger_posities.push_back(make_pair(rij-i, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn rechts boven
        for(int i = 1; i < 8; i++){
            if(rij-i >= 0){
                if(kolom+i <= 7) {
                    if(g.schaakboord[rij-i][kolom+i] == nullptr){
                        zetten.push_back(make_pair(rij - i, kolom + i));
                    } else if (g.schaakboord[rij-i][kolom+i] != nullptr && g.schaakboord[rij-i][kolom+i]->getKleur() == zwart){
                        zetten.push_back(make_pair(rij - i, kolom + i));
                        danger_posities.push_back(make_pair(rij-i, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn links onder
        for(int i = 1; i < 8; i++){
            if(rij+i <= 7){
                if(kolom-i >= 0) {
                    if(g.schaakboord[rij+i][kolom-i] == nullptr){
                        zetten.push_back(make_pair(rij + i, kolom - i));
                    } else if (g.schaakboord[rij+i][kolom-i] != nullptr && g.schaakboord[rij+i][kolom-i]->getKleur() == zwart){
                        zetten.push_back(make_pair(rij + i, kolom - i));
                        danger_posities.push_back(make_pair(rij+i, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
        //schijn rechts onder
        for(int i = 1; i < 8; i++){
            if(rij+i <= 7){
                if(kolom+i <= 7) {
                    if(g.schaakboord[rij+i][kolom+i] == nullptr){
                        zetten.push_back(make_pair(rij + i, kolom + i));
                    } else if (g.schaakboord[rij+i][kolom+i] != nullptr && g.schaakboord[rij+i][kolom+i]->getKleur() == zwart){
                        zetten.push_back(make_pair(rij + i, kolom + i));
                        danger_posities.push_back(make_pair(rij+i, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                        break;
                    } else{
                        break;
                    }
                } else{
                    break;
                }
            } else{
                break;
            }
        }
    }
    //EINDE LOPER

    //TOREN
    if(g.schaakboord[rij][kolom]->getKleur() == zwart){
        //under for black
        for(int i = 1; i < 8; i++){
            if(rij+i > 7){
                break;
            }
            if(g.schaakboord[rij+i][kolom] == nullptr){
                zetten.push_back(make_pair(rij+i, kolom));
            } else if(g.schaakboord[rij+i][kolom] != nullptr && g.schaakboord[rij+i][kolom]->getKleur() == wit){
                zetten.push_back(make_pair(rij+i, kolom));//stop
                danger_posities.push_back(make_pair(rij+i, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{ //als zwarte pion ervoor is
                break;
            }
        }
        //top for black
        for(int i = 1; i < 8; i++){
            if(rij-i < 0){
                break;
            }
            if(g.schaakboord[rij-i][kolom] == nullptr){
                zetten.push_back(make_pair(rij-i, kolom));
            } else if(g.schaakboord[rij-i][kolom] != nullptr && g.schaakboord[rij-i][kolom]->getKleur() == wit){
                zetten.push_back(make_pair(rij-i, kolom));//stop
                danger_posities.push_back(make_pair(rij-i, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else {
                break;
            }
        }
        // right for black
        for(int i = 1; i < 8; i++){
            if(kolom+i > 7){
                break;
            }
            if(g.schaakboord[rij][kolom+i] == nullptr){
                zetten.push_back(make_pair(rij, kolom+i));
            } else if(g.schaakboord[rij][kolom+i] != nullptr && g.schaakboord[rij][kolom+i]->getKleur() == wit){
                zetten.push_back(make_pair(rij, kolom+i));//stop
                danger_posities.push_back(make_pair(rij, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{
                break;
            }
        }
        //left for black
        for(int i = 1; i < 8; i++){
            if(kolom-i < 0){
                break;
            }
            if(g.schaakboord[rij][kolom-i] == nullptr){
                zetten.push_back(make_pair(rij, kolom-i));
            } else if(g.schaakboord[rij][kolom-i] != nullptr && g.schaakboord[rij][kolom-i]->getKleur() == wit){
                zetten.push_back(make_pair(rij, kolom-i));//stop
                danger_posities.push_back(make_pair(rij, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{
                break;
            }
        }
    } else{
        //under for white
        for(int i = 1; i < 8; i++){
            if(rij+i > 7){
                break;
            }
            if(g.schaakboord[rij+i][kolom] == nullptr){
                zetten.push_back(make_pair(rij+i, kolom));
            } else if(g.schaakboord[rij+i][kolom] != nullptr && g.schaakboord[rij+i][kolom]->getKleur() == zwart){
                zetten.push_back(make_pair(rij+i, kolom));//stop
                danger_posities.push_back(make_pair(rij+i, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{ //als white pion ervoor is
                break;
            }
        }
        //top for white
        for(int i = 1; i < 8; i++){
            if(rij-i < 0){
                break;
            }
            if(g.schaakboord[rij-i][kolom] == nullptr){
                zetten.push_back(make_pair(rij-i, kolom));
            } else if(g.schaakboord[rij-i][kolom] != nullptr && g.schaakboord[rij-i][kolom]->getKleur() == zwart){
                zetten.push_back(make_pair(rij-i, kolom));//stop
                danger_posities.push_back(make_pair(rij-i, kolom)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else {
                break;
            }
        }
        // right for white
        for(int i = 1; i < 8; i++){
            if(kolom+i > 7){
                break;
            }
            if(g.schaakboord[rij][kolom+i] == nullptr){
                zetten.push_back(make_pair(rij, kolom+i));
            } else if(g.schaakboord[rij][kolom+i] != nullptr && g.schaakboord[rij][kolom+i]->getKleur() == zwart){
                zetten.push_back(make_pair(rij, kolom+i));//stop
                danger_posities.push_back(make_pair(rij, kolom+i)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{
                break;
            }
        }
        //left for white
        for(int i = 1; i < 8; i++){
            if(kolom-i < 0){
                break;
            }
            if(g.schaakboord[rij][kolom-i] == nullptr){
                zetten.push_back(make_pair(rij, kolom-i));
            } else if(g.schaakboord[rij][kolom-i] != nullptr && g.schaakboord[rij][kolom-i]->getKleur() == zwart){
                zetten.push_back(make_pair(rij, kolom-i));//stop
                danger_posities.push_back(make_pair(rij, kolom-i)); //DEZE POSITIE KAN GEKILLED WORDEN
                break;
            } else{
                break;
            }
        }
    }
    //EINDE TOREN
    return zetten;
}