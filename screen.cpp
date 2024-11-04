#include "screen.h"

#include <iostream>
#include <cstdlib> // pour system


void clearConsole() {
    // Vérification du système d'exploitation
    #ifdef _WIN32 // Windows
        system("CLS");
    #else // Unix (Linux, MacOS, etc.)
        system("clear");
    #endif
}

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