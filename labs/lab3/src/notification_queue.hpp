#ifndef NOTIFICATION_QUEUE_HPP
#define NOTIFICATION_QUEUE_HPP

#include "notification.hpp"

class NotificationQueue {
private:
    Notification* data;
    int front;      // Индекс первого элемента
    int rear;       // Индекс последнего элемента
    int count;      // Текущее количество элементов
    int capacity;   // Выделенная память
    
    void expand();  // Расширение массива
    
public:
    NotificationQueue();
    ~NotificationQueue();
    
    // TODO: какая алгоритмическая сложность у операций push и pop?
    // push: O(1) амортизированно (редкое расширение)
    // pop: O(1) — просто сдвиг индекса
    void push(const Notification& n);
    Notification pop();
    int size() const;
    bool empty() const;
    
    // Итератор
    // TODO: верно ли делать it++, если буфер циклический?
    // С простыми указателями — неверно, указатель может выйти за границу.
    // Написан свой итератор, который вычисляет индекс через (start + offset) % capacity:

    class Iterator;
    Iterator begin();
    Iterator end();

    /* Notification* begin();
    Notification* end(); */
};

// Итератор для циклического буфера
class NotificationQueue::Iterator {
private:
    Notification* data;
    int start;      // Начальный индекс (front)
    int offset;     // Текущее смещение от начала
    int total;      // Общее количество элементов (count)
    int capacity;   // Размер массива (для модуля)
    
public:
    Iterator(Notification* d, int s, int off, int tot, int cap)
        : data(d), start(s), offset(off), total(tot), capacity(cap) {}
    
    bool operator!=(const Iterator& other) const {
        return offset != other.offset;
    }
    
    Iterator& operator++() {
        offset++;
        return *this;
    }
    
    Notification& operator*() {
        int idx = (start + offset) % capacity;
        return data[idx];
    }
};

#endif