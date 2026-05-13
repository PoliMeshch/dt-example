#ifndef LIST_HPP
#define LIST_HPP

#include "circle.hpp"
#include <cstddef>
#include <iostream>

class List {
private:
    class Node {
        Node* pPrev;
        Node* pNext;
        Circle m_Data;
    public:
        Node();
        Node(Node* prev, Node* next, const Circle& c);
        ~Node();

        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;

        friend class List;
        friend class Iterator;
        friend std::ostream& operator<<(std::ostream& out, const List& list);
    };

    struct Run {
        Node* start;
        int length;
    };

    Node Head;
    Node Tail;
    size_t m_size;

    Node* detach_all();
    void attach_all(Node* head_sorted);
    Node* find_run(Node* start, Node** run_end, int* run_length);
    void insertion_sort_run(Node* start, int length);
    Node* merge_runs(Node* left, int left_len, Node* right, int right_len);
    void merge_collapse(Run* stack, int& stack_size);

public:
    class Iterator {
        Node* node;
    public:
        explicit Iterator(Node* n);
        Circle& operator*();
        const Circle& operator*() const;
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    List();
    ~List();

    // TODO: лучше скопировать элементы
    /* List(const List&) = delete;
    List& operator=(const List&) = delete; */

    // Глубокое копирование
    List(const List& other);
    List& operator=(const List& other);

    // TODO: реализовать программный интерфейс для взаимодействия с элементами списка
    // Программный интерфейс: доступ по индексу(get), вставка(insert), удаление по позиции(removeAt).
    // И реализован итератор(Iterator).

    void addFirst(const Circle& c);
    void addLast(const Circle& c);
    void insert(size_t index, const Circle& c);

    const Circle& get(size_t index) const;

    bool deleteFirst(const Circle& c);
    int deleteAll(const Circle& c);
    bool removeAt(size_t index);    
    void clear();

    size_t size() const;
    bool empty() const;

    void sort_by_area();

    Iterator begin();
    Iterator end();

    // TODO: std::ostream& и std::istream& вариации
    /* void write_to_file(const char* filename) const;
    void read_from_file(const char* filename); */

    // Ввод-вывод
    friend std::ostream& operator<<(std::ostream& out, const List& list);
    friend std::istream& operator>>(std::istream& in, List& list);
};

#endif