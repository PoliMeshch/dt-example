#include "notification_priority_queue.hpp"
#include <cstring>

NotificationPriorityQueue::NotificationPriorityQueue() 
    : data(nullptr), size(0), capacity(0) {}

NotificationPriorityQueue::~NotificationPriorityQueue() {
    for (int i = 0; i < size; ++i) {
        Notification& n = data[i];
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

void NotificationPriorityQueue::expand() {
    int new_capacity = (capacity == 0) ? 4 : capacity * 2;
    Notification* new_data = new Notification[new_capacity];
    
    for (int i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

// Добавленные методы:

void NotificationPriorityQueue::swap(int i, int j) {
    Notification temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

void NotificationPriorityQueue::sift_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (is_more_relevant(data[index], data[parent])) {
            swap(index, parent);
            index = parent;
        } else {
            break;
        }
    }
}

void NotificationPriorityQueue::sift_down(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;
        
        if (left < size and is_more_relevant(data[left], data[largest])) {
            largest = left;
        }
        if (right < size and is_more_relevant(data[right], data[largest])) {
            largest = right;
        }
        if (largest != index) {
            swap(index, largest);
            index = largest;
        } else {
            break;
        }
    }
}

/* int NotificationPriorityQueue::find_most_relevant() const {
    int best_index = 0;
    
    for (int i = 1; i < size; ++i) {
        if (is_more_relevant(data[i], data[best_index])) {
            best_index = i;
        }
    }
    return best_index;
} */

bool NotificationPriorityQueue::is_more_relevant(const Notification& a, const Notification& b) const {
    // Правило 1: срочное системное важнее всего
    bool a_urgent = (a.type == TYPE_SYSTEM and a.system.severity == SEVERITY_URGENT);
    bool b_urgent = (b.type == TYPE_SYSTEM and b.system.severity == SEVERITY_URGENT);
    
    if (a_urgent != b_urgent) {
        return a_urgent;
    }
    
    // Правило 3: сравнение по типу
    if (a.type != b.type) {
        return get_type_priority(a.type) > get_type_priority(b.type);
    }
    
    // Правило 2 и 4: чем раньше пришло, тем актуальнее
    return a.timestamp < b.timestamp;
}

int NotificationPriorityQueue::get_type_priority(NotificationType type) const {
    switch (type) {
        case TYPE_INSTANT: return 3;
        case TYPE_SYSTEM: return 2;
        case TYPE_APP: return 1;
    }
    return 0;
}

void NotificationPriorityQueue::push(const Notification& n) {
    if (size >= capacity) {
        expand();
    }
    
    data[size] = n;
    sift_up(size);
    size++;
}

Notification NotificationPriorityQueue::pop() {
    if (size == 0) {
        throw "Очередь пуста";
    }
    
    //int index = find_most_relevant();
    Notification result = data[0];
    size--;
    if (size > 0) {
        data[0] = data[size];
        sift_down(0);
    }
    
    /* for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--; */
    
    return result;
}

int NotificationPriorityQueue::get_size() const {
    return size;
}

bool NotificationPriorityQueue::empty() const {
    return size == 0;
}

Notification* NotificationPriorityQueue::begin() {
    return data;
}

Notification* NotificationPriorityQueue::end() {
    return data + size;
}