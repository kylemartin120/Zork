#ifndef BORDER_H_
#define BORDER_H_

#include <string>
#include <iostream>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class Border {
 private:
  string name;
  string direction;

 public:
  Border(string n, string d);
  Border(xml_node<>* node);
  virtual ~Border();
  string getName();
  string getDirection();
};
#endif
