#include "notification.hpp"
#include <cstring>

// Создание системного уведомления
Notification create_system_notification(int time, const char* msg, Severity sev) {
    Notification n;
    n.type = TYPE_SYSTEM;
    n.timestamp = time;
    
    n.system.message = new char[strlen(msg) + 1];
    strcpy(n.system.message, msg);
    n.system.severity = sev;
    
    return n;
}

// Создание мгновенного сообщения
Notification create_instant_notification(int time, const char* contact, const char* text) {
    Notification n;
    n.type = TYPE_INSTANT;
    n.timestamp = time;
    
    n.instant.contact = new char[strlen(contact) + 1];
    strcpy(n.instant.contact, contact);
    
    n.instant.text = new char[strlen(text) + 1];
    strcpy(n.instant.text, text);
    
    return n;
}

// Создание уведомления от приложения
Notification create_app_notification(int time, const char* app, const char* title, const char* text) {
    Notification n;
    n.type = TYPE_APP;
    n.timestamp = time;
    
    n.app.app_name = new char[strlen(app) + 1];
    strcpy(n.app.app_name, app);
    
    n.app.title = new char[strlen(title) + 1];
    strcpy(n.app.title, title);
    
    n.app.text = new char[strlen(text) + 1];
    strcpy(n.app.text, text);
    
    return n;
}

// Вывод уведомления
void print_notification(const Notification& n) {
    std::cout << "[" << n.timestamp << "] ";
    
    switch (n.type) {
        case TYPE_SYSTEM:
            std::cout << "[SYSTEM] ";
            if (n.system.severity == SEVERITY_URGENT) {
                std::cout << "URGENT: ";
            } else {
                std::cout << "INFO: ";
            }
            std::cout << n.system.message << std::endl;
            break;
            
        case TYPE_INSTANT:
            std::cout << "[IM] " << n.instant.contact << ": " << n.instant.text << std::endl;
            break;
            
        case TYPE_APP:
            std::cout << "[APP] " << n.app.app_name << " / " << n.app.title << ": " << n.app.text << std::endl;
            break;
    }
}

// Подсчёт уведомлений заданного типа
int count_notifications_by_type(const Notification* arr, int size, NotificationType type) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i].type == type) {
            count++;
        }
    }
    return count;
}

void free_notification(Notification& n) {
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