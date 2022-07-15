#include "Skateboard.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Write the definitions of these functions below

// fill vector - fills Skateboard info
// vector<Skateboard>& - Skateboards in your garage
void fillVector(vector<Skateboard>&);


// printVectorWithIterator - prints the information
// of all Skateboard using the ::iterator
void printVectorWithIterator(vector<Skateboard>&);

// printVectorWithoutIterator - prints the information 
// of all Skateboard using unsigned int
void printVectorWithoutIterator(vector<Skateboard>&);

int main () {
  int i = 0;
  cout << "How many skates ya got ";
  cout << endl;
  //Creates a new vector of Skateboards for your garage
  vector<Skateboard> myGarage;

  //Populates the vector
  fillVector(myGarage);

  cout << "Garage List using unsigned int: " << endl;
  // Prints the contents of the vector using unsigned int
  printVectorWithoutIterator(myGarage);  

  cout << "\n";
  cout  << "Recipe using the ::iterator:" << endl;
  // Prints the contents of the vector using ::iterator 
  printVectorWithIterator(myGarage);
  
  return 0;
}


//Implement functions here

void fillVector(vector<Skateboard>& boards)
{
  for(unsigned int i = 0; i < sizeof(boards); i++)
    {
      string name;
      double price;
      int quant;
      cout <<  "Skateboard " << i << "Name: ";
      cin >> name;
      cout << endl;
      cout << "Skateboard " << i << "Price: ";
      cin >> price;
      cout << endl;
      cout << "Skateboard " << i << "Quantity: ";
      cin >> quant;
      cout << endl;
      Skateboard skate(name, price, quant);
      boards.push_back(skate);

    }
}

void printVectorWithIterator(vector<Skateboard>& boards)
{
  for(unsigned int i = 0; i < boards.size(); i++)
    {
      Skateboard skate = boards[i];
      cout << skate.getSkateboardName();
    }

}
