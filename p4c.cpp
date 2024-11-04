#include "game_manager.h"

#include <cstdlib>
#include <ctime>

int main(int argc, char** argv) {
    srand(time(nullptr));
    runGameLoop();
    return 0;
}