#include "test_utils.hpp"

int main() {
    srand(time(nullptr));
    const size_t DATA_SIZE = 50000;
    
    unsigned char* data = new unsigned char[DATA_SIZE];
    generate_random_data(data, DATA_SIZE);
    
    std::cout << "Тест композиции (Base32File2 + BaseFile): ";
    
    Base32File2 file(new BaseFile("tests/temp/test_composition.tmp", "w+"));
    
    if (test_file_class(file, data, DATA_SIZE)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
    
    delete[] data;
    return 0;
}