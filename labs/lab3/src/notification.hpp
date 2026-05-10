#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <iostream>

// Типы уведомлений
enum NotificationType {
    TYPE_SYSTEM,
    TYPE_INSTANT,
    TYPE_APP
};

// Уровень серьёзности системного уведомления
enum Severity {
    SEVERITY_NORMAL,
    SEVERITY_URGENT
};

// Структура уведомления
struct Notification {
    NotificationType type;
    int timestamp;  // Метка времени
    
    union {
        // Системное уведомление
        struct {
            char* message;
            Severity severity;
        } system;
        
        // Мгновенное сообщение
        struct {
            char* contact;
            char* text;
        } instant;
        
        // Уведомление от приложения
        struct {
            char* app_name;
            char* title;
            char* text;
        } app;
    };
};

// Функции создания уведомлений
Notification create_system_notification(int time, const char* msg, Severity sev);
Notification create_instant_notification(int time, const char* contact, const char* text);
Notification create_app_notification(int time, const char* app, const char* title, const char* text);

// Функция вывода уведомления
void print_notification(const Notification& n);

// Функция подсчёта уведомлений заданного типа в массиве
int count_notifications_by_type(const Notification* arr, int size, NotificationType type);

void free_notification(Notification& n);
#endif