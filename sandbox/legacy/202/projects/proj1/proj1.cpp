
//============================================================================
// Name        : Proj1.cpp
// Author      : Kyle Meyer OMEGALUL
// Version     :
// Copyright   : dont have one lol
// Description : AScii art tool
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>




using namespace std;
// constants
const int MAXSIZE = 75;

//prototypes
int useInp(int);
int loadArt(char[MAXSIZE][MAXSIZE]); //ignore this
void printArt(char[][MAXSIZE]);
void rotateArt(char[][MAXSIZE], int);
int editArt(char[MAXSIZE][MAXSIZE]);
void invert(char[MAXSIZE][MAXSIZE]);
int saveArt(char[MAXSIZE][MAXSIZE]);


// the save function, just saves out the current array into a text file of your naming
int saveArt(char myArray[MAXSIZE][MAXSIZE])
{
	char decis;
	cout << "would you like to save before exiting(y/n)? ";
	cin >> decis;
	cout << endl;
	if(decis == 'y')
	{
		char fileName[80] = {' '};
		cout << "what would you like to save the file as? ";
		cin >> fileName;
		cout << endl;
		ofstream myFile (fileName);
		if(myFile.is_open())
		{
			for(int x = 0; x < MAXSIZE; x ++)
			{
				for(int y = 0; y < MAXSIZE; y ++)
				{
					if(myArray[x][y] != ' ')
					{
						cout << "putting " << myArray[x][y] << " into file with coords" << x << " " << y;
						myFile << x << " " << y << " " << " "  << myArray[x][y] << endl;
					}
				}
			}
			myFile.close();
		}
	}
	return 0;
}

