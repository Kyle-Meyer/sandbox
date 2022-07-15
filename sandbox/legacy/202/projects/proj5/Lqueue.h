#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor
  T& GetData(); //Node Data Getter
  void SetData( const T& data ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  T m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}

template <class T>
T& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator= (const Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node.
  //                Requires a Lqueue
  // Postconditions: If the bool = true, adds to front else adds a new node to the
  //                 end of the lqueue.
  void Push(const T&, bool);
  // Name: Pop
  // Preconditions: Lqueue with at least one node.
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();
  // Name: TestHeadTail() (Optional test function)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns the value of the head and the tail (used for main below)
  void TestHeadTail();
  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const Lqueue<U>&);
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement Lqueue here

//default templated constructor, sets correct privates to arbitrary values
template <class T>
Lqueue<T>::Lqueue()
{
	m_head = NULL;
	m_tail = NULL;
	m_size = 0;
}

//templated copy constructor, generates a new head, then moves to the next element, as it moves along the targeted linked list, it will copy the data into a new node, creating a deep copy of the linked list as it moves through the original linked list
template <class T>
Lqueue<T>::Lqueue(const Lqueue &obj)
{
	Node<T> *temp = obj.m_head;
	m_head = new Node<T>(temp->GetData());
	m_tail = NULL;
	m_size = 0;
	m_head->SetData(temp->GetData());
	m_head->SetNext(NULL);
	Node<T> *curr = m_head;
	temp = temp->GetNext();
	while(temp != NULL)
	{
		curr->SetNext(new Node<T>(temp->GetData()));
		curr = curr->GetNext();
		curr->SetData(temp->GetData());
		temp = temp->GetNext();
	}

}
//overloaded = operator, literally the same code and functionality as the copy constructor, but now it has a conditional check at the beggining, where if the original linked list is not empty, then it will have its data deleted and then regenerates a linked list based on the target linked list
template <class T>
Lqueue<T>& Lqueue<T>::operator = (const Lqueue& obj)
{
  //condition to check if the Lqueue is empty, if it isnt, then it will be cleared and have its data copied from the target Lqueue
        bool buddy =IsEmpty();
	if(buddy == false)
	{
		cout << "list was not empty, clearing" << endl;
		Clear();
	}
  
	Node<T> *temp = obj.m_head;
		m_head = new Node<T>(temp->GetData());
		m_tail = NULL;
		m_size = 0;
		m_head->SetData(temp->GetData());
		m_head->SetNext(NULL);
		Node<T> *curr = m_head;
		temp = temp->GetNext();
		while(temp != NULL)
		{
			curr->SetNext(new Node<T>(temp->GetData()));
			curr = curr->GetNext();
			curr->SetData(temp->GetData());
			temp = temp->GetNext();
		}
		return *this;
}
//templated destructor, simply calls the clear function
template <class T>
Lqueue<T>::~Lqueue()
{
	Clear();
}
//templated push function
//generates a new node with the passed in data, then based on the boolean "isStart" will either add the new node to the end or the start of the linked list, by default, isStart being true means that it will actually be added to the end of the list, i got confused when I firt read the function description, hence the reason its called "isStart" and not "isEnd"
template <class T>
void Lqueue<T>::Push(const T &data, bool isStart)
{
	Node<T> *newNode = new Node<T>(data);
	Node<T> *next = m_head;
	newNode->SetData(data);
	int size = GetSize();
	//set the node to the head if the list is empty
	if(size == 0)
	{
		m_head = newNode;
	}
	else
	{
	  //if the bool is false, then we add the new node at the front of the list, and have it point to the original head
		if(isStart == false)
		{
			newNode->SetNext(m_head);
			m_head = newNode;
		}
		else
		{
		  //otherwise we sort through the whole list until we get to the end, and then we make the tail point to the new node, and the new node will point to null
			next = m_head;
			while(next->GetNext() != NULL)
			{
				//cout << "moving, on " << next->GetData() << endl;
				next = next->GetNext();
			}
			//cout << "found last entry, " << next->GetData() << endl;
			next->SetNext(newNode);
			m_tail = newNode;
		}
	}
}

//overloaded index operator
// a function that will return the templated data type of the linked list when given the index position of the data requested
template <class T>
T& Lqueue<T>::operator [](int posit)
{

		Node<T> *temp = m_head;
		int count = 0;
		while(temp != NULL && count < posit)
		{
			temp = temp->GetNext();
			count ++;
		}
		//cout << " temp data was " << temp->GetData() << " at position " << count << endl;
		return temp->GetData();

}


//overloaded << operator
//simply iterate through the list and display the data of each node
template <class U>
ostream& operator<<(ostream &output, const Lqueue<U> &que)
{
	Node<U> *temp = que.m_head;
	int count = 0;
	while(temp != NULL)
	{
		output << count + 1 << ". " << temp->GetData() << endl;
		count ++;
		temp = temp->GetNext();
	}
	return output;
}
//getSize
//simple function to iterate over the linked list and increment a counter with each node, return the counter when the the last node has been reached
template <class T>
int Lqueue<T>::GetSize()
{
	int size = 0;
	Node<T> *next = m_head;
	while(next != NULL)
		{
			size += 1;
			next = next->GetNext();
		}
	return size;
}
//Pop
//simple function to delete the first element of a linked list
template <class T>
T Lqueue<T>::Pop()
{
	int size = GetSize();
	T data;
	if(size == 1)
	{
		cout << "size is 1 so only deleting head" << endl;
		data = m_head->GetData();
		delete m_head;
		m_head = NULL;
	}
	else
	{
		Node<T> *temp = m_head;
		data = temp->GetData();
		m_head = temp->GetNext();
		delete temp;
		temp = NULL;
	}
	return data;
}

