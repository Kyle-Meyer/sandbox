#ifndef SONG_H
#define SONG_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Song
{
 public:
  Song(string name, string band);
  virtual void Play();
  virtual void Skip();
  virtual void Lyrics();
  string GetName();
  string GetBand();
 protected:
  string m_name;
  string m_band;

};

class Indie : public Song
{
 public:
  Indie(string name, string band);
  void Play();
  void Skip();
};


class Pop : public Song
{
 public:
  Pop(string name, string band);
  void Play();
  void Skip();
  void Lyrics();

};


#endif
