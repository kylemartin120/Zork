#ifndef ITEM_H_
#define ITEM_H_

#include "GameObject.h"
#include "Trigger.h"

#include <string>
#include <iostream>
#include <vector>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class Item : public GameObject {
 public:
  string writing;
  vector<string> prints;
  vector<string> actions;

  Item(string n, string s, string d, string w, vector<string> p,
       vector<string> a, vector<Trigger*> t);
  Item(xml_node<>* node);
  virtual ~Item();
  void printWriting();
  vector<string> getPrints();
  vector<string> getActions();
};
#endif
