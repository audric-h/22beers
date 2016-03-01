#include <iostream>
#include "business/game.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    quoridor::Game game(quoridor::Game::introGame(),5);
    game.gameOver();
    return 0;
    return 0;
}
