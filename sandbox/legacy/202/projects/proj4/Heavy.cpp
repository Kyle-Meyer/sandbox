//|=======================================================
//| Heavy.cpp
//|
//|Created on: Apr 15, 2019
//| Author: kyle
//| Desc: Class definition for the heavy class
//|=======================================================








#include <iostream>
#include "Heavy.h"
using namespace std;

//defualt constructor
Heavy::Heavy(){

}

//overloaded constructor that calls the overloaded warhorse constructor
Heavy::Heavy(string name, Size size, int speed, int health) : Warhorse(name, size, speed, health)
{


}


//simply returns the string "Heavy" primarily used for the print statement
string Heavy::toString()
{
  //cout << "This is an untrained horse" << endl;
	string truSize;
	Size size = getSize();
	Training train  = getTraining();
	if(size == 0)
	{
		truSize = "Light";
	}
	if(size == 1)
	{
		truSize = "Medium";
	}
	if(size == 2)
	{
		truSize = "Heavy";
	}
	string truTrain;
	if(train == 0)
	{
		truTrain = "UNTRAINED";
	}
	else if(train == 1)
	{
		truTrain = "SADDLE";
	}
	else if(train == 2)
	{
		truTrain = "GREEN";
	}
	else if(train == 3)
	{
		truTrain = "INTERMEDIATE";
	}
	else if(train == 4)
	{
		truTrain = "EXPERT";
	}
	else if(train == 5)
	{
		truTrain = "MASTER";
	}

	string str1;
	str1 += string(getName()) + "              " + string(truSize) + "        " + string(truTrain);
	//cout << str1 << endl;
	return "Heavy";
}

//the attack function that calculates the amount of damage done if the horse is a heavy class, also factors in the kick which i think the heavy class is supposed to do all the time?
int Heavy::attack(string targName, int targHealth)
{
  //	int health = getHealth();
	int train = int(getTraining());
	int dmg = (targHealth/6) + train + kick();
	cout << "heavy horse, " << getName() <<  " Attacked target " << targName << endl;
	return dmg;
}
//defintion of the kick function that is used for calculating the additional damage of teh attack function, generates a random number between 3 and 1 and returns it as additional damage
int Heavy::kick()
{
	cout << getName() << " does a heavy kick" << endl;
	srand(time(0));
	int dmg = rand()% (3 + 1 - 1) + 1;
	return dmg;
}
