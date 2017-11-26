#ifndef STATUSCONDITION_H_
#define STATUSCONDITION_H_

#include "Condition.h"
#include "GameObject.h"

#include <string>
#include <iostream>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class StatusCondition : public Condition {
 private:
  string status;

 public:
  StatusCondition(string obj, string stat);
  StatusCondition(xml_node<>* node);
  ~StatusCondition();
  string getStatus();
};
#endif
