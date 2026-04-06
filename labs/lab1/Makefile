# Задание 3.5*. Улучшенный Makefile с использованием переменных и неявных правил

# Переменные
CXX = g++
CXXFLAGS = -g -Wall -Wextra
CPPFLAGS = -DDEBUG_CONSTRUCTORS

# Директории
SRC = src
BUILD = build
TEST = tests

# Улучшения из раздела 2 документации GNU Make:

# 2.4 Переменные упрощают работу с Makefile
# Использование переменной OBJS чтобы не перечислять объектные файлы дважды
OBJS = $(BUILD)/rect.o $(BUILD)/barrel.o $(BUILD)/matrix.o \
       $(BUILD)/my_string.o $(BUILD)/text_wrapper.o

# Все исходные файлы
SOURCES = $(SRC)/lab1.cpp $(SRC)/rect.cpp $(SRC)/barrel.cpp \
          $(SRC)/matrix.cpp $(SRC)/my_string.cpp $(SRC)/text_wrapper.cpp

# Хедеры (для зависимостей lab1.o)
HDRS = $(wildcard $(SRC)/*.hpp)

# Цель по умолчанию
all: $(BUILD)/debug.out

# 2.5 Пусть make сам подбирает рецепты
# Неявное правило - автоматическая сборка .o из .cpp
$(BUILD)/%.o: $(SRC)/%.cpp $(SRC)/%.hpp
	mkdir -p $(BUILD) 
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# TODO: указать зависимость text_wrapper.hpp от my_string.hpp

$(BUILD)/text_wrapper.o: $(SRC)/text_wrapper.cpp $(SRC)/text_wrapper.hpp $(SRC)/my_string.hpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Явное правило для lab1.o (зависит от всех хедеров)
$(BUILD)/lab1.o: $(SRC)/lab1.cpp $(HDRS)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Сборка отладочной версии
$(BUILD)/debug.out: $(OBJS) $(BUILD)/lab1.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Цель для запуска отладчика
debug: $(BUILD)/debug.out
	gdb $(BUILD)/debug.out

# Версия с отладкой конструкторов
$(BUILD)/debug_ctors.out: $(SOURCES)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -DDEBUG_CONSTRUCTORS -o $@ $^

run_ctors: $(BUILD)/debug_ctors.out
	./$(BUILD)/debug_ctors.out

# Запуск без вывода конструкторов
run: $(BUILD)/debug.out
	./$(BUILD)/debug.out

# Проверка утечек памяти
$(BUILD)/leaks.out: $(SOURCES)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -fsanitize=address -o $@ $^

leaks: $(BUILD)/leaks.out
	./$(BUILD)/leaks.out < $(TEST)/test_input.txt

# Тесты
$(BUILD)/test_rect_basic_methods.out: $(TEST)/test_rect_basic_methods.cpp $(SRC)/rect.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $^

test_basic: $(BUILD)/test_rect_basic_methods.out
	./$(BUILD)/test_rect_basic_methods.out

$(BUILD)/test_rect_properties.out: $(TEST)/test_rect_properties.cpp $(SRC)/rect.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $^

test_properties: $(BUILD)/test_rect_properties.out
	./$(BUILD)/test_rect_properties.out

$(BUILD)/test_rect_operations.out: $(TEST)/test_rect_operations.cpp $(SRC)/rect.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $^

test_operations: $(BUILD)/test_rect_operations.out
	./$(BUILD)/test_rect_operations.out

$(BUILD)/test_bounding_rect.out: $(TEST)/test_bounding_rect.cpp $(SRC)/rect.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $^

test_bounding: $(BUILD)/test_bounding_rect.out
	./$(BUILD)/test_bounding_rect.out

test: test_basic test_properties test_operations test_bounding
	@echo "Все тесты пройдены!"

# Объявляем все цели, которые не создают файлы (раздел 4.6)
.PHONY: all debug run run_ctors leaks test test_basic test_properties test_operations test_bounding clean

# 2.7 Правила очистки каталога
clean:
	rm -rf $(BUILD)

