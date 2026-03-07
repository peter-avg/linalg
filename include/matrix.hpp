#ifndef _INCLUDE_MATRIX_HPP_
#define _INCLUDE_MATRIX_HPP_

#include <iostream>
#include <vector>

/**
 * @brief Namespace for dense and sparse matrices
 * */
namespace matrix {
    /**
     * @brief Matrix class for a dense matrix 
     */
    template <typename T>
    class Matrix {
        public:
            Matrix() = default;
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
            Matrix(std::vector<T>& data, size_t rows, size_t cols);

            /**
             * @brief Copy constructor for Matrix constructor 
             * @param const Matrix& other, the Matrix we are copying
             * @return The instance of a dense matrix
             */
            Matrix(const Matrix& other);

            /**
             * @brief Move constructor for Matrix constructor 
             * @param Matrix&& other, the Matrix we are moving
             */
            Matrix(Matrix&& other) noexcept;

            /**
             * @brief Matrix constructor with rows and cols, and an initial value
             * @param size_t rows, the number of rows in the matrix
             * @param size_t cols, the number of columns in the matrix
             * @param T initial, the initial value for all points in the matrix
             * @return The instance of a dense matrix
             */
            Matrix(size_t rows, size_t cols, T initial);

            /**
             * @brief Matrix destructor
             */
            ~Matrix();



            /*
             * @brief Method that returns the trace of a matrix
             * @return The trace of a matrix;
             */
            [[nodiscard]] T trace() const;

            T& operator()(size_t row, size_t col);
            const T& operator()(size_t row, size_t col) const;
            T& operator[](size_t index);
            const T& operator[](size_t index) const;

            bool operator==(const Matrix& other) const;

            Matrix<T>& operator=(const Matrix& other);
            Matrix<T>& operator=(Matrix&& other) noexcept;
            Matrix<T>& operator=(Matrix other);
            Matrix<T> operator+(const Matrix<T>& other);
            Matrix<T>& operator+=(const Matrix<T>& other);
            Matrix<T> operator-(const Matrix<T>& other);
            Matrix<T>& operator-=(const Matrix<T>& other);
            Matrix<T> operator*(const Matrix<T>& other);
            Matrix<T>& operator*=(const Matrix<T>& other);

            [[nodiscard]] const size_t& getRows() const { return rows; }
            [[nodiscard]] const size_t& getCols() const { return cols; }
            [[nodiscard]] const size_t& getData() const { return data; }

            friend std::ostream& operator<<(std::ostream& out, const Matrix<T>* mat);
            friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat);

        private:
            std::vector<T> data;
            size_t rows, cols;
    };
}

#endif // _INCLUDE_MATRIX_HPP_
