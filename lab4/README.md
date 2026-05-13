# Лабораторная работа №4. Двусвязный список.

## Исправления по TODO

### TODO 1: лучше скопировать элементы
Заменён запрет копирования (`= delete`) на глубокое копирование.
Реализован конструктор копирования и оператор присваивания.
Списки полностью независимы после копирования.
Где смотреть: `list.hpp` (List(const List&), operator=), `list.cpp` (реализация).

### TODO 2: реализовать программный интерфейс для взаимодействия с элементами списка
Добавлены методы get(index), insert(index, c), removeAt(index).
Реализован вложенный класс Iterator с операторами *, ++, ==, !=
и методы begin(), end() для обхода списка в цикле.
Где смотреть: `list.hpp` (Iterator, get, insert, removeAt), `list.cpp` (реализация).

### TODO 3: std::ostream& и std::istream& вариации
Убраны методы write_to_file и read_from_file (закомментированы для истории).
Реализованы operator<< и operator>> для любых потоков ostream/istream.
Запись в файл: ofstream fout("file.txt"); fout << list;
Чтение из файла: ifstream fin("file.txt"); fin >> list;
Где смотреть: `list.hpp` (operator<<, operator>>), `list.cpp` (реализация), `main.cpp` (использование).

## Сборка и проверка
make          - сборка
make run      - запуск
make check    - сборка с AddressSanitizer и запуск
make clean    - очистка