#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "rapidxml.hpp"
#include <vector>
#include <queue>

#include "Item.h"
#include "Container.h"
#include "GameObject.h"
#include "Room.h"
#include "Trigger.h"
#include "Game.h"

int main(int argc, char *argv[]) {
  Game* myGame = new Game("xml_source/sample.txt.xml");

  Room* room = myGame->rooms[0];
  cout << "rooms[0] is " << room << endl;
  cout << "rooms[0] has the border " << room->borders[0]->name << " to its " <<
    room->borders[0]->direction << endl;
  cout << "rooms[0] contains the item " << room->items[0] << endl;
}
