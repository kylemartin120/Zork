#ifndef HASCONDITION_H_
#define HASCONDITION_H_

#include "Condition.h"
#include "GameObject.h"

#include <string>
#include <iostream>

using namespace std;

class HasCondition : public Condition {
 private:
  bool has;
  GameObject* owner;

 public:
  HasCondition(bool h, GameObject* obj, GameObject* own);
  virtual ~HasCondition();
  bool isTrue();
};
#endif
