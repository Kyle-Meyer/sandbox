#include "Creature.h"
/**********
* File: Creature.cpp
*
* Intended for Lab 5: Classes
*
**********/

//Constructor -- Already Implemented

Creature::Creature() {
  cout << "Creating a creature..." << endl;
  m_species = "goat";
  m_age = 7;
  m_isHostile = false;
}



/*
For attack -
  If hostile: “<species of creature> attacks you!”
  If not hostile: “<species of creature> approaches you and nuzzles you.”
For age - 
  Define the function age - sets the age of the creature to the current age plus 1.
*/
//Accessors -- Student implements these
Creature::SetAge(int age)
{
  m_age = age;
 
}
Creature::SetName(string name)
{
  m_species = name;

}

Creature::SetHost(bool host)
{
  m_isHostile = host;
}

string Creature::GetName()
{
  string name = m_species;
  return name;
}
int Creature::GetAge()
{
  int age = m_age;
  return age;

}
int Creature::GetHost()
{
  bool host = m_isHostile;
  return host;

}

//Custom Functions -- Student implements these (attack and age)
Creature::attack()
{
  if(m_isHostile == true)
    {
      cout << m_species  <<  " attacks you" << endl;
      
    }
  else
    {
      cout << m_species  << " nuzzles you" << endl;
    }

}

Creature::age()
{
  cout << "the " << m_species << " is now " << m_age + 1 << " years old " << endl;

}
