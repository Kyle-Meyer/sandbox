//|=======================================================
//| Light.cpp
//|
//|Created on: Apr 8, 2019
//| Author: kyle
//| Desc: Class definition for the light horse
//|=======================================================




#include <iostream>
#include "Light.h"
using namespace std;

//default constructor
Light::Light(){

}
//overleaded constructor that calls the overloaded warhorse constructor
Light::Light(string name, Size size, int speed, int health) : Warhorse(name, size, speed, health)
{


}


//again overcomplicated, just know that it returns "light"
string Light::toString()
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
	return "Light";
}

//standard attack function that calculates the damge the light horse will do in battle
int Light::attack(string targName, int targHealth)
{
  //	int health = getHealth();
	int train = int(getTraining());
	int dmg = (targHealth/6) + train;
	cout << "light horse " << getName() <<  " Attacked target " << targName << endl;
	return dmg;
}


