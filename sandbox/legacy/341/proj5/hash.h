// CMSC 341 - Fall 2019 - Project 5
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"


using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;

 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions

  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions

  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;

 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps
  bool probe(unsigned int index, string key);

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************

};
//dont know why i even bother, I spend hours coding these projects and then the tests claim my program is just going to seg fault because of some random constraint that i never knew existed, like a seg fault because of data overflow, which shouldnt be possible, but Marron insits that im a brainlet

//regular constructor sets the proper values and such
template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash)
{
	_N = size;
	_n = 0;
	_hash = hash;
	_table = new Heap<T>[_N];
       

}
//copy constructor, sets the approriate values then steps through linearlly and copies each value
template <class T>
HashTable<T>::HashTable(const HashTable<T>& ht)
{
	_N = ht.tableSize();
	_n = ht.numEntries();
	_hash = ht._hash;
	_table = new Heap<T>[_N];
	for(unsigned int i = 0; i < _N; i++)
	{
		_table[i] = ht._table[i];
	}
	
}
//destructor, checks to make sure that the deleting target is not empty, then deletes
template <class T>
HashTable<T>::~HashTable()
{
  if(_n != 0)
    {
      delete[] _table;
    }
}
//overloaded assignment operator, checks to make sure that the target is empty before copying
template <class T>
const HashTable<T>& HashTable<T>:: operator=(const HashTable<T>& ht)
{
  bool same = true;
  //asignment guard check
  if(this == &ht)
    return *this;
  //if they arent the same, copy over
      if(same == false)
	{
	  //delete old content
	  if(_n != 0)
	    {
	      delete[] _table;
	    }
	  _N = ht.tableSize();
	  _n = ht.numEntries();
	  _hash = ht._hash;
	  _table = new Heap<T>[_N];
	  //copy new contnet
	  for(unsigned int i = 0; i < _N; i++)
	    {
	      _table[i] = ht._table[i];
	    }
	}
      return *this;
    
}

//insert function, if the target area is empty, then insert, if the bucket is filled and the key is different, then probe
template <class T>
bool HashTable<T>::insert(const T& object)
{
	unsigned int index = _hash(object.key()) % _N;
	unsigned int oldIndex =  _hash(object.key()) % _N;
	  //insert if empty adn unused
	if(_table[index].empty()== true && _table[index].used() == false)
	{
	       

 
		_table[index].insert(object);
		_n += 1;
		return true;
	}
	//if we find an empty spot that has been used we should parse the whole table to see if we can find a matching instance, if we dont find a matching istance, than we insert it to the original empty position
	if(_table[index].empty() == true && _table[index].used() == true)
	  {
	    bool probe = true;
			unsigned int offset = 0;
			while(probe == true)
			{
				offset += 1;
				if((offset + index) > _N-1)
				{
					offset = 0;
					index = 0;
				}
				if(_table[index + offset].empty() == false)
				  {
				if(_table[index + offset].readTop().key() == object.key())
				{
				       
				  _table[index + offset].insert(object);
				    probe = false;
				    return true;
				}
				  }
				if(offset + index == oldIndex)
				{
					
				  _table[oldIndex].insert(object);
				  return true;
				}
			}
	  }
	//bound check
	if(_table[index].empty() == false)
	  {
	    //the keys match
	    if(_table[index].readTop().key() == object.key())
	      {
		cout << "keys matched" << endl;
		_table[index].insert(object);
                _n += 1;
                return true;
	      }
	    //if we have mismatching keys
	    if(_table[index].readTop().key() != object.key())
		{
		  cout << "keyes did not match" << endl;
			bool probe = true;
			unsigned int offset = 0;
			//probe loop for unused buckets first
			while(probe == true)
			  {
			    offset += 1;
                                //start at the beggining of the table if we reach the end                                     
                                if((offset + index) > _N-1)
                                {
                                        offset = 0;
                                        index = 0;
                                }
                                //insert when we find an empty spot                                                           
                                if(_table[index + offset].empty() || _table[index +offset].readTop().key() == object.key())
                                {


                                        _table[index + offset].insert(object);
                                        _n += 1;
                                        probe = false;
                                        return true;
                                }
                                //if we do a full loop and end up where we started then we have a full table and throw an error message                                                                                                                                                // note this is only possible after our index is set to 0                                     
                                if(offset + index == oldIndex)
                                {
                                  cout << "table too large" << endl;
				  return false;
                                }
		       
			  }

		}

	
	  }
       
	      
	
	//if we somehow get to this point then that means we have exhausted all possible options for insertion and we shouldnt be able to insert
	return false;
}

