#ifndef STUDENTRECORD_H
#define STUDENTRECORD_H

#include <string>

using namespace std;

class StudentRecord {
public:
  /* Initialize member variables and dynamically allocate memory 
     where necessary.   */
  StudentRecord(string name, int numOfCourses);

  /* Destructor should deallocate any dynamically allocated memory. */
  ~StudentRecord();

  /* Get the memory location where student scores are stored, 
     i.e. get m_scores */
  int* GetScoreLocation();
  
  /* Iterate and display the list of scores of associated with the student object.
     It does not return anything. */
  void PrintScores();

  /* Returns the average score the student object has.  */
  double GetAverageScore();

  /* Prints the student name and number of Courses taken.
     It does not return anything. */
  void CheckProperties();


private:
  // The name of the student will be stored here when a Student Record
  // object is instantiated.
  string* m_name;
  
  /* References to the list of scores will be made here.
     i.e. Dynamically allocated memory for storage of score values 
     will be done through this pointer.
   */
  int* m_scores;

  // the number of scores the student has scores for.
  int m_numOfCourses;
};

#endif
