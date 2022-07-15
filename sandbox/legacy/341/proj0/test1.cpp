//
// test1.cpp : test driver for the my_array class
//    tests copy constructor and assignment operator
//
// Compile with:
//    g++ test1.cpp my_array.cpp -o test1
//
// To check for memory leaks, run with Valgrind:
//    valgrind test1
//

#include <iostream>
#include "my_array.h"

using namespace std;

int main() {

  const int ARRAY_SIZE = 20;
  
  // Create an array 
  my_array x(ARRAY_SIZE);

  // Write some values to the array
  for (int i = 1; i <= ARRAY_SIZE; i++ ) {
    x.at(i-1) = (i*i) % 19;
  }

  cout << "TEST OF COPY CONSTRUCTOR\n\n";
  
  // Print the values in the x array
  cout << "my_array x:" << endl;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    cout << x.at(i) << " ";
  }
  cout << endl << endl;

  // Test the copy constructor
  my_array y(x);
  
  // Print the values in the y array
  cout << "my_array y (copy of x):" << endl;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    cout << y.at(i) << " ";
  }
  cout << endl << endl;

  // Modify y and print again
  for (int i = 0; i < ARRAY_SIZE/2; i++) {
    y.at(i) = i;
  }
  cout << "my_array y (modified copy of x):" << endl;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    cout << y.at(i) << " ";
  }
  cout << endl << endl;

  // Print x again
  cout << "my_array x (should not have changed!):" << endl;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    cout << x.at(i) << " ";
  }
  cout << endl << endl;


  // Create a third array with values 0..ARRAY_SIZE-1
  my_array z(ARRAY_SIZE);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    z.at(i) = i;
  }

  cout << "TEST OF ASSIGNMENT OPERATOR\n\n";
  
  // Print the values in the z array
  cout << "my_array z:" << endl;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    cout << z.at(i) << " ";
  }
  cout << endl << endl;

  // Test assignment operator
  y = z;

  cout << "The altered Y array, should be the same as above" << endl;
  
  // ***********************
  //
  // COMPLETE THE TEST CODE
  //
  // ***********************
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << y.at(i) << " ";
    }
  
  cout << endl;

  z=x;
    cout << "modified Z array, should now be the original x array" << endl;
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << z.at(i) << " ";
    }
  cout << endl;
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
     x.at(i) = i;
    }
  cout << "modifying the X array to be simple digits " << endl;
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << x.at(i) << " ";
    }

  cout << endl;
  cout << "printing the Z array to establish that these two are independent" << endl;
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << z.at(i) << " ";
    }

  y=x;
  cout << endl;
  cout << "printing a new Y array which should be a copy of the new X array" << endl;
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << y.at(i) << " ";
    }
  cout << endl;


  x=y;
  z=y;
  cout << "setting all the arrays equal to each other" << endl;
  cout << "X: ";
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << x.at(i) << " ";
    }
  cout << endl;
  cout << "Y: ";
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << y.at(i) << " ";
    }
  cout << endl;
  cout << "Z: ";
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << z.at(i) << " ";
    }
  cout << endl;
  cout << endl;
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      x.at(i) = i+1;
    }
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      y.at(i) =	i+2;
    }
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      z.at(i) =	i+5;
    }
  cout << endl;
  cout << "printing the X, Y, Z, arrays, Z should be offset by 5, X offset by 1, y offset by 2"<< endl;
  cout << "X: ";
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << x.at(i) << " ";
    }
  cout << endl;
  cout << "Y: ";
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << y.at(i) << " ";
    }
  cout << endl;
  cout << "Z: ";
  for(int i = 0; i < ARRAY_SIZE; i++)
    {
      cout << z.at(i) << " ";
    }
  cout << endl;	
  return 0;
}
