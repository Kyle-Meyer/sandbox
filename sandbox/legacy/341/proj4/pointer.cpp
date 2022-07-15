#include <iostream>
using namespace std;



int main(){
  int *hello  = new int(9);

  cout << hello << endl;
  delete hello;
  cout << hello << endl;
  return 0;
  


}
