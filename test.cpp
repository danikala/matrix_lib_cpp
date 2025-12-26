#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(EqMatrix1, Equal) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 2;
  matrix_1(1, 0) = 3;
  matrix_1(1, 1) = 4;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 2;
  matrix_2(1, 0) = 3;
  matrix_2(1, 1) = 4;
  ASSERT_TRUE(matrix_1 == matrix_2);
}

TEST(EqMatrix2, NotEqual) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  matrix_1(0, 0) = 2;
  matrix_1(0, 1) = 2;
  matrix_1(1, 0) = 3;
  matrix_1(1, 1) = 4;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 2;
  matrix_2(1, 0) = 3;
  matrix_2(1, 1) = 4;
  ASSERT_FALSE(matrix_1 == matrix_2);
}

TEST(EqMatrix3, NotEqual) {
  S21Matrix matrix_1(3, 3);
  S21Matrix matrix_2(2, 2);
  matrix_1(0, 0) = 2;
  matrix_1(0, 1) = 2;
  matrix_1(1, 0) = 3;
  matrix_1(1, 1) = 4;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 2;
  matrix_2(1, 0) = 3;
  matrix_2(1, 1) = 4;
  ASSERT_FALSE(matrix_1 == matrix_2);
}

TEST(setRows, set) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(3, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 2;
  matrix_1(1, 0) = 3;
  matrix_1(1, 1) = 4;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 2;
  matrix_2(1, 0) = 3;
  matrix_2(1, 1) = 4;
  matrix_2(2, 0) = 0;
  matrix_2(2, 1) = 0;
  matrix_1.set_rows(3);
  ASSERT_TRUE(matrix_1 == matrix_2);
}

TEST(setCols, set) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 3);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 2;
  matrix_1(1, 0) = 3;
  matrix_1(1, 1) = 4;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 2;
  matrix_2(0, 2) = 0;
  matrix_2(1, 0) = 3;
  matrix_2(1, 1) = 4;
  matrix_2(1, 2) = 0;
  matrix_1.set_cols(3);
  ASSERT_TRUE(matrix_1 == matrix_2);
}

TEST(getRows1, get) {
  S21Matrix matrix_1;
  ASSERT_TRUE(matrix_1.get_rows() == 3 && matrix_1.get_cols() == 3);
}

TEST(errMatrix, err) {
  EXPECT_THROW(S21Matrix matrix(0, 3), std::invalid_argument);
}

TEST(operMatrix, copy) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 2;
  matrix_1(1, 0) = 3;
  matrix_1(1, 1) = 4;
  matrix_2(0, 0) = 4;
  matrix_2(0, 1) = 3;
  matrix_2(1, 0) = 2;
  matrix_2(1, 1) = 1;
  matrix_1 = matrix_2;
  ASSERT_TRUE(matrix_1 == matrix_2);
}

TEST(cpMatrix, copy) {
  S21Matrix matrix_2(2, 2);
  matrix_2(0, 0) = 4;
  matrix_2(0, 1) = 3;
  matrix_2(1, 0) = 2;
  matrix_2(1, 1) = 1;
  S21Matrix matrix_1(matrix_2);
  ASSERT_TRUE(matrix_1 == matrix_2);
}

TEST(mvMatrix, move) {
  S21Matrix matrix_2(2, 2);
  matrix_2(0, 0) = 4;
  matrix_2(0, 1) = 3;
  matrix_2(1, 0) = 2;
  matrix_2(1, 1) = 1;
  S21Matrix copy(matrix_2);
  S21Matrix matrix_1(std::move(matrix_2));
  ASSERT_TRUE(matrix_1 == copy && matrix_2.get_rows() == 0 &&
              matrix_2.get_cols() == 0);
}

TEST(sumM1, sum) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  S21Matrix res(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 1;
  matrix_2(1, 0) = 1;
  matrix_2(1, 1) = 1;
  res(0, 0) = 2;
  res(0, 1) = 2;
  res(1, 0) = 2;
  res(1, 1) = 2;
  ASSERT_TRUE((matrix_1 += matrix_2) == res);
}

