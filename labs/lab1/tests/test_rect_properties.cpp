#include "../src/rect.hpp"
#include <cassert>

int main() {
    std::cout << "Тест 4.2.1. Свойства прямоугольника:\n" << std::endl;
    
    // Тест 1: get_width и get_height
    {
        Rect r1(1, 5, 4, 2);
        assert(r1.get_width() == 4);
        assert(r1.get_height() == 2);
        std::cout << "  get_width/get_height: ОК" << std::endl;
    }
    
    // Тест 2: get_square
    {
        Rect r2(0, 3, 3, 0);
        assert(r2.get_square() == 9);
        std::cout << "  get_square: ОК" << std::endl;
    }
    
    // Тест 3: set_width
    {
        Rect r3(1, 5, 4, 2);
        r3.set_width(6);
        assert(r3.get_left() == 1);
        assert(r3.get_right() == 7);
        assert(r3.get_width() == 6);
        std::cout << "  set_width: ОК" << std::endl;
    }
    
    // Тест 4: set_height
    {
        Rect r4(1, 5, 4, 2);
        r4.set_height(3);
        assert(r4.get_bottom() == 2);
        assert(r4.get_top() == 5);
        assert(r4.get_height() == 3);
        std::cout << "  set_height: ОК" << std::endl;
    }
    
    std::cout << "\nВсе тесты свойств пройдены!" << std::endl;
    return 0;
}