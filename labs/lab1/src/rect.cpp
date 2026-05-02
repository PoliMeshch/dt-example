#include "rect.hpp"

// Конструктор по умолчанию (единичный квадрат в начале координат)
Rect::Rect() 
    : x(0), y(0), width(1), height(1) {
    #ifdef DEBUG_CONSTRUCTORS
    std::cout << "Constructor #1 (default): " << this << std::endl;
    #endif
}

// Конструктор с параметрами
Rect::Rect(int l, int r, int t, int b) {
    // Нормализуем и конвертируем в новый формат
    /* int left = std::min(l, r);
    int right = std::max(l, r);
    int bottom = std::min(t, b);
    int top = std::max(t, b); */

    int left, right, top, bottom;
    // Проверка горизонтальных координат
    if (l <= r) {
        left = l;
        right = r;
    } else {
        std::cout << "Предупреждение: left > right, значения исправлены" << std::endl;
        left = r;
        right = l;
    }
    
    // Проверка вертикальных координат
    if (b <= t) {
        bottom = b;
        top = t;
    } else {
        std::cout << "Предупреждение: bottom > top, значения исправлены" << std::endl;
        bottom = t;
        top = b;
    }

    x = left;
    y = bottom;
    width = right - left;
    height = top - bottom;
    
    #ifdef DEBUG_CONSTRUCTORS
    std::cout << "Constructor #2 (params): " << this << std::endl;
    #endif
}

// Конструктор копирования
Rect::Rect(const Rect& other) 
    : x(other.x), y(other.y), width(other.width), height(other.height) {
    #ifdef DEBUG_CONSTRUCTORS
    std::cout << "Constructor #3 (copy): " << this << std::endl;
    #endif
}

// Деструктор
Rect::~Rect() {
    #ifdef DEBUG_CONSTRUCTORS
    std::cout << "Destructor: " << this << std::endl;
    #endif
}

// Новые методы доступа
int Rect::get_left() const {
    return x;
}

int Rect::get_right() const {
    return x + width;
}

int Rect::get_top() const {
    return y + height;
}

int Rect::get_bottom() const {
    return y;
}


void Rect::set_all(int l, int r, int t, int b) {
    // Нормализуем
    /* int left = std::min(l, r);
    int right = std::max(l, r);
    int bottom = std::min(t, b);
    int top = std::max(t, b); */

    int left, right, top, bottom;
    // Проверка горизонтальных координат
    if (l <= r) {
        left = l;
        right = r;
    } else {
        std::cout << "Предупреждение: left > right, значения исправлены" << std::endl;
        left = r;
        right = l;
    }
    
    // Проверка вертикальных координат
    if (b <= t) {
        bottom = b;
        top = t;
    } else {
        std::cout << "Предупреждение: bottom > top, значения исправлены" << std::endl;
        bottom = t;
        top = b;
    }
    
    x = left;
    y = bottom;
    width = right - left;
    height = top - bottom;
}

// Методы с прямоугольниками
void Rect::inflate(int amount) {
    inflate(amount, amount, amount, amount);
}

void Rect::inflate(int dw, int dh) {
    inflate(dw, dw, dh, dh);
}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    x -= d_left;
    y -= d_bottom;
    width += d_left + d_right;
    height += d_top + d_bottom;
    
    if (width < 0) width = 0;
    if (height < 0) height = 0;
}

void Rect::move(int dx, int dy) {
    x += dx;
    y += dy;
}

// Вычисляемые свойства 
int Rect::get_width() const {
    return width;
}

int Rect::get_height() const {
    return height;
}

int Rect::get_square() const {
    return width * height;
}

// Изменение размеров
void Rect::set_width(int new_width) {
    if (new_width >= 0) {
        width = new_width;
    }
}

void Rect::set_height(int new_height) {
    if (new_height >= 0) {
        height = new_height;
    }
}

// Нормализованные геттеры
int Rect::normalized_left() const {
    return x;  // всегда левая
}

