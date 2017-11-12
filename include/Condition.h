#ifndef CONDITION_H_
#define CONDITION_H_

#include "GameObject.h"

#include <string>
#include <iostream>

using namespace std;

class Condition {
 private:
  GameObject * object;
  
 public:
  Condition(GameObject * obj);
  virtual ~Condition();
  virtual bool isTrue();
};

#endif
