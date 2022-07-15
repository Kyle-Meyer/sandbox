
// CMSC 341 - Fall 2019 - Project 3
// File: treap.cpp

using namespace std ;

#include "treap.h"

Treap::Treap() {
  _nptr = nullptr ;
}

Treap::Treap(const Treap& other) {
  //
  // Implement copy constructor
  //
  // set the _nptr to null so it wont point to outside data
  _nptr = nullptr;
  //create a temporary variable that points to the same place as the original tree, in hindsight I could pass other._nptr, but I really want to make sure that I dont overwrite the original nptr
  TreapNode * temp = other._nptr;
  //call the helper function to copy all data
  copy(temp);
   
}
void Treap::copy(TreapNode * node)
{
  //pretty straight forward, do a pre order traversal to make sure we insert from the top most nodes to the bottom most using the standard nullptr check to see if we made it to the end, since insert handles the creation of new nodes, we can just re-use it to help us create deep copies
  if(node != nullptr)
    {
     

      insert(node->_data, node->_pri);
   
      copy(node->_left.getRoot());
      copy(node->_right.getRoot());
    }
}
Treap::~Treap() {
  //
  // Implementdestructor
  //
  //call the iterative destructor, the reason I made this its own function was because
  // A.) i will need it for the assignment operator

  // B.) I wasnt allowed to modify the TreapNode destructor
  clear(_nptr);
}

void Treap::clear(TreapNode * temp)
{
  //check to see if our passed variable even exists, was supposed to be a check against empty trees, but I realized that the way my remove is setup there can be no empty trees
  //done using a post order traversal method
  if(temp)
    {
      //make sure our left tree exists
      if(temp->_left.getRoot())
	//iterative call left
	clear(temp->_left.getRoot());
      //make sure our right tree exists
      if(temp->_right.getRoot())
	//iterative call right
	clear(temp->_right.getRoot());
      //the actual deletion, making sure our left and right pointers aren't "dangling", then deleting the node itself
      temp->_left.setRoot(nullptr);
      temp->_right.setRoot(nullptr);
      delete temp;

   
    }
}
const Treap& Treap::operator=(const Treap& rhs) {
  //
  // Implement assignment operator
  //
  //check to see if we have any previous data, if so, clear it out
  if(this->_nptr != NULL)
    {
      clear(this->_nptr);
      
    }
  //set the nptr to null, more of a habit than anything
  _nptr = nullptr;
  //make a temp variable pointing to the target _nptr
  TreapNode * temp = rhs._nptr;
  //copy it over
  copy(temp);
  return *this;
}

// Return -1 if the treap is empty; otherwise, return value in _height.
int Treap::height() const {
  return _nptr ? _nptr->_height : -1 ;
}

// Return the priority of the root node of a Treap.
// Note: numeric_limits<priority_t>::min() returns the minimum value
// of the priority type.  We will only use int priorities, so this is
// the minimum integer value.
priority_t Treap::priority() const {
  return _nptr ? _nptr->_pri : numeric_limits<priority_t>::min() ;
}
//corect height function uses the code already provided in the insert function
void Treap::correctHeight(TreapNode * node)
{
        int leftHeight = node->_left.height();
	int rightHeight = node->_right.height();
	node->_height = 1 + ( leftHeight > rightHeight ? leftHeight : rightHeight );
	
}
const data_t* Treap::find(const data_t& x) {
  //
  // Implement find function
  //
    

  //if our data is found or is null return, our base case
  
		if ( _nptr == nullptr || _nptr->_data == x)
		{
			if(_nptr != nullptr)
			{
				
				return &_nptr->_data;
			}
		}



		//standard traversal going right first, then left
		if(_nptr->_data < x)
		{
			return _nptr->_right.find(x);
		}
	     
		return _nptr->_left.find(x);






}

// Inorder traversal.  Recommend you NOT change this!!!(I didnt)
void Treap::inorder() {

  if ( empty() )
    {
      return;
    }

  cout << "(" ;
  _nptr->_left.inorder() ;

  cout << _nptr->_data << ":" << priority() << ":" << height() ;

  _nptr->_right.inorder() ;
  cout << ")" ;

  return  ;
}

void Treap::postorder ()
{
	if ( empty() ) return ;

	  cout << "(" ;
	  _nptr->_left.inorder() ;

	  _nptr->_right.inorder() ;
	  	  cout << ")" ;

	  cout << _nptr->_data << ":" << priority() << ":" << height() ;



	  return  ;
}

