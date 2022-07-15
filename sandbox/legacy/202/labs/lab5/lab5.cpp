#include <iostream>
#include <Creature.h>

using namespace std;


int main()
{
  Creature bird;
  bird.SetName("Toucan");
  bird.SetAge(7);
  bird.SetHost(false);

  cout << "Data of creature 1: " << endl;
  cout << "The name of the creature is " << bird.GetName() << endl;
  cout << "is the creature hostile? " << bird.GetHost() << endl;


  return 0;
}
