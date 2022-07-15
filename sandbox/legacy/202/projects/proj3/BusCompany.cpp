//|=======================================================
//| BusCompany.cpp
//|
//|Created on: Mar 29, 2019
//| Author: kyle
//| Desc: The buscompany driver for buscompany.h the two  big things it does is generate the main menu, and read in the data from the text files, then it calls either display route or optimize route from route.cpp be warned, when running valgrind there are a ton of error messages, I dont know whats causing all of them but there are no memory leaks i hope that doesnt detract from my grade
//|=======================================================








#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include<vector>
#include <cmath>
#include "BusCompany.h"
using namespace std;

//constructor, sets newRoute, ignore the commented out code, that was for debugging in my IDE
BusCompany::BusCompany()
{
		/*
	cout << "1 - test1" << endl;
	cout << "2 - test2" << endl;
	cout << "3 - test3" << endl;
	int choice = 0;
	cin >> choice;
	if(choice == 1)
	{
		BusCompany("test1.txt");
	}
	if(choice == 2)
	{
		BusCompany("test2.txt");
	}
	if(choice == 3)
	{
		BusCompany("test3.txt");
	}
	*/
	//Buscompany(fileName);
	
}
//the overloaded constructor which reads in the data from the text file and then calls the main menu
BusCompany::BusCompany(string fileName)
{
  
   
	m_newRoute = new Route;
	ReadFile(fileName);
	cout << endl;
	cout << endl;
	cout << "*****************************" << endl;
	MainMenu();
	cout << "thank you for using the Route optimizer" << endl;
  
	/*
	 
		
  	Route rout;
	rout.InsertAt("Park Rd. & Poplar Ave.",1, 605 , 635);
	rout.InsertAt("Rolling Rd @ Valley Rd (CCBC)", 5, 238, 550);
	rout.InsertAt("Mellor Ave & Frederick Rd", 8,145,560);
	rout.InsertAt("Harlem La & Edmondson Ave", 11, 163, 569);
	rout.InsertAt("St. Agnes La & Harwall Rd",15,82,489);
	rout.InsertAt("Ingleside Ave & Craigmont Rd",18,105,625);
	rout.InsertAt("Bloomsbury Ave. & Holmes Ave.",	22,	120,385);
	rout.InsertAt("Hilltop Cir. & Hilltop Rd.",	26,	385,	755);
	rout.InsertAt("Park Rd. & Poplar Ave.",	30,	126,	610);
	rout.InsertAt("Fent", 12, 5, 12.0);
	rout.InsertAt("Fifth", 4, 5, 1200.0);
	//rout.RemoveStop(0);
	rout.DisplayRoute();
	//cout << "break" << endl;
	rout.optimizeroute1(3.25);
	rout.DisplayRoute();
	//rout.RemoveStop(3);
	//rout.OptimizeRoute(3.25);
	//rout.DisplayRoute();
	//rout.DisplayStopData(3.5);
	rout.Clear();
	cout << "route should have been deleted calling display to make sure" << endl;
	rout.DisplayRoute();
	*/
}
//the deconstructor, systematically goes through the vector of routes and clears them by calling their destructors, then sets each one to null
//also does this for m_newroute just in case there was data left in that pointer
BusCompany::~BusCompany()
{
  
  m_newRoute->~Route();
	for(long unsigned int i = 0; i < m_routes.size(); i++)
	{
	  m_routes[i]->~Route();
		delete m_routes[i];
	       
	}
		delete m_newRoute;

  

}

/*The read file
takes in the name of the text file and then passes through it once looking for the total number of lines
closes the file
then reopens it but with the intent of reading in actual data, as it reads it in, it passes the data to the insert function
and will automatically generate a new route when it hits the key phrase "end route" and will push the current route into the vector
then closes the file
 */
