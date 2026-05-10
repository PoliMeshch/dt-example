#include "notification_queue.hpp"
#include <cstring>

NotificationQueue::NotificationQueue() 
    : data(nullptr), front(0), rear(-1), count(0), capacity(0) {}

NotificationQueue::~NotificationQueue() {
    // Освобождение памяти каждого уведомления
    for (int i = 0; i < count; ++i) {
        int idx = (front + i) % capacity;
        Notification& n = data[idx];
        switch (n.type) {
            case TYPE_SYSTEM:
                delete[] n.system.message;
                break;
            case TYPE_INSTANT:
                delete[] n.instant.contact;
                delete[] n.instant.text;
                break;
            case TYPE_APP:
                delete[] n.app.app_name;
                delete[] n.app.title;
                delete[] n.app.text;
                break;
        }
    }
    delete[] data;
}

void NotificationQueue::expand() {
    int new_capacity = (capacity == 0) ? 4 : capacity * 2;
    Notification* new_data = new Notification[new_capacity];
    
    // Копирование существующих элементов
    for (int i = 0; i < count; ++i) {
        int idx = (front + i) % capacity;
        new_data[i] = data[idx];
    }
    
    delete[] data;
    data = new_data;
    front = 0;
    rear = count - 1;
    capacity = new_capacity;
}

void NotificationQueue::push(const Notification& n) {
    if (count >= capacity) {
        expand();
    }
    
    rear = (rear + 1) % capacity;
    data[rear] = n;
    count++;
}

Notification NotificationQueue::pop() {
    if (count == 0) {
        throw "Очередь пуста";
    }
    
    Notification result = data[front];
    front = (front + 1) % capacity;
    count--;
    
    return result;
}

int NotificationQueue::size() const {
    return count;
}

bool NotificationQueue::empty() const {
    return count == 0;
}

/* Notification* NotificationQueue::begin() {
    if (count == 0) return nullptr;
    return &data[front];
}

Notification* NotificationQueue::end() {
    if (count == 0) return nullptr;
    return &data[front] + count;
} */

NotificationQueue::Iterator NotificationQueue::begin() {
    return Iterator(data, front, 0, count, capacity);
}

NotificationQueue::Iterator NotificationQueue::end() {
    return Iterator(data, front, count, count, capacity);
}