//the #2 option, simple grab coordinates, and then replace the coordinate with a character of your choosing, then prompts the user to continue
int editArt(char myArray[MAXSIZE][MAXSIZE])
{
	int xCord = 0;
	int yCord = 0;
	char decis;
	char newChar;
	bool cont = true;
	while(cont == true)
	{
		cout << "Enter the x coordinate of the position you want to edit: ";
		xCord = useInp(MAXSIZE - 1);
		cout << endl;
		cout << "Enter the y coordinate of the position you would like to edit: ";
		yCord = useInp(MAXSIZE - 1);
		cout << endl;
		cout << "Now enter the character you would like to place in this position: ";
		cin >> newChar;
		myArray[xCord][yCord] = newChar;
		cout << endl;
		cout << "Would you like to continue editing coordinates(y/n)? ";
		cin >> decis;
		if(decis != 'y')
		{
			cont = false;
		}
	}
	return 0;
}
//the #4 option, this is done by creating a copy array that is at first entirely empty, and then populating it with the original array, but using the rows of the first array as the columns in reverse order, IE, the first row is now the last column and then over writing the original array with the new array
void rotateArt(char myArray[MAXSIZE][MAXSIZE], int deg)
{
	char newArray[MAXSIZE][MAXSIZE] = {' '};
	//the grabbing of the first rows and using them as the last column
	for(int x = 0; x < MAXSIZE; x++)
	{
		for(int y = 0; y < MAXSIZE; y++)
			{

					newArray[x][y] = myArray[MAXSIZE-y-1][x];

			}
	}
	//the overwriting of the original array
	for(int x = 0; x < MAXSIZE; x++)
		{
			for(int y = 0; y < MAXSIZE; y++)
			{
			  //debug stuff, ignore this
				//cout << newArray[x-70][y-70];
				//if(newArray[x][y] != ' ')
				//{
				//	cout << "found " << newArray[x][y] << " at " << x <<  " " << y << endl;

				//}

				myArray[x][y] = newArray[x][y];
				//
			}
			//cout << endl;
		}

}
//simple print function, just couts the array elements
void printArt(char myArray[MAXSIZE][MAXSIZE]){
	for(int x= 0; x < MAXSIZE; x ++)
	{
		for(int y = 0; y < MAXSIZE; y++)
		{
			cout << myArray[x][y];
		}
		cout << endl;
	}


}
// the #5 option, first prompts users for which axis they would like to invert the art over, either x or y, for the x axis, its simply rotating the art twice, for the y axis, its printing the y elements of the array, but in reverese order, this is done in a similar process by creating a new blank array, and populating it with the reverse order of y elements then overwriting the original array with the new array
void invert(char myArray[MAXSIZE][MAXSIZE])
{
	int decis = 0;
	char newArray [MAXSIZE][MAXSIZE] = {' '};
	cout << "your choices are: " << endl;
	cout << "1.) flip over the x axis" << endl;
	cout <<  "2.) flip over the y axis" << endl;
	cout << "what would you like to do?: ";
	decis = useInp(2);
	if(decis == 1)
	{
		rotateArt(myArray, 0);
		rotateArt(myArray, 0);
		//printArt(myArray);

	}
	if(decis == 2)
	{
		//cout << "YUPPERS";
		for(int x = 0; x < MAXSIZE; x++)
		{
			int newX = 0;
			int newY = 0;
			for(int y = 0; y < MAXSIZE; y++)
			{
				//cout << (MAXSIZE - 1) - x << " " << (MAXSIZE - 1) - y;
				//cout << endl;
				 newX = MAXSIZE - 1 - x;
				 newY = MAXSIZE - 1 - y;
				newArray[x][y] = myArray[x][newY];

			}
		}

		for(int x = 0; x < MAXSIZE; x++)
		{
			for(int y = 0; y < MAXSIZE; y++)
			{
				myArray[x][y] = newArray[x][y];
			}
		}

		//cout << "shoulda printed";
	}

}
// the #1 option, prompts the user to enter in the name of the file they would like to load, then using the fstream library to read in the contents of the file, the x coord first, the y coord second, and then the character that populates those coordinates this function also lets the user know if the file is open or not
int loadArt(char myArray[MAXSIZE][MAXSIZE]){

	char fileName[80] = {' '};
	cout << "Enter the name of the file you would like to open: ";
	cin >> fileName;

	cout << "loading" << endl;
	//char myArray[MAXSIZE][MAXSIZE] = {' '};
	ifstream myFile (fileName);
	int a, b;
	char c;


	if (myFile.is_open())
	{
		cout << "file is open" << endl;
		//while (getline(myFile, line))
		while (myFile >> a >> b >> c)
		{

			myArray[a][b] = c;

		}
	}
	else if(!myFile)
	{
		cout << "couldn't open file" << endl;
	}


	myFile.close();
	cout << "file is now closed" << endl;


	return 0;
}
int useInp(int maxChoice){
	int useChoice = -1;
	bool cont = false;
	while(cont == false){

		cin >> useChoice;
		if(useChoice > maxChoice || useChoice < 0){
			cout << "enter a number no greater than " << maxChoice << " and no less than 0" << endl;
			cout << "try agane: ";

		}
		else
		{
			cont = true;
			return useChoice;
		}
	}
	return useChoice;
}
int main() {

	cout << "Welcome to the ASCII art tool" << endl;
	cout << "What would you like to do?" << endl;
	bool cont = true;
	char myArray[MAXSIZE][MAXSIZE];
			for(int i = 0; i < MAXSIZE; i++)
			{

				for(int z = 0; z < MAXSIZE; z++)
				{
					myArray[i][z] = ' ';
				}
			}
	while(cont == true)
	{

		cout << "1.) Load ASCII art from a file" << endl;
		cout << "2.) Create ASCII art manually" << endl;
		cout << "3.) Display art" << endl;
		cout << "4.) Rotate art" << endl;
		cout << "5.) Invert art" << endl;
		cout << "6.) Exit" << endl;
		int choice = useInp(6);
		//cout << choice << endl;
		switch(choice){

			case 1: choice = 1;
			{
				loadArt(myArray);
			}
				break;
			case 2: choice = 2;
			{
				editArt(myArray);
			}
				break;
			case 3: choice = 3;
			{
				cout << "here she is " << endl;
				printArt(myArray);
			}
				break;
			case 4: choice = 4;
			{
				rotateArt(myArray, 90);

			}
				break;
			case 5: choice = 5;
			{
				invert(myArray);
				//		printArt(myArray);
			}
				break;
			case 6: choice = 6;
			{
				saveArt(myArray);
				cont = false;
			}
				break;

		}
	}

	return 0;
}

