#include <iostream>
using namespace std;

// Use this file to implement the templated class ProdList
// ProdList is a class that stores an array of 5 elements of a templated type
// The constructor takes no parameters and sets all elements of the array to 0
// setIndex function takes an index and value
//    and sets the element of the array at the given index to the given value
//    (assume 0<=index<=4)
// product function should return the product of all elements in the list

// Define Constants Here


// Implement the class ProdList here:
template <class T>
class ProdList {
public:
  ProdList();
  T product();
  void setIndex(int, T);
private:
  T array1[5];

};

// Implement constructor here:
template <class T>
ProdList<T>::ProdList() {
  for(int i = 0; i<5; i++)
    {
      array1[i] = 0;
    }

}

// Implement product function here:
template <class T>
T ProdList<T>::product() {
  int total = 0;
  return array1[0] * array1[1] * array1[2] * array1[3] * array1[4];

}

//Implement setIndex function here:
template <class T>
void ProdList<T>::setIndex(int index, T val) {
  array1[index] = val;

}

int main()
{
  ProdList<int> intList;            // list of 5 ints
  ProdList<float> floatList;        // list of 5 floats
  ProdList<unsigned int> uintList;  // list of 5 unsigned ints

  // test list of ints
  int intVals[] = {1,2,3,4,-5};
  for (int i=0; i<5; i++) {
      intList.setIndex(i, intVals[i]);
  }
  cout << "int results -120 expected):" << endl;
  cout << intList.product() << endl;

  // test list of floats
  // initial list should be all 0.0
  cout << endl << "float results: (0 expected):" << endl;
  cout << floatList.product() << endl;

  float floatVals[] = {10,1.5,2.5,4,-4.5};
  for (int i=0; i<5; i++) {
      floatList.setIndex(i, floatVals[i]);
  }
  cout << endl << "float results: (-675 expected):" << endl;
  cout << floatList.product() << endl;

  // test list of unsigned ints
  unsigned int uintVals[] = {56,1,78,2,3};
  for (int i=0; i<5; i++) {
      uintList.setIndex(i, uintVals[i]);
  }
  cout << endl << "unsigned int results: (26208 expected):" << endl;
  cout << uintList.product() << endl << endl;

  return 0;
}
