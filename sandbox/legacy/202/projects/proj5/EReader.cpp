//|=======================================================
//| EReader.cpp
//|
//|Created on: Apr 24, 2019
//| Author: kyle
//| Desc: EReader driver, does the big moves like displaying book lists, loading in the proper data throwing into the main menu, and then using a bubble sort method to sort through the data
//|=======================================================







#include <iostream>
#include "EReader.h"
using namespace std;

//default constructor, nothing special here
EReader::EReader()
{

}
//overloaded constuctor, passes in the filename then loads the elements from the specified filename
EReader::EReader(string filename)
{
  LoadCatalog(filename);
  //debug stuff, if you really want, uncomment out the code, to help you test out the sorting function, you can choose from a predefined set, that is as unorganized as I can make it, and just in case, the option to generate a random list with 40 books in it
  /*
  
	int choice = 0;
	LoadCatalog(filename);
	cout << "predefined or rand?" << endl;
	cout << "1.) pre" << endl;
	cout << "2.) rand" << endl;
	cin >> choice;
	if(choice == 1)
	{
	m_readList.Push(*m_bookCatalog[3], 1);
	m_readList.Push(*m_bookCatalog[4], 1);
	m_readList.Push(*m_bookCatalog[1], 1);
	m_readList.Push(*m_bookCatalog[0], 1);
	m_readList.Push(*m_bookCatalog[22], 1);
	m_readList.Push(*m_bookCatalog[27], 1);
	m_readList.Push(*m_bookCatalog[81], 1);
	m_readList.Push(*m_bookCatalog[80], 1);
	m_readList.Push(*m_bookCatalog[90], 1);
	}
	else
	{
		srand(time(0));
		for(int i = 0; i < 40; i++)
		{
			int random = rand()% 150 + 0;
			m_readList.Push(*m_bookCatalog[random], 1);
		}
	}
  */

}

//destructor, really just here to go through the BookCatalog, and delete the entries, 
EReader::~EReader()
{
  // m_readList.~Lqueue();
	for(long unsigned int i = 0; i < m_bookCatalog.size(); i++)
	{
		delete m_bookCatalog.at(i);
		//m_bookCatalog.at(i) = NULL;
	}
}

//load catalog
//uses my patented and foolproof method of opening the file once to get the number of lines, and hten reopening the file to read through each line, storing the data as needed and dummy values, for things like newline characters, stores the data in a new book object, and then places that sucker in the vector, bookCatalog
void EReader::LoadCatalog(string fileName)
{
	ifstream myFile;
		myFile.open(fileName);
		string line = "null";
		string title;
		string author;
		int rank;
		double price;
		string dum;
		int size = 0;
		while(getline(myFile, line, '\n'))
		{
			//cout << line << endl;
			size ++;
		}
		myFile.close();
		myFile.open(fileName);

		int count = 0;
	string comma1;
	while(myFile.is_open())
	{
		while(count < size)
		{
				getline(myFile, title, ',');
				//cout << "got title " << endl;
				getline(myFile, author, ',');
				//cout << "got author" << endl;
				myFile >> rank;
				//cout << "got rank" << endl;
				getline(myFile, comma1, ',');
				//cout << "stored waste comma" << endl;
				myFile >> price;
				//cout << "got price" << endl;
				getline(myFile, dum, '\n');
				//cout << title << " , " << author <<  " , " << rank << " , " << price << endl;
				Book *newBook = new Book(title, author, rank, price);
				m_bookCatalog.push_back(newBook);
				count ++;


			}

		myFile.close();
		}


}
//the main menu
//just uses a switch case nested in while loop for lazy levels of input validation, and calls the approriate function when called upon
void EReader::MainMenu()
{
	bool contin = true;
		while(contin == true)
		{
			cout << "What would you like to do?" << endl;
			cout << "1.) Display all books" << endl;
			cout << "2.) Add new book to read list" << endl;
			cout << "3.) Display read list" << endl;
			cout << "4.) Sort read list by price" << endl;
			cout << "5.) Exit" << endl;
			int choice;
			cin >> choice;
			cout << endl;
			switch(choice)
			{
				case 1: choice = 1;
				{
					DisplayBooks();

				}
				break;
				case 2: choice = 2;
				{
					AddBook();

				}
				break;

				case 3: choice = 3;
				{
					DisplayReadlist();

				}
				break;

				case 4: choice = 4;
				{
					SortReadlist();
				}
				break;

				case 5: choice = 5;
				{
					contin = false;
				}
				break;
			}
		}
}

//display books
//formats the entry of data behind each entry in bookCatalog, and displays it
void EReader::DisplayBooks()
{
  cout << setw(50) << left << "Title" << setw(25) << left << "Author" << setw(19) << left <<  "Price" << endl;
  cout << "----------------------------------------------------------------------------------------------------" << endl;
	for(long unsigned int i = 0; i < m_bookCatalog.size(); i++)
	{
		Book *booker = m_bookCatalog.at(i);
		cout << i + 1 << ".) " << setw(45) << left << booker->getTitle() << setw(25) << left << booker->getAuthor() << setw(1) << left << "($" << fixed << setprecision(2) << double(booker->getPrice()) << ")" << endl;
	}
	cout << endl;
}
//add book
//just asks the user for a choice from the book catalog and then pushes that entry into the linked list
void EReader::AddBook()
{
	int choice;
	cout << "enter the number of the book you'd like to add to your reading list " << endl;
	DisplayBooks();
	cout << "Which book would you like to add?: ";
	cin >> choice;
 cout << endl;
	int actualChoice = choice - 1;
	m_readList.Push(*m_bookCatalog.at(actualChoice), 1);

}
//display readlist
//does the same thing as display books, but know its with the linked list M_readlist, can use either the disaply function or the overloaded << operator
void EReader::DisplayReadlist()
{
  cout << "Your Read list is as follows" << endl;
  cout << setw(50) << left << "Title" << setw(25) << left << "Author" << setw(19) << left <<  "Price" << endl;
  cout << "----------------------------------------------------------------------------------------------------" << endl;
  cout << m_readList;
  //uncomment this if you want to test the display function
  //m_readList.Display();
	cout << endl;
}
//sort readlist
//uses the swap function to bubble sort each entry until the list is finally sorted
void EReader::SortReadlist()
{
	bool continSort = true;
	//Book *temp = m_readList.Front();
	cout << endl;
	//if you have entries that arent sorted, we must continue to sort
	while(continSort == true)
	{
	  //set it to false for reasons down below
		continSort = false;
		//grab an entry from the read list
		for(int i = 0; i < m_readList.GetSize() ; i++)
		{
		  //now compare it to the next entry, but only if the next entry exists

			if(i+1 <= m_readList.GetSize()-1)
			{
			  //do the comparison
				if(m_readList[i].getPrice() < m_readList[i+1].getPrice())
				{
					//cout << m_readList[i].getPrice() << " is greater in price than " << m_readList[i+1].getPrice() << endl;
				  //swap if its lower
					m_readList.Swap(i+1);
				}

			}

		}
		//after we have sorted that one entry we loop through the list to see if there are any out of order entries, if there are, then we set the boolean to true, and start over again, i understand this isnt the most efficient implementation of a bubble sort, but im dumb :)
		for(int i = 0; i < m_readList.GetSize(); i++)
		{
		  //check to make sure the entry exists
			if(i+1 <= m_readList.GetSize()-1)
			{
				if(m_readList[i].getPrice() < m_readList[i+1].getPrice())
				{
					continSort = true;
				}
			}
		}
	}
	cout << "***List has been sorted***" << endl;


}
