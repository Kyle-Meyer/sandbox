#include <iostream>
using namespace std;

int main () {
  string *p1, *p2;
  p1 = new string;
  p2 = new string;
  *p1 = "TRUE";
  *p2 = "GRIT";
  cout << *p1 << " " << *p2 << endl;
  p2 = p1;
  cout << *p1 << " " << *p2 << endl;
  *p1 = "DOG";
  cout << *p1 << " " << *p2 << endl;

  return 0;
}
