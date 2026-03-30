XX = g++
CXXFLAGS = -g -Wall -Wextra

SRC = src
BUILD = build
BUILD_RELEASE = build_release
TEST_DIR = tests
TEST_HDRS = $(SRC)/basefile.hpp $(SRC)/my_string.hpp

HDRS = $(wildcard $(SRC)/*.hpp)

all: $(BUILD_RELEASE)/debug.out

# Режим без отладки
$(BUILD_RELEASE)/%.o: $(SRC)/%.cpp $(SRC)/%.hpp
	mkdir -p $(BUILD_RELEASE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_RELEASE)/lab2.o: $(SRC)/lab2.cpp $(HDRS)
	mkdir -p $(BUILD_RELEASE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_RELEASE)/debug.out: $(BUILD_RELEASE)/basefile.o $(BUILD_RELEASE)/my_string.o $(BUILD_RELEASE)/lab2.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Режим с отладкой конструкторов
$(BUILD)/%.o: $(SRC)/%.cpp $(SRC)/%.hpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -DDEBUG_CONSTRUCTORS -c $< -o $@

$(BUILD)/lab2.o: $(SRC)/lab2.cpp $(HDRS)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -DDEBUG_CONSTRUCTORS -c $< -o $@

$(BUILD)/debug.out: $(BUILD)/basefile.o $(BUILD)/my_string.o $(BUILD)/lab2.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Тесты (с зависимостью от хедеров)
$(BUILD)/test_basefile.out: $(TEST_DIR)/test_basefile.cpp $(SRC)/basefile.cpp $(SRC)/my_string.cpp $(TEST_HDRS)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -I$(SRC) -o $@ $^

$(BUILD)/test_rlefile.out: $(TEST_DIR)/test_rlefile.cpp $(SRC)/basefile.cpp $(SRC)/my_string.cpp $(TEST_HDRS)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -I$(SRC) -o $@ $^

$(BUILD)/test_base32file.out: $(TEST_DIR)/test_base32file.cpp $(SRC)/basefile.cpp $(SRC)/my_string.cpp $(TEST_HDRS)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -I$(SRC) -o $@ $^

$(BUILD)/test_composition.out: $(TEST_DIR)/test_composition.cpp $(SRC)/basefile.cpp $(SRC)/my_string.cpp $(TEST_HDRS)
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
test: $(BUILD)/test_basefile.out $(BUILD)/test_rlefile.out $(BUILD)/test_base32file.out $(BUILD)/test_composition.out
	@echo "Запуск тестов"
	./$(BUILD)/test_basefile.out
	./$(BUILD)/test_rlefile.out
	./$(BUILD)/test_base32file.out
	./$(BUILD)/test_composition.out
	@echo "Тесты завершены"

# Проверка утечек
leaks: $(BUILD_RELEASE)/debug.out
	valgrind --leak-check=full ./$(BUILD_RELEASE)/debug.out

test_leaks: $(BUILD)/test_basefile.out $(BUILD)/test_rlefile.out $(BUILD)/test_base32file.out $(BUILD)/test_composition.out
	@echo "Проверка утечек в тестах"
	valgrind --leak-check=full ./$(BUILD)/test_basefile.out
	valgrind --leak-check=full ./$(BUILD)/test_rlefile.out
	valgrind --leak-check=full ./$(BUILD)/test_base32file.out
	valgrind --leak-check=full ./$(BUILD)/test_composition.out

clean:
	rm -rf $(BUILD) $(BUILD_RELEASE)
	rm -rf $(TEST_DIR)/temp/*
	rm -f $(TEST_DIR)/*.txt $(TEST_DIR)/*.b32 $(TEST_DIR)/*.rle
	rm -f *.txt *.b32 *.rle
	@echo "Очищены временные файлы"

.PHONY: all run run_debug debug test leaks test_leaks clean