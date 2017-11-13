#include "Item.h"
#include "GameObject.h"
#include "Trigger.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

Item::Item(string n, string s, string d, string w, vector<string> on,
	   vector<Trigger*> t) : GameObject(n, d, s, t) {
  writing = w;
  onCommands = on;
}

Item::~Item() {}

void Item::printWriting() {
  cout << writing << endl;
}

vector<string> getOnCommands() {
  return onCommands;
}
