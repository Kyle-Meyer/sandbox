#ifndef SKATEBOARD_H
#define SKATEBOARD_H

#include <iostream>
#include <string>
using namespace std;

class Skateboard {
 public:
  //Default Constructor
  Skateboard();
  //Overload Constructor
  Skateboard(string skateboardName, double price, int quantity);

  string getSkateboardName();
  double getPrice();
  int getQuantity();

  void setSkateboardName(string skateboardName);
  void setPrice(double price);
  void setQuantity(int quantity);

 private:
  string m_skateboardName;
  double m_price;
  int m_quantity;
};

#endif
