#include "Skateboard.h"
using namespace std;

Skateboard::Skateboard() {
  m_skateboardName = "Penny";
  m_price = 70.99;
  m_quantity = 1;
}

Skateboard::Skateboard(string skateboardName, double price, int quantity){
  m_skateboardName = skateboardName;
  m_price = price;

  m_quantity = quantity;
}

string Skateboard::getSkateboardName(){
  return m_skateboardName;
}
double Skateboard::getPrice(){
  return m_price;
}
int Skateboard::getQuantity(){
  return m_quantity;
}

void Skateboard::setSkateboardName(string skateboardName){
  m_skateboardName = skateboardName;
}
void Skateboard::setPrice(double price){
  m_price = price;
}
void Skateboard::setQuantity(int quantity){
  m_quantity = quantity;
}
