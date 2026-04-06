#include "../src/rect.hpp"
#include <cassert>

int main() {
    std::cout << "Тест 4.2.2. Операции с прямоугольником:\n" << std::endl;
    
    // Тест 1: move с одним параметром
    {
        Rect r1(1, 5, 4, 2);
        r1.move(3);
        assert(r1.get_left() == 4);
        assert(r1.get_right() == 8);
        std::cout << "  move(dx): ОК" << std::endl;
    }
    
    // Тест 2: move с двумя параметрами
    {
        Rect r2(1, 5, 4, 2);
        r2.move(2, 3);
        assert(r2.get_left() == 3);
        assert(r2.get_right() == 7);
        assert(r2.get_top() == 7);
        assert(r2.get_bottom() == 5);
        std::cout << "  move(dx, dy): ОК" << std::endl;
    }
    
    // Тест 3: inflate с одним параметром
    {
        Rect r3(2, 4, 5, 1);
        r3.inflate(1);
        assert(r3.get_left() == 1);
        assert(r3.get_right() == 5);
        assert(r3.get_top() == 6);
        assert(r3.get_bottom() == 0);
        std::cout << "  inflate(amount): ОК" << std::endl;
    }

    // Тест 4: inflate с двумя параметрами
    {
        Rect r4(2, 4, 5, 1);
        r4.inflate(2, 1);
        assert(r4.get_left() == 0); 
        assert(r4.get_right() == 6);
        assert(r4.get_top() == 6);
        assert(r4.get_bottom() == 0);
        std::cout << "  inflate(dw, dh): ОК" << std::endl;
    }

    // Тест 5: inflate с четырьмя параметрами
    {
        Rect r5(2, 4, 5, 1);
        r5.inflate(1, 2, 3, 4);
        assert(r5.get_left() == 1);
        assert(r5.get_right() == 6); 
        assert(r5.get_top() == 8); 
        assert(r5.get_bottom() == -3);
        std::cout << "  inflate(dl, dr, dt, db): ОК" << std::endl;
    }
    
    std::cout << "\nВсе тесты операций пройдены!" << std::endl;
    return 0;
}