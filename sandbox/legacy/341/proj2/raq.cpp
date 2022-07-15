//|=======================================================
//| raq.cpp
//|
//|Created on: Oct 1, 2019
//| Author: kyle
//| Desc: put whatever you want here
//|=======================================================








#include <iostream>
#include <iomanip>
#include "raq.h"
using namespace std;

RAQ::RAQ()
{

}
RAQ::~RAQ()
{

}
RAQ::RAQ(std::vector<float> dataT)
{
	data = dataT;
	fillGrid();
}
//simply returns the flaot index
float RAQ::query(int x, int y) const
{
	for(long unsigned int i = 0; i < grid.size(); i++)
	{
		if(grid[i].at(0) == x && grid[i].at(1) == y)
		{
			return grid[i].at(2);
		}
	}
	return 0;
}

//calculates the average for each index of the grid, and fills the 2d vector with them
void RAQ::fillGrid()
{
	int size = data.size();
	for(int i = 0; i < size; i++)
	{
	  //calculate the average for each entry range, once its calculated create a temporary vector entry of 3, 1st float is the minimum aka the X, 2nd is the end range the Y, and then the final entry is the average, push small vector as an entry into a larger vector
		for(int j = i; j < size; j++)
		{
			float avg = calcAvg(i, j);
			//std::cout << avg << std::endl;
			std::vector<float> entry = {float(i), float(j), avg};
			grid.push_back(entry);
		}
	}
}

//the calc average function, simply calculates the mean for the given "coordinates"
float RAQ::calcAvg(int x, int y)
{
  if(x < 0 || y > int(data.size()))
	{
		cout << "error, out of range " << endl;
		return 0;
	}
	float avg;
	float size = 0;
	float total = 0;
	for(int i = x; i <= y; i++)
	{
		total += data[i];
		size ++;
	}
	avg = float(total) / float(size);
	//std::cout << "the average for cell " << x << " , " << y << " was " << avg << std::endl;
	return avg;
}

//iterates through the grid and prints out the averages at each coordinate
void RAQ::dump() const
{
	//cout << "building RAQ " << endl;
	for(long unsigned int i = 0; i < data.size(); i++)
	{
		for(long unsigned int j = 0; j < grid.size(); j++)
		{
			if(i == grid[j].at(0))
			{
				cout << setw(10) << left << grid[j].at(2);
			}
		}
		cout << " " << endl;
	}
}

//default constructor
BlockRAQ::BlockRAQ()
{
	blockSize = 0;
}
//default destructor
BlockRAQ::~BlockRAQ()
{

}
//overloaded constructor
BlockRAQ::BlockRAQ(vector<float> data)
{
	dataT = data;
	genList();
}

//creates the blocks that will be used for finding the average
void BlockRAQ::genList()
{
	int blockSizer = 0;
	int num = 1;
	//calculate the size of each block
	blockSizer = sqrt(dataT.size());
	//std::cout << blockSizer << std::endl;
	blockSize = blockSizer;
	//generate smaller vectors which are the blocks, push them to a larger list that is a block list, if the block is smaller than the block size it gets removed
	for(long unsigned int i = 0; i < dataT.size(); i+= blockSize)
	{
		vector<float> blowq;
		//std::cout << "Block " << num << "contains ";
		for(int j = 0; j < blockSize; j++)
		{
		
 		  if(int(i+j) >= int(dataT.size()))
			{
				//std::cout << "nan   ";
			}
			else
			{

				blowq.push_back(dataT[i+j]);
				//std::cout << dataT[i+j] << "   ";
			}
		}
		blocks.push_back(blowq);
		//std::cout << std::endl;
		num++;
	}
	//erase the smaller blocks from the list
	for(long unsigned int m = 0; m < blocks.size(); m++)
	{
	  if(int(blocks[m].size()) < blockSize)
		{
			blocks.erase(blocks.begin()+ m);
		}
	}


}


//query, calculate the average based on the coordinates given using the list of blocks generated from above
float BlockRAQ::query(int x, int y)const
{
  if(x < 0 || y > int(dataT.size()))
	{
		cout << "error, out of range " << endl;
		return 0;
	}
	//check the bounds for whole blocks within the passed arguments then pushes that into the wholeAVG vector, andthe loose members into a loose vector, we then use the given equation provided in the project description of combining averages of blokcs and loose elements
        vector<float> wholeAvg;
	vector <float> loose;
	int upperB = 0;
	int lowerB = dataT.size() + 1;
	for(int i = x; i <= y; i++)
	{
	  for(int j = 0; j < int(blocks.size()); j++)
		{

			if(dataT[i] == blocks[j].at(0) && i + (blockSize - 1) < y)
			{
				//cout << i + blockSize << endl;
				if(i < lowerB)
				{
					lowerB = i;
				}
				if(i + (blockSize - 1) > upperB)
				{
					upperB = i + (blockSize - 1);
				}
				float avg = calcAvg(blocks[j]);
				wholeAvg.push_back(avg);
				//std::cout << "position " << i << " is the start of a whole block within the range specified " << std::endl;
			}
		}
	}
	//cout << "upper bound: " << upperB << " lower bound: " << lowerB << endl;
	for(int i = 0; i <= y; i++)
	{
		if(i < lowerB)
		{
			loose.push_back(dataT[i]);
		}
		else if(i > upperB)
		{
			loose.push_back(dataT[i]);
		}
	}
	float totalAvg = 0;
	int sizer = 0;
	for(int i = x ; i < int(loose.size()) ; i++)
	{
		//cout << loose[i] << " , ";
		totalAvg += loose[i];
	}
	//cout << endl;
	for(int i = 0; i < int(wholeAvg.size()); i++)
	{
		totalAvg += (wholeAvg[i] * blockSize);
	}
	//cout<< totalAvg << endl;
	sizer = (y - x) + 1;
	totalAvg = totalAvg / sizer;
	//cout << totalAvg << endl;
	wholeAvg.clear();
	loose.clear();
	return totalAvg;

}

//calculates the average of a passed block
float BlockRAQ::calcAvg(vector<float> blockT) const
{
	float average = 0;
	float	total = 0;
	for(int i = 0; i < int(blockT.size()); i++)
	{
		total += blockT[i];
	}
	average = total / blockT.size();
	return average;
}
//prints out number of blocks, block sizes, and the averages for each block
void BlockRAQ::dump() const
{
	cout << "Num of blocks: " << blocks.size() << endl;
	cout << "Block size: " << blockSize << endl;
	cout << "Block averages: " << endl;
	for(int i = 0; i < int(blocks.size()); i++)
	{
		cout << calcAvg(blocks[i]) << "    ";
	}
	cout << endl;
}
