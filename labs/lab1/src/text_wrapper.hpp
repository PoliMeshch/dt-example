#ifndef TEXT_WRAPPER_HPP
#define TEXT_WRAPPER_HPP

#include "my_string.hpp"

class TextWrapper {
private:
    MyString input_text;
    int line_width;
    MyString* lines;
    int line_count;
    int line_capacity;
    
    // Методы для логических условий
    bool is_delimiter(char c) const;
    bool is_end_of_text(const char* pos) const;
    
    // Методы для атомарных действий
    void skip_spaces(const char*& pos) const;
    void add_line_from_buffer(const char* start, const char* end);
    void expand_lines_array();

public:
    TextWrapper();
    TextWrapper(const MyString& text, int width);
    ~TextWrapper();
    
    void wrap_text();
    void print_wrapped() const;
};

#endif