#include "bool_array.hpp"
#include <cstring>

int BoolArray::bytes_needed(int size) const {
    return (size + 7) / 8;
}

BoolArray::BoolArray(int size) : arr_size(size) {
    int bytes = bytes_needed(size);
    capacity = bytes;
    data = new unsigned char[capacity]();
}

BoolArray::BoolArray(int size, bool fill_value) : arr_size(size) {
    int bytes = bytes_needed(size);
    capacity = bytes;
    data = new unsigned char[capacity];
    
    unsigned char fill_byte = fill_value ? 0xFF : 0x00;
    for (int i = 0; i < capacity; ++i) {
        data[i] = fill_byte;
    }
}

BoolArray::BoolArray(const BoolArray& other) 
    : arr_size(other.arr_size), capacity(other.capacity) {
    data = new unsigned char[capacity];
    for (int i = 0; i < capacity; ++i) {
        data[i] = other.data[i];
    }
}

BoolArray::~BoolArray() {
    delete[] data;
}

BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        delete[] data;
        arr_size = other.arr_size;
        capacity = other.capacity;
        data = new unsigned char[capacity];
        for (int i = 0; i < capacity; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

void BoolArray::expand(int new_size, bool fill_value) {
    int old_bytes = bytes_needed(arr_size);
    int new_bytes = bytes_needed(new_size);
    unsigned char* new_data = new unsigned char[new_bytes];
    
    // Копируем старые данные
    for (int i = 0; i < old_bytes; ++i) {
        new_data[i] = data[i];
    }
    
    // Заполняем новые байты
    unsigned char fill_byte = fill_value ? 0xFF : 0x00;
    for (int i = old_bytes; i < new_bytes; ++i) {
        new_data[i] = fill_byte;
    }
    
    // Если расширяемся в пределах последнего байта
    if (new_bytes == old_bytes) {
        int old_bits = arr_size % 8;
        int new_bits = new_size % 8;
        for (int i = old_bits; i < new_bits; ++i) {
            if (fill_value) {
                new_data[old_bytes - 1] |= (1 << i);
            } else {
                new_data[old_bytes - 1] &= ~(1 << i);
            }
        }
    }
    
    delete[] data;
    data = new_data;
    capacity = new_bytes;
    arr_size = new_size;
}

int BoolArray::size() const {
    return arr_size;
}

void BoolArray::resize(int new_size, bool fill_value) {
    if (new_size == arr_size) return;
    
    if (new_size < arr_size) {
        arr_size = new_size;
        int new_bytes = bytes_needed(new_size);
        if (new_bytes < capacity) {
            capacity = new_bytes;
        }
    } else {
        expand(new_size, fill_value);
    }
}

// Bit реализация
BoolArray::Bit::Bit(unsigned char* b, int bit_index) 
    : byte(b), bit(bit_index) {}

BoolArray::Bit& BoolArray::Bit::operator=(bool value) {
    if (value) {
        *byte |= (1 << bit);
    } else {
        *byte &= ~(1 << bit);
    }
    return *this;
}

BoolArray::Bit::operator bool() const {
    return (*byte >> bit) & 1;
}

BoolArray::Bit BoolArray::operator[](int index) {
    if (index < 0 or index >= arr_size) {
        throw "Индекс за пределами массива";
    }
    int byte_index = index / 8;
    int bit_index = index % 8;
    return Bit(&data[byte_index], bit_index);
}

bool BoolArray::operator[](int index) const {
    if (index < 0 or index >= arr_size) {
        throw "Индекс за пределами массива";
    }
    int byte_index = index / 8;
    int bit_index = index % 8;
    return (data[byte_index] >> bit_index) & 1;
}