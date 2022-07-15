//|=======================================================
//| Horse.cpp
//|
//|Created on: Apr 8, 2019
//| Author: kyle
//| Desc: The horse cpp file used to define default behaviors and traits across all classes
//|=======================================================




#include <iostream>
#include "Horse.h"
using namespace std;

//default constructor
Horse::Horse()
{

}

//overloeaded constructor setting name, size, health, and speed, defualting training to untrained
Horse::Horse(string name, Size size, int health, int speed)
{
	m_name = name;
	m_training = Training(0);
	m_size = size;
	m_speed = speed;
	m_health = health;
}




//simple return of name
string Horse::getName()
{
	return m_name;
}
//simple return of size
Size Horse::getSize()
{
	return m_size;
}
//simple return of health
int Horse::getHealth(){
	return m_health;
}
//simple return of speed
int Horse::getSpeed()
{
	return m_speed;
}
//simple return of training
Training Horse::getTraining()
{
	return m_training;
}
//simple set health function
void Horse::setHealth(int health)
{
	m_health = health;
}
//increase training
//will call the random chance function passing it a int of 50 (for 50% chance) and then grab the return boolean to determine if the horse trained or not, if it did, increment the training Enum, if the horse is at max training level then it will return false
bool Horse::increaseTraining()
{
	Training train = getTraining();
	int trainNum = int(train);
	if(train == 5)
	{
		cout << "horse is at max level cannot train anymore" << endl;
		return false;
	}
	else
	{
		trainNum ++;
		m_training = Training(trainNum);
		return true;
	}
	return true;

	//cout << size << " " << train << endl;

}

//the randome percent based function
// takes in the passed int as the level for which it should check out of 100
// then compares it to a random int that gets generated between 0 and 100 inclusivley
// if the passed int it less than or equal to the random number, returns true, else false
bool Horse::randomPercentBased(int chance)
{
	srand(time(0));
	int proc = rand() % 100 + 0;
	//cout << proc << endl;
	if(chance <= proc)
	{
	  //	cout << "chance was within range, returning true" << endl;
		return true;
	}
	else
	{
	  //	cout << "chance was not in range, returning false" << endl;
		return false;
	}

}

//traingin String
// i couldnt get this to work, but it should have simply chekced the training passed in enum and returned a string value of what that enum value means, in this case, the level of training
string Horse::trainingString(Training train)
{
  if(train == 0)
		{
			return "UNTRAINED";
		}
		else if(train == 1)
		{
			return "SADDLE";
		}
		else if(train == 2)
		{
			return "GREEN";
		}
		else if(train == 3)
		{
			return "INTERMEDIATE";
		}
		else if(train == 4)
		{
			return "EXPERT";
		}
		else if(train == 5)
		{
			return "MASTER";
		}
  return "Null";
}

//overaloaded insertion operator
// i used a mach set up of the above toString() function to get it to work here, but it simply takes in the passed horse object as a reference, and then alligns and displays the appropriate data uses the toString function to find the horses size
ostream& operator<<(ostream &output, Horse &horse)
{
		string truSize;
		string size = horse.toString();
		//NOTE this didnt work for some reason because trainingString was apparently not in the scope of the parent function, i couldnt get this to work no matter how hard i tried
		//string train = trainingString(horse.getTraining());
		Training train = horse.getTraining();
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
		//the massive allign statement
	    	output << setw(20) << right << horse.getName() << setw(10) << right << size << setw(10) << right << horse.getHealth() << setw(10) << right << horse.getSpeed() << setw(15) << right << truTrain << endl;
		return output;
}

//specialize
// returns null because its not needed here
Horse* Horse::specialize()
{
  return nullptr;
}

//returns false since its not needed here
bool Horse::battle(Horse*)
{
  return false;
}


