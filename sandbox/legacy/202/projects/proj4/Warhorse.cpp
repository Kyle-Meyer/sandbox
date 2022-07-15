//|=======================================================
//| Warhorse.cpp
//|
//|Created on: Apr 8, 2019
//| Author: kyle
//| Desc: Warhorse class definition, used mainly for handling the battle
//|=======================================================




#include <iostream>
#include "Warhorse.h"
#include "Horse.h"
using namespace std;

//default constructor
Warhorse::Warhorse():Horse()
{

}
//overloaded constructr that calls the overloaded warhorse constructor
Warhorse::Warhorse(string name, Size size, int speed, int health) : Horse(name, size, speed, health)
{

}
//the meat of the class, the battle function
// grabs the respective values needed for the battle in the beggining, health, speed
// uses a counter that keeps track of if the horse should attack, using a modulo division
// if either horse's speed is a factorial of the counter, then that respective horse attacks, calling the appropriate attack function, the function also makes sure that the horse cannot do 0 damage, and must always return some damage to the enemy health, the target will lose health respectivley, the first horse to reach 0 health loses, if the player wins, then the function will return true, if the player loses then the function will return false
bool Warhorse::battle(Horse *enemy)
{
	int enemySpeed = enemy->getSpeed();
	int yourSpeed = getSpeed();
	int yourHealth = getHealth();
	int enemyHealth = enemy->getHealth();
	cout << "enemies speed: " << enemySpeed << endl;
	cout << "your speed: " << yourSpeed << endl;
	cout << "your health: " << yourHealth << endl;
	cout << "enemy health: " << enemyHealth << endl;
	int counter =0;
	bool contin = true;
	int youcount = 0;
	int theycount = 0;
	while(contin == true)
	{
		if((counter % yourSpeed) == 0)
		{
			//cout << counter << " % " << yourSpeed << " = " << counter%yourSpeed << endl;
			//cout << "you attack" << endl;
			int damage = attack(enemy->getName(), yourHealth);
			if(damage < 1)
			{
				damage = 1;
			}
			//cout << "enemy will take " << damage << " damage" << endl;
			enemyHealth = enemyHealth - damage;
			//cout << "enemy has " << enemyHealth << " now" << endl;
			youcount ++;
		}
		if((counter % enemySpeed) == 0)
		{
			//cout << "enenmy attacks" << endl;
			int damage = enemy->attack(getName(), enemyHealth);
			if(damage < 1)
			{
				damage = 1;
			}
			yourHealth = yourHealth - damage;
			theycount++;
		}
		counter++;
		if(yourHealth <= 0)
		{

			contin = false;
			return false;
		}
		if(enemyHealth <= 0)
		{
			/*
			cout << "enemy loses, horse will be removed " << endl;
			cout << "you attacked " << youcount << " times" << endl;
			cout << "they attacked " << theycount << " times" << endl;
			cout << "your health: " << yourHealth << endl;
			cout << "enemy health: " << enemyHealth << endl;
			*/
			contin = false;
			return true;
		}
	}
	return true;

}


//the train function, essentially determines if the horse should train or not by passing in a 50% gate limit to the random chance function, and then returns the respective boolean;
bool Warhorse::train()
{
	bool chance = randomPercentBased(50);
	return chance;
}



