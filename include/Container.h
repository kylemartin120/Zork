#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "GameObject.h"
#include "Trigger.h"

#include <string>
#include <iostream>
#include <vector>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class Container : public GameObject {
 public:
  vector<string> accept;
  vector<string> items;
  bool isOpened;

  Container(string n, string s, string d, vector<string> a,
	    vector<string> i, vector<Trigger*> t);
  Container(xml_node<>* node);
  virtual ~Container();
  void open();
  vector<string> getItems();
  bool isOpen();
  bool putItem(string item);
};
#endif
  
