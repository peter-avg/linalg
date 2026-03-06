#include "matrix.hpp"

namespace matrix {
    template <typename T>
    Matrix<T>::Matrix(size_t rows, size_t cols) 
        : rows(rows), cols(cols), data(rows * cols, 0) {}

    template <typename T>
    Matrix<T>::Matrix(std::vector<T>& data, size_t rows, size_t cols)
        : data(data), rows(rows), cols(cols) {}

    template <typename T>
    Matrix<T>::Matrix(const Matrix& other) 
        : data(other.data), rows(other.rows), cols(other.cols) {}

    template <typename T>
    Matrix<T>::Matrix(size_t rows, size_t cols, T initial)
        : rows(rows), cols(cols), data(rows * cols, initial) {}

    template <typename T>
    Matrix<T>::~Matrix() = default;

    template <typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) = default;

    template <typename T>
    T Matrix<T>::trace() const {
        T trace = 0;

        for (int i=0; i < rows * cols; i++) {
            trace += data[(i * cols) + i];
        }

        return trace;
    }

    template <typename T>
    bool Matrix<T>::operator==(const Matrix<T>& other) const {
        return this->data == other.data &&
               this->cols == other.cols &&
               this->rows == other.rows;
    }

    template <typename T>
    T& Matrix<T>::operator()(size_t row, size_t col) {
        return this->data[(row * col) + col];
    }

    template <typename T>
    const T& Matrix<T>::operator()(size_t row, size_t col) const {
        return this->data[(row * col) + col];
    }
    
    template <typename T>
    T& Matrix<T>::operator[](size_t index) {
        return this->data[index];
    }

    template <typename T>
    const T& Matrix<T>::operator[](size_t index) const {
        return this->data[index];
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator+=(Matrix<T>& other) {
        size_t size = this->cols * this->rows;

        for (size_t i=0; i < size; i++) {
            this->data[i] = this->data[i] + other.data[i];
        }

        return *this;
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator+(Matrix<T>& other) {
        Matrix<T> result = *this;
        result += other;
        return result;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& out, const Matrix<T>* mat) {
        out << "Matrix( ";

        for (size_t i=0; i < mat->getRows(); i++) {
            out << "[ ";
            for (size_t j=0; j < mat->getCols(); j++) {
                out << mat(i, j);
                if (j < mat->getCols() - 1) {
                    out << ", ";
                }
            }

            out << " ]\n";
        }

        out << ")";

        return out;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat) {
        out << "Matrix( ";

        for (size_t i=0; i < mat.getRows(); i++) {
            out << "[ ";
            for (size_t j=0; j < mat.getCols(); j++) {
                out << mat(i, j);
                if (j < mat.getCols() - 1) {
                    out << ", ";
                }
            }

            out << " ]\n";
        }

        out << ")";

        return out;
    }

    template class Matrix<int>;
    template class Matrix<float>;
    template class Matrix<double>;
}
