#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include "direction.h"
#include "position.h"
#include "orientation.h"
#include "board.h"
#include "player.h"

namespace quoridor {

class Game {

private:

    unsigned idCurrent_;
    int idWinner_;
    std::vector<Player> players_;
    Board board_;

public:

    Game(std::vector<std::string> names, unsigned size=9);
    bool play();
    bool isOver();
    static std::vector<std::string> introGame();
    void gameOver();

private:

    bool playMove(Direction d, bool playerAlreadyOnCase=false);
    bool playWall(Position p, Orientation o);
    void nextPlayer();
    std::vector<Position> getVoisin(Position p);
    bool dfs(Position p, unsigned idPlayer);

};

}

#endif // GAME_H
