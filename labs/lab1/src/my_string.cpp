#include "my_string.hpp"
#include <iostream>
#include <cstring>

// Конструктор по умолчанию - пустая строка
MyString::MyString() : str(nullptr) {
    // TODO: обойтись без выделения памяти
    /* str = new char[1];
    str[0] = '\0'; */
}

// Конструктор из C-строки
MyString::MyString(const char* s) {
    if (s == nullptr) {
        str = nullptr;
        /* str = new char[1];
        str[0] = '\0'; */
        return;
    }
    
    int len = strlen(s);
    str = new char[len + 1];
    
    // Копируем строку
    for (int i = 0; i <= len; i++) {
        str[i] = s[i];
    }
}

// Конструктор копирования
MyString::MyString(const MyString& other) {
    // TODO: переиспользовать оператор присваивания (ниже то же самое в операторе присваивания)
    str = nullptr;  
    *this = other;  
    /* int len = strlen(other.str);
    str = new char[len + 1];
    
    for (int i = 0; i <= len; i++) {
        str[i] = other.str[i];
    } */
}

// Деструктор
MyString::~MyString() {
    delete[] str;
}

// Оператор присваивания
MyString& MyString::operator=(const MyString& other) {
    if (this == &other) {
        return *this;
    }
    
    delete[] str;
    if (other.str == nullptr) {
        str = nullptr;
        return *this;
    }
    
    int len = strlen(other.str);
    str = new char[len + 1];
    
    for (int i = 0; i <= len; i++) {
        str[i] = other.str[i];
    }
    
    return *this;
}

// Получаем символ по индексу
char MyString::get(int i) const {
    if (str == nullptr) throw "Строка пуста";
    int len = strlen(str);
    if (i < 0 or i >= len) {
        throw "Индекс за пределами допустимых значений";
    }
    return str[i];
}

// Устанавливаем символ по индексу
void MyString::set(int i, char c) {
    int len = strlen(str);
    if (i < 0 or i >= len) {
        throw "Индекс за пределами допустимых значений";
    }
    str[i] = c;
}

// Заменяем строку на новую
void MyString::set_new_string(const char* s) {
    /* if (s == nullptr) {
        delete[] str;
        str = new char[1];
        str[0] = '\0';
        return;
    } */
    delete[] str;
    if (s == nullptr or s[0] == '\0') {
        str = nullptr;
        return;
    }
    int len = strlen(s);
    str = new char[len + 1]; 
    for (int i = 0; i <= len; i++) {
        str[i] = s[i];
    }
}

void MyString::print() const {
    if (str == nullptr) {
        std::cout << "";
    } else {
        std::cout << str;
    }
}

// Читаем строку
void MyString::read_line() {
    const int size = 32;  // Начальный размер
    int capacity = size;
    char* buffer = new char[capacity];
    
    int pos = 0;
    char ch;
    
    // Читаем по одному символу
    while (std::cin.get(ch) and ch != '\n') {
        // Если буфер заполнен - увеличиваем
        if (pos + 1 >= capacity) {  
            int new_capacity = capacity * 2;
            char* new_buffer = new char[new_capacity];
            
            // Копируем уже прочитанное
            for (int i = 0; i < pos; i++) {
                new_buffer[i] = buffer[i];
            }
            
            delete[] buffer;
            buffer = new_buffer;
            capacity = new_capacity;
        }
        
        buffer[pos++] = ch;
    }
    
    buffer[pos] = '\0';
    if (pos == 0) {
        delete[] buffer;
        set_new_string(nullptr);
        return;
    }
    set_new_string(buffer);
    delete[] buffer;
}

int MyString::get_length() const {
    if (str == nullptr) return 0;
    return strlen(str);
}