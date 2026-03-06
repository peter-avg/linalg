#include "matrix.hpp"

#include <gtest/gtest.h>
#include <cassert>

TEST(DenseMatrix, Init) {
    matrix::Matrix<int>* mat = new matrix::Matrix<int>(2, 2, 1);
    EXPECT_EQ((* mat)(1, 1), 1);
    delete mat;
}
