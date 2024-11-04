#include "game_manager.h"
#include "screen.h"
#include "game.h"
#include "ia.h"

#include <iostream>
#include <string>
#include <ctime>

void runGameLoop() {
    while (true) {
        int grille[7][6] = {};
        int modeDeJeu;
        int offensive = 50; // Pourcentage d'orientation initial
        bool vsIA = false;

        initializeGame(modeDeJeu, offensive, vsIA);

        drawGrid(grille);
        int player = (rand() % 2) + 1; // Choisir aléatoirement le joueur qui commence

        while (true) {
            bool iaIsPlay = false;
            bool iaIssuccess = false;
            int col = 0;

            if (vsIA && player == 2) { // Tour de l'IA
                iaIsPlay = true;
                handleIATurn(grille, player, offensive);
            } else { // Tour du joueur
                handlePlayerTurn(grille, player);
            }

            clearConsole();
            int player_win = 0;
            if (checkGameOver(grille, player_win)) {
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

            if (iaIsPlay) {
                std::cout << "IA joue en colonne : " << col << "\n";
                if (!iaIssuccess) {
                    std::cout << "Choix IA incorrect\n";
                    continue;
                }
            }
        }

        drawGrid(grille);
        if (!askReplay()) break; // Demander si le joueur veut rejouer
    }
}

void initializeGame(int& modeDeJeu, int& offensive, bool& vsIA) {
    std::cout << "Choisissez le mode de jeu :\n";
    std::cout << "1. Joueur vs Joueur\n";
    std::cout << "2. Joueur vs IA\n";
    std::cout << "3. Quitter\n";
    std::cin >> modeDeJeu;

    if (modeDeJeu == 3) exit(0); // Quitter le programme

    vsIA = (modeDeJeu == 2);
    if (vsIA) {
        std::cout << "Choisissez le niveau d'agressivité de l'IA (0-100) : ";
        std::cin >> offensive;
        if (offensive < 0) offensive = 0;
        if (offensive > 100) offensive = 100;
    }
}

void handlePlayerTurn(int grid[7][6], int player) {
    std::string choix;
    std::cout << "Joueur_" << player << " -> col : ";
    std::cin >> choix;

    if (choix == "exit") exit(0);

    bool success = false;
    if (choix.size() == 1 && choix[0] >= '0' && choix[0] <= '6') {
        int col = choix[0] - '0';
        int line = 0;
        if (testPlayTurn(grid, col, line)) {
            success = playTurn(grid, col, line, player);
        }
    }

    if (!success) {
        std::cout << "Votre choix est incorrect\n";
    }
}

void handleIATurn(int grid[7][6], int player, int offensive) {
    int iaGrille[7][6] = {};
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            iaGrille[i][j] = grid[i][j];
        }
    }

    int col = iaturn(iaGrille, offensive);
    int iaLine = 0;

    if (testPlayTurn(grid, col, iaLine)) {
        playTurn(grid, col, iaLine, player);
    } else {
        std::cout << "Choix IA incorrect\n";
    }
}

bool checkGameOver(int grid[7][6], int& player_win) {
    return gameOver(grid, player_win);
}

bool askReplay() {
    std::string replay;
    std::cout << "Voulez-vous rejouer ? (o/n) : ";
    std::cin >> replay;
    return (replay == "o" || replay == "O");
}
