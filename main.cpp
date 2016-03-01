#include <iostream>
#include "business/game.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    vector<string> names;
    names.push_back("Audric");
    names.push_back("Quentin");
    names.push_back("Audric");
    names.push_back("Quentin");
    quoridor::Game g(names,5);
    while(!g.isOver()) g.play();
    cout << "isover" << endl;
    return 0;
}
