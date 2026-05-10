#ifndef WORKER_DB_HPP
#define WORKER_DB_HPP

#include "my_string.hpp"

// Структура для хранения данных о работнике
struct WorkerData {
    MyString name;      
    int age;            
    double salary;      
    int experience;     
    
    WorkerData() : name(), age(0), salary(0.0), experience(0) {}
    
    WorkerData(const MyString& n, int a, double s, int e) 
        : name(n), age(a), salary(s), experience(e) {}
};

// Класс ассоциативного массива
class WorkerDb {
private:
    // Структура одной записи в хэш-таблице
    struct Entry {
        MyString key;
        WorkerData value;
        bool occupied;   // Занята ли ячейка
        bool deleted;    // Помечена ли на удаление
        
        Entry() : occupied(false), deleted(false) {}
    };

    Entry* table;
    int size;      // Количество элементов
    int capacity;  // Размер таблицы
    
    int hash(const MyString& key) const; // Хэш-функция
    int find_pos(const MyString& key) const; // Поиск позиции ключа (возвращает индекс или отрицательное число)
    void expand(); // Расширение таблицы и перехеширование

    /* MyString* keys;        // Массив ключей (фамилии)
    WorkerData* values;    // Массив значений (данные сотрудников) */
    
    // Вспомогательные методы
    /* int find(const MyString& key) const;   // Поиск ключа: возвращает индекс или -1
    void expand();                         // Расширение массивов */
    
public:
    WorkerDb();                             
    ~WorkerDb();                            
    
    // Оператор доступа по ключу
    WorkerData& operator[](const MyString& key);
    
    // Методы для получения информации
    int get_size() const;

    // Объявление итератора
    class Iterator;
    Iterator begin();
    Iterator end();
};

// Итератор для перебора элементов
class WorkerDb::Iterator {
private:
    Entry* ptr;
    Entry* end;
    /* MyString* key_ptr;      // Указатель на текущий ключ
    WorkerData* value_ptr;   // Указатель на текущее значение
    int index;               // Текущий индекс */
    
public:
    // Iterator(MyString* k, WorkerData* v, int i = 0);
    Iterator(Entry* p, Entry* e);

    // Операторы сравнения
    //bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    
    // Операторы инкремента
    Iterator& operator++();
    //Iterator operator++(int);
    
    // Операторы разыменования
    WorkerData& operator*();
    WorkerData* operator->();
    
    // Дополнительный метод для получения ключа
    MyString key() const;
};

// Функции для задания 3.3
void print_db(WorkerDb& db); // Функция печати базы данных
double get_avg_age(WorkerDb& db); // Функция подсчёта среднего возраста

#endif