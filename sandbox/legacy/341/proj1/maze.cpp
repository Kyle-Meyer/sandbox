//|=======================================================
//| maze.cpp
//|
//|Created on: Sep 11, 2019
//| Author: kyle
//| Desc: put whatever you want here
//|=======================================================

#include <stdexcept>
#include "maze.h"

Maze::Maze(int ncell) {
  if (ncell < 1) {
    throw std::invalid_argument("Maze::Maze(): ncell must be >= 1");
  }

  _ncell = ncell;
  _maze = new cell_t[_ncell];
}

Maze::~Maze() {
  //simply deletes the _maze array and sets ncell to 0
  delete [] _maze;
  _ncell = 0;
}

void Maze::readFile(std::string fileName) {
  int numCells;
  int cell, n1, n2, n3, n4;
  std::ifstream dataFile;

  dataFile.open(fileName);

  if (dataFile.is_open()) {
    dataFile >> numCells;
    this->reset(numCells);

    for (int i = 0; i < numCells; i++) {
      dataFile >> cell >> n1 >> n2 >> n3 >> n4;
      this->insert(cell_t(cell, n1, n2, n3, n4));
    }
  }
}

int Maze::getNcell() const {
  return _ncell;
}

void Maze::reset(int ncell) {
  if (ncell < 1) {
    throw std::invalid_argument("Maze::reset(): ncell must be >= 1");
  }

  if (_maze != nullptr) {
    delete [] _maze;
  }

  _ncell = ncell;
  _maze = new cell_t[_ncell];
}

void Maze::insert(cell_t cell) {
  if (_maze == nullptr) {
    throw std::domain_error("Maze::insert(): attempt to insert into uninitialized Maze object");
  }
  if (cell.cellNum < 0 || cell.cellNum >= _ncell) {
    throw std::invalid_argument("Maze:insert(): invalid cell number");
  }
  _maze[cell.cellNum] = cell;
}

cell_t Maze::retrieve(int nc) const {
  if (_maze == nullptr) {
    throw std::domain_error("Maze::retrieve(): attempt to retrieve from an uninitialized Maze object");
  }
  if (nc < 0 || nc >= _ncell) {
    throw std::invalid_argument("Maze:retrieve(): invalid cell index");
  }

  return _maze[nc];
}

void Maze::dump() const {

  std::cout << "[*] Dumping the maze cells..." << std::endl;
  for (int i = 0; i < _ncell; i++) {
    int nc = _maze[i].cellNum;
    int nb = _maze[i].neighbors[0];

    if (nc != i) {
      std::cerr << "Warning: maze cell at index " << i
		<<" has cellNum of " << nc << std::endl;
    }
    std::cout << "Cell " << i << " has neighbor cells: ";
    neighbor_t nbs = _maze[i].neighbors;
    int n0, n1, n2, n3;
    if ( nbs[0] >= 0 ) std::cout << nbs[0] << " ";
    if ( nbs[1] >= 0 ) std::cout << nbs[1] << " ";
    if ( nbs[2] >= 0 ) std::cout << nbs[2] << " ";
    if ( nbs[3] >= 0 ) std::cout << nbs[3] << " ";
    std::cout << std::endl;
  }
}
//ignore this, all for debug
/*
bool Maze::deadEnd(const cell_t cell)
{
	SolveStack stk;
	std::vector<int> temp = cell.neighbors;

	int size = 0;
	for(int i = 0; i < temp.size(); i++)
	{
		if(temp[i] == stk.read().first)
		{
			std::cout << temp[i] << " was already on the stack so ignoring" << std::endl;


		}
		else
		{
			size ++;
		}


	}
	std::cout << "entry " << cell.cellNum << " had " << size << " actual neighbors" << std::endl;
	if(size < 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Maze::setNeighbors(int pos)
{

}
*/

