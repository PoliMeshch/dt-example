#include "list.hpp"
#include <fstream>
#include <iostream>
#include <cstddef>

List::Node::Node() : pPrev(nullptr), pNext(nullptr), m_Data() {}

List::Node::Node(Node* prev, Node* next, const Circle& c)
    : pPrev(prev), pNext(next), m_Data(c) {
    if (prev) prev->pNext = this;
    if (next) next->pPrev = this;
}

List::Node::~Node() {
    if (pPrev) pPrev->pNext = pNext;
    if (pNext) pNext->pPrev = pPrev;
    pPrev = pNext = nullptr;
}

// Итератор для обхода списка
List::Iterator::Iterator(Node* n) : node(n) {}

Circle& List::Iterator::operator*() {
    return node->m_Data;
}

const Circle& List::Iterator::operator*() const {
    return node->m_Data;
}

List::Iterator& List::Iterator::operator++() {
    node = node->pNext;
    return *this;
}

List::Iterator List::Iterator::operator++(int) {
    Iterator tmp = *this;
    node = node->pNext;
    return tmp;
}

bool List::Iterator::operator==(const Iterator& other) const {
    return node == other.node;
}

bool List::Iterator::operator!=(const Iterator& other) const {
    return node != other.node;
}

List::Iterator List::begin() {
    return Iterator(Head.pNext);
}

List::Iterator List::end() {
    return Iterator(&Tail);
}

List::List(const List& other) : List() {
    Node* current = other.Head.pNext;
    while (current != &other.Tail) {
        addLast(current->m_Data);
        current = current->pNext;
    }
}

List& List::operator=(const List& other) {
    if (this != &other) {
        clear();
        Node* current = other.Head.pNext;
        while (current != &other.Tail) {
            addLast(current->m_Data);
            current = current->pNext;
        }
    }
    return *this;
}

List::List() : m_size(0) {
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
}

List::~List() {
    Node* current = Head.pNext;
    while (current != &Tail) {
        Node* toDelete = current;
        current = current->pNext;
        delete toDelete;
    }
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
    m_size = 0;
}

const Circle& List::get(size_t index) const {
    if (index >= m_size) throw std::out_of_range("Индекс за пределами допустимых значений");
    Node* current = Head.pNext;
    for (size_t i = 0; i < index; ++i) {
        current = current->pNext;
    }
    return current->m_Data;
}

/* void List::insert(size_t index, const Circle& c) {
    if (index > m_size) throw std::out_of_range("Индекс за пределами допустимых значений");
    Node* current = Head.pNext;
    for (size_t i = 0; i < index; ++i) {
        current = current->pNext;
    }
    new Node(current->pPrev, current, c);
    ++m_size;
} */

void List::insert(Iterator pos, const Circle& c) {
    Node* current = pos.node;
    new Node(current->pPrev, current, c);
    ++m_size;
}

List::Iterator List::remove(Iterator pos) {
    Node* current = pos.node;
    Node* next = current->pNext;
    delete current;
    --m_size;
    return Iterator(next);
}

/* bool List::removeAt(size_t index) {
    if (index >= m_size) return false;
    Node* current = Head.pNext;
    for (size_t i = 0; i < index; ++i) {
        current = current->pNext;
    }
    delete current;
    --m_size;
    return true;
} */

void List::addFirst(const Circle& c) {
    new Node(&Head, Head.pNext, c);
    ++m_size;
}

void List::addLast(const Circle& c) {
    new Node(Tail.pPrev, &Tail, c);
    ++m_size;
}

bool List::deleteFirst(const Circle& c) {
    Node* current = Head.pNext;
    while (current != &Tail) {
        if (current->m_Data == c) {
            Node* toDelete = current;
            current = current->pNext;
            delete toDelete;
            --m_size;
            return true;
        }
        current = current->pNext;
    }
    return false;
}

