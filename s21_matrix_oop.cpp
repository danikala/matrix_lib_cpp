#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  if (rows < 1 || cols < 1)
    throw std::invalid_argument("Error Create: matrix size eq/greater 1");
  else {
    _matrix = new double*[rows];
    for (int i = 0; i < rows; ++i) _matrix[i] = new double[cols]();
  }
}

S21Matrix::S21Matrix(const S21Matrix& o) : S21Matrix(o._rows, o._cols) {
  for (int i = 0; i < _rows; ++i)
    for (int j = 0; j < _cols; ++j) _matrix[i][j] = o._matrix[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& o)
    : _rows(o._rows), _cols(o._cols), _matrix(o._matrix) {
  o._rows = 0;
  o._cols = 0;
  o._matrix = nullptr;
}

S21Matrix::~S21Matrix() {
  if (_matrix)
    for (int i = 0; i < _rows; ++i) delete[] _matrix[i];
  delete[] _matrix;
}

int S21Matrix::get_rows() { return _rows; }

int S21Matrix::get_cols() { return _cols; }

void S21Matrix::set_rows(int row) {
  if (row < 0) throw std::out_of_range("Rows should be more or eq 1");
  if (row != _rows) {
    int minrow = std::min(row, _rows);
    S21Matrix result(row, _cols);
    for (int i = 0; i < minrow; ++i)
      for (int j = 0; j < _cols; ++j) result._matrix[i][j] = _matrix[i][j];
    *this = std::move(result);
  }
}

void S21Matrix::set_cols(int col) {
  if (col < 0) throw std::out_of_range("Cols should be more or eq 1");
  if (col != _cols) {
    int mincol = std::min(col, _cols);
    S21Matrix result(_rows, col);
    for (int i = 0; i < _rows; ++i)
      for (int j = 0; j < mincol; ++j) result(i, j) = (*this)(i, j);
    *this = std::move(result);
  }
}

bool S21Matrix::eq_matrix(const S21Matrix& o) const {
  if (_rows <= 0 || _cols <= 0 || o._rows <= 0 || o._cols <= 0)
    return false;
  else if (_rows != o._rows || _cols != o._cols)
    return false;
  for (int i = 0; i < _rows; ++i)
    for (int j = 0; j < _cols; ++j)
      if ((float)(*this)(i, j) != (float)o(i, j)) return false;
  return true;
}

void S21Matrix::sum_matrix(const S21Matrix& o) {
  if (_rows != o._rows || _cols != o._cols)
    throw std::out_of_range("incorect input, matrices size don`t eq");
  else
    for (int i = 0; i < _rows; ++i)
      for (int j = 0; j < _cols; ++j) (*this)(i, j) += o(i, j);
}

void S21Matrix::sub_matrix(const S21Matrix& o) {
  if (_rows != o._rows || _cols != o._cols)
    throw std::out_of_range("incorect input, matrices size don`t eq");
  else
    for (int i = 0; i < _rows; ++i)
      for (int j = 0; j < _cols; ++j) (*this)(i, j) -= o(i, j);
}

void S21Matrix::mul_number(const double num) {
  for (int i = 0; i < _rows; ++i)
    for (int j = 0; j < _cols; ++j) (*this)(i, j) *= num;
}

void S21Matrix::mul_matrix(const S21Matrix& o) {
  if (_cols != o._rows)
    throw std::out_of_range(
        "The number of columns of the matrix 1 is not eq to the number of rows "
        "of the matrix 2");
  S21Matrix result(_rows, o._cols);
  for (int i = 0; i < result._rows; ++i)
    for (int j = 0; j < result._cols; ++j) {
      result._matrix[i][j] = 0.0;
      for (int k = 0; k < _cols; ++k) result(i, j) += (*this)(i, k) * o(k, j);
    }
  *this = result;
}

S21Matrix S21Matrix::transpose() const {
  if (_rows <= 0 || _cols <= 0)
    throw std::invalid_argument(
        "Transpose_ERROR: Matrix must have positive dimensions");
  S21Matrix result(_cols, _rows);
  for (int i = 0; i < _rows; ++i)
    for (int j = 0; j < _cols; ++j) result(j, i) = (*this)(i, j);
  return result;
}

S21Matrix S21Matrix::calc_complements() const {
  if (_rows != _cols)
    throw std::out_of_range("Calc_Complence_ERROR: Matrix is not square");
  S21Matrix result(_rows, _cols);
  if (_rows == 1)
    result(0, 0) = 1;
  else if (_rows > 1)
    for (int i = 0; i < _rows; i++)
      for (int j = 0; j < _cols; j++) {
        S21Matrix M = minor(i, j);
        result(i, j) = ((i + j) % 2 == 0 ? 1 : -1) * M.determinant();
      }
  return result;
}

double S21Matrix::determinant() const {
  if (_rows != _cols)
    throw std::out_of_range("Determinant_ERROR: Matrix is not square");
  double det = 0;
  if (_rows == 1)
    det = (*this)(0, 0);
  else if (_rows == 2)
    det = (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  else {
    for (int i = 0; i < _rows; ++i) {
      S21Matrix M = minor(0, i);
      det += pow((-1), i) * (*this)(0, i) * M.determinant();
    }
  }
  return det;
}

S21Matrix S21Matrix::minor(int row, int col) const {
  S21Matrix M(_rows - 1, _cols - 1);
  if (_rows != _cols)
    throw std::out_of_range("Minor_ERROR: Matrix is not square");
  int k = 0;
  for (int i = 0; i < _rows; ++i) {
    if (i == row) continue;
    int l = 0;
    for (int j = 0; j < _cols; ++j) {
      if (j == col) continue;
      M(k, l) = (*this)(i, j);
      l++;
    }
    k++;
  }
  return M;
}

S21Matrix S21Matrix::inverse_matrix() const {
  double det = determinant();
  if (fabs(det) < 1e-6)
    throw std::out_of_range("Inverse_ERROR: Determinant is 0");
  S21Matrix result(_rows, _cols);
  result = calc_complements();
  result = result.transpose();
  return result * (1.0 / det);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
  if (this == &o) return *this;
  if (this->_matrix != nullptr) {
    for (int i = 0; i < _rows; ++i) delete[] _matrix[i];

    delete[] _matrix;
  }
  _rows = o._rows;
  _cols = o._cols;
  _matrix = new double*[_rows];
  for (int i = 0; i < _rows; ++i) {
    _matrix[i] = new double[_cols];
    for (int j = 0; j < _cols; ++j) (*this)(i, j) = o(i, j);
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& o) const { return eq_matrix(o); }

double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= _rows || col < 0 || col >= _cols)
    throw std::out_of_range(
        "Argument row(col) should be more or eq 0 and less _rows(_cols)");
  else
    return _matrix[row][col];
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  sum_matrix(o);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& o) const {
  S21Matrix result(*this);
  result.sum_matrix(o);
  return result;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  sub_matrix(o);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) const {
  S21Matrix result(*this);
  result.sub_matrix(o);
  return result;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& o) {
  mul_matrix(o);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  mul_number(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) const {
  S21Matrix result(*this);
  result.mul_matrix(o);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.mul_number(num);
  return result;
}
