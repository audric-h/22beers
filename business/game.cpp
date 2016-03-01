#include "game.h"
#include "../view/display.h"

namespace quoridor {

Game::Game(std::vector<std::string> names, unsigned size) : board_(Board(size)) {
    if(names.size() != 2 && names.size() != 4) throw std::invalid_argument { "Nombre de joueurs invalide." };
    for(unsigned i=0; i<names.size(); i++) {
        players_.push_back(Player(names[i]));
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
            playMove(Display::chooseDirection(),true);
        }
        board_.getCase(players_[idCurrent_].getPosition()).setIdPlayerOnMe(idCurrent_);
    }

    return canGo;
}

bool Game::playWall(Position p, Orientation o) {
    bool hori = board_.getWall(p).getHorizontal();
    bool verti = board_.getWall(p).getVertical();
    std::cout << std::boolalpha << "hori : " << hori << " verti : " << verti << std::endl;
    bool wallPlaced = board_.setWall(p,o);
    std::cout << "wallplaced : " << std::boolalpha << wallPlaced << std::endl;
    if(wallPlaced) {
        board_.turnOffMarque();
        for(unsigned i=0; i<players_.size();i++) {
            bool b = dfs(players_[i].getPosition(),i);
            for(int i=0; i<Board::getSize();i++) {
                for(int j=0; j<Board::getSize();j++) {
                    std::cout << "(";
                    if(board_.getCase(Position(i,j)).isMarqued()) std::cout << ".";
                    else std::cout << " ";
                    std::cout << ") ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            if(!b) {
                board_.wallRollBack(p, o,hori,verti);
                return false;
            }
            /*
            if(!dfs(players_[i].getPosition(),i)) {
                board_.wallRollBack(p);
                return false;
            }*/
        }
    }
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
