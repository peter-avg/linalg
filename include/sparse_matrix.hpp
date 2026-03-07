#ifndef _INCLUDE_SPARSE_MATRIX_HPP_
#define _INCLUDE_SPARSE_MATRIX_HPP_

#include <cstdio>
#include <map>
#include <vector>

#include "matrix.hpp"

namespace matrix {
template <typename T>
struct CSRValue {
  T data;
  size_t col;

  CSRValue(T data, size_t col) : data(data), col(col) {}
};

template <typename T>
using CSRValuePtr = std::shared_ptr<CSRValue<T>>;

template <typename T, typename... Args>
CSRValuePtr<T> makeCSRValuePtr(Args&&... args) {
  return std::make_shared<CSRValue<T>>(std::forward<Args>(args)...);
}

template <typename T>
using CSRData = std::map<size_t, std::vector<CSRValuePtr<T>>>;

template <typename T>
class SparseMatrix : public Matrix<T> {
 public:
  SparseMatrix() = default;
  SparseMatrix(size_t rows, size_t cols);
  SparseMatrix(const Matrix<T> other);

  ~SparseMatrix();

  const T& operator()(size_t row, size_t col);

  [[nodiscard]] const size_t& getRows() const { return rows; }
  [[nodiscard]] const size_t& getCols() const { return cols; }
  [[nodiscard]] const CSRData<T>& getData() const { return data; }

 private:
  CSRData<T> data;
  size_t rows, cols;
  T zero = T{0};
};
}  // namespace matrix

#endif  // _INCLUDE_SPARSE_MATRIX_HPP_
