#ifndef HASCONDITION_H_
#define HASCONDITION_H_

#include "Condition.h"

#include <string>
#include <iostream>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class HasCondition : public Condition {
 public:
  bool has;
  string owner;
  
  HasCondition(bool h, string obj, string own);
  HasCondition(xml_node<>* node);
  virtual ~HasCondition();
  bool getHas();
  string getOwner();
};
#endif
