#ifndef MY_STRING_HPP
#define MY_STRING_HPP
#include <iostream>

class MyString {
private:
    char* str;

public:
    MyString();
    MyString(const char* s);
    MyString(const MyString& other);

    MyString(MyString&& other);
    MyString& operator=(MyString&& other);
    
    ~MyString();
    
    MyString& operator=(const MyString& other);

    // Составное присваивание
    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char* s);

    // Операторы сравнения
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator<=(const MyString& other) const;

    // Операторы индекисрования
    char& operator[](int index);
    const char& operator[](int index) const;
    
    char get(int i) const;
    void set(int i, char c);

    void set_new_string(const char* str);
    void print() const;
    void read_line();

    int get_length() const;
    const char* c_str() const { return str; }
};
// Бинарные операторы
MyString operator+(const MyString& a, const MyString& b);
MyString operator+(const MyString& a, const char* b);
MyString operator+(const char* a, const MyString& b);

// Глобальные операторы для сравнения с const char* 
bool operator==(const char* s, const MyString& str);
bool operator!=(const char* s, const MyString& str);
bool operator<(const char* s, const MyString& str);
bool operator<=(const char* s, const MyString& str);

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& os, const MyString& s);
std::istream& operator>>(std::istream& is, MyString& s);

MyString addTxtExtension(const MyString &path);
#endif