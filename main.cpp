#include <iostream>
#include <stdlib.h>
#include <string>

void drawGrid(int grid[7][6]);
bool playTurn(int grid[7][6], int column, int player);

int main(int argc, char** argv){
    int grille[7][6] = {};
    std::string choix;

    int player = 1;
        drawGrid(grille);

    while (true){
        std::cout << "player_" << player << " -> col :";
        std::cin >> choix;

        if (choix == "exit"){
            break;
        }

        bool success = false;

        if (choix.size() == 1){
            if (choix[0] >= '0' && choix[0] <= '7'){
                int col = choix[0]  - '0';

                success = playTurn(grille, col, player);
            }
        }

        system("CLS");

        if (!success){
            std::cout << "votre choix est incorrect\n";
        } else{
            if (player == 1) player = 2;
            else player = 1;
        }

        drawGrid(grille);
    }

    return 0;
}


// 0, 1, 2
void drawGrid(int grille[7][6]){
    for (int ligne = 0; ligne < 6; ligne++){
        std::cout << "|";
        for (int col = 0; col < 7; col++){
            if (grille[col][ligne] == 1){
                std::cout << "\033[31m*\033[37m";
            } else 
            if (grille[col][ligne] == 2){
                std::cout << "\033[32m*\033[37m";
            }
            else {
                std::cout << "\033[37m*\033[37m";
            }
            std::cout << "|";
        }
        std::cout << "\n";
    }
}

bool playTurn(int grid[7][6], int column, int player){
    for (int line = 5 ; line >= 0; line--){
        if (grid[column - 1][line] == 0){
            grid[column - 1][line] = player;
            return true;
        }
    }
    return false;
}