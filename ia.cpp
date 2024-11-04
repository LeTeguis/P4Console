#include "ia.h"

#include "game.h"
#include <cstdlib> // pour system

int iaturn(int grid[7][6], int offensive) {
    int ligne;

    // Pourcentage de stratégies
    int defensive = 100 - offensive; // Calculer le pourcentage défensif

    // Déterminer quelle stratégie appliquer (offensive ou défensive)
    int randomValue = rand() % 100; // Valeur aléatoire entre 0 et 99

    // Stratégie offensive (IA cherche à gagner)
    if (randomValue < offensive) {
        for (int col = 0; col < 7; col++) {
            if (testPlayTurn(grid, col, ligne)) { // Trouve la ligne où placer
                playTurn(grid, col, ligne, 2); // Tester le coup de l'IA
                if (playerWin(grid, 2)) { // Si l'IA gagne
                    resetTurn(grid, col); // Annule le coup de test
                    return col;
                }
                resetTurn(grid, col); // Annule le coup de test
            }
        }
    }

    // Stratégie défensive (Empêcher le joueur de gagner)
    if (randomValue >= offensive) {
        for (int col = 0; col < 7; col++) {
            if (testPlayTurn(grid, col, ligne)) {
                playTurn(grid, col, ligne, 1); // Tester le coup du joueur
                if (playerWin(grid, 1)) { // Si le joueur gagne
                    resetTurn(grid, col); // Annule le coup de test
                    return col; // IA joue ici pour bloquer
                }
                resetTurn(grid, col); // Annule le coup de test
            }
        }
    }

    // Jouer au centre (stratégie par défaut)
    if (testPlayTurn(grid, 3, ligne)) {
        return 3;
    }

    // Choisir une colonne libre au hasard si toutes les stratégies échouent
    for (int col = 0; col < 7; col++) {
        if (testPlayTurn(grid, col, ligne)) {
            return col;
        }
    }

    return -1; // Aucun coup possible
}

