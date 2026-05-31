#include "worker_db.hpp"
#include <iostream>

WorkerDb::WorkerDb() : table(nullptr), size(0), capacity(0) {}

WorkerDb::~WorkerDb() {
    delete[] table;
    table = nullptr;
    size = 0;
    capacity = 0;
}

int WorkerDb::hash(const MyString& key) const {
    const char* str = key.c_str();
    int h = 0;
    
    for (int i = 0; str[i] != '\0'; ++i) {
        h = (h * 31 + str[i]) % capacity;
    }
    return h;
}

int WorkerDb::find_pos(const MyString& key) const {
    if (capacity == 0) return -1;
    
    int idx = hash(key);
    int first_deleted = -1;
    
    // Линейное пробирование
    for (int i = 0; i < capacity; ++i) {
        int pos = (idx + i) % capacity;
        
        if (!table[pos].occupied) {
            return (first_deleted != -1) ? first_deleted : -pos - 1;
        }
        
        if (table[pos].deleted and first_deleted == -1) {
            first_deleted = pos;
        }
        
        if (!table[pos].deleted and table[pos].key == key) {
            return pos;
        }
    }
    
    return (first_deleted != -1) ? first_deleted : -1;
}

// Расширение массивов
/* void WorkerDb::expand() {
    int new_capacity = (capacity == 0) ? 4 : capacity * 2;
    
    MyString* new_keys = new MyString[new_capacity];
    WorkerData* new_values = new WorkerData[new_capacity];
    
    for (int i = 0; i < size; ++i) {
        // TODO: std::move
        new_keys[i] = std::move(keys[i]);
        new_values[i] = std::move(values[i]);
        //new_keys[i] = keys[i];
        //new_values[i] = values[i];
    }
    
    delete[] keys;
    delete[] values;
    
    keys = new_keys;
    values = new_values;
    capacity = new_capacity;
} */

void WorkerDb::expand() {
    int new_capacity = (capacity == 0) ? 8 : capacity * 2;
    Entry* new_table = new Entry[new_capacity];
    
    // Перехеширование всех существующих элементов
    for (int i = 0; i < capacity; ++i) {
        // TODO: можно ли оставить только одно?

        // Три состояния ячейки нельзя закодировать одной булевой переменной:
        //      1. Пустая (occupied=false) - конец цепочки пробирования
        //      2. Занята активным элементом (occupied=true, deleted=false) - участвует в поиске
        //      3. Удалена (occupied=true, deleted=true) - пропускаем при поиске, но не останавливаемся
        // Если объединить удаленные и пустые в одно состояние:
        //      [A][удалена][B] - поиск B остановится на "удалена" и не найдет B
        // Поэтому нужны два флага: occupied (ячейка использовалась) и deleted (элемент удален)

        if (table[i].occupied and !table[i].deleted) { 
            const MyString& key = table[i].key;
            const char* str = key.c_str();
            int h = 0;
            for (int j = 0; str[j] != '\0'; ++j) {
                h = (h * 31 + str[j]) % new_capacity;
            }
            
            // Линейное пробирование для новой таблицы
            int pos = h;
            while (new_table[pos].occupied) {
                pos = (pos + 1) % new_capacity;
            }
            // TODO: использовать move-семантику
            // new_table[pos] = table[i];
            new_table[pos].key = std::move(table[i].key);
            new_table[pos].value = std::move(table[i].value);
            
            // move не копирует флаги, поэтому их нужно установить вручную
            new_table[pos].occupied = true;   // Занята
            new_table[pos].deleted = false;   // Не удалена

        }
    }
    
    delete[] table;
    table = new_table;
    capacity = new_capacity;
}

// TODO: почему поиск по отсортированному массиву быстрее? какую сложность он имеет?
// Поиск по отсортированному массиву выполняется за O(log n) с помощью бинарного поиска,
// а линейный поиск в несортированном массиве — за O(n). При большом количестве элементов
// бинарный поиск значительно быстрее. Однако поддержание отсортированного порядка при вставке
// потребовало бы O(n) сдвигов, что не даёт выигрыша.

// TODO: исследовать вопрос организации ассоциативного массива со скоростью операции поиска и вставки быстрее линейной
//       реализовать какой-то вариант

// Реализация ассоциативного массива на основе хэш-таблицы с открытой адресацией.
// Сравнение с другими вариантами:
// Линейный поиск: O(n) поиск, O(1) вставка. Просто, но медленно.
// Бинарный поиск: O(log n) поиск, но O(n) вставка (сдвиги).
// Хэш-таблица(текущая): O(1) в среднем для поиска и вставки.

// Особенности реализации:
// 1. Хэш-функция: сумма кодов символов с умножением на 31.
// 2. Разрешение коллизий: линейное пробирование.
// 3. Ленивое удаление: элементы помечаются как deleted.
// 4. Расширение при заполнении > 50%: удвоение размера и перехеширование.
// Поиск и вставка в среднем O(1), в худшем O(n) (при плохой хэш-функции)

// Оператор доступа по ключу
WorkerData& WorkerDb::operator[](const MyString& key) {
    if (size * 2 >= capacity) {
        expand();
    }
    
    int pos = find_pos(key);
    
    if (pos >= 0) {
        return table[pos].value;
    }
    
    pos = -pos - 1;
    if (pos < 0) pos = 0;
    
    table[pos].key = key;
    table[pos].occupied = true;
    table[pos].deleted = false;
    size++;
    
    return table[pos].value;
}

int WorkerDb::get_size() const {
    return size;
}

WorkerDb::Iterator::Iterator(Entry* p, Entry* e) : ptr(p), end(e) {
    while (ptr != end and (!ptr->occupied or ptr->deleted)) {
        ++ptr;
    }
}

bool WorkerDb::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

WorkerDb::Iterator& WorkerDb::Iterator::operator++() {
    ++ptr;
    while (ptr != end and (!ptr->occupied or ptr->deleted)) {
        ++ptr;
    }
    return *this;
}

WorkerData& WorkerDb::Iterator::operator*() {
    return ptr->value;
}

WorkerData* WorkerDb::Iterator::operator->() {
    return &ptr->value;
}

MyString WorkerDb::Iterator::key() const {
    return ptr->key;
}

WorkerDb::Iterator WorkerDb::begin() {
    if (capacity == 0) return Iterator(nullptr, nullptr);
    return Iterator(table, table + capacity);
}

WorkerDb::Iterator WorkerDb::end() {
    if (capacity == 0) return Iterator(nullptr, nullptr);
    return Iterator(table + capacity, table + capacity);
}

// Функция печати базы данных
void print_db(WorkerDb& db) {
    for (auto it = db.begin(); it != db.end(); ++it) {
        std::cout << it.key() << ": " 
                  << it->name << ", " 
                  << it->age << " years, "
                  << it->salary << " rub, "
                  << it->experience << " years experience" << std::endl;
    }
}

// Функция подсчёта среднего возраста
double get_avg_age(WorkerDb& db) {
    if (db.get_size() == 0) return 0.0;
    int sum = 0;
    int count = 0;
    for (auto it = db.begin(); it != db.end(); ++it) {
        sum += it->age;
        count++;
    }
    return static_cast<double>(sum) / count;
}