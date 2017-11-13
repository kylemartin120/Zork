#ifndef CREATURE_H_
#define CREATURE_H_

#include "GameObject.h"
#include "Trigger.h"
#include "Attack.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Creature : public GameObject {
 private:
  vector<string> vulnerability;
  Attack* attack;

 public:
  Creature(string n, string s, string d, vector<string> v, Attack* a,
	   vector<Trigger*> t);
  virtual ~Creature();
  Attack* getAttack(GameObject* item);
};
#endif
