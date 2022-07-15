#include <iostream>
using namespace std;

// Use this file to implement the templated isDivisible function
// this function takes two args:
//   a: object of type T (where T is the templated class type)
//   b: object of type T (where T is the templated class type)
//
// the function returns an int (either -1, 0, or 1):
//   -1 if a is not evenly divisible by b
//   0 if a==b
//   1 if a is evenly divisible by b


// Implement the templated isDivisible function here:
template <class T>
  T isDivisible(const T&a, const T&b)
  {
    if(a%b != 0)
      {
	return -1;
      }
    if(a == b)
      {
	return 0;
      }
    if(a%b == 0)
      {
	return 1;
      }

}

int main(){
  cout << "isDivisible(10, 5)\t\t (1 expected):" << endl;
  cout << isDivisible(10,5) << endl << endl;

  cout << "isDivisible(1, 4)\t\t (-1 expected):" << endl;
  cout << isDivisible(1,4) << endl << endl;

  cout << "isDivisible(100, 3)\t\t (-1 expected):" << endl;
  cout << isDivisible(100,3) << endl << endl;

  cout << "isDivisible(1000, 50)\t\t (1 expected):" << endl;
  cout << isDivisible(1000,50) << endl << endl;

  cout << "isDivisible(99, 3)\t\t (1 expected):" << endl;
  cout << isDivisible(99,3) << endl << endl;

  cout << "isDivisible(12, 5)\t\t (-1 expected):" << endl;
  cout << isDivisible(12,5) << endl << endl;

  cout << "isDivisible(89, 4)\t\t (-1 expected):" << endl;
  cout << isDivisible(89,4) << endl << endl;

  cout << "isDivisible(66, 66)\t\t (0 expected):" << endl;
  cout << isDivisible(66,66) << endl << endl;

  cout << "isDivisible(17, 5)\t\t (-1 expected):" << endl;
  cout << isDivisible(17,5) << endl << endl;

  return 0;
}
