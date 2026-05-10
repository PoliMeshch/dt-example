#ifndef BOOL_ARRAY_HPP
#define BOOL_ARRAY_HPP

#include <iostream>

class BoolArray {
private:
    unsigned char* data;
    int arr_size;
    int capacity;  // Количество байт
    
    int bytes_needed(int size) const;
    void expand(int new_size, bool fill_value = false);
    
public:
    BoolArray(int size);
    BoolArray(int size, bool fill_value);
    BoolArray(const BoolArray& other);
    ~BoolArray();
    
    BoolArray& operator=(const BoolArray& other);
    
    class Bit;
    Bit operator[](int index);
    bool operator[](int index) const;
    
    int size() const;
    void resize(int new_size, bool fill_value = false);
};

// TODO: вспомнить, зачем это нужно
// Bit нужен, чтобы operator[] работал и на запись, и на чтение.
// Бит не имеет адреса, поэтому нельзя вернуть bool&.
// Bit перехватывает присваивание и устанавливает бит,
// а при чтении преобразуется в bool.

// array[1] ||= 1
class BoolArray::Bit {
private:
    unsigned char* byte;
    int bit;
    
public:
    Bit(unsigned char* b, int bit_index);
    
    Bit& operator=(bool value);
    operator bool() const;
};

#endif