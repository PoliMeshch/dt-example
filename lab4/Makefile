CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
ASANFLAGS = -fsanitize=address -g
TARGET = build/lab4

SRCDIR = src
BUILDDIR = build

SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/point.cpp $(SRCDIR)/circle.cpp $(SRCDIR)/list.cpp
OBJS = $(BUILDDIR)/main.o $(BUILDDIR)/point.o $(BUILDDIR)/circle.o $(BUILDDIR)/list.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

leaks: CXXFLAGS += $(ASANFLAGS)
leaks: clean $(TARGET)

$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/point.hpp $(SRCDIR)/circle.hpp $(SRCDIR)/list.hpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/point.o: $(SRCDIR)/point.cpp $(SRCDIR)/point.hpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/circle.o: $(SRCDIR)/circle.cpp $(SRCDIR)/circle.hpp $(SRCDIR)/point.hpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/list.o: $(SRCDIR)/list.cpp $(SRCDIR)/list.hpp $(SRCDIR)/circle.hpp $(SRCDIR)/point.hpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) output.txt

run: $(TARGET)
	./$(TARGET)

check: leaks
	./$(TARGET)