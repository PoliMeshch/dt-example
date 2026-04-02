#include "my_string.hpp"
#include <iostream>
#include <cstring>

MyString::MyString() : str(nullptr) {}

MyString::MyString(const char* s) {
    if (s == nullptr) {
        str = nullptr;
        return;
    }
    
    int len = strlen(s);
    str = new char[len + 1];
    
    for (int i = 0; i <= len; i++) {
        str[i] = s[i];
    }
}

MyString::MyString(const MyString& other) {
    str = nullptr;  
    *this = other;  
}

MyString::~MyString() {
    delete[] str;
}

MyString::MyString(MyString&& other) noexcept : str(other.str) {
    other.str = nullptr;  
}

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

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        delete[] str;          
        str = other.str;      
        other.str = nullptr;  
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