//display function
//same functionality as the overloaded << operator, but now its a designated function, iterate over the list, and print the data of each node
template <class T>
void Lqueue<T>::Display()
{
	Node<T> *temp = m_head;
	int count = 0;
	while(temp != NULL)
	{
		cout << count + 1 << ". " << temp->GetData() << endl;
		temp = temp->GetNext();
		count ++;
	}
}
//is Empty
//function to return a bool based on if the linked list is empty, using size, if size is anything greater than 0, then it clearly isnt empty, and will return false
template <class T>
bool Lqueue<T>::IsEmpty()
{
	int size = GetSize();
	if(size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Front
//return the data of the head of the list
template <class T>
T Lqueue<T>::Front()
{
	bool empter = IsEmpty();
	if(empter == true)
	{
		cout << "list is empty nothing to return" << endl;
	}
	else
	{
		return m_head->GetData();
	}
}

//swap
//iterate over the linked list until you reach the desired index position, take the data of the node before and copy it into a dummy variable, set the data of the previous node, to the data of the current node, and then take the dummy variable data and set it to the current node data
template <class T>
void Lqueue<T>::Swap(int posit)
{
	Node<T> *curr = m_head;
	Node<T> *prev;
	int count = 0;
	if(posit == 0)
	{
		cout << "you cant swap the first element dude" << endl;
	}
	else if(posit > GetSize()-1)
	{
		cout << "invalid position, beyond end of stack" << endl;
	}
	else
	{
		while(curr->GetNext() != NULL && count < posit)
		{
			prev = curr;
			curr = curr->GetNext();
		count ++;
		}

		//cout << "the previous entry is " << prev->GetData() << " and the current entry is " << curr->GetData() << endl;
			T copyDat = prev->GetData();
			prev->SetData(curr->GetData());
			curr->SetData(copyDat);

	}
}

//Clear
//iterate over the linked list, and then delete the node as you move through the list
template <class T>
void Lqueue<T>::Clear()
{
	  Node<T> *toDelete = m_head;
	  Node<T> *next;
	  while(toDelete != NULL)
	          {
	            next = toDelete->GetNext();
	            delete toDelete;
	            //need to find a way to set the data of the Node to a null
	            //toDelete->SetNext(nullptr);
	            toDelete = next;
	        }
	        m_head = NULL;
	        m_tail = NULL;
	        toDelete = NULL;
}

//TestHeadTail
//just a function that prints the head and the tail of a linked list
template <class T>
void Lqueue<T>::TestHeadTail()
{
	Node<T> *findHead = m_head;
	Node<T> *temp = m_head;
	Node<T> *findTail;
	int size = GetSize();
	if(size == 1)
	  {
	    cout << "Head is the same as the tail, as there is only one entry, and that is" << findHead->GetData() << endl;
	  }
	else
	  {
	while(temp->GetNext() != NULL)
	{
		temp = temp->GetNext();
	}
	findTail = temp;
	cout << "head is " << findHead->GetData() << " tail is " << findTail->GetData();
	//return findHead, findTail;
	  }
}

//****************************************************************
// To test just Lqueue follow these instructions:
//   1.  mv Lqueue.h Lqueue.cpp
//   2.  Uncomment out int main below
//   3.  make Lqueue
//   4.  ./Lqueue (try valgrind too!)

/*
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Lqueue <int> newLQ1;
  //Push 4 nodes into Lqueue
  newLQ1.Push(10, 1);
  newLQ1.Push(11, 1);
  newLQ1.Push(12, 1);
  newLQ1.Push(13, 1);
  cout << endl;

  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Lqueue <int> newLQ2(newLQ1);
  //Test Overloaded Assignment Operator
  Lqueue <int> newLQ3;
  newLQ3 = newLQ1;
  cout << endl;

  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLQ1" << endl;
  newLQ1.Display();
  cout << "newLQ2" << endl;
  newLQ2.Display();
  cout << "newLQ3" << endl;
  newLQ3.Display();
  cout << "newLQ1" << endl;
  cout << newLQ1;
  cout << "newLQ2" << endl;
  cout << newLQ2;
  cout << "newLQ3" << endl;
  cout << newLQ3;
  cout << endl;

  //Test 4 - Test Front and Pop
  cout << "Test 4 - Front and Pop Running" << endl;
  //Test Front()
  cout << "Testing Front - Output 10" << endl;
  cout << newLQ1.Front() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  cout << endl;

  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newLQ1.GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ1.Clear();
  cout << endl;

  //Test 6 - Test Swap
  cout << "Test 6 - Swap Running" << endl;
  newLQ2.Swap(2);
  cout << "Swap 2 - Should display 10->12->11->13->END" << endl;
  newLQ2.Display();
  //Testing to make sure head and tail point at the correct node
  newLQ2.TestHeadTail();
  cout << "Should display head 10 and tail 13" << endl;
  cout << endl;

  return 0;
}
*/
