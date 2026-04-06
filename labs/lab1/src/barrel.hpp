#ifndef BARREL_HPP
#define BARREL_HPP

class Barrel {
private:
    double total_volume;     // Объем бочки
    double current_volume;   // Текущее количество жидкости
    double alcohol_percent;  // Концентрация спирта в процентах

public:
    Barrel(double volume, double start_volume, double start_concentration);
    
    // Получить текущую концентрацию спирта
    double get_alcohol_percent() const;
    
    // Перелить из этой бочки в другую amount литров
    void pour_to(Barrel& other, double amount);
};

#endif