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
  Game* myGame = new Game("xml_source/roomsample.xml");
  myGame->cur_room = myGame->getRoom("Entrance");
  cout << myGame->cur_room->description << endl;
  
  while (!myGame->gameOver) {
    myGame->turn_num++;
    getline(cin, myGame->input);

    // check all triggers, and only execute command if not triggered
    if (!myGame->checkAllTriggers()) {
      myGame->handleCommand(myGame->input);
    }

    // keep checking triggers until effects are over
    while (myGame->checkAllTriggers()) {}
  }
}
