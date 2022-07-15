//|=======================================================
//| Medium.cpp
//|
//|Created on: Apr 15, 2019
//| Author: kyle
//| Desc: Medium class definition
//|=======================================================








#include <iostream>
#include "Medium.h"
using namespace std;
//defualt constructor
Medium::Medium(){

}
//overloaded constructor that calls the overloaded warhorse constructor
Medium::Medium(string name, Size size, int speed, int health) : Warhorse(name, size, speed, health)
{


}


//simple function to return the string "medium"
string Medium::toString()
{
  //	cout << "This is an untrained horse" << endl;
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
	//	cout << str1 << endl;
	return "Medium";
}


//attack function that is used to generate the amount of damage that the horse will do if its a medium class horse
int Medium::attack(string targName, int targHealth)
{
  //	int health = getHealth();
	int train = int(getTraining());
	int dmg = (targHealth/6) + train;
	cout << "Medium Horse " << getName() <<  " Attacked target " << targName << endl;
	return dmg;
}
