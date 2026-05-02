#include "../src/rect.hpp"
#include <cassert>

int main() {
    std::cout << "Тест 4.2.3. Функция bounding_rect:\n" << std::endl;
    
    // Тест 1: обычные прямоугольники
    {
        Rect r1(1, 3, 5, 2);
        Rect r2(4, 6, 4, 1);
        Rect result = bounding_rect(r1, r2);
        
        assert(result.get_left() == 1);
        assert(result.get_right() == 6);
        assert(result.get_top() == 5);
        assert(result.get_bottom() == 1);
        std::cout << "  Обычные прямоугольники: ОК" << std::endl;
    }
    
    // Тест 2: один внутри другого
    {
        Rect r1(0, 10, 10, 0);
        Rect r2(2, 5, 5, 2);
        Rect result = bounding_rect(r1, r2);
        
        assert(result.get_left() == 0);
        assert(result.get_right() == 10);
        assert(result.get_top() == 10);
        assert(result.get_bottom() == 0);
        std::cout << "  Один внутри другого: ОК" << std::endl;
    }
    
    // Тест 3: перепутанные горизонтальные координаты (left > right)
    {
        Rect r1(5, 1, 2, 4);
        Rect r2(3, 6, 7, 2);
        Rect result = bounding_rect(r1, r2);
        
        assert(result.get_left() == 1);
        assert(result.get_right() == 6);
        assert(result.get_top() == 7);
        assert(result.get_bottom() == 2);
        std::cout << "  Перепутанные горизонтальные координаты: ОК" << std::endl;
    }
    
    // Тест 4: перепутанные вертикальные координаты
    {
        Rect r1(1, 4, 2, 5);
        Rect r2(2, 3, 6, 1);
        Rect result = bounding_rect(r1, r2);
        
        assert(result.get_left() == 1);
        assert(result.get_right() == 4);
        assert(result.get_top() == 6);
        assert(result.get_bottom() == 1);
        std::cout << "  Перепутанные вертикальные координаты: ОК" << std::endl;
    }
    
    std::cout << "\nВсе тесты bounding_rect пройдены!" << std::endl;
    return 0;
}