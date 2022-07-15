#include <iostream>
#include <string>
#include "StudentRecord.h"

using namespace std;

/*
  Initialize member variables in the constructor and dynamically allocate memory 
  where necessary.
*/
StudentRecord::StudentRecord(string name, int numOfCourses) {
  m_name = &name;
  m_numOfCourses = numOfCourses;
  int *newArr;
  newArr = new int[numOfCourses];
  for(int i = 0; i < numOfCourses; i++)
    {
      int scr;
      cout << "Please enter the score for course #" << i << " ";
      cin >> scr;
      newArr[i] = scr;
    }
  m_scores = newArr;
}

StudentRecord::~StudentRecord() {
  cout << "destructor called " << endl;

  // De-allocate any dynamically allocated memory here...
  delete[] m_scores;
}

int* StudentRecord::GetScoreLocation() {
  return m_scores;
  // One line of code should do the 'trick' here.
}

void StudentRecord::PrintScores() {
  cout << "The list of scores is as follows..." << endl;
  for(int i = 0; i<m_numOfCourses ; i++)
    {
      cout << "the score for course " << i << " is" << m_scores[i] << endl;
    }
  // Iterate and display the stored scores for the student  
}

// Request score values for each course, calculate and return the average score.
double StudentRecord::GetAverageScore() {
  int tot = 0;
  for(int i = 0 ; i<m_numOfCourses ; i++)
    {
      tot += m_scores[i];
    }
  double avg = double(tot)/double(m_numOfCourses);
  return avg;
  
}

/* Prints the student name and number of Courses taken.
     It does not return anything. */
void StudentRecord::CheckProperties() {
  
}
