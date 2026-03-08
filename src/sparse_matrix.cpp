#include "sparse_matrix.hpp"

#include "matrix.hpp"

namespace matrix {
template <typename T>
SparseMatrix<T>::SparseMatrix(size_t rows, size_t cols)
    : data{}, rows(rows), cols(cols) {}

template <typename T>
SparseMatrix<T>::~SparseMatrix() = default;

template <typename T>
SparseMatrix<T>::SparseMatrix(const Matrix<T> other)
    : rows(other.getRows()), cols(other.getCols()), data{} {
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      T val = other(i, j);
      if (val != 0) {
        data[i].push_back(makeCSRValuePtr<T>(other(i, j), j));
      }
    }
  }
}

template <typename T>
const T& SparseMatrix<T>::operator()(size_t row, size_t col) {
  if ((row > rows || row < 0) || (col > cols || col < 0)) {
    std::cerr << "Row and column should be inside the bounds of the Matrix\n";
    std::cerr << "Got " << row << " and " << col << " instead\n";
    exit(1);
  }

  for (auto& value : data[row]) {
    if (col == value->col) {
      return value->data;
    }
  }

  return zero;
}

template <typename T>
[[nodiscard]] SparseMatrix<T> SparseMatrix<T>::toDense() {
  Matrix<T> mat(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat(i, j) = (*this)(i, j);
    }
  }

  return mat;
}

template <typename T>
[[nodiscard]] std::shared_ptr<T[]> SparseMatrix<T>::getDiagonal() {
  size_t diagSize = std::min(rows, cols);
  auto diag = std::make_shared<T[]>(diagSize);
  size_t diagIdx = 0;

  for (size_t i = 0; i < rows; i++) {
    std::vector<CSRValuePtr<T>> data = this->data[i];
    for (auto& value : data) {
      if (value->col == i) {
        diag[diagIdx++] = value->data;
        break;
      }
    }
  }

  return diag;
}

template <typename T>
[[nodiscard]] std::shared_ptr<T[]> SparseMatrix<T>::getInverseDiagonal() {
  size_t diagSize = std::min(rows, cols);
  auto invDiag = std::make_shared<T[]>(diagSize);
  size_t diagIdx = 0;

  for (size_t i = 0; i < rows; i++) {
    std::vector<CSRValuePtr<T>> data = this->data[i];
    for (auto& value : data) {
      if (value->col == i) {
        invDiag[diagIdx++] = T(1) / value->data;
        break;
      }
    }
  }

  return invDiag;
}

template <typename T>
[[nodiscard]] T SparseMatrix<T>::computeTrace() {
  auto diag = this->getDiagonal();
  size_t diagIdx = 0;
  T res = 0;

  for (size_t i = 0; i < rows; i++) {
    res += diag[diagIdx++];
  }

  return res;
}

template class CSRValue<int>;
template class CSRValue<float>;
template class CSRValue<double>;
template class SparseMatrix<int>;
template class SparseMatrix<float>;
template class SparseMatrix<double>;
}  // namespace matrix
