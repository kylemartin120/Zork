#ifndef BORDER_H_
#define BORDER_H_

#include <string>

using namespace std;

class Border {
 private:
  string name;
  string direction;

 public:
  Border(string n, string d);
  virtual ~Border();
  string getName();
  string getDirection();
};
#endif
