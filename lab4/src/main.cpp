#include "point.hpp"
#include "circle.hpp"
#include "list.hpp"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    Point p1;
    Point p2(2, 4);

    Circle c1;
    Circle c2(p1, 1);
    Circle c3(p2, 2.5);
    Circle c4(1, 7, 8);
    Circle c5(c3);

    List list;

    list.addLast(c1);
    list.addLast(c2);
    list.addLast(c3);
    list.addFirst(c4);
    list.addLast(c5);

    cout << "Исходный список:" << endl;
    cout << list;

    list.sort_by_area();
    cout << "После сортировки:" << endl;
    cout << list;

    list.sort_by_area();
    cout << "Повторная сортировка:" << endl;
    cout << list;

    List copy(list);
    cout << "Копия:" << endl;
    cout << copy;

    List assigned;
    assigned = list;
    cout << "Присвоенный список:" << endl;
    cout << assigned;

    cout << "Элемент[0]: " << list.get(0) << endl;
    cout << "Элемент[1]: " << list.get(1) << endl;

    list.insert(1, Circle(9, 9, 9));
    cout << "После вставки на позицию 1:" << endl;
    cout << list;

    list.removeAt(1);
    cout << "После удаления позиции 1:" << endl;
    cout << list;

    cout << "Обход итератором:" << endl;
    for (List::Iterator it = list.begin(); it != list.end(); ++it) {
        cout << *it << endl;
    }

    std::ofstream fout("output.txt");
    fout << list;
    fout.close();

    list.clear();
    cout << "После очистки:" << endl;
    cout << list;

    std::ifstream fin("output.txt");
    fin >> list;
    fin.close();
    cout << "После чтения из файла:" << endl;
    cout << list;

    std::ifstream fin_bad("no_such_file.txt");
    if (fin_bad) {
        fin_bad >> list;
    }
    fin_bad.close();
    cout << "После чтения несуществующего файла:" << endl;
    cout << list;

    cout << "Удаление c2: " << (list.deleteFirst(c2) ? "удалён" : "не найден") << endl;
    cout << list;

    Circle fake(99, 99, 99);
    cout << "Удаление несуществующего: " << (list.deleteFirst(fake) ? "удалён" : "не найден") << endl;

    int deleted = list.deleteAll(c3);
    cout << "Удаление всех c3: удалено " << deleted << endl;
    cout << list;

    List reverseList;
    reverseList.addLast(Circle(0, 0, 10));
    reverseList.addLast(Circle(0, 0, 7));
    reverseList.addLast(Circle(0, 0, 5));
    reverseList.addLast(Circle(0, 0, 3));
    reverseList.addLast(Circle(0, 0, 1));

    cout << "Обратный порядок:" << endl;
    cout << reverseList;
    reverseList.sort_by_area();
    cout << "После сортировки:" << endl;
    cout << reverseList;

    int removed = reverseList.deleteAll(Circle(0, 0, 5));
    cout << "Удаление всех элементов (0, 0, 5): удалено " << removed << endl;
    cout << reverseList;

    list.clear();
    cout << "Финальный size: " << list.size() << endl;

    bool delEmpty = list.deleteFirst(c2);
    int delAllEmpty = list.deleteAll(c3);
    cout << "Удаление из пустого: deleteFirst = " << (delEmpty ? "удалён" : "не найден")
         << ", deleteAll = " << delAllEmpty << endl;

    return 0;
}