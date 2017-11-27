#include "GameObject.h"
#include "Trigger.h"
#include "Condition.h"
#include "HasCondition.h"
#include "StatusCondition.h"
#include "Container.h"
#include "Room.h"
#include "Item.h"
#include "Game.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char *argv[]) {
  Game* myGame = new Game("xml_source/sample.txt.xml");
  myGame->cur_room = myGame->rooms[0];
}
