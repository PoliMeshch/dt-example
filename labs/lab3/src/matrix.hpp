#ifndef MATRIX_CLASS_HPP
#define MATRIX_CLASS_HPP

class Matrix {
private:
    int rows;
    int cols;
    double* data;

public:
    Matrix(int n);
    Matrix(int m, int n, double fill_value = 0);
    Matrix(const Matrix& other);
    
    ~Matrix();

    Matrix& operator=(const Matrix& other);
    Matrix(Matrix&& other);
    Matrix& operator=(Matrix&& other);

    // Составное присваивание
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    // Бинарные операторы
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;

    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const;
    int get_width() const;

    void negate();
    void add_in_place(Matrix& other);
    Matrix multiply(Matrix& other) const;


    void print() const;
};
// Глобальные функции
Matrix operator*(double scalar, const Matrix& m);
Matrix operator-(const Matrix& m);

#endif