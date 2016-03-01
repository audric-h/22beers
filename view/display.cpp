#include "display.h"
#include <iostream>
#include "../keyboardAndStringConvert/keyboard.hpp"

using namespace std;
using namespace quoridor;

void Display::viewBoard(Board &b) {
    for(unsigned i= 0; i<b.getSize();i++) {
        for(unsigned j=0; j<b.getSize();j++) {
            cout << "(";
            if(b.getCase(Position(i,j)).isThereAPlayerOnMe()) {
                cout << b.getCase(Position(i,j)).getIdPlayerOnMe();
            } else {
                cout << " ";
            }
            cout << ")";
            if(b.canIGoRight(Position(i,j))) {
                cout << " ";
            } else {
                if(j == Board::getSize()-1) {
                    std::cout << " ";
                } else {
                    cout << "#";
                }
            }
        }
        cout << endl;
        for(unsigned j=0; j<b.getSize(); j++) {
            if(b.canIGoDown(Position(i,j))) {
                cout << "    ";
            } else {
                if(i==Board::getSize()-1) {
                    cout << "    ";
                } else {
                    cout << "### ";
                }
            }
        }
        cout << endl;
    }
}

void Display::player(quoridor::Player & p) {
    std::cout << p.getName()<<"(joueur "<<p.getId() << ") : Il vous reste " << p.getNbWall() << " murs." << std::endl;
}

char Display::play() {
    char c = '\0';
     do {
        try {
            std::cout << "Voulez-vous vous deplacer (1) ou placer un mur (2) : ";
            c = nvs::lineFromKbd<char>();
        } catch (const std::exception & e) {
            std::cout << "Action impossible, reessayer." << std::endl;
        }
    }while (c != '1' && c != '2');
    return c;
}

Direction Display::chooseDirection() {
    char c = '\0';
    do {
        try {
            std::cout << "Voulez-vous vous deplacer:" << std::endl;
            std::cout << "vers le haut (1)" << std::endl;
            std::cout << "vers le bas (2)" << std::endl;
            std::cout << "vers la gauche (3)" << std::endl;
            std::cout << "vers la droite (4)" << std::endl;
            std::cout << "votre choix : ";
            c = nvs::lineFromKbd<char>();
            std::cout << std::endl;
        } catch (const std::exception & e) {
            std::cout << "Action impossible, reessayer." << std::endl;
        }
    } while (c != '1' && c != '2' && c != '3' && c != '4');
    quoridor::Direction d;
    switch(c) {
    case '1':
        d = quoridor::Direction::UP;
        break;
    case '2':
        d = quoridor::Direction::DOWN;
        break;
    case '3':
        d = quoridor::Direction::LEFT;
        break;
    case '4':
        d = quoridor::Direction::RIGHT;
        break;
    }
    return d;
}

Orientation Display::chooseOrientation() {
    char c = '\0';
    do {
        try {
            std::cout << "Voulez-vous placer un mur horizontal (1) ou vertical (2) ?";
            c = nvs::lineFromKbd<char>();
        } catch (const std::exception & e) {
            std::cout << "Action impossible, reessayer." << std::endl;
        }
    } while (c != '1' && c != '2');
    quoridor::Orientation o;
    switch (c) {
    case '1':
        o = quoridor::Orientation::HORIZONTAL;
        break;
    case '2':
        o = quoridor::Orientation::VERTICAL;
        break;
    }
    return o;
}

Position Display::choosePosition() {
    int x = -1, y = -1;
    quoridor::Position p(0,0);
    do {
        try {
            std::cout << "x : ";
            x = nvs::lineFromKbd<int>();
            std::cout << "y : ";
            y = nvs::lineFromKbd<int>();
            p = quoridor::Position(x,y);
        } catch (const std::exception & e) {
            std::cout << "Action impossible, reessayer." << std::endl;
        }
    } while(x == -1 || y == -1 || x >= quoridor::Board::getSize()-1 || y >= quoridor::Board::getSize()-1);
    return p;
}
