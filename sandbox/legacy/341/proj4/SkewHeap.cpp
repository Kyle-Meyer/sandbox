
//SkewHeap.cpp driver

using namespace std;
#include <iomanip>
#include "SkewHeap.h"
#include "TypedHeap.h"

//standard constructor
SkewHeap::SkewHeap(pri_fn pri)
{
  priority = pri;
  m_heap = nullptr;
  size = 0;
}
//copy constructor
SkewHeap::SkewHeap(const SkewHeap& rhs)
{
  //set the values
  priority = rhs.priority;
  m_heap = nullptr;
  size = 0;
  //copy them
  copy(rhs.m_heap, m_heap);
     
}
//overloaded assignment
const SkewHeap& SkewHeap::operator=(const SkewHeap& rhs)
{
  //clear out old data
  if(this->m_heap != NULL)
    {
      clear(this->m_heap);
    }
  //copy over new data
  m_heap = nullptr;
  Node* node = rhs.m_heap;
  copy(node, m_heap);
  return *this;
}

//copy helper function, the algorithm is simple, copy over the node from the tree with data, then as you move left to copy the next node, you also move left in the target tree
Node* SkewHeap::copy(Node* node, Node* org)
{
  //to identify end of tree
  if(node == NULL)
    {
     
      return org;

    }      
  if(node)
    {
      //copy the data
      if(node->tagged_union == ISINT)
	{
	  org = new Node(node->data_int);
	}
      if(node->tagged_union == ISSTRING)
	{
	  org = new Node(node->data_string);
	}
   
    }
  //recursive calls, left then right
  org->left = copy(node->left, org->left);
  org->right = copy(node->right, org->right);
  //cement mheap to make sure the tree is copied correctly
  m_heap = org;
  m_heap->left = org->left;
  m_heap->right = org->right;
  //move back up the tree
  return org;
}

//standard destructor
SkewHeap::~SkewHeap()
{
  if(m_heap)
    clear(m_heap);
 
}

//clear healper function, start from the bottom of the tree and move up deleting things as you find them
void SkewHeap::clear(Node* node)
{
  if(node)
    {
  
        clear(node->left);
        clear(node->right);
      node->left = NULL;
      node->right = NULL;
      delete node;
    }
}

//simple if else to see if the tree is empty or not
bool SkewHeap::empty() const
{
  if(m_heap)
    return false;
  else
    return true;
}

//just returns pri_fn
pri_fn SkewHeap::getPriFn() const
{
  return priority;
}

//insert is like merging a tree of one node to the rest of the tree
//for strings
void SkewHeap::insert(string data)
{
  Node* node = new Node(data);
  m_heap = merge(m_heap, node);
  size ++;
}


//insert is like merging a tree of one node to the rest of the tree            
//for ints
void SkewHeap::insert(int data)
{

  Node* node = new Node(data);
  m_heap = merge(m_heap, node);
  size++;
}

//merge two skewheaps
void SkewHeap::skewHeapMerge(SkewHeap& sh)
{
  //just call merge on the mheap of both trees
  m_heap = merge(this->m_heap, sh.m_heap);
  sh.m_heap = NULL;
  
}

//the merge function as provided by the pseudo code int he project handout
Node* SkewHeap::merge(Node* origin, Node* merger)
{
  
  if(origin == NULL)
    {
     
      return merger;
      
    }
  if(merger == NULL)
    {
     
    return origin;
   
    }
  //make sure p1 has greater priority
  if(priority(origin) <  priority(merger))
    {
      
      swap(origin, merger);
   
    }
  //standard swap
   swap(origin->left, origin->right);
   //recursive call
   origin->left = merge(origin->left, merger);
   //move back up the tree
  return origin;
}

//dump
//make a copy of the tree and then call the helper function
void SkewHeap::dump()const
{
  SkewHeap temp(priority);
  temp = *this;
  temp.dumped(temp.m_heap);
}

//helper function to dump, print the contents of the top of the tree, then remove it to ensure that we are always printing from the top of the tree
void SkewHeap::dumped(Node* node)
{
  //make sure we dont print anything we shouldnt
  if(node == NULL)
    return;
  //print the final node then exit
  if(node->left == NULL && node->right == NULL)
    {
      cout << "node data is: ";
      if(node->tagged_union == ISINT)
	cout << left << setw(20) <<  node->data_int;
      if(node->tagged_union == ISSTRING)
	cout << left << setw(20)  <<  node->data_string;
      cout << right << setw(20) <<"priority: "<< right <<  setw(10) << priority(node) << endl;
      return;
    }

  //print the contents of the top of the tree
  cout << "node data is: ";
  if(node->tagged_union == ISINT)
    cout << left << setw(20) << node->data_int;
  if(node->tagged_union == ISSTRING)
    cout << left << setw(20)  << node->data_string;
  cout << right << setw(20) << "priority: " << right <<  setw(10) <<  priority(node) << endl;

  //remove the top then recursively call the helper function with the new top
  removeTop();
  dumped(m_heap);
  
}

//call the recursive inorder helper function
void SkewHeap::inorder()const
{
  inorderer(m_heap);
  cout << endl;
}

//standard in order print function, setup exactly like it was in project 3
void SkewHeap::inorderer(Node* node) const
{
  if (node == NULL)
    return;
  cout << "(";
  inorderer(node->left);
  if(node->tagged_union == ISINT)
    cout << node->data_int;
  if(node->tagged_union == ISSTRING)
    cout << node->data_string;
  inorderer(node->right);
  cout << ")";
}

//remove top, follow deletion protocol for the current m_heap, then compare the the two children, merge them accordingly
void SkewHeap::removeTop()
{
  //make sure that we wont try to access anything if the tree is empty
  if(m_heap == NULL)
    return;
  //for the comparison
  Node* left = m_heap->left;
  Node* right = m_heap->right;
  //deletion protocol
  m_heap->left = nullptr;
  m_heap->right = nullptr;
  delete m_heap;

  //compare and merge
  if(left > right)
     m_heap =  merge(left, right);
  if(right > left)
    m_heap =  merge(right, left);
}

//set prifn
//make s a copy of the current tree, and a new empty tree with the new priority function, calls the helper function which acts as a copy constructor, copying elements into the new tree, then after that is done, set the current tree to the new tree, and change the priority 
void SkewHeap::setPriFn(pri_fn pri)
{

  SkewHeap newHeap(pri);
  makeHeap(m_heap, &newHeap);
  *this = newHeap;
  priority = pri;
  
}

//helper function for set pri fn, works in a similar fashion to dump, copying the top element then removing it
void SkewHeap::makeHeap(Node* node,SkewHeap* heap)
{
  //copy the final element and return
  if(node->right == NULL && node->left == NULL)
    {

      if(node->tagged_union == ISINT)
	heap->insert(node->data_int);
      if(node->tagged_union == ISSTRING)
	heap->insert(node->data_string);
      return;
    }
  //copy the head
  if(node->tagged_union == ISINT)
    heap->insert(node->data_int);
  if(node->tagged_union == ISSTRING)
    heap->insert(node->data_string);
  //remove the top
  removeTop();
  //recursive call with new top
  makeHeap(m_heap, heap);
}

