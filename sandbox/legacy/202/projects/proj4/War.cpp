//|=======================================================
//| War.cpp
//|
//|Created on: Apr 15, 2019
//| Author: kyle meyer, 
//| Desc: used to actually run most of the programs modules from train horse, to battle, to the main menu
//|=======================================================








#include <iostream>
#include "War.h"
using namespace std;

//default constructor prints out the appropriate message and throws into the main menu
War::War()
{
	cout << endl;
	cout << "Welcome to UMBC War" << endl;
	cout << endl;
  
	//these two horses are here for convenience, their names indicate what they are meant to do, either automatically win, or automatically lose, id figure that I would try and make it easier for the poor TA that has to look at my spaget code
	Horse *horse = new Untrained("Garuanteed Loser", Size(2), 5, 17);
	Horse *horse1 = new Untrained("Absolute Champion", Size(0), 150, 2);
	m_myStable.push_back(horse);
	m_myStable.push_back(horse1);
}

//the destrtuctor, goes through both enemy stable and my stable and deletes each entry, while setting the pointer to each entry to nullptr
War::~War()
{
	for(long unsigned int i = 0; i < m_myStable.size(); i++)
	{
		delete m_myStable[i];
		m_myStable[i] = nullptr;
	}
	for(long unsigned int i = 0; i < m_enemyStable.size(); i++)
	{
		delete m_enemyStable.at(i);
		m_enemyStable[i] = nullptr;
	}
}

//the main menu, simply uses a switch statement to adhere to the corresponding functions
void War::mainMenu()
{
  
        bool contin = true;
	while(contin == true)
	{
	  if(m_enemyStable.size() == 0)
	    {
	      cout << "You have defeated all the other horses, congrats, you win champ" << endl;
	      contin = false;
	    }
		cout << "What would you like to do?" << endl;
		cout << "1.) Display friendly stable" << endl;
		cout << "2.) Display enemy stable" << endl;
		cout << "3.) Aquire new horse" << endl;
		cout << "4.) Train a Horse" << endl;
		cout << "5.) Battle" << endl;
		cout << "6.) Exit" << endl;
		int choice;
		cin >> choice;
		switch(choice)
		{
			case 1: choice = 1;
			{
				displayMyHorses();

			}
			break;
			case 2: choice = 2;
			{
				displayEnemyHorses();

			}
			break;

			case 3: choice = 3;
			{
				acquireHorse();

			}
			break;

			case 4: choice = 4;
			{
				trainHorse();
			}
			break;

			case 5: choice = 5;
			{
				startBattle();
			}
			break;

			case 6: choice = 6;
			{
			  cout << endl;
			  cout << "----------------------------------" << endl;
			  cout << "       THANK YOU FOR PLAYING   " << endl;
			  cout << "----------------------------------" << endl;
				contin = false;
			}
			break;
		}
	}
}
//the train horse function
// first displays the horses, and prompts the user to enter a choice
// after doing so train() is called respectivley to determine if the horse should train or not, for warhorses there is a 50% chance, for untrained horses there is a garuantee specialization
void War::trainHorse()
{
	int choice = chooseHorse();
	Horse *selec = m_myStable.at(choice);
	bool shouldTrain = selec->train();
	if(shouldTrain == true)
	{
	  //if the horse was untrained, specialize, create a copy of the horse in the respective class and delete the original
		if(selec->getTraining() == 0)
		{
		  cout << "Horse was not trained so automatically specializing" << endl;
			Horse *newHorse = selec->specialize();
			m_myStable.at(choice) = newHorse;
			delete selec;
		}
		//otherwise the horse should train normally
		else
		{
		  cout << "Horse Successfully Trained!" << endl;
		  
			selec->increaseTraining();
		}
	}
	else
	{
		cout << "horse failed to train " << endl;
 	}

}
//the aquire horse function
// generates a new untrained horse of randome size(between 0-2) with health and speed to match
// the random genereation algortithm works as follows
// rand()%(MAX-MIN + 1) + MIN
// its the normal rand template but with an adjusted max as thats the way the rand function handles values
void War::acquireHorse()
{
	srand(time(0));
	int newSize = rand()% 2 + 0;
	//	cout << newSize;
	cout << "What would you like to name your new horse?: ";
	string name;
	cin.ignore();
	getline(cin, name);
	cout << endl;
	//the corresponding generating of values based on the size of the horse
	if(newSize == 0)
	{
		int newHealth = rand() % (LT_MAX_HEALTH - LT_MIN_HEALTH + 1) + LT_MIN_HEALTH;
		int newSpeed = rand()% (LT_MAX_SPEED - LT_MIN_SPEED + 1) + LT_MIN_SPEED;
		Horse *newHorse = new Untrained(name, Size(newSize), newHealth, newSpeed);
		//	cout << "New Horses speed = " << newSpeed << " and has a new health of: " << newHealth << " with new size: " << newSize << endl;
		m_myStable.push_back(newHorse);
	}

	else if(newSize == 1)
	{

		int newHealth = rand()% (MD_MAX_HEALTH - MD_MIN_HEALTH + 1) + MD_MIN_HEALTH;

		int newSpeed = rand()% (MD_MAX_SPEED - MD_MIN_SPEED + 1) + MD_MIN_SPEED;
		Horse *newHorse = new Untrained(name, Size(newSize), newHealth, newSpeed);
		//cout << "New Horses speed = " << newSpeed << " and has a new health of: " << newHealth << " with new size: " << newSize << endl;
		m_myStable.push_back(newHorse);
	}
	else if(newSize == 2)
	{
		int newHealth = rand()% (HV_MAX_HEALTH - HV_MIN_HEALTH + 1) + HV_MIN_HEALTH;
		int newSpeed = rand()% (HV_MAX_SPEED - HV_MIN_SPEED + 1) + HV_MIN_SPEED;
		Horse *newHorse = new Untrained(name, Size(newSize), newHealth, newSpeed);
		//cout << "New Horses speed = " << newSpeed << " and has a new health of: " << newHealth << " with new size: " << newSize << endl;
		m_myStable.push_back(newHorse);
	}

}

