#include "matrix.hpp"
#include <iostream>

// Конструктор единичной матрицы
Matrix::Matrix(int n) : rows(n), cols(n) {
    if (n <= 0) {
        throw "Размер матрицы должен быть положительным числом";
    }
    
    data = new double[rows * cols]();  // инициализирует нулями
    
    // Заполняем единичную матрицу
    for (int i = 0; i < rows; ++i) {
        data[i * cols + i] = 1.0;
    }
}

// Конструктор матрицы с заполнением
Matrix::Matrix(int m, int n, double fill_value) : rows(m), cols(n) {
    if (m <= 0 or n <= 0) {
        throw "Размеры матрицы должны быть положительными числами";
    }
    
    data = new double[rows * cols];
    
    for (int i = 0; i < rows * cols; ++i) {
        data[i] = fill_value;
    }
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = new double[rows * cols];
    
    for (int i = 0; i < rows * cols; ++i) {
        data[i] = other.data[i];
    }
}

// Деструктор
Matrix::~Matrix() {
    delete[] data;
}

// Оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
    // Проверка на самоприсваивание
    if (this == &other) {
        return *this;
    }
    
    // Освобождаем старую память
    delete[] data;
    
    // Копируем размеры
    rows = other.rows;
    cols = other.cols;
    
    // Выделяем новую память и копируем данные
    data = new double[rows * cols];
    for (int i = 0; i < rows * cols; ++i) {
        data[i] = other.data[i];
    }
    
    return *this;
}


// Конструктор перемещения
Matrix::Matrix(Matrix&& other) noexcept
    : rows(other.rows), cols(other.cols), data(other.data) {
    other.rows = 0;
    other.cols = 0;
    other.data = nullptr;
}

// Оператор присваивания перемещением
Matrix& Matrix::operator=(Matrix&& other) noexcept {
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


// Получить элемент
double Matrix::get(int i, int j) const {
    if (i < 0 or i >= rows or j < 0 or j >= cols) {
        throw "Индекс за пределами допустимых значений";
    }
    
    return data[i * cols + j];
}

// Установить элемент
void Matrix::set(int i, int j, double value) {
    if (i < 0 or i >= rows or j < 0 or j >= cols) {
        throw "Индекс за пределами допустимых значений";
    }
    
    data[i * cols + j] = value;
}

// Получить высоту
int Matrix::get_height() const {
    return rows;
}

// Получить ширину
int Matrix::get_width() const {
    return cols;
}

// Операция отрицания
void Matrix::negate() {
    for (int i = 0; i < rows * cols; ++i) {
        data[i] = -data[i];
    }
}

// Сложение матриц
void Matrix::add_in_place(Matrix& other) {
    if (rows != other.rows or cols != other.cols) {
        throw "Несоответствие размеров матрицы для сложения";
    }
    
    for (int i = 0; i < rows * cols; ++i) {
        data[i] += other.data[i];
    }
}

// Умножение матриц
Matrix Matrix::multiply(Matrix& other) const {
    if (cols != other.rows) {
        throw "Несоответствие размеров матрицы для умножения";
    }
    
    // Результирующая матрица размера rows x other.cols
    Matrix result(rows, other.cols, 0.0);
    
    // Умножение
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

// Вспомогательный метод для печати
void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << get(i, j) << " ";
        }
        std::cout << std::endl;
    }
}