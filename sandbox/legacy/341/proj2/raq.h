#ifndef _RAQ_H
#define _RAQ_H

#include <vector>
#include <array>
#include "math.h"

// RAQ Class implements the Dynamic Programming solution

class RAQ {
 public:

  // Create the RAQ object; perform precomputation
  RAQ();
  RAQ(std::vector<float> data);
  ~RAQ();
  friend std::ostream& operator<<(std::ostream& outStream, const std::vector<float>& entry)
  {
	  outStream << "range " << entry[0] << " - " << entry[1] << " has average: " << entry[2] << std::endl;
	  return outStream;
  }
  // ******************************************************
  // **
  // ** IF NEEDED (depends on class variables),
  // **   constructor, destructor, assignment operator
  // **   go here
  // **
  // ******************************************************

  // Query the RAQ for interval [i, j]
  float query(int i, int j) const;
  float calcAvg(int i, int j);
  void fillGrid();

  // Dump the RAQ data structure to stdout
  void dump() const;

 private:
  std::vector<std::vector<float> > grid;
  std::vector<float> data;
  // ******************************************************
  // **
  // **  Define the class variables here
  // **
  // ******************************************************

  // ******************************************************
  // **
  // ** Declare private helper functions here
  // **
  // ******************************************************

};

// BlockRAQ class implements the Block Decomposition solution

class BlockRAQ {
public:
  // Create the BlockRAQ object; perform precomputation
	BlockRAQ();
	~BlockRAQ();
  BlockRAQ(std::vector<float> data);

  // ******************************************************
  // **
  // ** IF NEEDED (depends on class variables),
  // **   constructor, destructor, assignment operator
  // **   go here
  // **
  // ******************************************************

  // Query the BlockRAQ for interval [i, j]
  float query(int i, int j) const;
  std::vector<float> makeBlocks(int i, int j);
  float calcAvg(std::vector<float>) const;
  void genList();
  // Dump the BlockRAQ data structure to stdout
  void dump() const;

 private:
  std::vector<std::vector <float> > blocks;
  std::vector<float> dataT;
  int blockSize;
  // ******************************************************
  // **
  // **  Define the class variables here
  // **
  // ******************************************************

  // ******************************************************
  // **
  // ** Declare private helper functions here
  // **
  // ******************************************************

};


#endif
