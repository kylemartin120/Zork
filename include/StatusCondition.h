#ifndef STATUSCONDITION_H_
#define STATUSCONDITION_H_

#include "Condition.h"
#include "GameObject.h"

#include <string>
#include <iostream>

using namespace std;

class StatusCondition : public Condition {
 private:
  string status;

 public:
  StatusCondition(GameObject* obj, string stat);
  ~StatusCondition();
  bool isTrue();
};
#endif