int Rect::normalized_right() const {
    return x + width;  // всегда правее left
}

int Rect::normalized_top() const {
    return y + height;  // всегда выше bottom
}

int Rect::normalized_bottom() const {
    return y;  // всегда нижняя
}
// Свободные функции
Rect bounding_rect(const Rect& r1, const Rect& r2) {
    /* // Нормализуем первый прямоугольник
    int r1_left = (r1.get_left() < r1.get_right()) ? r1.get_left() : r1.get_right();
    int r1_right = (r1.get_left() < r1.get_right()) ? r1.get_right() : r1.get_left();
    int r1_top = (r1.get_top() > r1.get_bottom()) ? r1.get_top() : r1.get_bottom();
    int r1_bottom = (r1.get_top() > r1.get_bottom()) ? r1.get_bottom() : r1.get_top();
    
    // Нормализуем второй прямоугольник
    int r2_left = (r2.get_left() < r2.get_right()) ? r2.get_left() : r2.get_right();
    int r2_right = (r2.get_left() < r2.get_right()) ? r2.get_right() : r2.get_left();
    int r2_top = (r2.get_top() > r2.get_bottom()) ? r2.get_top() : r2.get_bottom();
    int r2_bottom = (r2.get_top() > r2.get_bottom()) ? r2.get_bottom() : r2.get_top();
    
    // Берем границы
    int min_left = (r1_left < r2_left) ? r1_left : r2_left;
    int max_right = (r1_right > r2_right) ? r1_right : r2_right;
    int max_top = (r1_top > r2_top) ? r1_top : r2_top;         
    int min_bottom = (r1_bottom < r2_bottom) ? r1_bottom : r2_bottom; */
    
    int min_left = std::min(r1.normalized_left(), r2.normalized_left());
    int max_right = std::max(r1.normalized_right(), r2.normalized_right());
    int max_top = std::max(r1.normalized_top(), r2.normalized_top());
    int min_bottom = std::min(r1.normalized_bottom(), r2.normalized_bottom());

    return Rect(min_left, max_right, max_top, min_bottom);
}
void print_rect(const Rect& r) {
    std::cout << "r3(" << r.get_left() 
              << ", " << r.get_right()
              << ", " << r.get_top()
              << ", " << r.get_bottom() << ")" << std::endl;
}

