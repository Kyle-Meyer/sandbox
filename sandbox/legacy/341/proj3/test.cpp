// CMSC 341 - Fall 2019 - Project 3
// Basic test driver for the Treap class
// Creates the treap example from the project write-up and deletes two
// values

#include <iostream>
#include "treap.h"

using namespace std;

int main() {

  Treap T;

  T.insert("B", 24);
  T.insert("C", 35);
  T.insert("H", 29);
  T.insert("E", 33);
  T.insert("I", 25);
  T.insert("K", 9);
  T.insert("A", 21);
  T.insert("L", 16);
  T.insert("D", 8);
  T.insert("J", 13);
  T.insert("G", 50);


  T.dump();
  // Delete "K" and "C"
  T.inorder();
  
  T.remove("B");
  T.remove("C");
  T.remove("H");
  T.remove("E");
  T.remove("I");
  T.remove("K");
  T.remove("A");
  T.remove("L");
  T.remove("J");
  T.remove("G");
  cout << endl;
  T.inorder();
  cout << endl;

   T.dump();
  
  return 0;
}