std::vector<int> Maze::solve() const {
  // IMPLEMENT THE SOLVE METHOD
  //variable intilization
  SolveStack stk;
	src_dest_t bi(_maze[0].cellNum, _maze[0].neighbors[0]);
	stk.push(bi);
	//	stk.printStack();
	std::cout << "attempting to solve maze " << std::endl;
	std::vector<int> win;
	win.push_back(bi.first);
	bool done = false;
	bool begin = true;
	//while not done, keep searching through the maze
	while(done == false)
	{
	  //grab the top most stack item, first enry was already pushed on
		src_dest_t stackCurr = stk.read();
		//std::cout << "on node " << stackCurr.first << " moving to its neighbor " << stackCurr.second << std::endl;
		//iterate through the list of maze cells until we find the one that is related to the top most stack
		for(int i = 1; i < _ncell; i++)
		{

			if(_maze[i].cellNum == stackCurr.second)
			{
				//std::cout << "scanning through " << stackCurr.second << " 's neighbors" << std::endl;
				//std::cout << _maze[i].neighbors.size() << std::endl;
			  //create a new list of neighbors that arent -1 and already on the stack
				std::vector<int> neihbs;
				for(int z = 0; z < _maze[i].neighbors.size(); z++)
				{

					if(_maze[i].neighbors[z] != -1 && _maze[i].neighbors[z] != stackCurr.first)
					{
						neihbs.push_back(_maze[i].neighbors[z]);


					}





				}
				// after grabbing the new neigbors, throw the first one onto the stack as a valid move
				if(neihbs.size() > 0)
				{
					src_dest_t cc(_maze[i].cellNum, neihbs[0]);
					win.push_back(cc.first);
					stk.push(cc);

				}
				//if there are no more "real" neighbors, then this must be a dead end, so we find the maze cell before this entry and set the neighbor to -1 as it is now a dead end, we then pop off the entry from the stack and remove the entry from the winning vector list, we also incorporate a bit of game theory to help us determine if a maze is unsolvable, the moment we pop something off the stack, we are no longer at the beggining of the maze, meaning we cant generate a lose as soon as we enter the loop, so we set a flag to false which will be used further down to determine when the maze has no solution
				else
				{
					//std::cout << "there were no more neighbors, at " << stackCurr.second << std::endl;
				  //setting the previous entries neighbor to -1
					for(int m = 0; m < _ncell; m++)
					{
						if(_maze[m].cellNum == stackCurr.first)
						{
							for(int k = 0; k < _maze[m].neighbors.size(); k++)
							{
								if(_maze[m].neighbors[k] == stackCurr.second)
								{
									_maze[m].neighbors[k] = -1;

									//std::cout << " set " << stackCurr.first << "'s neighbor " << stackCurr.second << " to -1" << std::endl;

								}
							}
						}
					}
					//removing the entry from the win list and popping off stack
					int iter = 0;
					for(int y = 0; y < win.size(); y++)
					{
						iter++;
					}
					win.erase(win.begin()+(iter -1));
					begin = false;
					stk.pop();

				}

			}

		}
		//if we encounter the last cell on the stack, then we have won, so we end the while loop and push the winning vector set
		int act = stk.read().second;
		if(act == _ncell-1)
		{
		  //std::cout << "you have won, ending" << std::endl;
			win.push_back(stk.read().second);
			done = true;;
		}
		//the lose condition, once the begin flag is set false from the pop function above, and we have no more entries left in our winning vector, then we must also have no more entries in the stack, meaning the first entry must have been declared as a dead end, meaning the maze is unsolveable, in which case we pass back an empty vector
		if(begin == false)
		{
			if(win.size() == 0)
			{
				std::cout << "this maze is not solveable " << std::endl;
				//std::cout << stackCurr.first << std::end
				return win;
				done = true;
			}

		}
		//std::cout << "******* on num iteration " << num << " **********" << std::endl;
		//std::cout << std::endl;
		//num ++;
	}

	//stk.printStack();
	std::cout << "the maze has been solved, output as follows  " << std::endl;
	return win;

}
/*
void Maze::SolveStack::printStack()
{
	int num = 0;
	StackEntry *looper = _stack;
	if(looper == NULL)
	{
		std::cout << "stack is empty" << std::endl;
	}
	while(looper != NULL)
	{
		std::cout << "entry " << num << " contains " << looper->src_dest.first << " , " << looper->src_dest.second << std::endl;

		num ++;
		looper = looper->next;
	}

}
*/
Maze::SolveStack::SolveStack() {
  _stack = nullptr;

}

Maze::SolveStack::~SolveStack() {
  // IMPLEMENT DESTRUCTOR
  //  std::cout <<"destructor called" << std::endl;
  //check to see if the stack is empty
  if(_stack == nullptr)
    {
      std::cout << "nothing to delete, list is empty" << std::endl;
    }
  else
    {
      //simply go throuhg the whole linked list, deleting each node we come across
	StackEntry *temp = _stack;
	while (temp != NULL)
	{
		StackEntry *old = temp;
		//		std::cout << old->src_dest.first << std::endl;
		temp = temp->next;
		delete old;
		//		old->next = nullptr;
	}
    }
}

bool Maze::SolveStack::empty() const {
  //if the beggining is nullptr, then we have an empty list
  if(_stack == nullptr)
  {
	  return true;
	  
  }
  return false;
}


void Maze::SolveStack::push(src_dest_t src_dest) {
	StackEntry * temp = new StackEntry(src_dest);
	StackEntry *looper = _stack;
	//if the list was empty, default the current entry as the head
	if(empty() == true)
	{
		//std::cout << "stack was empty, initializing the head" << std::endl;
		_stack = temp;
	}
	else
	{
	  //used to calculate the size of the list
		int num = 1;
		while(looper->next != NULL)
		{
			num ++;
			looper = looper->next;
		}
		//std::cout << num;
		//if we have only one entry, stick it on the end, simple
		if(num == 1)
		{
			//std::cout << " list has element of one, defualting tail to current entry" << std::endl;
			_stack->next = temp;
		}
		else
		{
		  //iterate through the list until we encounter the last element, when that happens, we tack on the current entry to the end, by setting the last element's next pointer to the new entrt that was just made
			looper =_stack;
			while(looper->next != NULL)
			{
				StackEntry *old = looper;
				looper = looper->next;
				//std::cout << "encountered the end of the stack the previous node was " << old->src_dest.first << " the ending node is " << looper->src_dest.first << std::endl;
			}
			looper->next = temp;
		}
	}
}

src_dest_t Maze::SolveStack::pop() {
  // IMPLEMENT POP METHOD
	StackEntry *curr = _stack;
	StackEntry *old = curr;
	//check to see if there is only one element, if there is, simply return that element so it can be destroyed by the destructor at the end of program
	if(curr->next == NULL)
	  {
	    //std::cout << "size of 1" << std::endl;
	    // delete curr;
	    //	    curr = nullptr;
	    src_dest_t burner(-1,-1);
	  	    return curr->src_dest;
	  }
	else
	  {
	    //iterate through until the end, and destroy the last element, returning the new last element in the process
	    while(curr->next != NULL)
	      {
		old = curr;
		curr = curr->next;
	      }
	delete curr;
	old->next = nullptr;
	return old->src_dest;
	  }
}

src_dest_t Maze::SolveStack::read() const {
  // IMPLEMENT READ METHOD
  //same deal as pop, but instead of deleting the last element, we iterate to the end, and simply return the last entry 
	StackEntry *curr = _stack;
		StackEntry *old = curr;
		while(curr->next != NULL)
		{
			old = curr;
			curr = curr->next;
		}
		return curr->src_dest;
}
