#include "test_utils.hpp"

int main()
{
    srand(time(nullptr));
    const size_t DATA_SIZE = 50000;
    
    unsigned char* data = new unsigned char[DATA_SIZE];
    generate_random_data(data, DATA_SIZE);
    
    std::cout << "Тест RleFile: ";
    
    RleFile file("tests/temp/test_rle.tmp", "w+");
    
    if (test_file_class(file, data, DATA_SIZE)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
    
    delete[] data;
    return 0;
}