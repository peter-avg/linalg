#include "sparse_matrix.hpp"
#include "matrix.hpp"

namespace matrix {
    template <typename T>
    SparseMatrix<T>::SparseMatrix() : SparseMatrix<T>(0, 0) {}

    template <typename T>
    SparseMatrix<T>::SparseMatrix(size_t rows, size_t cols) 
        : rows(rows), cols(cols) {}

    template <typename T>
    SparseMatrix<T>::SparseMatrix(const Matrix<T>& other)
        : rows(other.getRows()), cols(other.getCols()) {
            for (size_t i=0; i < other.getRows(); i++) {
                for (size_t j=0; j < other.getCols(); j++) {
                    if (i != 0 && j != 0) {
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

        for (size_t i=0; i < this->data.size(); i++) {
            for (auto& value : data[row]) {
                if (col == value->col) {
                    return value->data;
                }
            }
        }

        return zero;
    }

    template class CSRValue<int>;
    template class CSRValue<float>;
    template class CSRValue<double>;
    template class SparseMatrix<int>;
    template class SparseMatrix<float>;
    template class SparseMatrix<double>;
}