// Старая версия
/**
 * Rect::Rect() 
 *     : left(0), right(0), top(0), bottom(0) {
 *     #ifdef DEBUG_CONSTRUCTORS
 *     std::cout << "Constructor #1 (default): " << this << std::endl;
 *     #endif
 * }
 * 
 * Rect::Rect(int l, int r, int t, int b)
 *     : left(l), right(r), top(t), bottom(b) {
 *     #ifdef DEBUG_CONSTRUCTORS
 *     std::cout << "Constructor #2 (params): " << this << std::endl;
 *     #endif
 * }
 * 
 * Rect::Rect(const Rect& other) 
 *     : left(other.left), right(other.right), top(other.top), bottom(other.bottom) {
 *     #ifdef DEBUG_CONSTRUCTORS
 *     std::cout << "Constructor #3 (copy): " << this << std::endl;
 *     #endif
 * }
 * 
 * Rect::~Rect() {
 *     #ifdef DEBUG_CONSTRUCTORS
 *     std::cout << "Destructor: " << this << std::endl;
 *     #endif
 * }
 * 
 * int Rect::get_left() const {
 *     return left;
 * }
 * 
 * int Rect::get_right() const {
 *     return right;
 * }
 * 
 * int Rect::get_top() const {
 *     return top;
 * }
 * 
 * int Rect::get_bottom() const {
 *     return bottom;
 * }
 * 
 * void Rect::set_all(int l, int r, int t, int b) {
 *     left = l;
 *     right = r;
 *     top = t;
 *     bottom = b;
 * }
 * 
 * void Rect::inflate(int amount) {
 *     // Старая реализация:
 *     // left -= amount;
 *     // right += amount;
 *     // top += amount;
 *     // bottom -= amount;
 *     inflate(amount, amount, amount, amount);
 * }
 * 
 * void Rect::inflate(int dw, int dh) {
 *     // Старая реализация:
 *     // left -= dw;
 *     // right += dw;
 *     // top += dh;
 *     // bottom -= dh;
 *     inflate(dw, dw, dh, dh);
 * }
 * 
 * void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
 *     left -= d_left;
 *     right += d_right;
 *     top += d_top;
 *     bottom -= d_bottom;
 * }
 * 
 * void Rect::move(int dx, int dy) {
 *     left += dx;
 *     right += dx;
 *     top += dy;
 *     bottom += dy;
 * }
 * 
 * int Rect::get_width() const {
 *     // Старая реализация: return right - left;
 *     return std::abs(right - left);
 * }
 * 
 * int Rect::get_height() const {
 *     // Старая реализация: return top - bottom;
 *     return std::abs(top - bottom);
 * }
 * 
 * int Rect::get_square() const {
 *     return get_width() * get_height();
 * }
 * 
 * void Rect::set_width(int new_width) {
 *     if (new_width >= 0) {
 *         right = left + new_width;
 *     }
 * }
 * 
 * void Rect::set_height(int new_height) {
 *     if (new_height >= 0) {
 *         top = bottom + new_height;
 *     }
 * }
 * 
 * int Rect::normalized_left() const {
 *     return std::min(left, right);
 * }
 * 
 * int Rect::normalized_right() const {
 *     return std::max(left, right);
 * }
 * 
 * int Rect::normalized_top() const {
 *     return std::max(top, bottom);
 * }
 * 
 * int Rect::normalized_bottom() const {
 *     return std::min(top, bottom);
 * }
 * 
 * Rect bounding_rect(const Rect& r1, const Rect& r2) {
 *     // Старая реализация (до 4.4):
 *     // int r1_left = (r1.get_left() < r1.get_right()) ? r1.get_left() : r1.get_right();
 *     // int r1_right = (r1.get_left() < r1.get_right()) ? r1.get_right() : r1.get_left();
 *     // int r1_top = (r1.get_top() > r1.get_bottom()) ? r1.get_top() : r1.get_bottom();
 *     // int r1_bottom = (r1.get_top() > r1.get_bottom()) ? r1.get_bottom() : r1.get_top();
 *     // 
 *     // int r2_left = (r2.get_left() < r2.get_right()) ? r2.get_left() : r2.get_right();
 *     // int r2_right = (r2.get_left() < r2.get_right()) ? r2.get_right() : r2.get_left();
 *     // int r2_top = (r2.get_top() > r2.get_bottom()) ? r2.get_top() : r2.get_bottom();
 *     // int r2_bottom = (r2.get_top() > r2.get_bottom()) ? r2.get_bottom() : r2.get_top();
 *     // 
 *     // int min_left = (r1_left < r2_left) ? r1_left : r2_left;
 *     // int max_right = (r1_right > r2_right) ? r1_right : r2_right;
 *     // int max_top = (r1_top > r2_top) ? r1_top : r2_top;         
 *     // int min_bottom = (r1_bottom < r2_bottom) ? r1_bottom : r2_bottom;
 *
 *     int min_left = std::min(r1.normalized_left(), r2.normalized_left());
 *     int max_right = std::max(r1.normalized_right(), r2.normalized_right());
 *     int max_top = std::max(r1.normalized_top(), r2.normalized_top());
 *     int min_bottom = std::min(r1.normalized_bottom(), r2.normalized_bottom());
 * 
 *     return Rect(min_left, max_right, max_top, min_bottom);
 * }
 * 
 * void print_rect(const Rect& r) {
 *     std::cout << "Rect(" << r.get_left() 
 *               << ", " << r.get_right()
 *               << ", " << r.get_top()
 *               << ", " << r.get_bottom() << ")" << std::endl;
 * }
 */