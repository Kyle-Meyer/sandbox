//|=======================================================
//| Route.cpp
//|
//|Created on: Mar 25, 2019
//| Author: kyle meyer
//| Desc: driver for route.h, defines routes, organizes data then stores them as stops
//|		  also deletes the stops within a route
//|=======================================================




#include <string>
#include <iostream>
#include <iomanip>
#include<vector>
#include <cmath>
#include "Route.h"
using namespace std;

//these are experimental functions that I explain down below


//constructor, sets m_start to null and m_size to 0 for each new route
Route::Route()
{
	m_start = NULL;
	m_size = 0;

}
//deconstructor, calls the clear function to empty a list of stops
Route::~Route()
{
	Clear();

}

ostream& operator<<(ostream &output, Route &myRoute)
{
	Stop *temp = myRoute.m_start;
	long unsigned int count = 0;
	while(temp != NULL)
	{
	  output << "Stop " << count+1 << " - " << temp->m_name << "(" <<temp->m_location << ")"<< endl;
		temp = temp->m_next;
		count ++;
	}
	return output;
}
//InsertAt
//first generates the new stop
//then runs through a series of if statments to determine where the new stop should
//be inserted based on the new stops location
void Route::InsertAt(string name, int location, int riders, double cost)
{
	// create the new stop and placeholders for traversing
	Stop *newStop = new Stop;
	Stop *prev;
	Stop *curr;
	//allocate data to new node
	newStop->m_name = name;
	newStop->m_riders = riders;
	newStop->m_cost = cost;
	newStop->m_location = location;
	newStop->m_next= m_start;
	m_size++;

	int size = GetSize();
	//cout << count << endl;



	int tempPos = 0;   // counter to go through list

	curr = m_start;      // Initialize current to head;
	//cout << "going to add" << newStop->m_name;
	//checks to see if the head is there, if it isnt, then the entry gets defaulted to the new head
	if(m_start != NULL)
	{

		//debugging stuff ignore this
		

		//boolean value to help determine index position;
		bool bunt = false;
		//iterate through the list to find position of where the entry should go
		while(curr->m_next != NULL && bunt == false)
	    {
			//set pointer the current entry
	        prev = curr;
	        //set pointer to the next entry
	        curr = curr->m_next;

	        //pinpointing index position based on location value
	        if(location <= curr->m_location && location >= prev->m_location)
	        {
	        	bunt = true;

	        }
	        //increment the index position
	        tempPos++;

	        //debug
	        //cout << "**" << endl;
	        //cout << newStop->m_name << endl;
	        //cout << prev->m_name << " " <<  curr->m_name << endl;
	        //cout << tempPos << endl;
	    }

		//checks to see if there is only a head, if so then it allocates the next entry as a tail
		if(size == 1)
		{
			//cout << "adding a tail cuz there isnt one" << endl;
			if(location > curr->m_location)
			{
				curr->m_next = newStop;
				newStop->m_next = NULL;
			}
			else
			{
				m_start = newStop;
			}
		}
		//add entry as the head
		else if(tempPos == 0 || location == 1)
	    {

	       m_start = newStop;

	    }

		//add as tail
	    else if(location > curr->m_location)
	    {
	      curr->m_next = newStop;
	      newStop->m_next = NULL;



	    }
		//add in a certain location
	    else
	    {
	    		prev->m_next = newStop;
	    		newStop->m_next = curr;
	    		//cout << "Node added at position: " << tempPos << " between " << prev->m_location << " and " << curr->m_location << endl;

	    }
	 }
	//default to new head if list is empty
	 else
	 {
		newStop->m_next = m_start;
	    m_start = newStop;

	 }
       

}
//display route function, simple while loop that falls off if the node points to NULL
void Route::DisplayRoute()
{
	Stop *temp;
	temp = m_start;
	int count = 0;
	while(temp != NULL)
	{
		count ++;
		cout << "Stop " << count << " - " << temp->m_name << "(" << temp->m_location << ")" << endl;
		temp = temp->m_next;
	}

}

//is empty function, just checks if the head points to null
bool Route::IsEmpty()
{
	if(m_start == NULL)
	{
		return true;
	}
	return false;
}

//Get size iterates through the list incrementing a counter for every entry that does not point to null then returns the counter
int Route::GetSize()
{
	int count = 0;
	Stop *temp = m_start;
	while(temp != NULL)
	{
		count ++;
		temp = temp->m_next;
	}
	return count;

}

//Get route earnings, again iterates until node points to null, grabs the total number of riders at each node, and then multiplies it by the rider fare, then adds that to a total count
double Route::GetRouteEarnings(double riderFare)
{
	Stop *temp;
	temp = m_start;
	double total = 0;
	while(temp != NULL)
	{
		int ride = temp->m_riders;
		double currEarn = 0;
		currEarn = double(ride) * double(riderFare);
		total += currEarn;
		temp = temp->m_next;

	}
	return total;

}
//get route expenses works identically to get route earnings, but now adds up the total number of costs at each node
double Route::GetRouteExpenses()
{
	Stop *temp;
	temp = m_start;
	double expense = 0.0;
	while(temp != NULL)
	{
		expense += temp->m_cost;
		temp = temp->m_next;
	}
	return expense;

}
/* this is a test function, its designed to handle remove stop but takes in the location of the node
 * rather than the index location, i found that for the most part it achieves the same goal in a very similar manner
 */
