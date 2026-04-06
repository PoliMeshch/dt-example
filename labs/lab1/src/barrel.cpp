#include "barrel.hpp"
#include <iostream>

Barrel::Barrel(double volume, double start_volume, double start_concentration)
    : total_volume(volume), current_volume(start_volume), 
      alcohol_percent(start_concentration) {
    // Защита от некорректных значений
    if (current_volume > total_volume) current_volume = total_volume;
    if (alcohol_percent < 0.0) alcohol_percent = 0.0;
    if (alcohol_percent > 100.0) alcohol_percent = 100.0;
}

double Barrel::get_alcohol_percent() const {
    return alcohol_percent;
}

// TODO: определиться до конца с семантикой перелива: как обрабатываются граничные 
//       условия, когда переливается


void Barrel::pour_to(Barrel& other, double amount) {
    // Семантика перелива:
    // 1. Если amount > current_volume - переливаем сколько есть и выводим предупреждение
    // 2. Если amount <= 0 - выводим сообщение об ошибке
    // 3. Если other полная - переливаем, но лишнее выливается (теряется), выводим предупреждение
    // 4. Если свободного места в other меньше, чем amount - переливаем только сколько поместится,
    //    остальное выливается на землю, выводим предупреждение

    // 2. Проверка на некорректный amount
    if (amount <= 0) {
        std::cout << "Ошибка: попытка перелить " << amount 
                  << " л. Операция отменена." << std::endl;
        return;
    }

    // 1. Проверка, хватает ли жидкости в текущей бочке
    if (amount > current_volume) {
        std::cout << "Предупреждение: запрошено " << amount 
                  << " л, но доступно только " << current_volume 
                  << " л. Переливается всё, что есть." << std::endl;
        amount = current_volume;
    }

    if (amount <= 0) return;  // защита от случая, когда current_volume = 0
    

    // 3. Проверка свободного места в целевой бочке (полная ли бочка)
    double free_space = other.total_volume - other.current_volume;

    if (free_space <= 0) {
        // Целевая бочка полная
        std::cout << "Предупреждение: целевая бочка полная. " 
                  << amount << " л вылилось на землю." << std::endl;
        return;
    }

    // 4. Проверка, если свободного места меньше, чем amount, но оно есть
    if (amount > free_space) {
        std::cout << "Предупреждение: в целевой бочке только " << free_space 
                << " л свободного места. Переливаю " << free_space 
                << " л, остальное (" << (amount - free_space) << " л) вылилось на землю." << std::endl;
        amount = free_space;  // Переливаем только сколько помещается
    }

    // Концентрация переливаемой жидкости
    double transfer_concentration = alcohol_percent;
    
    // Количество спирта в переливаемой порции
    double transfer_alcohol = amount * (transfer_concentration / 100.0);
    
    // Уменьшаем текущую бочку (alcohol_percent остается прежним)
    current_volume -= amount;

    // Увеличиваем другую бочку (смешиваем)
    if (other.current_volume > 0) {
        // Общее количество спирта после смешивания
        double other_alcohol = other.current_volume * (other.alcohol_percent / 100.0);
        double total_alcohol = other_alcohol + transfer_alcohol;
        
        other.current_volume += amount;
        other.alcohol_percent = (total_alcohol / other.current_volume) * 100.0;
    } else {
        // Если другая бочка была пуста
        other.current_volume = amount;
        other.alcohol_percent = transfer_concentration;
    }
}
