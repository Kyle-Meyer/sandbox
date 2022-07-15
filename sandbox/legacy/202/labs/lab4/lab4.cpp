#include <iostream>

using namespace std;

// Constants go here
const int START_ATM = 1000;
const int START_WALLET = 100;

void withdraw(double&, double&);
void deposit(double*, double*);

void deposit(double* wallet, double* atm)
{
  double dep = 0.0;
  double wall = *wallet;
  double at = *atm;
  cout << "how much would you like to deposit? ";
  cin >> dep;
  cout << endl;
  *wallet = wall - (dep+(dep*.1));
  *atm = at + dep;
}
void withdraw(double& wallet, double& atm)
{
  double take = 0.0;
  cout << "how much money would you like to withdraw? ";
  cin >> take;
  cout << endl;
  wallet = wallet + take;
  atm = atm - (take + (take*.1));
}
int main()
{
  double atm = START_ATM;
  double wallet = START_WALLET;

  cout << "Welcome to the ATM." << endl;
  cout << "The ATM contains " << atm << " dollars" << endl;
  cout << "Your wallet contains " << wallet << " dollars" << endl;

  cout << endl;
  
  withdraw(wallet, atm);

  cout << endl;
  cout << "ATM contains " << atm << " dollars" << endl;
  cout << "Wallet contains " << wallet << " dollars" << endl;
  cout << endl;
  
  deposit(&wallet, &atm);

  cout << endl;
  cout << "ATM contains " << atm << " dollars" << endl;
  cout << "Wallet contains " << wallet << " dollars" << endl;
  
  return 0;
}

// Implement withdraw and deposit here

