#ifndef ITEM_H_
#define ITEM_H_

#include "GameObject.h"
#include "Trigger.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Item : public GameObject {
 private:
  string writing;
  vector<string> onCommands;

 public:
  Item(string n, string s, string d, string w, vector<string> on,
       vector<Trigger*> t);
  virtual ~Item();
  void printWriting();
  vector<string> getOnCommands();
};
#endif
