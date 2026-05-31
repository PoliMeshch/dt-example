#include "matrix.hpp"
#include <iostream>

Matrix::Matrix(int n) : rows(n), cols(n) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[Matrix] Конструктор единичной матрицы: " << this << std::endl;
    #endif
    if (n <= 0) {
        throw "Размер матрицы должен быть положительным числом";
    }
    
    data = new double[rows * cols]();
    
    for (int i = 0; i < rows; ++i) {
        data[i * cols + i] = 1.0;
    }
}

Matrix::Matrix(int m, int n, double fill_value) : rows(m), cols(n) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[Matrix] Конструктор с заполнением: " << this << " (" << rows << "x" << cols << ")" << std::endl;
    #endif
    if (m <= 0 or n <= 0) {
        throw "Размеры матрицы должны быть положительными числами";
    }
    
    data = new double[rows * cols];
    
    for (int i = 0; i < rows * cols; ++i) {
        data[i] = fill_value;
    }
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[Matrix] Конструктор копирования: " << this << " (" << rows << "x" << cols << ")" << std::endl;
    #endif
    data = new double[rows * cols];
    
    for (int i = 0; i < rows * cols; ++i) {
        data[i] = other.data[i];
    }
}

Matrix::~Matrix() {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[Matrix] Деструктор: " << this << std::endl;
    #endif
    delete[] data;
}

Matrix& Matrix::operator=(const Matrix& other) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[Matrix] Оператор = копированием: " << this << std::endl;
    #endif
    if (this == &other) {
        return *this;
    }
    
    delete[] data;
    
    rows = other.rows;
    cols = other.cols;
    
    data = new double[rows * cols];
    for (int i = 0; i < rows * cols; ++i) {
        data[i] = other.data[i];
    }
    
    return *this;
}

Matrix::Matrix(Matrix&& other)
    : rows(other.rows), cols(other.cols), data(other.data) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[Matrix] Конструктор перемещения: " << this << " (память НЕ выделяется)" << std::endl;
    #endif
    other.rows = 0;
    other.cols = 0;
    other.data = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[Matrix] Оператор = перемещением: " << this << " (память НЕ выделяется)" << std::endl;
    #endif
    if (this != &other) {
        delete[] data;
        
        rows = other.rows;
        cols = other.cols;
        data = other.data;
        
        other.rows = 0;
        other.cols = 0;
        other.data = nullptr;
    }
    return *this;
}

// Составное присваивание
Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows != other.rows or cols != other.cols) {
        throw "Размеры матриц должны совпадать для сложения";
    }
    for (int i = 0; i < rows * cols; ++i) {
        data[i] += other.data[i];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows != other.rows or cols != other.cols) {
        throw "Размеры матриц должны совпадать для вычитания";
    }
    for (int i = 0; i < rows * cols; ++i) {
        data[i] -= other.data[i];
    }
    return *this;
}

Matrix& Matrix::operator*=(double scalar) {
    for (int i = 0; i < rows * cols; ++i) {
        data[i] *= scalar;
    }
    return *this;
}

Matrix& Matrix::operator/=(double scalar) {
    if (scalar == 0) {
        throw "Деление на ноль!";
    }
    for (int i = 0; i < rows * cols; ++i) {
        data[i] /= scalar;
    }
    return *this;
}

// Бинарные операторы (через составные)
Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result = *this;
    result += other;
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result = *this;
    result -= other;
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw "Количество столбцов первой матрицы должно равняться количеству строк второй";
    }
    Matrix result(rows, other.cols, 0.0);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < cols; ++k) {
                sum += get(i, k) * other.get(k, j);
            }
            result.set(i, j, sum);
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result = *this;
    result *= scalar;
    return result;
}

Matrix Matrix::operator/(double scalar) const {
    Matrix result = *this;
    result /= scalar;
    return result;
}


double Matrix::get(int i, int j) const {
    if (i < 0 or i >= rows or j < 0 or j >= cols) {
        throw "Индекс за пределами допустимых значений";
    }
    
    return data[i * cols + j];
}

void Matrix::set(int i, int j, double value) {
    if (i < 0 or i >= rows or j < 0 or j >= cols) {
        throw "Индекс за пределами допустимых значений";
    }
    
    data[i * cols + j] = value;
}

int Matrix::get_height() const {
    return rows;
}

int Matrix::get_width() const {
    return cols;
}

void Matrix::negate() {
    for (int i = 0; i < rows * cols; ++i) {
        data[i] = -data[i];
    }
}

void Matrix::add_in_place(Matrix& other) {
    if (rows != other.rows or cols != other.cols) {
        throw "Несоответствие размеров матрицы для сложения";
    }
    
    for (int i = 0; i < rows * cols; ++i) {
        data[i] += other.data[i];
    }
}

Matrix Matrix::multiply(Matrix& other) const {
    if (cols != other.rows) {
        throw "Несоответствие размеров матрицы для умножения";
    }
    
    Matrix result(rows, other.cols, 0.0);
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < cols; ++k) {
                sum += get(i, k) * other.get(k, j);
            }
            result.set(i, j, sum);
        }
    }
    
    return result;
}

void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << get(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

// Глобальные функции
Matrix operator*(double scalar, const Matrix& m) {
    return m * scalar;
}

Matrix operator-(const Matrix& m) {
    Matrix result = m;
    result.negate();
    return result;
}