#include "../src/rect.hpp"
#include <cassert>

int main() {
    std::cout << "Тестирование базовых методов Rect:\n" << std::endl;
    
    // Тест 1: конструктор по умолчанию
    {
        Rect r1;
        assert(r1.get_left() == 0);
        assert(r1.get_right() == 1); // было 0, стало 1
        assert(r1.get_top() == 1); // было 0, стало 1
        assert(r1.get_bottom() == 0);
        std::cout << "  Конструктор по умолчанию: ОК" << std::endl;
    }
    
    // Тест 2: конструктор с параметрами
    {
        Rect r2(1, 5, 10, 2);
        assert(r2.get_left() == 1);
        assert(r2.get_right() == 5);
        assert(r2.get_top() == 10);
        assert(r2.get_bottom() == 2);
        std::cout << "  Конструктор с параметрами: ОК" << std::endl;
    }
    
    // Тест 3: метод set_all
    {
        Rect r3;
        r3.set_all(3, 7, 8, 4);
        assert(r3.get_left() == 3);
        assert(r3.get_right() == 7);
        assert(r3.get_top() == 8);
        assert(r3.get_bottom() == 4);
        std::cout << "  Метод set_all: ОК" << std::endl;
    }
    
    // Тест 4: конструктор копирования
    {
        Rect r4(2, 6, 9, 3);
        Rect r5 = r4;
        assert(r5.get_left() == 2);
        assert(r5.get_right() == 6);
        assert(r5.get_top() == 9);
        assert(r5.get_bottom() == 3);
        std::cout << "  Конструктор копирования: ОК" << std::endl;
    }
    
    // Тест 5: проверка граничных значений
    {
        Rect r6(-5, -1, -2, -8);
        assert(r6.get_left() == -5);
        assert(r6.get_right() == -1);
        assert(r6.get_top() == -2);
        assert(r6.get_bottom() == -8);
        std::cout << "  Отрицательные координаты: ОК" << std::endl;
    }
    
    std::cout << "\nВсе тесты базовых методов пройдены!" << std::endl;
    return 0;
}