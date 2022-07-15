//|=======================================================
//| Book.cpp
//|
//|Created on: Apr 23, 2019
//| Author: kyle
//| Desc: Basic stuff for the book object, just really here for setting values and getting values
//|=======================================================








#include <iostream>
#include "Book.h"
using namespace std;

//basic constructor, does nothing really
Book::Book()
{

}

//overloaded constructor, sets the appropriate variables, like title, author, rank, price
Book::Book(string title, string author, int rank,  double price)
{
	m_title = title;
	m_author = author;
	m_rank = rank;
	m_price = price;
}
//getter for title
string Book::getTitle()const
{
	return m_title;
}
//getter for author
string Book::getAuthor()const
{
	return m_author;
}
//getter for price
double Book::getPrice()const
{
	return m_price;
}
//getter for rank
int Book::getRank()const
{
	 //cout << "you shouldnt be needing this " << endl;
	 return m_rank;
}
//setter for author
void Book::setAuthor(string author)
{
	m_author = author;
}
//setter for title
void Book::setTitle(string title)
{
	m_title = title;
}
//setter for rank
void Book::setRank(int rank)
{
	m_rank = rank;
}
//setter for price
void Book::setPrice(double price)
{
	m_price = price;
}
//overloaded extraction operator
//outputs data in an ordered fashion
ostream& operator << (ostream& output, Book& bookObj)
{
	output << setw(45) << left << bookObj.getTitle() << setw(25) << left << bookObj.getAuthor() << setw(1) << left << "($" << fixed << setprecision(2) << double(bookObj.getPrice()) << ")";
	return output;
}
//overloaded comparison operator
//returns true if book 1 has a lower price than book2
//otherwise it will return false
bool operator < (Book const & lhs, Book const & rhs)
{
	if(lhs.getPrice() < rhs.getPrice())
	{
		return true;
	}
	else
	{
		return false;
	}
}
