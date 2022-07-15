#include <iostream>
using namespace std;

int main()
{
  // This creates a pointer to a read-only literal value: "Pokemon".
  // To make it point to writable memory, use char[] instead of char*
  char *temp = "Pokemon";
  int i = 0;
  temp[3] = 'F';
  for (i = 0 ; i < 7 ; i++ )
    cout << temp[i] << endl;
  return 0;
}