int List::deleteAll(const Circle& c) {
    Node* current = Head.pNext;
    int deletedCount = 0;
    while (current != &Tail) {
        if (current->m_Data == c) {
            Node* toDelete = current;
            current = current->pNext;
            delete toDelete;
            --m_size;
            ++deletedCount;
        } else {
            current = current->pNext;
        }
    }
    return deletedCount;
}

void List::clear() {
    Node* current = Head.pNext;
    while (current != &Tail) {
        Node* toDelete = current;
        current = current->pNext;
        delete toDelete;
    }
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
    m_size = 0;
}

size_t List::size() const {
    return m_size;
}

bool List::empty() const {
    return m_size == 0;
}

List::Node* List::detach_all() {
    if (m_size == 0) return nullptr;

    Node* first = Head.pNext;
    Node* last  = Tail.pPrev;

    Head.pNext = &Tail;
    Tail.pPrev = &Head;

    first->pPrev = nullptr;
    last->pNext  = nullptr;

    return first;
}

void List::attach_all(Node* head_sorted) {
    if (head_sorted == nullptr) {
        Head.pNext = &Tail;
        Tail.pPrev = &Head;
        return;
    }

    Node* last = head_sorted;
    while (last->pNext != nullptr) {
        last = last->pNext;
    }

    Head.pNext = head_sorted;
    head_sorted->pPrev = &Head;
    last->pNext = &Tail;
    Tail.pPrev = last;
}

List::Node* List::find_run(Node* start, Node** run_end, int* run_length) {
    if (start == nullptr) {
        *run_end = nullptr;
        *run_length = 0;
        return nullptr;
    }

    if (start->pNext == nullptr) {
        *run_end = start;
        *run_length = 1;
        return nullptr;
    }

    int length = 2;
    Node* current = start;
    bool ascending = (current->m_Data.area() <= current->pNext->m_Data.area());

    if (ascending) {
        while (current->pNext != nullptr
               and current->m_Data.area() <= current->pNext->m_Data.area()) {
            current = current->pNext;
            ++length;
        }
    } else {
        while (current->pNext != nullptr
               and current->m_Data.area() > current->pNext->m_Data.area()) {
            current = current->pNext;
            ++length;
        }
        Node* left = start;
        Node* right = current;
        while (left != right and left->pPrev != right) {
            Circle temp = std::move(left->m_Data);
            left->m_Data = std::move(right->m_Data);
            right->m_Data = std::move(temp);
            left = left->pNext;
            right = right->pPrev;
        }
    }

    *run_end = current;
    *run_length = length;
    return current->pNext;
}

void List::insertion_sort_run(Node* start, int length) {
    if (length <= 1) return;

    Node* current = start->pNext;
    for (int i = 1; i < length and current != nullptr; ++i) {
        Circle key = std::move(current->m_Data);
        Node* pos = current->pPrev;

        while (pos != nullptr and pos->m_Data.area() > key.area()) {
            pos->pNext->m_Data = std::move(pos->m_Data);
            pos = pos->pPrev;
        }

        if (pos == nullptr) {
            start->m_Data = std::move(key);
        } else {
            pos->pNext->m_Data = std::move(key);
        }

        current = current->pNext;
    }
}

List::Node* List::merge_runs(Node* left, int left_len,
                              Node* right, int right_len) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Node dummy;
    Node* tail = &dummy;

    int left_count = 0;
    int right_count = 0;

    while (left_count < left_len and right_count < right_len) {
        if (left->m_Data.area() <= right->m_Data.area()) {
            tail->pNext = left;
            left->pPrev = tail;
            tail = left;
            left = left->pNext;
            ++left_count;
        } else {
            tail->pNext = right;
            right->pPrev = tail;
            tail = right;
            right = right->pNext;
            ++right_count;
        }
    }

    while (left_count < left_len) {
        tail->pNext = left;
        left->pPrev = tail;
        tail = left;
        left = left->pNext;
        ++left_count;
    }

    while (right_count < right_len) {
        tail->pNext = right;
        right->pPrev = tail;
        tail = right;
        right = right->pNext;
        ++right_count;
    }

    tail->pNext = nullptr;

    if (dummy.pNext != nullptr) {
        dummy.pNext->pPrev = nullptr;
    }

    return dummy.pNext;
}

