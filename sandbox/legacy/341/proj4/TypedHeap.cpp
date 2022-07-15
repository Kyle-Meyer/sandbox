using namespace std;

#include "TypedHeap.h"


//insert to heap function, O(n^2) complexity because of the fact that we have to check each character to identify if the string is an int, converts the necessary strings to integers then inserts them into their respective heap
void TypedHeap::insertToHeaps(vector<string> vec)
{
  //for loop to parse the vector
  for(long unsigned int i = 0; i < vec.size() ; i++)
    {
      //used to identify digits
      bool isDig = true;
      //loop to parse each entry 
      for(long unsigned int y = 0; y < vec.at(i).size(); y++)
	{
	  //the moment it encounters a non digit we can stop checking and move on
	  if(isdigit(vec.at(i).at(y)) == false)
	    {
	      isDig = false;
	      break;
	    }
	}
      //insert to int heap if its a digit
      if(isDig == true)
	{
  
	  intHeap.insert(stoi(vec.at(i)));
	}
      //otherwise insert it to the string heap
      else
	{
	  stringHeap.insert(vec.at(i));
	}
    
    }
}

//just call the dump heap of each of the heaps so long as they exist
void TypedHeap::printHeaps() const
{
  cout << endl;
  cout << "int heap holds: " << endl;
  if(intHeap.empty() == false)
    {
    
      intHeap.dump();
     
    }
  else
    cout << "nothing " << endl;
  cout << endl;
  cout << "string heap holds: " << endl;
  if(stringHeap.empty() == false)
    {
     
      stringHeap.dump();
    
    }
  else
    cout << "nothing " << endl;
  cout << endl;
  cout << "total holds: " << endl;
  if(totalHeap.empty() == false)
    {
  
      totalHeap.dump();
      
    }
  else
    cout << "nothing " << endl;
}

//if the heap exists, change its priority by calling setPriFn
void TypedHeap::changePriority(pri_fn pri)
{
  if(intHeap.empty() == false)
    intHeap.setPriFn(pri);
  if(stringHeap.empty() == false)
    stringHeap.setPriFn(pri);
  if(totalHeap.empty() == false)
    totalHeap.setPriFn(pri);
}

//combine all the heaps into total heap, then set the int heap and the string heap to null
void TypedHeap::combineHeaps()
{
  SkewHeap temp(intHeap);
  SkewHeap empty(intHeap.getPriFn());
  temp.skewHeapMerge(stringHeap);
  totalHeap = temp;
  intHeap = empty;
  stringHeap = empty;
 
}
