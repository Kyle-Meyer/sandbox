/**********
* File: Creature.h
*
* Intended for Lab 5: Classes
*
**********/

#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>

using namespace std;

class Creature {
private:
  string m_species;
  int m_age;
  bool m_isHostile;


public:
  string GetSpecies();

  int GetAge();

  bool GetHost();

  void SetSpec(string m_species);
  void SetAge(int m_age);
  void SetHost(bool m_isHostile);


  void attack();
  void age;
  //Creature class must have 3 private variables:
  //  m_species (of type string), m_age (of type int), and m_isHostile (of type bool)
  //Declare public getter (accessors) and setter (mutators)
  //  functions for the above three variables.
  //Conceptually, a getter returns a private variable
  //  and a setter sets a private variable.
  //Declare two public functions void attack(); and void age();
  

  
};

#endif