void Treap::preorder()
{
	//stop if root is empty
	if ( empty() ) return ;


	//root
	 cout << _nptr->_data << ":" << priority() << ":" << height() ;
	 //go left
	 cout << "(" ;
	 _nptr->_left.inorder() ;
	  //go right
	 _nptr->_right.inorder() ;
	 cout << ")" ;





	  return  ;
}

// Used for debugging and grading.  Interprets the characters in
// position[] as directions in the tree.  E.g., "RLR" means, "starting
// from root, go right, then left, then right."  If position[] is an
// empty string, then it just locats the value a the root.
// See project description for details.
bool Treap::locate (const char position[], data_t& x, priority_t& p, int& h, int offset) {

  if (_nptr == nullptr) return false ;

  if (position[offset] == '\0') {
    x = _nptr->_data ;
    p = _nptr->_pri ;
    h = _nptr->_height ;
    return true ;
  }

  if (position[offset] == 'L') {
    return _nptr->_left.locate(position, x, p, h, offset+1) ;
  }

  if (position[offset] == 'R') {
    return _nptr->_right.locate(position, x, p, h, offset+1) ;
  }

  cerr << "Bad position character!\n" ;
  exit(17) ;

  return false ;
}


// Basic BST insertion.  Does not allow duplicate values.
//
// Complete this function to do Treap insertion.
//
void Treap::insert(const data_t& x, const priority_t& p) {
  if ( empty() ) {

    //put the node at the end
	  _nptr = new TreapNode(x, p) ;
     
  }
  
  //right traversal
  if (_nptr->_data < x) {

    _nptr->_right.insert(x, p) ;
    //if we inserted right, then we can only ever rotate left, so we preform a check to see if the parent priority is less than the child priority, if so preform a left rotate
    if(_nptr->_pri < p)
        {
	  
	  //the only way I could get my rotates to work is if they returned the altered pointers, I dont know why
	        _nptr = _nptr->_right.rotateLeft(_nptr);
	   
        }


  }

  //left traversal
  else if (x < _nptr->_data )
    {
      _nptr->_left.insert(x, p) ;
      //if we insert left, we can only ever rotate right
      if(_nptr->_pri < p)
	{
	  //rotate and set the _nptr
	  _nptr = _nptr->_left.rotateRight(_nptr);
      
	}
    }


  // Update height. Maybe this should be a helper function??
  int leftHeight = _nptr->_left.height();
  int rightHeight = _nptr->_right.height();
  int offset = 0;
  _nptr->_height = 1 + ( leftHeight > rightHeight ? leftHeight : rightHeight ) - offset;
 

}

//rotate left, the algorithm is that the left node of the rotated child will become the new right child of the parent, and the parent will become the left child of the rotated node
TreapNode* Treap::rotateLeft(TreapNode* node)
{

        //get the rotated child
        TreapNode * y = node->_right.getRoot();
	//get the left child of the rotating node
	TreapNode * x = y->_left.getRoot();
	//set the left root of the rotating node to the original node
	y->_left.setRoot(node);
	//set the right root of the parent node to the left child of the rotating node
	node->_right.setRoot(x);
	//fix the height of the parent node
	correctHeight(node);
	//make the rotated node the new parent
	node = y;
	return node;
     
}

//the same exact function as rotate left but we reverse it, so now the right child of rotating node becomes the left child of the old parent, and the parent becomes the right child of the rotating node
TreapNode* Treap::rotateRight(TreapNode* node)
{
	TreapNode * y = node->_left.getRoot();
        TreapNode * x = y->_right.getRoot();
        y->_right.setRoot(node); 
        node->_left.setRoot(x);
	correctHeight(node);
        node = y;
	return node;
}
//helper function to set the root of the current _nptr
void Treap::setRoot(TreapNode* node)
{
	_nptr = node;
}
//helper function to get the current nptr
TreapNode* Treap::getRoot()
{
	return _nptr;
}


