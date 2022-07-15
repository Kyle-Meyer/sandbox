//============================================================================
// Name        : lab2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
using namespace std;

/****************************************************************
 *   FUNCTION PROTOTYPES FOR sumInts() and isEven() GO HERE     *
 ****************************************************************/
int sumInts(int);
int isEven(int);

int main() {
        /****************************************************************
         *             CODE TO INVOKE FUNCTIONS GOES HERE               *
         * Note: the user should enter 3 numbers, and the program will  *
         * display the sum of such numbers, as well as if the sum is    *
         * even/odd. MUST BE IMPLEMENTED IN ONE LINE.                   *
         ****************************************************************/
	int sent;
	cout << "how many numbers would you like to send: ";
	cin >> sent;
	cout << endl;
	int sum = sumInts(sent);


    return 0;
}

int sumInts(int sent){
	int sum;
	for(int i = 0; i < sent; i++){
		int num;
		cout << "please enter a number";
		cin >> num;
		cout << endl;
		sum += num;

	}
	return sum;

}
int isEven(int sum){
	if (sum % 2 == 0){
		cout << sum << " is even" << endl;
	}
	else {
		cout << sum << " is odd" << endl;
	}
	return 0;
}
