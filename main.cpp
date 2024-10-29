#include <iostream>
#include <stdlib.h>
#include <string>

void print_grid(int grid[7][6]);
bool valid_colum(int grid[7][6], int column, int player);

int main(int argc, char** argv){
    bool running = true;

    const int line = 6;
    const int column = 7;
    int grid[column][line] = {};

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            grid[j][i] = 0;

    int player = 1;
    std::string choix("");
    print_grid(grid);

    while (running){
        std::cout << "choix de la conole (" << player << ") : ";
        std::cin >> choix;

        if (choix == "exit"){
            running = false;
            break;
        }

        bool isvalid = false;

        if (choix.size() == 1){
            if (choix[0] >= '1' && choix[0] <= '7'){
                int choix_column = choix[0] - '0';
                isvalid = valid_colum(grid, choix_column, player);
            }
        }

        system("CLS"); 
        if (!isvalid){
            std::cout << "votre jeux n'est pas bon recommencer\n";
        } else {
            if (player == 1) player = 2;
            else player = 1;
        }
        print_grid(grid);
    }

    return 0;
}


// 0, 1, 2
void print_grid(int grid[7][6]){
    for (int line = 0; line < 6; line++){
        for (int column = 0; column < 7; column++){
            if (grid[column][line] == 1){
                std::cout << "\033[31m*\033[37m|";
            } else if (grid[column][line] == 2){
                std::cout << "\033[32m*\033[37m|";
            } else {
                std::cout << "\033[37m*\033[37m|";
            }
        }
        std::cout << std::endl;
    }
}

bool valid_colum(int grid[7][6], int column, int player){
    for (int line = 5 ; line >= 0; line--){
        if (grid[column - 1][line] == 0){
            grid[column - 1][line] = player;
            print_grid(grid);
            return true;
        }
    }
    return false;
}