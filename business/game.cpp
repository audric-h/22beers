#include "game.h"
#include "../view/display.h"

namespace quoridor {

Game::Game(std::vector<std::string> names, unsigned size) : board_(Board(size)) {
    if(names.size() != 2 && names.size() != 4) throw std::invalid_argument { "Nombre de joueurs invalide." };
    for(unsigned i=0; i<names.size(); i++) {
        if(names.size() == 2) {
            players_.push_back(Player(names[i],size+1));
        } else if (names.size() == 4) {
            players_.push_back(Player(names[i], (size+1)/2));
        }
        board_.getCase(players_[i].getPosition()).setIdPlayerOnMe(i);
    }
    idCurrent_ = 0;
    idWinner_ = -1;
}

bool Game::play() {
    bool played = false;
    do {
        Display::viewBoard(board_);
        Display::player(players_[idCurrent_]);
        char c = Display::play();

        switch(c) {
        case '1':
            played = playMove(Display::chooseDirection());
            break;
        case '2':
            played = playWall(Display::choosePosition(),Display::chooseOrientation());
            break;
        }
    } while(!played);

    if(players_[idCurrent_].isArrived()) idWinner_ = idCurrent_;
    nextPlayer();
    return played;
}

bool Game::isOver() {
    return idWinner_ != -1;
}

bool Game::playMove(Direction d, bool playerAlreadyOnCase) {
    bool canGo = false;
    switch(d) {
    case Direction::UP:
        canGo = board_.canIGoUp(players_[idCurrent_].getPosition());
        break;
    case Direction::DOWN:
        canGo = board_.canIGoDown(players_[idCurrent_].getPosition());
        break;
    case Direction::LEFT:
        canGo = board_.canIGoLeft(players_[idCurrent_].getPosition());
        break;
    case Direction::RIGHT:
        canGo = board_.canIGoRight(players_[idCurrent_].getPosition());
        break;
    }
    if(canGo) {
        if(!playerAlreadyOnCase) board_.getCase(players_[idCurrent_].getPosition()).setIdPlayerOnMe(-1);
        players_[idCurrent_].move(d);
        if(board_.getCase(players_[idCurrent_].getPosition()).isThereAPlayerOnMe()) {
            if(playerAlreadyOnCase) {
                switch(d) {
                case Direction::UP:
                    players_[idCurrent_].getPosition().move(1,0);
                    return false;
                    break;
                case Direction::DOWN:
                    players_[idCurrent_].getPosition().move(-1,0);
                    return false;
                    break;
                case Direction::LEFT:
                    players_[idCurrent_].getPosition().move(0,1);
                    return false;
                    break;
                case Direction::RIGHT:
                    players_[idCurrent_].getPosition().move(0,-1);
                    return false;
                    break;
                }
            } else {
                while(!playMove(Display::chooseDirection(),true));
            }
        }
        board_.getCase(players_[idCurrent_].getPosition()).setIdPlayerOnMe(idCurrent_);
    }

    return canGo;
}

bool Game::playWall(Position p, Orientation o) {
    if(players_[idCurrent_].getNbWall() == 0) return false;
    bool wallPlaced = board_.setWall(p,o);
    if(wallPlaced) {
        board_.turnOffMarque();
        for(unsigned i=0; i<players_.size();i++) {
            if(!dfs(players_[i].getPosition(),i)) {
                board_.wallRollBack(p,o);
                return false;
            }
        }
    }
    if(wallPlaced) players_[idCurrent_].nbWallDecremente();
    return wallPlaced;
}

void Game::nextPlayer() {
    idCurrent_++;
    if(idCurrent_ == players_.size()) idCurrent_ = 0;
}

std::vector<Position> Game::getVoisin(Position p) {
    std::vector<Position> vp;
    if(board_.canIGoUp(p)) vp.push_back(Position(p.getRow()-1,p.getColumn()));
    if(board_.canIGoDown(p)) vp.push_back(Position(p.getRow()+1,p.getColumn()));
    if(board_.canIGoLeft(p)) vp.push_back(Position(p.getRow(),p.getColumn()-1));
    if(board_.canIGoRight(p)) vp.push_back(Position(p.getRow(),p.getColumn()+1));
    return vp;
}

bool Game::dfs(Position p, unsigned idPlayer) {
    board_.getCase(p).setMarqued();
    std::vector<Position> vp = getVoisin(p);
    for(unsigned i=0; i<vp.size(); i++) {
        if(!board_.getCase(vp[i]).isMarqued()) {
            dfs(vp[i],idPlayer);
        }
    }
    switch(idPlayer) {
    case 0:
        for(unsigned i=0; i<Board::getSize();i++)
            if(board_.getCase(Position(0,i)).isMarqued()) return true;
        break;
    case 1:
        for(unsigned i=0; i<Board::getSize();i++)
            if(board_.getCase(Position(Board::getSize()-1,i)).isMarqued()) return true;
        break;
    case 2:
        for(unsigned i=0; i<Board::getSize();i++)
            if(board_.getCase(Position(i,Board::getSize()-1)).isMarqued()) return true;
        break;
    case 3:
        for(unsigned i=0; i<Board::getSize();i++)
            if(board_.getCase(Position(i,0)).isMarqued()) return true;
        break;
    }
    return false;
}

}
