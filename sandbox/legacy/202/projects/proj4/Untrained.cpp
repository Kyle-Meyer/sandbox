//|=======================================================
//| Untrained.cpp
//|
//|Created on: Apr 14, 2019
//| Author: kyle
//| Desc: put whatever you want here
//|=======================================================








#include <iostream>
#include "Untrained.h"
#include "Horse.h"
using namespace std;

//default constructor
Untrained::Untrained()
{

}

//overloaded constructor that calls to the horse constructor
Untrained :: Untrained(string name, Size size, int health, int speed) : Horse(name, size, health, speed)
{

}
//defualts to true since the horse should always train and there fore specialize when they are untrained
bool Untrained::train()
{
	//bool chance = randomPercentBased(50);
	return true;
}
//the specialize function
// checks the size of the horse, and then creates a new horse object of the respected class (light, medium, heavy), increases the horses training to the basic level, and then returns the new horse object
Horse* Untrained::specialize()
{
	string name = getName();
	Size size = getSize();
	int health = getHealth();
	//	Training train = getTraining();
	int speed = getSpeed();
	if(size == 0)
	{
	  cout << getName() << " has become a light Horse! " << endl;
		Horse *horse = new Light(name, size, health, speed);
		horse->increaseTraining();
		return horse;
	}
	else if(size == 1)
	{
	  cout << getName() << " has become a medium Horse! " << endl;
		Horse *horse = new Medium(name, size, health, speed);
		horse->increaseTraining();
		return horse;
	}
	else if(size == 2)
	{
	  cout << getName() << " has become a heavy Horse! " << endl;
		Horse *horse = new Heavy(name, size, health, speed);
		horse->increaseTraining();
		return horse;
	}
	return nullptr;


}
//this function is massivley overcomplicated because it was used for debugging, just know that it returns "untrained"
string Untrained::toString()
{
  //cout << "This is an untrained horse" << endl;
	string truSize;
	Size size = getSize();
	//	Training train  = getTraining();
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
	truTrain = "Untrained";

	string str1;
	str1 += string(getName()) + "              " + string(truSize) + "        " + string(truTrain);
	//	cout << str1 << endl;
	return "Unknown";
}

//defualt print statement for when the user tries to use an untrained horse in battle
int Untrained::attack(string target, int attackpt)
{
	cout << "Untrained units cannot attack" << endl;
	return 0;
}
