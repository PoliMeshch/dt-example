#ifndef MY_STRING_HPP
#define MY_STRING_HPP

class MyString {
private:
    char* str;

public:
    // Конструкторы
    MyString();
    MyString(const char* s);
    MyString(const MyString& other);
    
    // Деструктор
    ~MyString();
    
    // Оператор присваивания
    MyString& operator=(const MyString& other);
    
    // Методы доступа
    char get(int i) const;
    void set(int i, char c);

    // Методы для работы со строкой
    void set_new_string(const char* str);
    void print() const;
    void read_line();

    // Метод для текстового облака
    int get_length() const;
};

#endif