#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

void runGameLoop();
void initializeGame(int& modeDeJeu, int& offensive, bool& vsIA);
void handlePlayerTurn(int grid[7][6], int player);
void handleIATurn(int grid[7][6], int player, int offensive);
bool checkGameOver(int grid[7][6], int& player_win);
bool askReplay();

#endif // __GAME_MANAGER_H__
