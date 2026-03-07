#include "sparse_matrix.hpp"

int main() {
  matrix::Matrix<int> dense(4, 4, 0);
  dense(0, 0) = 4;

  matrix::SparseMatrix<int> sparse(dense);

  matrix::CSRData<int> data = sparse.getData();

  std::cout << data;

  return 0;
}
