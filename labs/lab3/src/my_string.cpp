#include "my_string.hpp"
#include <iostream>
#include <cstring>

MyString::MyString() : str(nullptr) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[MyString] Конструктор по умолчанию: " << this << std::endl;
    #endif
}


MyString::MyString(const char* s) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[MyString] Конструктор из C-строки: " << this << std::endl;
    #endif
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
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[MyString] Конструктор копирования: " << this << std::endl;
    #endif
    str = nullptr;  
    *this = other;  
}

MyString::~MyString() {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[MyString] Деструктор: " << this << std::endl;
    #endif
    delete[] str;
}

MyString::MyString(MyString&& other) : str(other.str) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[MyString] Конструктор перемещения: " << this << std::endl;
    #endif
    other.str = nullptr;  
}

MyString& MyString::operator=(const MyString& other) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[MyString] Оператор присваивания копированием: " << this << std::endl;
    #endif
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

MyString& MyString::operator=(MyString&& other) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "[MyString] Оператор присваивания перемещением: " << this << std::endl;
    #endif
    if (this != &other) {
        delete[] str;          
        str = other.str;      
        other.str = nullptr;  
    }
    return *this;
}

// Составное присваивание
MyString& MyString::operator+=(const MyString& other) {
    if (other.str == nullptr) return *this;
    
    int old_len = get_length();
    int new_len = old_len + other.get_length();
    char* new_str = new char[new_len + 1];
    
    for (int i = 0; i < old_len; ++i) {
        new_str[i] = str[i];
    }
    for (int i = 0; i < other.get_length(); ++i) {
        new_str[old_len + i] = other.str[i];
    }
    new_str[new_len] = '\0';
    
    delete[] str;
    str = new_str;
    return *this;
}

MyString& MyString::operator+=(const char* s) {
    if (s == nullptr) return *this;
    return *this += MyString(s);
}

// Операторы сравнения
bool MyString::operator==(const MyString& other) const {
    if (str == nullptr and other.str == nullptr) return true;
    if (str == nullptr or other.str == nullptr) return false;
    int i = 0;
    while (str[i] != '\0' and other.str[i] != '\0') {
        if (str[i] != other.str[i]) return false;
        i++;
    }
    return str[i] == other.str[i];
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

bool MyString::operator<(const MyString& other) const {
    if (str == nullptr and other.str == nullptr) return false;
    if (str == nullptr) return true;
    if (other.str == nullptr) return false;
    int i = 0;
    while (str[i] != '\0' and other.str[i] != '\0') {
        if (str[i] < other.str[i]) return true;
        if (str[i] > other.str[i]) return false;
        i++;
    }
    return str[i] == '\0' and other.str[i] != '\0';
}

bool MyString::operator<=(const MyString& other) const {
    return (*this == other) or (*this < other);
}

// Операторы индекисрования
char& MyString::operator[](int index) {
    int len = get_length();
    if (index < 0 or index >= len) {
        throw "Индекс за пределами строки";
    }
    return str[index];
}

const char& MyString::operator[](int index) const {
    int len = get_length();
    if (index < 0 or index >= len) {
        throw "Индекс за пределами строки";
    }
    return str[index];
}

// Бинарные операторы
MyString operator+(const MyString& a, const MyString& b) {
    MyString result = a;
    result += b;
    return result;
}

MyString operator+(const MyString& a, const char* b) {
    MyString result = a;
    result += b;
    return result;
}

MyString operator+(const char* a, const MyString& b) {
    MyString result(a);
    result += b;
    return result;
}

char MyString::get(int i) const {
    if (str == nullptr) throw "Строка пуста";
    int len = strlen(str);
    if (i < 0 or i >= len) {
        throw "Индекс за пределами допустимых значений";
    }
    return str[i];
}

void MyString::set(int i, char c) {
    int len = strlen(str);
    if (i < 0 or i >= len) {
        throw "Индекс за пределами допустимых значений";
    }
    str[i] = c;
}

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

void MyString::read_line() {
    const int size = 32;
    int capacity = size;
    char* buffer = new char[capacity];
    
    int pos = 0;
    char ch;
    
    while (std::cin.get(ch) and ch != '\n') {
        if (pos + 1 >= capacity) {  
            int new_capacity = capacity * 2;
            char* new_buffer = new char[new_capacity];
            
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

// Глобальные операторы
bool operator==(const char* s, const MyString& str) {
    return str == MyString(s);
}

bool operator!=(const char* s, const MyString& str) {
    return !(s == str);
}

bool operator<(const char* s, const MyString& str) {
    return MyString(s) < str;
}

bool operator<=(const char* s, const MyString& str) {
    return MyString(s) <= str;
}

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& os, const MyString& s) {
    if (s.get_length() == 0) return os;
    for (int i = 0; i < s.get_length(); ++i) {
        os << s.get(i);
    }
    return os;
}

std::istream& operator>>(std::istream& is, MyString& s) {
    char buffer[1024];
    is.getline(buffer, 1024);
    s.set_new_string(buffer);
    return is;
}

MyString addTxtExtension(const MyString &path) { 
    return path + ".txt"; 
}