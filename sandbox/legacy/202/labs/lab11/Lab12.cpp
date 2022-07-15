#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int factorial(int);

int factorial(int n)
{
 
  if(n == 1)
    {

      return n;
    }
  else
    {
      // cout << n << " * ";
   
      return n * factorial(n-1);
      // return factorial(n);
    }
}

int main()
{
  int inp;
  cout << "factorial num?: ";
  cin >> inp;
  cout << endl;
  int sum = factorial(inp);
  for(int i = inp; i > 0 ; i--)
    {
      cout << i+1 << " * ";
    }
  cout << " = " << sum << endl;
  return 0;
}
