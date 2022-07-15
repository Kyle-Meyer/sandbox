#include <iostream>
#include <string>
using namespace std;

/*
 * Lab 8: Debugging
 * There are three errors - one is a runtime that causes a segmentation fault
 * The other two are logical errors. Find them using gdb.
 *
 * You must find the errors using gdb
 */

int main(){

  // Initialize string pointer
  string *name = new string("Darren");

  // Print contents of string pointer
  cout << *name << endl;

  // delete name;
  int size = 3;
  string *listNames = new string[3]();

  // Fill listNames
 listNames[0] = "Alex";
 listNames[1] = "Beter";
 listNames[2] = "Cara";


  // Print contents of listNames
  for(int i = 0; i < size; i++){

    cout << "My name is " << listNames[i] << endl;

  }

  delete name;
  delete [] listNames;
}
