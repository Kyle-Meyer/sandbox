//|=======================================================
//| Alchemist.cpp
//|
//|Created on: Mar 5, 2019
//| Author: kyle
//| Desc: put whatever you want here
//|=======================================================













#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "Alchemist.h"
#include "Game.h"
using namespace std;

Alchemist::Alchemist()
{

}

string Alchemist::GetName()
{
	return m_myName;
}
void Alchemist::SetName(string name)
{
	string name1;
	cout << "what would you like to be known as? ";
	getline(cin, name1);
	m_myName = name1;
	//cout << "element at pos 1 should be Fire, at pos 1 we have: " << m_myElements[1].m_name << endl;
}
void Alchemist::AddElement(Element elem)
{
	bool flag = true;
	for(int i = 0; i < PROJ2_SIZE; i++)
	{

		if (elem.m_name == m_myElements[i].m_name)
		{
			flag = false;
		}


		if(flag == false)
		{
			cout << "this element is already known " << endl;
			AddRepeat();
			break;

		}
		else
		{
			if(m_myElements[i].m_name == "")
			{
				//m_myElements[i] = {elem.m_name, elem.m_element1, elem.m_element2};
				m_myElements[i].m_name = elem.m_name;
				m_myElements[i].m_element1 = elem.m_element1;
				m_myElements[i].m_element2 = elem.m_element2;
				//cout << "placed " << elem.m_name << " at " << i << endl;
				break;

			}
		}
	}

}

Element Alchemist::GetElement(int posit)
{
	/*
	cout << "supposed to be grabbing elements"  << posit << endl;
	cout << "Testing to see that myElements is populated:" << endl;
	for(int i = 0; i < PROJ2_SIZE; i++)
	{
		if(m_myElements[i].m_name != "")
		{
			cout << m_myElements[i].m_name << endl;
		}
	}
	cout << m_myElements[posit].m_name;
	*/
	return m_myElements[posit];


}

void Alchemist::AddAttempt()
{
	m_attempts += 1;

}

int Alchemist::GetAttempts()
{
	return m_attempts;
}
void Alchemist::AddRepeat()
{
	m_repeats += 1;

}
int Alchemist::GetRepeats()
{
	return m_repeats;
}

