#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  // cppcheck-suppress unusedStructMember
  int _rows, _cols;
  // cppcheck-suppress unusedStructMember
  double** _matrix;

 public:
  S21Matrix();                    // default constructor
  S21Matrix(int rows, int cols);  // parameterized constructor
  S21Matrix(const S21Matrix& o);  // copy constructor
  S21Matrix(S21Matrix&& o);       // move constructor
  ~S21Matrix();                   // destructor

  int get_rows();
  int get_cols();
  void set_rows(int row);
  void set_cols(int col);

  S21Matrix& operator=(const S21Matrix& o);
  bool operator==(const S21Matrix& o) const;
  double& operator()(int row, int col) const;
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix operator+(const S21Matrix& o) const;
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o) const;
  S21Matrix operator*=(const S21Matrix& o);
  S21Matrix operator*=(const double num);
  S21Matrix operator*(const S21Matrix& o) const;
  S21Matrix operator*(const double num) const;

  bool eq_matrix(const S21Matrix& o) const;
  void sum_matrix(const S21Matrix& o);
  void sub_matrix(const S21Matrix& o);
  void mul_number(const double num);
  void mul_matrix(const S21Matrix& other);
  S21Matrix transpose() const;
  S21Matrix calc_complements() const;
  double determinant() const;
  S21Matrix inverse_matrix() const;
  S21Matrix minor(int row, int col) const;
};

#endif
