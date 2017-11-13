#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "GameObject.h"
#include "Trigger.h"

#include <string>
#include <iostream>
#include <vector>

class Container : public GameObject {
 private:
  vector<string> accept;
  vector<GameObject*> items;
  bool isOpen;

 public:
  Container(string n, string s, string d, vector<string> a,
	    vector<GameObject*> i, vector<Trigger*> t);
  virtual ~Container();
  void open();
  GameObject* getItem(string name);
  bool putItem(GameObject* item);
};
#endif
  
