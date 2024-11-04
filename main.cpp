
#include "screen.h"
/*
    void drawGrid(int grid[7][6]);
    void clearConsole();
*/

#include "game.h"
/*
    bool testPlayTurn(int grid[7][6], int column, int& ligne);
    bool playTurn(int grid[7][6], int column, int ligne, int player);
    bool gameOver(int grid[7][6], int& player);
    bool playerWin(int grid[7][6], int player);
    bool gameEnd(int grid[7][6]);
    bool resetTurn(int grid[7][6], int column);
*/


#include "ia.h"
/*
    int iaturn(int grid[7][6], int offensive);
*/

#include <iostream>
#include <string>
#include <ctime>

int main(int argc, char** argv) {
    srand(time(nullptr));

    while (true) {
        int grille[7][6] = {};
        std::string choix;
        int modeDeJeu;

        std::cout << "Choisissez le mode de jeu :\n";
        std::cout << "1. Joueur vs Joueur\n";
        std::cout << "2. Joueur vs IA\n";
        std::cout << "3. Quitter\n";
        std::cin >> modeDeJeu;

        if (modeDeJeu == 3) return 0;

        bool vsIA = (modeDeJeu == 2);

        int player = (rand() % 2) + 1;
        int offensive = 50; // Pourcentage d'orientation initial (0 = totalement défensif, 100 = totalement offensif)

        if (vsIA) {
            std::cout << "Choisissez le niveau d'agressiviter de l'IA (0-100) : ";
            std::cin >> offensive;
            if (offensive < 0) offensive = 0;
            if (offensive > 100) offensive = 100;
        }

        drawGrid(grille);

        while (true) {
            bool iaIsPlay = false;
            bool iaIssuccess = false;
            int col = 0;

            if (vsIA && player == 2) { // Tour de l'IA
                int iaGrille[7][6] = {};

                for (int i = 0; i < 7; i++){
                    for (int j = 0; j < 6; j++){
                        iaGrille[i][j] = grille[i][j];
                    }
                }

                iaIsPlay = true;
                col = iaturn(iaGrille, offensive);
                int iaLine = 0;

                if (testPlayTurn(grille, col, iaLine)){
                    iaIssuccess = playTurn(grille, col, iaLine, player);
                }
            } else { // Tour du joueur
                std::cout << "Joueur_" << player << " -> col : ";
                std::cin >> choix;

                if (choix == "exit") return 0;

                bool success = false;
                if (choix.size() == 1 && choix[0] >= '0' && choix[0] <= '6') {
                    col = choix[0] - '0';
                    int line = 0;
                    if (testPlayTurn(grille, col, line)){
                        success = playTurn(grille, col, line, player);
                    }
                }

                if (!success) {
                    std::cout << "Votre choix est incorrect\n";
                    continue;
                }
            }

            clearConsole();
            int player_win = 0;
            if (gameOver(grille, player_win)) {
                if (player_win == 0) {
                    std::cout << "Match nul !\n";
                } else if (player_win == 1) {
                    std::cout << "Le joueur 1 a gagner !\n";
                } else {
                    std::cout << "Le joueur 2 a gagner !\n";
                }
                break;
            }

            player = (player == 1) ? 2 : 1; // Alterner entre les joueurs
            drawGrid(grille);

            if (iaIsPlay){
                std::cout << "IA joue en colonne : " << col << "\n";
                if (!iaIssuccess) {
                    std::cout << "Choix IA incorrect\n";
                    continue;
                }
            }
        }

        drawGrid(grille);
        std::string replay;
        std::cout << "Voulez-vous rejouer ? (o/n) : ";
        std::cin >> replay;
        if (replay != "o" && replay != "O") break;
    }
    return 0;
}

// Correction de la fonction iaturn
