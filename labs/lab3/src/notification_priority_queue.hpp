#ifndef NOTIFICATION_PRIORITY_QUEUE_HPP
#define NOTIFICATION_PRIORITY_QUEUE_HPP

#include "notification.hpp"

class NotificationPriorityQueue {
private:
    Notification* data;
    int size;
    int capacity;
    
    void expand();
    void swap(int i, int j);
    void sift_up(int index);
    void sift_down(int index);
    // int find_most_relevant() const;
    // Метод больше не нужен, так как приоритетная очередь на куче
    // хранит наиболее актуальный элемент в корне (индекс 0)
    bool is_more_relevant(const Notification& a, const Notification& b) const;
    int get_type_priority(NotificationType type) const;
    
public:
    NotificationPriorityQueue();
    ~NotificationPriorityQueue();
    
    // TODO: какая сложность добавления и получения элемента тут?
    // Сейчас: push O(1) - добавление элемента в конец массива 
    //         pop O(n) - линейный поиск наиболее актуального элемента + сдвиг массива

    // TODO: можно ли лучше? прочитать про варианты и реализовать какой-нибудь
    // Я прочитала про варианты реализации приоритетной очереди:
    // 1. Отсортированный массив: push O(n), pop O(1) — вставка медленная.
    // 2. Бинарная куча: push O(log n), pop O(log n) — быстро и просто.
    // 3. Двоичное дерево: push O(log n), pop O(log n), но сложно реализовать, нужно балансировать.

    // Выбрала бинарную кучу (max-heap). Храню в массиве, дети на индексах 2*i+1 и 2*i+2.

    // Добавила sift_up (подъём) и sift_down (опускание).
    // push: кладу в конец, поднимаю.
    // pop: беру корень, ставлю последний элемент на его место, опускаю.

    void push(const Notification& n);
    Notification pop();
    int get_size() const;
    bool empty() const;
    
    Notification* begin();
    Notification* end();
};

#endif