//|=======================================================
//| lab3.cpp
//|
//|Created on: Feb 14, 2019
//| Author: kyle
//| Desc: put whatever you want here
//|=======================================================






#include <iostream>
using namespace std;

int divThree(int[], int);

int main(){
   const int MAXSIZE = 100;
   int myArray[MAXSIZE] = {0};
   int currSize = 0;
   int inputValue = 1;

   //Code to take in values and print results goes here
   while(inputValue != 0){
     cout << "enter a value(0 to stop): ";
     cin >> inputValue;
     cout << endl;
     myArray[currSize] = inputValue;
     currSize ++;



   }
   cout << "the array" << endl;
   for(int i = 0; i < currSize -1; i++){
     cout << " " << myArray[i] << " ";

   }
   cout << endl;
   divThree(myArray, currSize);
   return 0;
}

int divThree(int myArray[], int currSize){
	int counter = 0;
	for(int i=0; i < currSize - 1; i++){
		if ((myArray[i] % 3) == 0){
			counter ++;
			myArray[i] = myArray[i] / 3;
		}
	}
	cout << "there were " << counter << " numbers divisible by 3" << endl;
	cout << "modified array" << endl;
	for (int i=0; i < currSize - 1; i++){
		cout << " " << myArray[i] << " ";
	}
	cout << endl;
	return 0;
}


