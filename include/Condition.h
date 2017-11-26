#ifndef CONDITION_H_
#define CONDITION_H_

#include <string>
#include <iostream>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class Condition {
 protected:
  string object;

 public:
  Condition(string obj);
  Condition(xml_node<>* node);
  virtual ~Condition();
  string getObject();
};

#endif
