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
  
}
