//|=======================================================
//| Game.cpp
//|
//|Created on: Mar 4, 2019
//| Author: kyle
//| Desc: put whatever you want here
//|=======================================================








#include <iostream>
#include "Game.h"
#include "Alchemist.h"
using namespace std;

Game::Game()
{

}

int getInput(int, int);
//Alchemist alchem;
void Game::StartGame()
{
	LoadElements();
	//Alchemist alchem;
	Element air("Air", " ", " ");
	Element fire("Fire", " ", " ");
	Element erf("Earth", " ", " ");
	Element water("Wate", " ", " ");
	m_myAlchemist.AddElement(air);
	//m_myAlchemist.AddElement(air);
	m_myAlchemist.AddElement(fire);
	m_myAlchemist.AddElement(erf);
	m_myAlchemist.AddElement(water);
	GameTitle();
	string name;
	cout << endl;
	cout << "welcome! ";
	m_myAlchemist.SetName(name);
	//m_myAlchemist.GetElement(1);
	//test();
	//DisplayElements();
	MainMenu();

}

void Game::RequestElement(int &choice)
{
	//cout << choice;
	if(choice == -1)
	{
		for(int i = 0; i < PROJ2_SIZE; i++)
		{
			Element elem = m_elements[i];
      			cout << elem.m_name << " is made of " << elem.m_element1 << " and " << elem.m_element2 << endl;
		}
	}
	else
	{
		Element elem = m_myAlchemist.GetElement(choice-1);
		cout << "you have selected " << elem.m_name << endl;
		cout << endl;
	}
}
int getInput(int max, int min)
{

	int choice;
	bool cont = false;
	while(cont == false)
	{
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;
		if(choice < min || choice > max)
		{
			cout << "Invalid option" << endl;
			cout << endl;
		}
		else
		{
			return choice;
		}
	}
}

int Game::MainMenu()
{
	bool cont = true;
	int choice = 0;
	while(cont == true)
	{
		cout << "All powerful Alchemist " << m_myAlchemist.GetName() << " Here are your options: " << endl;
		cout << "-----------------------------------------" << endl;
		cout << "1.) See all current elements" << endl;
		cout << "2.) Attempt to combine elements" << endl;
		cout << "3.) See score" << endl;
		cout << "4.) Exit" << endl;
		choice = getInput(4,0);
		switch(choice)
		{
		case 1: choice = 1;
		  {
				DisplayElements();

		  }	
			break;
		case 2: choice = 2;
		  {	
			  //cout << "no no no" << endl;
				CombineElements();

		  }	
			break;

		case 3: choice = 3;
		  {
			CalcScore();
		  }
		  break;
		case 4: choice = 4;
		  {
		    cont = false;
		    return 0;
		  }
		  break;

	}
		
}
	return 0;
}
void Game::LoadElements()
{

	ifstream myFile (PROJ2_DATA);
	string name,elem1,elem2;

	int count = 0;
		while(myFile.is_open())
		{
			while (count < PROJ2_SIZE) {
				getline(myFile, name, ',');
				getline(myFile, elem1, ',');
				getline(myFile, elem2, '\n');
				//	cout << "name was " << name << " elem 1 was: " << elem1 <<" elem 2 was: " << elem2 << endl;

				Element myElem(name, elem1, elem2);
				m_elements[count] = myElem;
				//myElem.m_name = ;
				count++;
				}
				myFile.close();
			}
       


}

void Game::DisplayElements()
{

	Element elem;
	for(int i = 0; i < PROJ2_SIZE; i++)
	{

		elem = m_myAlchemist.GetElement(i);
		//cout << elem.m_name;
		if(elem.m_name != "")
		{
			cout << i+1 << ".) " << elem.m_name << endl;
		}
	}
	cout << endl;
}

void Game::CombineElements()
{
	cout << "Here is what you can combine" << endl;
	DisplayElements();
	cout << endl;
	int useChoice1 = 0;
	int useChoice2 = 0;
	int size = 0;
	for(int i = 0; i < PROJ2_SIZE; i++)
	{
		Element elem = m_myAlchemist.GetElement(i);
		if(elem.m_name != "")
		{
			size += 1;
		}
	}
	useChoice1 = getInput(size, -1);
	RequestElement(useChoice1);
	cout << "Now Choose your second element" << endl;
	DisplayElements();
	useChoice2 = getInput(size, -1);
	RequestElement(useChoice2);
	//cout << m_myAlchemist.GetElement(useChoice1 - 1).m_name <<  " " << m_myAlchemist.GetElement(useChoice2 - 1).m_name << endl;
	int bigboiNew = SearchRecipes(m_myAlchemist.GetElement(useChoice1 - 1).m_name, m_myAlchemist.GetElement(useChoice2 - 1).m_name);
	//cout << bigboiNew << endl;
	cout << endl;
	if(bigboiNew != - 1)
	{
		Element newElem = m_elements[bigboiNew];
		cout << "**You have created " << newElem.m_name << " **" << endl;
		m_myAlchemist.AddElement(newElem);
	}
	m_myAlchemist.AddAttempt();

}
int Game::SearchRecipes(string elem1, string elem2)
{
	for(int i = 0; i < PROJ2_SIZE; i++)
	{
		Element elem = m_elements[i];
		//cout << elem.m_name << endl;
		if(elem.m_element1 == elem1)
		{
			//cout << "found a matching element for " << elem.m_name << endl;
			if(elem.m_element2 == elem2)
			{
				//cout << "found a second matching element for" << elem.m_name << endl;
				return i;
			}
		}
	}
	cout << "Invalid combo" << endl;
	return -1;

}

void Game::CalcScore()
{
	int count = 0;
	cout << "here is your progress: " << endl;
	for(int i = 0; i < PROJ2_SIZE; i ++)
	{
		Element elem = m_myAlchemist.GetElement(i);
		for(int z = 0; z < PROJ2_SIZE; z++)
		{
			if(elem.m_name == m_elements[z].m_name)
			{
			  //      			  cout << "found matching element: " << elem.m_name << endl;
				count += 1;
			}
		}
	}
	//cout << count;
	double tote = double(count) / double(PROJ2_SIZE);
	cout << "After " << m_myAlchemist.GetAttempts() << " Attempts" << endl;
	cout << "you have discovered: " << count<< " /390 elements "<< endl;
	cout << "with " << m_myAlchemist.GetRepeats() << " repeats" << endl;
	cout <<  "you are " << setprecision(2) << tote * 100 << "% of the way there!" << endl;
	cout << endl;
}

