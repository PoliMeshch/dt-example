#include "text_wrapper.hpp"
#include <iostream>
#include <cstring>

TextWrapper::TextWrapper() : line_width(40), lines(nullptr), line_count(0), line_capacity(0) {}

TextWrapper::TextWrapper(const MyString& text, int width) 
    : input_text(text), line_width(width), lines(nullptr), line_count(0), line_capacity(0) {}

TextWrapper::~TextWrapper() {
    delete[] lines;
}

bool TextWrapper::is_delimiter(char c) const {
    return c == ' ' or c == '\t' or c == '\n';
}

bool TextWrapper::is_end_of_text(const char* pos) const {
    return *pos == '\0';
}


void TextWrapper::skip_spaces(const char*& pos) const {
    while (*pos and is_delimiter(*pos)) {
        pos++;
    }
}

void TextWrapper::expand_lines_array() {
    int new_capacity = (line_capacity == 0) ? 4 : line_capacity * 2;
    MyString* new_lines = new MyString[new_capacity];
    
    for (int i = 0; i < line_count; i++) {
        new_lines[i] = lines[i];
    }
    
    delete[] lines;
    lines = new_lines;
    line_capacity = new_capacity;
}

void TextWrapper::add_line_from_buffer(const char* start, const char* end) {
    if (lines == nullptr or line_count >= line_capacity) {
        expand_lines_array();
    }
    
    int len = end - start;
    char* buffer = new char[len + 1];
    for (int i = 0; i < len; i++) {
        buffer[i] = start[i];
    }
    buffer[len] = '\0';
    
    lines[line_count].set_new_string(buffer);
    line_count++;
    
    delete[] buffer;
}

void TextWrapper::wrap_text() {
    delete[] lines;
    lines = nullptr;
    line_count = 0;
    
    if (input_text.get_length() == 0) return;
    
    int text_len = input_text.get_length();
    char* text = new char[text_len + 1];
    for (int i = 0; i < text_len; i++) {
        text[i] = input_text.get(i);
    }
    text[text_len] = '\0';
    
    const char* current_pos = text;
    
    while (!is_end_of_text(current_pos)) {
        // Пропускаем пробелы в начале
        skip_spaces(current_pos);
        if (is_end_of_text(current_pos)) break;
        
        const char* line_start = current_pos;
        const char* line_end = current_pos;
        const char* last_space = nullptr;
        const char* word_start = current_pos;
        int line_length = 0;
        int word_length = 0;
        
        // Ищем место разрыва строки
        while (*line_end and line_length < line_width) {
            if (is_delimiter(*line_end)) {
                last_space = line_end;
                word_length = 0;
                word_start = line_end + 1;
            } else {
                word_length++;
                if (word_length >= line_width) {
                    line_end = word_start + line_width;
                    break;
                }
            }
            line_end++;
            line_length++;
        }
        
        // Если дошли до конца текста - берем все что осталось
        if (is_end_of_text(line_end)) {
            line_end = current_pos + strlen(current_pos);
        }
        // Иначе если есть пробел для переноса - используем его
        else if (last_space != nullptr and !is_delimiter(*line_end)) {
            line_end = last_space;
        }
        
        // Добавляем строку
        add_line_from_buffer(line_start, line_end);
        
        // Переходим к следующей позиции
        current_pos = line_end;
    }
    
    delete[] text;
}

void TextWrapper::print_wrapped() const {
    for (int i = 0; i < line_count; i++) {
        lines[i].print();
        std::cout << std::endl;
    }
}