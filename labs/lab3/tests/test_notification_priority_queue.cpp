#include "../src/notification.hpp"
#include "../src/notification_priority_queue.hpp"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Тест NotificationPriorityQueue" << std::endl;
    
    NotificationPriorityQueue pq;
    
    pq.push(create_system_notification(100, "Low battery", SEVERITY_NORMAL));
    pq.push(create_system_notification(50, "System critical", SEVERITY_URGENT));
    pq.push(create_instant_notification(200, "Alice", "Hello"));
    pq.push(create_app_notification(150, "Telegram", "Update", "New version"));
    pq.push(create_instant_notification(80, "Bob", "Quick question"));
    
    assert(pq.get_size() == 5);
    
    // Срочное системное должно быть первым
    Notification n1 = pq.pop();
    assert(n1.type == TYPE_SYSTEM);
    assert(n1.system.severity == SEVERITY_URGENT);
    assert(n1.timestamp == 50);
    
    // СледующиеSZaoiuy6t52`d1  X? мгновенные сообщения
    Notification n2 = pq.pop();
    assert(n2.type == TYPE_INSTANT);
    assert(n2.timestamp == 80);
    
    Notification n3 = pq.pop();
    assert(n3.type == TYPE_INSTANT);
    assert(n3.timestamp == 200);
    
    // Обычное системное
    Notification n4 = pq.pop();
    assert(n4.type == TYPE_SYSTEM);
    assert(n4.system.severity == SEVERITY_NORMAL);
    assert(n4.timestamp == 100);
    
    // Уведомление от приложения
    Notification n5 = pq.pop();
    assert(n5.type == TYPE_APP);
    assert(n5.timestamp == 150);
    
    assert(pq.get_size() == 0);
    
    std::cout << "Все тесты пройдены" << std::endl;
    return 0;
}