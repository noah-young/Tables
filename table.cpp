/*
 * Implementation file for the Table class.
 *
 * Author: Noah Young
 */
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include "table.h"

// constructor takes parameters r, c specifying the number
// of rows and columns in the table.
template <typename T>
Table<T>::Table(int r, int c) {
  rows = r;
  cols = c;
  ptr = new T*[rows];
  for (int i = 0; i < rows; i++) {
    ptr[i] = new T[cols];
  }
}

// constructor takes parameter s specifying an equal number
// of rows and columns in the table.
template <typename T>
Table<T>::Table(int s) : Table(s, s) {}

// copy constructor
template <typename T>
Table<T>::Table(Table<T>& t) {
  ptr = new T*[t.rows];
  for (int i = 0; i < t.rows; i++) {
    ptr[i] = new T[t.cols];
    for (int j = 0; j < t.cols; j++)
      ptr[i][j] = t.ptr[i][j];
  }
  rows = t.rows;
  cols = t.cols;
}

// destructor
template <typename T>
Table<T>::~Table() {
   for (int i = 0; i < rows; i++) {
        delete []ptr[i]; // delete each row
    }
    delete []ptr; // delete array of rows
}

// overload assignment operator
template <typename T>
Table<T>& Table<T>::operator=(const Table<T>& t) {
  for (int i = 0; i < rows; i++) {
    delete []ptr[i];
  }
  delete []ptr;

  ptr = new T*[t.rows];
  for (int i = 0; i < t.rows; i++) {
    ptr[i] = new T[t.cols];
    for (int j = 0; j < t.cols; j++)
      ptr[i][j] = t.ptr[i][j];
  }
  rows = t.rows;
  cols = t.cols;
  return *this;
}

// returns the reference to the value at location r, c
template <typename T>
T& Table<T>::operator()(int r, int c) {
  return ptr[r][c];
}

// returns an extracted subtable using arguments to specify 
// top-left and bottom-right corners of the subtable.
template <typename T>
Table<T> Table<T>::operator()(int r1, int c1, int r2, int c2) {
  int r = (r2-r1)+1;
  int c = (c2-c1)+1;
  Table<T> t(r, c); // creates a new subtable

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++)
      t.ptr[i][j] = ptr[r1+i][c1+j];
  }

  return t;
}

// returns the number of rows in the table
template <typename T>
int Table<T>::get_rows() const {
   return rows;
}

// returns the number of columns in the table
template <typename T>
int Table<T>::get_cols() const {
   return cols;
}

// returns a new table with rows appended from Table t
template <typename T>
Table<T> Table<T>::append_rows(const Table<T>& t) {
  assert(cols == t.cols);
  int r = rows + t.rows;
  int c = cols;
  Table<T> t_append(r, c);

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if(i < rows)
        t_append.ptr[i][j] = ptr[i][j];
      else
        t_append.ptr[i][j] = t.ptr[i-rows][j];
    }
  }

  return t_append;
}

// returns a new table with columns appended from Table t
template <typename T>
Table<T> Table<T>::append_cols(const Table<T>& t) {
  assert(rows == t.rows);
  int r = rows;
  int c = cols + t.cols;
  Table<T> t_append(r, c);

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if(j < cols)
        t_append.ptr[i][j] = ptr[i][j];
      else
        t_append.ptr[i][j] = t.ptr[i][j-cols];
    }
  }

  return t_append;
}

// overload addition operator
template <typename T>
Table<T> Table<T>::operator+(T (*f)(T)) {
  Table<T> t_new(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++)
      t_new.ptr[i][j] = f(ptr[i][j]);
  }

  return t_new;
}

// overload leftshift operator
// Displays the table with space between the columns set by width w.
template <typename T>
ostream& operator<<(ostream& out, const Table<T>& r) {
  int w = out.width();
  for (int i = 0; i < r.get_rows(); i++) {
    for (int j = 0; j < r.get_cols(); j++) {
        cout << setw(w) << r.ptr[i][j] << " ";
    }
    cout << endl;
  }
   return cout;
} 
