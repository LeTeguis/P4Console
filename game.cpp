#include "game.h"
#include <cstdlib> // pour system

// Correction de la fonction resetTurn pour annuler correctement un coup
bool resetTurn(int grid[7][6], int column) {
    for (int line = 0; line < 6; line++) {
        if (grid[column][line] != 0) {
            grid[column][line] = 0;
            return true;
        }
    }
    return false;
}

// 0, 1, 2

bool testPlayTurn(int grid[7][6], int column, int& ligne){
    if (column <= 0 || column > 7) return false;

    for (int line = 5 ; line >= 0; line--){
        if (grid[column - 1][line] == 0){
            ligne = line;
            return true;
        }
    }

    return false;
}

bool playTurn(int grid[7][6], int column, int ligne, int player){
    if (ligne < 0 || ligne >= 6 || column < 0 || column >= 7) return false;
    grid[column - 1][ligne] = player;
    return true;
}

bool gameOver(int grid[7][6], int& player){
    if (playerWin(grid, 1)){
        player = 1;
        return true;
    } else if (playerWin(grid, 2)){
        player = 2;
        return true;
    } else if (gameEnd(grid)){
        player = 0;
        return true;
    }

    return false;
}

bool playerWin(int grid[7][6], int player) {
    if (player != 1 && player != 2) return false;

    // Vérification verticale
    for (int col = 0; col < 7; col++) {
        int count = 0;
        for (int ligne = 0; ligne < 6; ligne++) {
            if (grid[col][ligne] == player) {
                count++;
                if (count >= 4) {
                    return true;
                }
            } else {
                count = 0; // Réinitialiser si la séquence est rompue
            }
        }
    }

    // Vérification horizontale
    for (int ligne = 0; ligne < 6; ligne++) {
        int count = 0;
        for (int col = 0; col < 7; col++) {
            if (grid[col][ligne] == player) {
                count++;
                if (count >= 4) {
                    return true;
                }
            } else {
                count = 0; // Réinitialiser si la séquence est rompue
            }
        }
    }

    // Vérification diagonale (oblique gauche vers droite)
    for (int col = 0; col < 7; col++) {
        for (int ligne = 0; ligne < 6; ligne++) {
            if (col + 3 < 7 && ligne + 3 < 6) {
                if (grid[col][ligne] == player &&
                    grid[col + 1][ligne + 1] == player &&
                    grid[col + 2][ligne + 2] == player &&
                    grid[col + 3][ligne + 3] == player) {
                    return true;
                }
            }
        }
    }

    // Vérification diagonale (oblique droite vers gauche)
    for (int col = 0; col < 7; col++) {
        for (int ligne = 0; ligne < 6; ligne++) {
            if (col - 3 >= 0 && ligne + 3 < 6) {
                if (grid[col][ligne] == player &&
                    grid[col - 1][ligne + 1] == player &&
                    grid[col - 2][ligne + 2] == player &&
                    grid[col - 3][ligne + 3] == player) {
                    return true;
                }
            }
        }
    }

    return false; // Aucune condition de victoire n'a été remplie
}

bool gameEnd(int grid[7][6]){
    for (int col = 0; col < 7; col++){
        if (grid[col][0] == 0){
            return false;
        }
    }
    return true;
}

// Fonction pour que l'IA choisisse un coup
int getAIMove(int grid[7][6]) {
    int col;
    while (true) {
        col = rand() % 7; // Choisir une colonne aléatoire entre 0 et 6
        // Vérifier si la colonne est disponible
        if (grid[col][0] == 0) {
            return col; // Retourner la colonne valide
        }
    }
}