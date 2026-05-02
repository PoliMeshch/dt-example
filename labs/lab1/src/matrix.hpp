#ifndef MATRIX_CLASS_HPP
#define MATRIX_CLASS_HPP

class Matrix {
private:
    int rows;
    int cols;
    double* data;

public:
    // Конструкторы
    Matrix(int n);  // Единичная матрица n x n
    Matrix(int m, int n, double fill_value = 0);  // Матрица m x n, заполненная fill_value
    Matrix(const Matrix& other);  // Конструктор копирования
    
    // Деструктор
    ~Matrix();

    // Оператор присваивания 
    Matrix& operator=(const Matrix& other);
    // TODO: узнать про move-семантику, добавить конструктор/оператор

    // Move-семантика позволяет передавать владение ресурсами между объектами
    // без лишнего копирования. Для этого нужны конструктор перемещения
    // и оператор присваивания перемещением.

    // Конструктор перемещения вызывается при создании объекта из временного
    // (например, при возврате из функции).
    // Оператор присваивания перемещением — при присваивании временного объекта.

    // Они не выделяют новую память, а просто передают указатель на данные
    // от исходного объекта к новому, а исходный обнуляют.
    // Это намного быстрее, чем копирование всех элементов.

    // Добавляю оба метода для полноты реализации:
    Matrix(Matrix&& other);                // Конструктор перемещения
    Matrix& operator=(Matrix&& other);     // Оператор присваивания перемещением


    // Методы доступа
    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const;
    int get_width() const;

    // Операции с матрицами
    void negate();  // -A
    void add_in_place(Matrix& other);  // this += other
    Matrix multiply(Matrix& other) const;  // Умножение

    // Вспомогательные методы
    void print() const;  // Для отладки
};

#endif