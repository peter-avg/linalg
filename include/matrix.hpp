#ifndef _INCLUDE_MATRIX_HPP_
#define _INCLUDE_MATRIX_HPP_

#include <vector>

/**
 * @brief Namespace for matrices 
 * */
namespace matrix {
    /**
     * @brief Matrix class for a dense matrix 
     */
    template <typename T>
    class Matrix {
        public:
            /**
             * @brief Matrix constructor with rows and cols
             * @param size_t rows, the number of rows in the matrix
             * @param size_t cols, the number of columns in the matrix
             * @return The instance of a dense matrix
             */
            Matrix(size_t rows, size_t cols);

            /**
             * @brief Matrix constructor with data, rows, and cols
             * @param std::vector<T> data, the data inside the matrix
             * @param size_t rows, the number of rows in the matrix
             * @param size_t cols, the number of columns in the matrix
             * @return The instance of a dense matrix
             */
            Matrix(std::vector<T> data, size_t rows, size_t cols);
            Matrix(const Matrix& other);
            ~Matrix();

            Matrix<T>& operator=(const Matrix& other) = default;
            bool operator==(const Matrix& other) const;

            T& operator()(size_t row, size_t col);
            const T& operator()(size_t row, size_t col) const;
            T& operator[](size_t index);
            const T& operator[](size_t index) const;

            Matrix<T>& operator+=(Matrix<T>& other);
            Matrix<T> operator+(Matrix<T>& other);

        private:
            std::vector<T> data;
            size_t rows, cols;
    };
}

#endif // _INCLUDE_MATRIX_HPP_
