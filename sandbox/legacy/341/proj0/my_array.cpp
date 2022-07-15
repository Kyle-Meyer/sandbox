#include <iostream>
#include <stdexcept>
#include "my_array.h"

using namespace std;

// Default constructor (size has default value of 1; see .h file)
my_array::my_array( unsigned int size ) {
  if (size < 1) {
    throw range_error("my_array(): array must have at least one element");
  }
  m_data = new int[size];
  m_size = size;
}

// Default destructor, deletes the data behind the m_data pointer and sets size to 0
my_array::~my_array()
{
  /*
	for(unsigned int i = 0; i < m_size; i++)
	  {
	    delete m_data[i];
	  }
  */
	delete [] m_data;
	m_size = 0;
}

// Overloaded assignment operator, literally the exact same thing as
// the copy constructor except now we have a manual check in the beggining to make sure
// that the overwritten target is empty before we allocate any data
my_array& my_array::operator = (const my_array& obj)
{
		int len = obj.size();
		int oldlen = m_size;
		if( oldlen > 0)
		{
		  //cout << "there was data here so delete now" << endl;
			delete [] m_data;
			m_size = 0;
		}
		m_data = new int[len];
		m_size = len;
		if ( len < 1 ) {
			    throw range_error("my_array(): input data must have at least one element");
			 }
		for (int i = 0; i < len; i++) {
		    m_data[i] = obj.m_data[i];
		  }
		return *this;
}

// implicit constructor, populates a dynamic array with integers
my_array::my_array(int* data, int len) {

  // if data array is empty, throw range_error exception
  if ( len < 1 ) {
    throw range_error("my_array(): input data must have at least one element");
  }

  m_data = new int[len];
  m_size = len;

  // copy data to m_data
  for (int i = 0; i < len; i++) {
    m_data[i] = data[i];
  }
}

/* Copy constructor, takes in the object array and copies its data into a new dyanmically allocated
array, doesnt need to do a memory check since the object will always be new
 */
my_array::my_array(const my_array& obj)
{
	int len = obj.size();
	m_data = new int[len];
	m_size = len;
	if ( len < 1 ) {
		    throw range_error("my_array(): input data must have at least one element");
		 }
	for (int i = 0; i < len; i++) {
	    m_data[i] = obj.m_data[i];
	  }
}

//size function, returns size
int my_array::size() const { return m_size; }

int& my_array::at(unsigned int indx) {
  if (indx >= m_size) {
    throw range_error("at(): index is out-of-range");
  }
  return m_data[indx];
}