//this gets weird fast, but here is my layout currently for this function
//
//       --Check case 1--: our node is a leaf, we do this by checking the parents children
//
//       --Fail Case--: we reached the end of our tree without encountering the data
//
//       --Traversal Methods -- : left first, right next
//
//
//       --Check Case 2 -- : our node has one leaf, so we swap the parent and the child
//
//       --Check Case 3 -- : our node has two children, compare their priorities and then swap between whoever has the greatest priority
//
bool Treap::remove(const data_t& x) {
  //
  // Implement treap element removal
  //
  //
  // Implement treap element removal
  //
       
  //our base case, if we ever encoutner a null _Nptr, it means we reached the end of the tree without ever fidning our value, so we return false
	if(_nptr == NULL) return false;

	//the first check for if we have a leafnode, the first if statement is a bound check so we wont segfault trying to do the following checks
	if(_nptr->_right._nptr)
	  {
	    //if our right child contains the data we are looking for
	    if(_nptr->_right._nptr->_data == x)
	      {
	       
		TreapNode * temp = _nptr->_right.getRoot();
		//if our found data is a leaf node
		if(temp->_left.getRoot() == NULL && temp->_right.getRoot() == NULL)
		  {
		 
		    _nptr->_right.setRoot(nullptr);
		    delete temp;
		    correctHeight(_nptr);
		    return true;
		  }
       
	  }
	 }
	//if our left child contains the data we are looking for
	//bound check
	if(_nptr->_left._nptr)
	  {
	    //compare against our data
	    if(_nptr->_left._nptr->_data == x)
	      {
		TreapNode * temp = _nptr->_left.getRoot();
		//if its a leaf node
		if(temp->_left.getRoot() == NULL && temp->_right.getRoot() == NULL)
		  {
		    //cut off the pointer to this data
		    _nptr->_left.setRoot(nullptr);
		    //delete the data
		    delete temp;
		    correctHeight(_nptr);
		    return true;
	       
		  }
	      }
	  }
	//traversal methods
     
	if(x <_nptr->_data)
		_nptr->_left.remove(x);
	else if (x > _nptr->_data)
		_nptr->_right.remove(x);
	 //if our element is found and has only one child, in this case on the right, all we have to do is shift our node up, we achieve this by copying the data into a temp, then preforming our standard deletion, then replacing the previously deleted node, with the copied node
	else if(_nptr->_left.getRoot() == NULL && _nptr->_right.getRoot() != NULL)
	{
	  
		TreapNode * temp = _nptr->_right.getRoot();
		_nptr->_left.setRoot(nullptr);
                _nptr->_right.setRoot(nullptr);
		delete _nptr;
		_nptr = temp;
		correctHeight(_nptr);
		return true;
	}
	//if our element is found and has only one child, in this case on the left, all we have to do is shift our node up, we achieve this by copying the data into a temp, then preforming our standard deletion, then replacing the previously deleted node, with the copied node
	else if(_nptr->_right.getRoot() == NULL && _nptr->_left.getRoot() != NULL)
	{
    
		TreapNode *temp = _nptr->_left.getRoot();
		_nptr->_left.setRoot(nullptr);
		_nptr->_right.setRoot(nullptr);
		delete _nptr;
		_nptr = temp;
		correctHeight(_nptr);
		return true;
	}
 
	//if the object is found but we have two non null children
	//if our left priority is lower, we rotate the right child up and switch it with our found element
	else if(_nptr->_left.priority() < _nptr->_right.priority())
	{
	       
		_nptr = _nptr->_right.rotateLeft(_nptr);

		_nptr->_left.remove(x);
	}
	//if our left priority is higher, we rotate it up and replace it with the found node
	else if(_nptr->_right.priority() < _nptr->_left.priority())
		{
		     
			_nptr = _nptr->_left.rotateRight(_nptr);
		   
			_nptr->_right.remove(x);
		}
	return true;
}



// Treap::dump() just calls TreapNode::dump()
void Treap::dump() {
  if ( !empty() )
	  {


	  	  _nptr->dump();


	  }
}

ostream& operator<< (ostream& os, const Treap& T) {
  os << T._nptr ;
  return os ;
}


TreapNode::TreapNode() : _height(0) {
  // Empty constructor body
}

TreapNode::TreapNode(const data_t& x, const priority_t& p)
  : _data(x), _pri(p), _height(0) {
  // Empty constructor body
}

TreapNode::~TreapNode() {
  // Empty destructor
  // Retained for debugging
}

// Dump the contents of a node
void TreapNode::dump() {
  cout << "===== TreapNode::dump()\n" ;
  cout << "      this = " << this << endl ;
  cout << "      left = " << _left << endl ;
  cout << "      right= " << _right << endl ;
  cout << "      data = " << _data << endl ;
  cout << "      height = " << _height << endl ;
  _left.dump() ;
  _right.dump() ;
}
