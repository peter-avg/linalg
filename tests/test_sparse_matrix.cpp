#include <gtest/gtest.h>

#include <cassert>

#include "matrix.hpp"
#include "sparse_matrix.hpp"

TEST(SparseMatrix, Init) {
  matrix::Matrix<int> dense(4, 4, 0);
  dense(0, 0) = 1;
  EXPECT_NO_FATAL_FAILURE(matrix::SparseMatrix<int> sparse(dense));
}

TEST(SparseMatrix, NonZeroItem) {
  matrix::Matrix<int> dense(4, 4, 0);
  dense(0, 0) = 1;
  matrix::SparseMatrix<int> sparse(dense);

  std::cerr << "Sparse Matrix at (0, 0): " << sparse(0, 0) << "\n";

  EXPECT_EQ(sparse(0, 0), 1);
}

TEST(SparseMatrix, ZeroItem) {
  matrix::Matrix<int> dense(4, 4, 0);
  dense(0, 0) = 1;
  matrix::SparseMatrix<int> sparse(dense);

  std::cerr << "Sparse Matrix at (0, 0): " << sparse(0, 0) << "\n";

  EXPECT_EQ(sparse(1, 1), 0);
}