//display horses function that simply uses the overloaded opreator to print out the stable entries
void War::displayMyHorses()
{
  if(m_myStable.size() == 0)
    {
      cout << "your stable is currently empty and needs horses, use the aquire horse function to do so" << endl;
    }
  else
    {
      cout << "Num" << setw(20) << right << "Name" << setw(10) << right << "Size" << setw(10) << right << "Health" << setw(10) << right << "Speed" << setw(15) << right << "Training" << endl;
     cout << "-------------------------------------------------------------------------------" << endl;
	for(long unsigned int i = 0; i < m_myStable.size(); i++)
	{
		cout << i+1 << ".) " << *m_myStable.at(i) << endl;
	}
    }
	cout << endl;
}

//display enemy horses, does the same thing as displaymyhorses but now it iterates over the enemy stable instead
void War::displayEnemyHorses()
{
  cout << "Num" << setw(20) << right << "Name" << setw(10) << right << "Size" << setw(10) << right << "Health" << setw(10)\
 << right << "Speed" << setw(15) << right << "Training" << endl;
     cout << "-------------------------------------------------------------------------------" << endl;
	for(long unsigned int i = 0; i < m_enemyStable.size(); i++)
	{
		cout << i+1 << ".) " << *m_enemyStable.at(i) << endl;
	}
	cout << endl;
}

//the load horses function, works by opening the file twice, once to get the number of lines in the whole file, the second time to actually read in the data, using cin's for the actual data and getline to store newline characters in dummy strings
void War::loadHorses(char* fileName)
{
       
	ifstream myFile;
	myFile.open(string(fileName));
	string line = "null";
	string name = "Null";
	int horseSize = 0;
	int horseHealth = 0;
	int horseSpeed = 0;
	string dum = "Dumb";
	int size = 0;
	while(getline(myFile, line, '\n'))
	{

		size ++;
	}
	myFile.close();
	myFile.open(fileName);

	int count = 0;

while(myFile.is_open())
{
	while(count < size)
	{
			myFile >> name;
			myFile >> horseSize;
			myFile >> horseHealth;
			myFile >> horseSpeed;
			getline(myFile, dum, '\n');
			//cout << count << " " << "name: " << name << " size " << horseSize << " horseHealth " << horseHealth << " horse's speed " << horseSpeed << endl;
			count ++;

			if(horseSize == 0)
			{
				Horse *newHorse = new Light(name, Size(horseSize), horseHealth, horseSpeed);
				m_enemyStable.push_back(newHorse);
			}
			else if(horseSize == 1)
			{
				Horse *newHorse = new Medium(name, Size(horseSize), horseHealth, horseSpeed);
				m_enemyStable.push_back(newHorse);
			}
			else if(horseSize == 2)
			{
				Horse *newHorse = new Heavy(name, Size(horseSize), horseHealth, horseSpeed);
				m_enemyStable.push_back(newHorse);
			}


		}

	myFile.close();
	}



}

//the Choose horse helper function, displays horses of your stalb then prompts for a choice and returns the user choice-1
int War::chooseHorse()
{
	cout << "Here are your choices of horses horses: " << endl;
	displayMyHorses();
	int choice;
	cout << "Enter your selection: ";
	cin >> choice;
        cout << endl;
	return choice - 1;
}

//the start battle function, prompts for the user to enter a horse for battle, if the horse is untrained then the function quits, if the horse is trained it calls the battle function for the chosen horse, and passes in the target, which is always the first horse in the enemy stable
void War::startBattle()
{

	int choice = chooseHorse();
	Horse *selec = m_myStable.at(choice);
	int maxHealth = selec->getHealth();
	int maxerHealth = m_enemyStable.at(0)->getHealth();
	if(selec->getTraining() == 0)
	{
		cout << "Untrained horses cannot battle " << endl;
	}
	else if(m_enemyStable.size() == 0)
	  {
	    cout << "There are no horses left to battle" <<endl;
	  }
	else
	{
		bool didWin  = selec->battle(m_enemyStable.at(0));
		if(didWin == false)
		{
			cout << endl;
			cout << "********************************" << endl;
			cout << "	YOU HAVE LOST	" << endl;
			cout << "********************************" << endl;
			cout << endl;
			m_enemyStable.at(choice)->setHealth(maxerHealth);
			delete m_myStable.at(choice);
			m_myStable[choice] = nullptr;
			m_myStable.erase(m_myStable.begin() + choice);


		}
		else
		{
			cout << endl;
			cout << "********************************" << endl;
			cout << "	YOU HAVE WON	" << endl;
			cout << "********************************" << endl;
			cout << endl;
			selec->setHealth(maxHealth);
			delete m_enemyStable.at(0);
			m_enemyStable.erase(m_enemyStable.begin() + 0);
		       
		}
	}
	//delete newHorse;



}