// standard dump function, iteratively move through the table and dump each entry
template <class T>
void HashTable<T>::dump() const
{
	//HashTable<T> temp = new HashTable<T> ;
	for(unsigned int i = 0; i < tableSize(); i++)
	{

		cout << "[" << i <<"]: " << endl;

		_table[i].dump();
	}
}

//get next, we work on 3 possible scenarios
//1 the indexed position is filled and has our key
//2 the inedexd position is filled but the keys dont match, probe
//3 the indexed position is not filled but was used in the past, probe
template <class T>
bool HashTable<T>::getNext(string key, T& object)
{
      
	unsigned int index = _hash(key) % _N;
	unsigned int oldIndex = _hash(key) % _N;
  
	//bound check to make sure we arent trying to access null elements
	if(_table[index].empty() == false)
	{
	  //if our keys match up, set object, decrement _n remove it from the list
	   if(_table[index].readTop().key() == key)
          {
          
            object = _table[index].readTop();
            _table[index].removeTop();
            _n = _n - 1;
            return true;
          }
	   //if our keys dont match up, we probe
	   else if(_table[index].readTop().key() != key)
		{
		 
		  bool probe = true;
		  unsigned int offset = 0;
		  //probe loop same as insert probe loop, should probably be its own function but I had to make some modifications to it
		  while(probe == true)
		   {
					offset += 1;
					if((offset + index) > _N-1)
                                        {
                                                offset = 0;
                                                index = 0;
                                        }
				     
					 //if we come across an empty slot that hasnt been used then we can stop searching as it means that the searched for value never existed in the table, or if we end up where we started, then it never existed                                                                       
                                        if(_table[index + offset].used() == false || index + offset == oldIndex)
                                        {
					 
                                                return false;
                                        }
					//if we have an empty slot that was used, skip over it
					if(_table[index + offset].empty() == true)
						break;
				        
					//if we find our key, read it and pop it off
					if(_table[index + offset].readTop().key() == key)
					{
						
						object = _table[index + offset].readTop();

						_table[index + offset].removeTop();
						
						_n = _n - 1;
						
						return true;
					}
				   
				}
		}
	       
		       
			

	}
	//if our indexed position is empty but has been used in the past
	else if(_table[index].used() == true)
	{
	  
		bool probe = true;
			unsigned int offset = 0;
			//probe loop
			while(probe == true)
			{
				offset += 1;
				 if((offset + index) > _N-1)
                                  {
                                      offset = 0;
                                      index = 0;
                                  }
				//again if we encounter an unused slot, or end up back where we started then we are done, the element never existed                                                                                                       
                                if(_table[index + offset].used() == false || index + offset == oldIndex)
                                {
                                        return false;
                                }
				//skip over the empty position IFF its been filled at one point
				if(_table[index + offset].empty() == true)
	       
					break;
			       
				//preform necessary operations when we find the element
				if(_table[index + offset].readTop().key() == key)
				{
					
					object = _table[index + offset].readTop();
					_table[index + offset].removeTop();
					_n = _n - 1;
					return true;
				}
			      
			}
	}
	//if we end up with an empty index that has never been used, return false
      return false;


}


// *****************************************
// Templated function definitions go here! *
// *****************************************

#endif
