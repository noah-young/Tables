/*
 * Header file for a class representing dynamic tables.
 *
 * Author: Noah Young
 */

#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

template <typename T>
class Table {
  // overload leftshift operator.
  // displays the table with space between columns set by width.
  template<typename S>
  friend ostream& operator<<(ostream&, const Table<S>&);

public:
  // constructors
  Table<T>(int);
  Table<T>(int, int);

  // copy constructor 
  Table<T>(Table<T>&);

  // assignment operator
  Table<T>& operator=(const Table<T>&);

  // destructor
  ~Table<T>();

  // returns the reference to the value at specified location
  T& operator()(int, int);

  // extracts a subtable
  Table<T> operator()(const int, const int, const int, const int);
  
  // returns number of rows in the table object
  int get_rows() const;
  // returns number of cols in the table object
  int get_cols() const;

  // overload addition operator
  Table<T> operator+(T (*)(T));

  // returns a new table with rows appended from Table t
  Table<T> append_rows(const Table<T>&);
  // returns a new table with columns appended from Table t
  Table<T> append_cols(const Table<T>&);
private:
   T** ptr;
   int rows;
   int cols;
};

#endif
