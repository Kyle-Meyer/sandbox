

#include <iostream>
#include <iomanip>
#include <string>
#include "Song.h"
using namespace std;





int main()
{
  Song newSong("I dont love you", "My Chemical romance");
  Indie indie1("New Slang", "The Shins");
  Pop pop1("thank u , next", "Ariana Grande");

  Song *song1 = &newSong;
  Song *song2 = &indie1;
  Song *song3 = &pop1;

  cout << "song - I dont love you" << endl;
  song1->Play();
  cout << "Indie - Sad Boi" << endl;
  song2->Play();
  song2->Skip();

  cout << "Pop - hot 100" << endl;
  song3->Play();
  song3->Skip();
  song3->Lyrics();
  return 0;
}