void BusCompany::ReadFile(string fileName)
{
	//fileName = "test1.txt";
	ifstream myFile;
	myFile.open(fileName);
	string name = "null";
	int location = 0;
	int riders = 0;
	string line;
	double cost = 0.0;
	int size = 0;
	//cout << "attempting to open file" << endl;
	//debug
	if(myFile.is_open())
	{
	  //cout << "file is open" << endl;
	}
	//first instance of opening the file, needed to find the number of lines
	while(getline(myFile, line, '\n'))
	{

		size ++;


	}
	int count = 0;
	myFile.close();
	//dummy inputs
	string dummy1, dummy2;
	myFile.open(fileName);
	int totalRoute = 0;
	//while loop to cycle through the file, then through the number of lines and grab
	//the necessary data, while using dummy inputs, to ignore things like new lines;
	while(myFile.is_open())
	{
		while(count < size)
		{
			//cout << "on line " << count << endl;
			getline(myFile, name, ',');
			//check to see if end of route, push to stack if so, then make new route
			if(name == "End Route")
			{
			  totalRoute++;
			  //cout << "any trues XD";
				getline(myFile, dummy2, '\n');
				m_routes.push_back(m_newRoute);
				//cout << "hit end route " << m_routes.size();
				cout << "Route " << totalRoute << " loaded with " << m_newRoute->GetSize() << " Stops" << endl;
				m_newRoute = new Route;
			}
			//otherwise keep reading in values then inserting them into the route
			else
			{
				myFile >> location;
				myFile >> riders;
				myFile >> cost;
				getline(myFile, dummy2, '\n');
				m_newRoute->InsertAt(name, location, riders, cost);
			}

			//cout << name << " " << location << " " <<  riders << " " <<  cost << " " <<  endl;

			count ++;
		}
		size = m_newRoute->GetSize();
		//throws away the route if its empty
		if(size > 0)
		  m_routes.push_back(m_newRoute);
		myFile.close();
	}
	m_newRoute->Clear();
       
	//cout << location << endl;
}

/* Display route
simply iterate through a for loop the size of the vector and display the stops behind each entry in the vector
returns nothing
 */
void BusCompany::DisplayRoutes()
{
	for(long unsigned int i =0; i < m_routes.size(); i++)
	{
		cout << "**Route " << i+1 << endl;
		//the switch between the two display methods uncomment out the below line if you want to test the display function
		//m_routes[i]->DisplayRoute();
		cout << *m_routes[i] << endl;
	}
	cout << endl;
}
/* Display route data
uses another unsigned long int for loop to call the DisplayStopData for each entry in the vector
returns nothing 
*/
void BusCompany::DisplayRouteData()
{
	for(long unsigned int i =0; i < m_routes.size(); i++)
		{
			cout << "** Route " << i+1 << "**" << endl;
			m_routes[i]->DisplayStopData(RIDER_FARE);
		}
}
/*optimize route
again goes through the vector and calls optimize route for each entry
returns nothing
 */
void BusCompany::OptimizeRoute()
{
  
  bool boyo = true;
  vector<long unsigned int> choices;
  cout << endl;
  if(m_routes.size() > 1)
    {
      while(boyo == true)
	{
	  if(choices.size() >= m_routes.size())
	    {
	      boyo = false;
	    }
	  cout << "Which route would you like to optomize? " << endl;
	  for(long unsigned int z = 0; z < m_routes.size() ; z++)
	    {
	      cout << "Route " << z+1 << endl;
	    }
	  cout << "Enter 1 - " << m_routes.size() << " inclusive(enter a number outside of this range to exit): ";
	  long unsigned int choice;
	  cin >> choice;
	  cout << endl;
	  if(choice <= m_routes.size() && choice >= 1)
	    {
	      long unsigned int quickChoice  = choice - 1;
	      cout << endl;
	      cout <<  "Optomizing route " << choice << "..." << endl;
	      m_routes[quickChoice]->OptimizeRoute(RIDER_FARE);
	      boyo = false;
	    }
	}
    }
  //cout << "optimizing route ..." << endl;
  else
    {
  
  for(long unsigned int i =0; i < m_routes.size(); i++)
      {
		m_routes[i]->OptimizeRoute(RIDER_FARE);
		cout << "route " << i+1 << " has been optimized" << endl;
	}
      }

}
/* main menu
the main menu that uses a switch statement nested in a while loop to keep track of users input and then execute the corresponding function
returns nothing
 */
void BusCompany::MainMenu()
{
	bool cont = true;
	cout << "welcome to the route optimizer tool " << endl;
	while(cont == true)
	{
		cout << "What would you like to do?:" << endl;
		cout << "1. Display Routes" << endl;
		cout << "2. Display Earnings vs Expenses By Route" << endl;
		cout << "3. Optimize Routes" << endl;
		cout << "4. Exit" << endl;
		int choice = 0;
		cin >> choice;
		switch(choice)
		{
			case 1: choice = 1;
			{
				DisplayRoutes();

			}
			break;
			case 2: choice = 2;
			{
				DisplayRouteData();

			}
			break;

			case 3: choice = 3;
			{
				OptimizeRoute();

			}
			break;

			case 4: choice = 4;
			{
				cont = false;
			}
		}

	}
}
