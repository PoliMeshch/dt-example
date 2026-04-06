#ifndef RECT_HPP
#define RECT_HPP
#include <iostream>
class Rect {
private:
    // Новая реализация
    int x;      // x координата левой нижней точки
    int y;      // y координата левой нижней точки  
    int width;
    int height;
    /* Старая реализация:
    int left;
    int right;
    int top;
    int bottom;  
    */
public:
    Rect(); // Конструктор по умолчанию

    // TODO: перечислить все места, где пользователь может ввести неконсистентные данные
    // 1. Конструктор Rect(int l, int r, int t, int b) - может передать l > r или t < b
    // 2. Метод set_all(int l, int r, int t, int b) - аналогично

    // TODO: убедиться, что в этом случае, поля будут записаны так, что лево <= право, низ <= верх

    // Теперь меняю поля в этих методах и вывожу сообщение об исправлении данных 

    Rect(int l, int r, int t, int b); // Конструктор с параметрами
    Rect(const Rect& other); // Конструктор копирования
    ~Rect();

    // Методы доступа
    int get_left() const;
    int get_right() const;
    int get_top() const;
    int get_bottom() const;
    
    void set_all(int l, int r, int t, int b);

    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_left, int d_right, int d_top, int d_bottom);
    void move(int dx, int dy = 0);

    // Методы для вычисляемых свойств
    int get_width() const;
    int get_height() const;
    int get_square() const;
    
    // Методы для изменения размеров
    void set_width(int new_width);
    void set_height(int new_height);

    // Задание 4.4*. Рефакторинг.
    // Вспомогательные методы для нормализации
    int normalized_left() const;
    int normalized_right() const;
    int normalized_top() const;
    int normalized_bottom() const;
};

// Rect bounding_rect(Rect r1, Rect r2);
Rect bounding_rect(const Rect& r1, const Rect& r2);  // const& вместо копирования
void print_rect(const Rect& r);

#endif