void List::merge_collapse(Run* stack, int& stack_size) {
    while (stack_size > 1) {
        int n = stack_size - 1;

        if (n >= 2 and stack[n-2].length <= stack[n-1].length + stack[n].length) {
            if (stack[n-2].length < stack[n].length) {
                Node* merged = merge_runs(
                    stack[n-2].start, stack[n-2].length,
                    stack[n-1].start, stack[n-1].length);
                stack[n-2].start = merged;
                stack[n-2].length += stack[n-1].length;
                stack[n-1] = stack[n];
                --stack_size;
            } else {
                Node* merged = merge_runs(
                    stack[n-1].start, stack[n-1].length,
                    stack[n].start, stack[n].length);
                stack[n-1].start = merged;
                stack[n-1].length += stack[n].length;
                --stack_size;
            }
        } else if (n >= 1 and stack[n-1].length <= stack[n].length) {
            Node* merged = merge_runs(
                stack[n-1].start, stack[n-1].length,
                stack[n].start, stack[n].length);
            stack[n-1].start = merged;
            stack[n-1].length += stack[n].length;
            --stack_size;
        } else {
            break;
        }
    }
}

void List::sort_by_area() {
    if (m_size < 2) return;

    const int MIN_RUN = 32;

    Node* head = detach_all();

    Run stack[64];
    int stack_size = 0;

    Node* current = head;

    while (current != nullptr) {
        Node* run_end = nullptr;
        int run_length = 0;

        Node* next_start = find_run(current, &run_end, &run_length);

        if (run_length < MIN_RUN) {
            Node* temp = run_end;
            int count = run_length;
            while (temp != nullptr and temp->pNext != nullptr and count < MIN_RUN) {
                temp = temp->pNext;
                ++count;
            }
            run_length = count;
            run_end = temp;
            next_start = (temp != nullptr) ? temp->pNext : nullptr;

            insertion_sort_run(current, run_length);
        }

        stack[stack_size].start = current;
        stack[stack_size].length = run_length;
        ++stack_size;

        merge_collapse(stack, stack_size);

        current = next_start;
    }

    while (stack_size > 1) {
        Node* merged = merge_runs(
            stack[stack_size-2].start, stack[stack_size-2].length,
            stack[stack_size-1].start, stack[stack_size-1].length);
        stack[stack_size-2].start = merged;
        stack[stack_size-2].length += stack[stack_size-1].length;
        --stack_size;
    }

    head = (stack_size > 0) ? stack[0].start : nullptr;
    attach_all(head);
}

std::ostream& operator<<(std::ostream& out, const List& list) {
    if (list.empty()) {
        out << "Список пуст" << std::endl;
        return out;
    }
    List::Node* current = list.Head.pNext;
    while (current != &list.Tail) {
        out << current->m_Data << std::endl;
        current = current->pNext;
    }
    return out;
}

std::istream& operator>>(std::istream& in, List& list) {
    list.clear();
    double x, y, r;
    while (in >> x >> y >> r) {
        list.addLast(Circle(x, y, r));
    }
    return in;
}

/* void List::write_to_file(const char* filename) const {
    std::ofstream fout(filename); //?
    if (not fout) return;
    Node* current = Head.pNext;
    while (current != &Tail) {
        fout << current->m_Data << std::endl;
        current = current->pNext;
    }
    fout.close();
}

void List::read_from_file(const char* filename) {
    std::ifstream fin(filename);
    if (not fin) return;

    clear();

    double x, y, r;
    while (fin >> x >> y >> r) {
        addLast(Circle(x, y, r));
    }
    fin.close();
} */