#include "GameObject.h"
#include "Trigger.h"
#include "Condition.h"
#include "HasCondition.h"
#include "StatusCondition.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char *argv[]) {
  vector<Trigger*> t1;
  vector<Trigger*> t2;
  GameObject* torch = new GameObject("torch", "", "", t1);
  GameObject* inventory = new GameObject("inv", "", "", t2);
  HasCondition* hasTorch = new HasCondition(false, torch, inventory);
  vector<string> s;
  s.push_back("print hi");
  vector<Condition*> c;
  c.push_back(hasTorch);
  Trigger* torchTrig = new Trigger(s, false, c);
  cout << "starting trigger check" << endl;
  vector<string> commands;
  commands.push_back("fail");
  if (torchTrig->isTriggered()) {
    cout << "successful trigger" << endl;
    commands = torchTrig->getCommands();
  }
  for (unsigned int i = 0; i < commands.size(); i++) {
    cout << commands[i] << endl;
  }
  if (torchTrig->isTriggered()) {
    cout << "not asserting used" << endl;
  }
  else {
    cout << "correctly asserting used" << endl;
  }
}
