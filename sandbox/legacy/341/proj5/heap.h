// CMSC 341 - Fall 2019 - Project 5
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;

 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;

 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.

  // *********************************************
  // Private helper function declarations go here!
  // *********************************************
  void heapMoveBU(int);
  void heapMoveUB(int);
  void genericFill(int);
  void clear();
  Heap<T> get(int pos);

};

// ***************************************
// Templated function definitions go here!
// ***************************************

//standard constructor, fills the [0] index with a dummy value
template <class T>
Heap<T>::Heap()
{
	T temp;
	_heap.push_back(temp);
	_used = false;
}

//a maxheap insert, add it to the end of the list, then swap up until we satisfy the max heap property 
template <class T>
void Heap<T>::insert(const T& object)
{
	_heap.push_back(object);
	_used = true;
	heapMoveBU(size());


}
//the reheap helper function
template <class T>
void Heap<T>::heapMoveBU(int index)
{
	int parent = (index)/2;
	//cout << parent << endl;
	//base case, if we end up at the top, we are done, or if we satisfy the max heap property
	if(parent < 1 || _heap.at(parent).priority() >= _heap.at(index).priority())
	{

		return;
	}
	//if the current index has a greater priority than its parent, we swap the two
	if(_heap.at(index).priority() > _heap.at(parent).priority())
	{
		T temp = _heap.at(parent);
		_heap.at(parent) = _heap.at(index);
		_heap.at(index) = temp;
		index = parent;
		heapMoveBU(index);
	}
	//safety net
	else
		return;
}

//return the top
template <class T>
T Heap<T>::readTop() const
{
  T dummy;
  if(empty())
    {
      throw std::range_error("empty set");
      return dummy;
    }
  return _heap.at(1);
}

//remove the top by swapping the top element and the last element, then deleting the last element (Which is now the top element) we then re heap from the top moving down
template <class T>
void Heap<T>::removeTop()
{
       if(empty())
	 {
	   throw std::range_error("empty set");
	   return;
	 }
	if(_heap.size() == 2)
	{
		
		_heap.pop_back();
		return;
	}
	T root = _heap.at(1);
	T last = _heap.at(_heap.size()-1);
	_heap.at(1) = last;
	_heap.at(_heap.size()-1) = root;
	_heap.pop_back();
	heapMoveUB(1);
}

//the reheap helper function
//start from the top, check left, if there is a discrepency, move left, then check right, if discrepency in the right, swap and move right 
template <class T>
void Heap<T>::heapMoveUB(int index)
{
     
	unsigned int left = (index * 2);
	unsigned int right = (index *2) + 1;
	//stop if we reach the end of the list
	if(left > size() || right > size())
		return;
	//also stop if we satisfy the heap property
	if(_heap.at(index).priority() > _heap.at(right).priority() && _heap.at(index).priority() > _heap.at(left).priority())
		{

			return;
		}
	//if left tree produces a discrepency, swap left and move left
	if(_heap.at(left).priority() > _heap.at(index).priority())
	{

		T temp = _heap.at(index);
		_heap.at(index) = _heap.at(left);
		_heap.at(left) = temp;
		heapMoveUB(left);
	}
	//if right produces a discrepency, swap and move right
	if(_heap.at(right).priority() > _heap.at(index).priority())
		{

			T temp = _heap.at(index);
			_heap.at(index) = _heap.at(right);
			_heap.at(right) = temp;
			heapMoveUB(right);
		}


}

//print out the entires in the list
template <class T>
void Heap<T>::dump() const
{

	for(long unsigned int i = 1; i < _heap.size(); i++)
	{
		cout << "	heap entry " << i << " is " << _heap.at(i) << endl;
	}
}


//ignore all of this
//used almost exclusively for the initialization of the hash table


//this function is only used by the hash table
template <class T>
Heap<T> Heap<T>::get(int pos)
{
	return _heap.at(pos);
}

template <class T>
void Heap<T>::clear()
{
  while(empty() == false)
    {
      removeTop();
    }
}
#endif