void Route::removeStop1(int stopLocation)
{
   
	Stop *curr;
	Stop *prev;
	curr = m_start;
	bool bull = false;
	cout << stopLocation << endl;
	if(curr != NULL)
	{
		while(curr->m_next != NULL && bull == false)
		{
			prev = curr;
			curr = curr->m_next;
			if(curr->m_location == stopLocation)
			{
				bull = true;
			}
		}
		//cout << "curr is " << curr->m_name << " and prev is " << prev->m_name << endl;
		if(stopLocation == 1)
		{
			m_start = curr->m_next;
			delete curr;
		}
		else if(stopLocation > curr->m_location)
		{
			prev->m_next = NULL;
			delete curr;
		}

		else
		{
			prev->m_next = curr->m_next;
			delete curr;
		}
	}

}
/*this is also a test function, works in tandem with removestop1
 * passes stop location rather than index value
 */
void Route::optimizeroute1(double riderFare)
{
	Stop *temp = m_start;
	int count = 0;
	int totalRemove =0;
	while(temp!= NULL)
	{
		//cout << "on stop " << temp->m_name << "which should has count " << count << endl;
		double earn = double(temp->m_riders) * riderFare;
		if(earn < temp->m_cost)
		{
			//cout << "removed stop " << temp->m_name << "since it was only earning " << earn << " but cost " << temp->m_cost << endl;
			removeStop1(temp->m_location);
			totalRemove++;
			count = 0;
			temp = m_start;
		}
		else
		{
			temp = temp->m_next;
			count++;
		}


	}
	cout << "*** a total of " << totalRemove << " stops have been removed from this route *** " << endl;
}



//Removestop, works in a similar fashion to insertat
//finds the index location of the stop that needs to be removed and does so
//setting the prev pointer to point to the next pointer, isolating out the original node
//and then deleting it, if the function finds that the stop location is 0 or the route has a size of 1
//then the list is just a head, or is deleting at the head, so it deletes the head
//should the function fall off while traversing the list, then the tail should be deleted
void Route::RemoveStop(int stopLocation)
{
	Stop *curr;
	Stop *prev;
	curr = m_start;
	int size = GetSize();

	if(curr != NULL)
	{
		int count = 0;

		while(curr->m_next != NULL && count < stopLocation)
		//for(int i = 0; i < stopLocation; i++)
		{
			prev = curr;
			curr = curr->m_next;
			count ++;
			//cout << "am here1" << endl;

		}
		//cout << "curr is " << curr->m_name << " and prev is " << prev->m_name << endl;
		if(stopLocation == 0 || size == 1)
		{
			//cout << "removing head" << endl;
			m_start = curr->m_next;
			delete curr;
		}
		else if(curr->m_next == NULL && stopLocation == count+1)
		{
			//cout << "removing tail" << endl;
			prev->m_next = NULL;
			delete curr;
		}
		else
		{

			//cout << count << endl;
			prev->m_next = curr->m_next;
			delete curr;
			//cout << "removed " << curr->m_name << " at " << count << endl;
		}
	}
}
//the clear function, works by traversing through the list and deleting the stops
//finishes by setting the head to null
void Route::Clear()
{
	Stop *toDelete = m_start;
	while(toDelete != NULL)
	  {
	    Stop *next = toDelete->m_next;
	    delete toDelete;
	    //	    toDelete->m_next = NULL;
	    toDelete = next;
	}
	m_start = NULL;
	toDelete = NULL;
}
/* iterates through the list and finds the stops that have a negative total
 * passes the index location of the stop that has a negative total to
 * removeStop and then starts over to ensure that no node is skipped over
 * after removal
 */
void Route::OptimizeRoute(double riderFare)
{
	Stop *temp = m_start;
	int count = 0;
	int totalRemove =0;
	while(temp!= NULL)
	{
		//cout << "on stop " << temp->m_name << "which should has count " << count << endl;
		double earn = double(temp->m_riders) * riderFare;
		if(earn < temp->m_cost)
		{
			//cout << "removed stop " << temp->m_name << "since it was only earning " << earn << " but cost " << temp->m_cost << endl;
			RemoveStop(count);
			totalRemove++;
			count = 0;
			temp = m_start;
		}
		else
		{
			temp = temp->m_next;
			count ++;
		}


	}
	cout << "*** a total of " << totalRemove << " stops have been removed from this route *** " << endl;
}

/* Display stop data
 * iterates through the list, and displays the expenses vs the cost of each individual stop
 */
void Route::DisplayStopData(double riderFare)
{
	Stop *temp = m_start;
	bool opt = false;
	int count = 0;
	while(temp != NULL)
	{
		double earns = double(temp->m_riders) * riderFare;
		cout << temp->m_name << endl;
		cout << " Earnings -  " << temp->m_riders << " @ " << riderFare << " = " << earns << endl;
		cout << " Expenses - " << temp->m_cost << endl;
		cout << " Total - " << earns - temp->m_cost;
		cout << endl;
		if((double(temp->m_riders) * riderFare) < temp->m_cost)
		{
			opt = true;
			count ++;
		}

		temp = temp->m_next;

	}
	if(opt == true)
	{
		cout << endl;
		cout << "***there are " << count << " stops that are causing a net loss, this route should be optimized ***" << endl;
		cout << endl;
	}

}
