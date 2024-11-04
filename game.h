#ifndef __GAME_H__
#define __GAME_H__

bool testPlayTurn(int grid[7][6], int column, int& ligne);
bool playTurn(int grid[7][6], int column, int ligne, int player);
bool gameOver(int grid[7][6], int& player);
bool playerWin(int grid[7][6], int player);
bool gameEnd(int grid[7][6]);
bool resetTurn(int grid[7][6], int column);

#endif