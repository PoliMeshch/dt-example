#ifndef MY_STRING_HPP
#define MY_STRING_HPP

class MyString {
private:
    char* str;

public:
    MyString();
    MyString(const char* s);
    MyString(const MyString& other);

    // Move-конструктор
    MyString(MyString&& other) noexcept;
    
    ~MyString();
    
    MyString& operator=(const MyString& other);

    // Move-оператор присваивания
    MyString& operator=(MyString&& other) noexcept;
    
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