#include <iostream>
#include <iomanip>
#include<string>
#include "Song.h"
using namespace std;

Song::Song(string name, string band)
{
  m_name = name;
  m_band = band;
}

string Song::GetName()
{
  return m_name;
}

string Song::GetBand()
{
  return m_band;
}

void Song::Play()
{
  cout << "you love the song lyrics in " << m_name << " by " << m_band << endl;
}

void Song::Skip()
{
}

void Song::Lyrics()
{
}




Indie::Indie(string name, string band):Song(name, band)
{
}

void Indie::Play()
{
  cout << "you play your favorite indie song, " << m_name << " by " << m_band << endl;

}

void Indie::Skip()
{
  cout << "you are not in the mood to listen to the indie song " << m_name;
}

Pop::Pop(string name, string band):Song(name, band)
{
 
}
void Pop::Play()
{
  cout << "you play your favorite pop song, "  << m_name << " by " << m_band;
}

void Pop::Skip()
{
  cout << "after hearing it for a few seconds you decide you dont want to listen to " << m_name << " by " << m_band << " so you skip it" << endl;
}

void Pop::Lyrics()
{
  cout << "you love the lyrics in the pop song " << m_name << " by " << m_band << endl;
}
