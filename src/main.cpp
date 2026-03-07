#include "sparse_matrix.hpp"

int main() {
  matrix::Matrix<int> dense(4, 4, 0);
  dense(0, 0) = 4;

  std::cout << dense;
  std::cout << dense(0, 0);
  std::cout << dense(1, 0);

  matrix::SparseMatrix<int> sparse(dense);

  return 0;
}