TEST(sumM2, sumErr) {
  S21Matrix matrix_1(3, 3);
  S21Matrix matrix_2(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 1;
  matrix_2(1, 0) = 1;
  matrix_2(1, 1) = 1;
  EXPECT_THROW(matrix_1.sum_matrix(matrix_2), std::out_of_range);
}

TEST(sumM3, sum) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  S21Matrix res(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 1;
  matrix_2(1, 0) = 1;
  matrix_2(1, 1) = 1;
  res(0, 0) = 2;
  res(0, 1) = 2;
  res(1, 0) = 2;
  res(1, 1) = 2;
  ASSERT_TRUE((matrix_1 + matrix_2) == res);
}

TEST(subM1, sub) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  S21Matrix res(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 1;
  matrix_2(1, 0) = 1;
  matrix_2(1, 1) = 1;
  res(0, 0) = 0;
  res(0, 1) = 0;
  res(1, 0) = 0;
  res(1, 1) = 0;
  ASSERT_TRUE((matrix_1 -= matrix_2) == res);
}

TEST(subM2, sub) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  S21Matrix res(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 1;
  matrix_2(1, 0) = 1;
  matrix_2(1, 1) = 1;
  res(0, 0) = 0;
  res(0, 1) = 0;
  res(1, 0) = 0;
  res(1, 1) = 0;
  ASSERT_TRUE((matrix_1 - matrix_2) == res);
}

TEST(subM3, subErr) {
  S21Matrix matrix_1(3, 3);
  S21Matrix matrix_2(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 1;
  matrix_2(1, 0) = 1;
  matrix_2(1, 1) = 1;
  EXPECT_THROW(matrix_1.sub_matrix(matrix_2), std::out_of_range);
}

TEST(mulM1, mul) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  S21Matrix res(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  matrix_2(0, 0) = 2;
  matrix_2(0, 1) = 2;
  matrix_2(1, 0) = 2;
  matrix_2(1, 1) = 2;
  res(0, 0) = 4;
  res(0, 1) = 4;
  res(1, 0) = 4;
  res(1, 1) = 4;
  ASSERT_TRUE((matrix_1 * matrix_2) == res);
}

TEST(mulM2, mul) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  S21Matrix res(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  matrix_2(0, 0) = 2;
  matrix_2(0, 1) = 2;
  matrix_2(1, 0) = 2;
  matrix_2(1, 1) = 2;
  res(0, 0) = 4;
  res(0, 1) = 4;
  res(1, 0) = 4;
  res(1, 1) = 4;
  ASSERT_TRUE((matrix_1 *= matrix_2) == res);
}

TEST(mulM3, mulErr) {
  S21Matrix matrix_1(3, 3);
  S21Matrix matrix_2(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = 1;
  matrix_2(1, 0) = 1;
  matrix_2(1, 1) = 1;
  EXPECT_THROW(matrix_1.mul_matrix(matrix_2), std::out_of_range);
}

TEST(mulN1, mulN) {
  S21Matrix matrix_1(2, 2);
  double n = 5;
  S21Matrix res(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  res(0, 0) = 5;
  res(0, 1) = 5;
  res(1, 0) = 5;
  res(1, 1) = 5;
  ASSERT_TRUE((matrix_1 *= n) == res);
}

TEST(mulN2, mulN) {
  S21Matrix matrix_1(2, 2);
  double n = 5;
  S21Matrix res(2, 2);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 1;
  matrix_1(1, 0) = 1;
  matrix_1(1, 1) = 1;
  res(0, 0) = 5;
  res(0, 1) = 5;
  res(1, 0) = 5;
  res(1, 1) = 5;
  ASSERT_TRUE((matrix_1 * n) == res);
}

TEST(transpM1, trans) {
  S21Matrix matrix_1(3, 2);
  S21Matrix res(2, 3);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 4;
  matrix_1(1, 0) = 2;
  matrix_1(1, 1) = 5;
  matrix_1(2, 0) = 3;
  matrix_1(2, 1) = 6;
  res(0, 0) = 1;
  res(0, 1) = 2;
  res(0, 2) = 3;
  res(1, 0) = 4;
  res(1, 1) = 5;
  res(1, 2) = 6;
  ASSERT_TRUE(matrix_1.transpose() == res);
}

TEST(detM1, determinant) {
  S21Matrix matrix_1(3, 3);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 2;
  matrix_1(0, 2) = 3;
  matrix_1(1, 0) = 4;
  matrix_1(1, 1) = 5;
  matrix_1(1, 2) = 6;
  matrix_1(2, 0) = 7;
  matrix_1(2, 1) = 8;
  matrix_1(2, 2) = 9;

  double det = matrix_1.determinant();
  ASSERT_EQ(det, 0.0);
}

TEST(detM2, determinantErr) {
  S21Matrix matrix_1(4, 3);

  ASSERT_THROW(matrix_1.determinant(), std::out_of_range);
}

TEST(calcM1, calcCom) {
  S21Matrix matrix_1(3, 3);
  S21Matrix res(3, 3);
  S21Matrix origin_res(3, 3);
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 2;
  matrix_1(0, 2) = 3;
  matrix_1(1, 0) = 0;
  matrix_1(1, 1) = 4;
  matrix_1(1, 2) = 2;
  matrix_1(2, 0) = 5;
  matrix_1(2, 1) = 2;
  matrix_1(2, 2) = 1;
  origin_res(0, 0) = 0;
  origin_res(0, 1) = 10;
  origin_res(0, 2) = -20;
  origin_res(1, 0) = 4;
  origin_res(1, 1) = -14;
  origin_res(1, 2) = 8;
  origin_res(2, 0) = -8;
  origin_res(2, 1) = -2;
  origin_res(2, 2) = 4;
  res = matrix_1.calc_complements();
  ASSERT_TRUE(res == origin_res);
}

TEST(calcM2, calcCom) {
  S21Matrix matrix_1(1, 1);
  S21Matrix res(1, 1);
  S21Matrix origin_res(1, 1);
  matrix_1(0, 0) = 5;
  origin_res(0, 0) = 1;
  res = matrix_1.calc_complements();
  ASSERT_TRUE(res == origin_res);
}

TEST(calcM3, calcComErr) {
  S21Matrix matrix_1(2, 1);
  ASSERT_THROW(matrix_1.calc_complements(), std::out_of_range);
}

TEST(invM1, invers) {
  S21Matrix matrix_1(1, 1);
  S21Matrix res(1, 1);
  S21Matrix origin_res(1, 1);
  matrix_1(0, 0) = 50;
  origin_res(0, 0) = 1.0 / 50.0;
  res = matrix_1.inverse_matrix();
  ASSERT_TRUE(res == origin_res);
}

TEST(invM2, invers) {
  S21Matrix matrix_1(3, 3);
  S21Matrix res(3, 3);
  S21Matrix origin_res(3, 3);
  matrix_1(0, 0) = 2;
  matrix_1(0, 1) = 5;
  matrix_1(0, 2) = 7;

  matrix_1(1, 0) = 6;
  matrix_1(1, 1) = 3;
  matrix_1(1, 2) = 4;

  matrix_1(2, 0) = 5;
  matrix_1(2, 1) = -2;
  matrix_1(2, 2) = -3;

  origin_res(0, 0) = 1;
  origin_res(0, 1) = -1;
  origin_res(0, 2) = 1;

  origin_res(1, 0) = -38;
  origin_res(1, 1) = 41;
  origin_res(1, 2) = -34;

  origin_res(2, 0) = 27;
  origin_res(2, 1) = -29;
  origin_res(2, 2) = 24;
  res = matrix_1.inverse_matrix();
  ASSERT_TRUE(res == origin_res);
}

TEST(invM3, inversErr) {
  S21Matrix matrix_1(3, 3);

  matrix_1(0, 0) = 0;
  matrix_1(0, 1) = 0;
  matrix_1(0, 2) = 0;

  matrix_1(1, 0) = 6;
  matrix_1(1, 1) = 3;
  matrix_1(1, 2) = 4;

  matrix_1(2, 0) = 5;
  matrix_1(2, 1) = -2;
  matrix_1(2, 2) = -3;

  ASSERT_THROW(matrix_1.inverse_matrix(), std::out_of_range);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
