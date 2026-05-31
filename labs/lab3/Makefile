CXX = g++
CXXFLAGS = -g -Wall -Wextra

SRC = src
BUILD = build
BUILD_RELEASE = build_release
TEST_DIR = tests

HDRS = $(wildcard $(SRC)/*.hpp)

# Объектные файлы
OBJS_RELEASE = $(BUILD_RELEASE)/my_string.o $(BUILD_RELEASE)/matrix.o \
               $(BUILD_RELEASE)/worker_db.o $(BUILD_RELEASE)/notification.o \
               $(BUILD_RELEASE)/notification_queue.o $(BUILD_RELEASE)/notification_priority_queue.o \
               $(BUILD_RELEASE)/bool_array.o $(BUILD_RELEASE)/basefile.o $(BUILD_RELEASE)/lab3.o

OBJS_DEBUG = $(BUILD)/my_string.o $(BUILD)/matrix.o \
             $(BUILD)/worker_db.o $(BUILD)/notification.o \
             $(BUILD)/notification_queue.o $(BUILD)/notification_priority_queue.o \
             $(BUILD)/bool_array.o $(BUILD)/basefile.o $(BUILD)/lab3.o

all: $(BUILD_RELEASE)/debug.out

# Режим без отладки
$(BUILD_RELEASE)/%.o: $(SRC)/%.cpp $(SRC)/%.hpp
	mkdir -p $(BUILD_RELEASE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_RELEASE)/lab3.o: $(SRC)/lab3.cpp $(HDRS)
	mkdir -p $(BUILD_RELEASE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_RELEASE)/debug.out: $(OBJS_RELEASE)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Режим с отладкой конструкторов
$(BUILD)/%.o: $(SRC)/%.cpp $(SRC)/%.hpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -DDEBUG_CONSTRUCTORS -c $< -o $@

$(BUILD)/lab3.o: $(SRC)/lab3.cpp $(HDRS)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -DDEBUG_CONSTRUCTORS -c $< -o $@

$(BUILD)/debug.out: $(OBJS_DEBUG)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Тесты
$(BUILD)/test_notification_priority_queue.out: $(TEST_DIR)/test_notification_priority_queue.cpp $(SRC)/notification.cpp $(SRC)/notification_priority_queue.cpp $(SRC)/my_string.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -I$(SRC) -o $@ $^

# Запуск
run: $(BUILD_RELEASE)/debug.out
	./$(BUILD_RELEASE)/debug.out

run_debug: $(BUILD)/debug.out
	./$(BUILD)/debug.out

debug: $(BUILD)/debug.out
	gdb $(BUILD)/debug.out

# Запуск тестов
test: $(BUILD)/test_notification_priority_queue.out
	@echo "Запуск тестов"
	./$(BUILD)/test_notification_priority_queue.out
	@echo "Тесты завершены"

# Проверка утечек памяти
leaks: $(BUILD_RELEASE)/debug.out
	valgrind --leak-check=full ./$(BUILD_RELEASE)/debug.out

clean:
	rm -rf $(BUILD) $(BUILD_RELEASE)
	rm -f test5.txt
	@echo "Очищены временные файлы"

.PHONY: all run run_debug debug test leaks test_leaks clean