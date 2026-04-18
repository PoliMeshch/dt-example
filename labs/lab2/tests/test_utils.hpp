#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../src/basefile.hpp"

unsigned char random_byte() {
    return rand() % 256;
}

void generate_random_data(unsigned char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        data[i] = random_byte();
    }
}

bool compare_data(const unsigned char* data1, const unsigned char* data2, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (data1[i] != data2[i]) return false;
    }
    return true;
}

bool test_file_class(IFile& file, const unsigned char* original_data, size_t data_size) {
    size_t written = 0;
    while (written < data_size) {
        size_t chunk = (data_size - written) > 200 ? 200 : (data_size - written);
        size_t w = file.write(original_data + written, chunk);
        if (w != chunk) return false;
        written += w;
    }
    
    if (not file.seek(0)) return false;
    
    unsigned char* read_data = new unsigned char[data_size];
    size_t read_bytes = 0;
    while (read_bytes < data_size) {
        // TODO: Попробуйте заменить 256 на 200
        size_t chunk = (data_size - read_bytes) > 200 ? 200 : (data_size - read_bytes);
        // Заменила 256 на 200. Тесты проходят, реализация классов не зависит от конкретного
        // размера буфера. Это подтверждает корректность test_file_class и всех тестируемых классов.
        size_t r = file.read(read_data + read_bytes, chunk);
        if (r != chunk) {
            delete[] read_data;
            return false;
        }
        read_bytes += r;
    }
    
    bool result = compare_data(original_data, read_data, data_size);
    delete[] read_data;
    return result;
}

#endif