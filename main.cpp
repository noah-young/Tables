/*
 * Test program for Table<int>.
 *
 * Author: Noah Young
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <math.h>
#include "table.cpp"
using namespace std;

void initialize(Table<int>&);
void squares(Table<int>&);
int divide(int);

int main() {
  const int WIDTH = 4;

  Table<int> t(5, 6);
  initialize(t);

  Table<int> t2(5, 3);
  initialize(t2);

  Table<int> t3(WIDTH);
  squares(t3);

  cout << setw(WIDTH) << t << endl;
  cout << setw(WIDTH) << t2 << endl;
  cout << setw(WIDTH) << t3 << endl;

  // appends the columns from t2 to t
  t = t.append_cols(t2);
  cout << setw(WIDTH) << t << endl;


  // extract a subtable
  t3 = t3(1, 1, 2, 3);
  cout << setw(WIDTH) << t3 << endl;

  cout << setw(WIDTH) << t3 + divide;

  return 0;
}
 
// fills a table with 1's and 0's
void initialize(Table<int>& t) {
   for (int i = 0; i < t.get_rows(); i++) {
   	   for (int j = 0; j < t.get_cols(); j++) {
   	   	   t(i, j) = rand()%2;
   	   }
   }
}

// fills a table the powers of 2
void squares(Table<int>& t) {
   for (int i = 0; i < t.get_rows(); i++) {
   	   for (int j = 0; j < t.get_cols(); j++) {
   	   	  if (i == 0 || j == 0) {
            t(i, j) = 2;
          } else {
            t(i, j) = (int) pow(t(i-1, j-1), 2);
          }
   	   }
   }
}

// divides a number by 2
int divide(int n) {
  return n / 2;
}