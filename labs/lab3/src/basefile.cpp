#include "basefile.hpp"
#include <iostream>

// Реализация BaseFile
BaseFile::BaseFile() : file(nullptr), open_mode(nullptr) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "BaseFile конструктор по умолчанию: " << this << std::endl;
    #endif
}

BaseFile::BaseFile(const char* filename, const char* mode)
    : file(fopen(filename, mode)), open_mode(mode) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "BaseFile конструктор с параметрами: " << this << std::endl;
    #endif
}

BaseFile::BaseFile(FILE* existing_file) : file(existing_file), open_mode(nullptr) {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "BaseFile конструктор от FILE*: " << this << std::endl;
    #endif
}

BaseFile::~BaseFile() {
    #ifdef DEBUG_CONSTRUCTORS
        std::cout << "BaseFile деструктор: " << this << std::endl;
    #endif
    if (file != nullptr) fclose(file);
}

// Добавила реализацию move-методов 

BaseFile::BaseFile(BaseFile&& other) noexcept
    : file(other.file), open_mode(other.open_mode) {
    other.file = nullptr;
    other.open_mode = nullptr;
}

BaseFile& BaseFile::operator=(BaseFile&& other) noexcept {
    if (this != &other) {
        if (file != nullptr) fclose(file);
        file = other.file;
        open_mode = other.open_mode;
        other.file = nullptr;
        other.open_mode = nullptr;
    }
    return *this;
}

bool BaseFile::is_open() const { return file != nullptr; }
bool BaseFile::can_read() const { 
    if (file == nullptr) return false; 
    if (open_mode == nullptr) return false;
    for (int i = 0; open_mode[i] != '\0'; ++i) {
        if (open_mode[i] == 'r') return true;
    }
    return false;
}
bool BaseFile::can_write() const { 
    if (file == nullptr) return false; 
    if (open_mode == nullptr) return false;
    for (int i = 0; open_mode[i] != '\0'; ++i) {
        if (open_mode[i] == 'w' or open_mode[i] == 'a') return true;
    }
    return false;
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (file == nullptr or buf == nullptr) return 0;
    return fwrite(buf, 1, n_bytes, file);
}

size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (file == nullptr or buf == nullptr) return 0;
    return fread(buf, 1, max_bytes, file);
}

long BaseFile::tell() const {
    if (file == nullptr) return -1;
    return ftell(file);
}

bool BaseFile::seek(long offset) {
    if (file == nullptr) return false;
    return fseek(file, offset, SEEK_SET) == 0;
}

size_t BaseFile::write(const void* buf, size_t n_bytes) { return write_raw(buf, n_bytes); }
size_t BaseFile::read(void* buf, size_t max_bytes) { return read_raw(buf, max_bytes); }

// Реализация Base32File
void Base32File::init_tables(const char* table) {
    for (int i = 0; i < 32; ++i) encode_table[i] = table[i];
    for (int i = 0; i < 256; ++i) decode_table[i] = -1;
    for (int i = 0; i < 32; ++i) decode_table[(unsigned char)table[i]] = i;
}

int Base32File::encoded32_size(int raw_size) const {
    if (raw_size < 0) return -1;
    return (raw_size * 8 + 4) / 5;
}

Base32File::Base32File(const char* filename, const char* mode, const char* table)
    : BaseFile(filename, mode),
      read_bit_buffer(0), read_bits_in_buffer(0),
      write_bit_buffer(0), write_bits_in_buffer(0) {
    init_tables(table);
#ifdef DEBUG_CONSTRUCTORS
    std::cout << "Base32File конструктор с параметрами: " << this << std::endl;
#endif
}

Base32File::Base32File(FILE* existing_file, const char* table)
    : BaseFile(existing_file), // open_mode = nullptr, так как режим неизвестен
      read_bit_buffer(0), read_bits_in_buffer(0),
      write_bit_buffer(0), write_bits_in_buffer(0) {
    init_tables(table);
#ifdef DEBUG_CONSTRUCTORS
    std::cout << "Base32File конструктор от FILE*: " << this << std::endl;
#endif
}

Base32File::~Base32File() {
    if (write_bits_in_buffer > 0) {
        int idx = (write_bit_buffer << (5 - write_bits_in_buffer)) & 0x1F;
        char ch = encode_table[idx];
        BaseFile::write_raw(&ch, 1);
    }
#ifdef DEBUG_CONSTRUCTORS
    std::cout << "Base32File деструктор: " << this << std::endl;
#endif
}

size_t Base32File::write(const void* buf, size_t n_bytes) {
    if (not is_open() or buf == nullptr) return 0;

    const unsigned char* data = (const unsigned char*)buf;
    int& bit_buffer = write_bit_buffer;
    int& bits = write_bits_in_buffer;

    char* encoded = new char[encoded32_size(n_bytes) + 2];
    int dst = 0;

    for (size_t i = 0; i < n_bytes; ++i) {
        bit_buffer = (bit_buffer << 8) | data[i];
        bits += 8;

        while (bits >= 5) {
            int idx = (bit_buffer >> (bits - 5)) & 0x1F;
            encoded[dst++] = encode_table[idx];
            bits -= 5;
        }
    }

    size_t written = BaseFile::write_raw(encoded, dst);
    delete[] encoded;
    return (written == (size_t)dst) ? n_bytes : 0;
}

size_t Base32File::read(void* buf, size_t max_bytes) {
    if (not is_open() or buf == nullptr) return 0;

    unsigned char* data = (unsigned char*)buf;
    size_t decoded = 0;
    char ch;

    while (decoded < max_bytes) {
        if (read_bits_in_buffer < 8) {
            size_t rd = BaseFile::read_raw(&ch, 1);
            if (rd == 0) break;

            int idx = decode_table[(unsigned char)ch];
            if (idx == -1) return 0;

            read_bit_buffer = (read_bit_buffer << 5) | idx;
            read_bits_in_buffer += 5;
        }

        while (read_bits_in_buffer >= 8 and decoded < max_bytes) {
            data[decoded++] = (read_bit_buffer >> (read_bits_in_buffer - 8)) & 0xFF;
            read_bits_in_buffer -= 8;
        }
    }

    return decoded;
}

bool Base32File::seek(long offset) {
    if (write_bits_in_buffer > 0) {
        int idx = (write_bit_buffer << (5 - write_bits_in_buffer)) & 0x1F;
        char ch = encode_table[idx];
        BaseFile::write_raw(&ch, 1);
        write_bits_in_buffer = 0;
        write_bit_buffer = 0;
    }
    read_bit_buffer = 0;
    read_bits_in_buffer = 0;
    return BaseFile::seek(offset);
}

// Реализация RleFile
RleFile::RleFile(const char* filename, const char* mode)
    : BaseFile(filename, mode),
      leftover_value(0), leftover_count(0),
      last_byte(0), last_count(0) {
#ifdef DEBUG_CONSTRUCTORS
    std::cout << "RleFile конструктор с параметрами: " << this << std::endl;
#endif
}

RleFile::RleFile(FILE* existing_file)
    : BaseFile(existing_file),
      leftover_value(0), leftover_count(0),
      last_byte(0), last_count(0) {
#ifdef DEBUG_CONSTRUCTORS
    std::cout << "RleFile конструктор от FILE*: " << this << std::endl;
#endif
}

RleFile::~RleFile() {
    if (last_count > 0) {
        unsigned char pair[2] = {(unsigned char)last_count, last_byte};
        BaseFile::write_raw(pair, 2);
    }
#ifdef DEBUG_CONSTRUCTORS
    std::cout << "RleFile деструктор: " << this << std::endl;
#endif
}

size_t RleFile::write(const void* buf, size_t n_bytes) {
    if (not is_open() or buf == nullptr) return 0;

    const unsigned char* data = (const unsigned char*)buf;
    size_t i = 0;

    // Обработка предыдущей последовательности
    if (last_count > 0) {
        if (last_byte == data[0]) {
            last_count++;
            if (last_count == 255) {
                unsigned char pair[2] = {255, last_byte};
                BaseFile::write_raw(pair, 2);
                last_count = 0;
            }
            i = 1;
        } else {
            unsigned char pair[2] = {(unsigned char)last_count, last_byte};
            BaseFile::write_raw(pair, 2);
            last_count = 0;
        }
    }

    // Нахождение повторений и запись пары
    while (i < n_bytes) {
        unsigned char current = data[i];
        unsigned char count = 1;
        // Количество одинаковых символов подряд
        while (i + count < n_bytes and data[i + count] == current and count < 255) {
            count++;
        }

        unsigned char pair[2] = {count, current};
        BaseFile::write_raw(pair, 2);
        i += count;
    }

    return n_bytes;
}

size_t RleFile::read(void* buf, size_t max_bytes) {
    if (not is_open() or buf == nullptr) return 0;

    unsigned char* data = (unsigned char*)buf;
    size_t read_bytes = 0;

    if (leftover_count > 0) {
        size_t to_copy = (leftover_count < max_bytes) ? leftover_count : max_bytes;
        for (size_t i = 0; i < to_copy; ++i) data[read_bytes++] = leftover_value;
        leftover_count -= to_copy;
        if (read_bytes == max_bytes) return read_bytes;
    }

    while (read_bytes < max_bytes) {
        unsigned char pair[2];
        size_t rd = BaseFile::read_raw(pair, 2);
        if (rd < 2) break;

        unsigned char count = pair[0];
        unsigned char value = pair[1];

        size_t to_write = count;
        if (read_bytes + to_write > max_bytes) {
            to_write = max_bytes - read_bytes;
            leftover_value = value;
            leftover_count = count - to_write;
        }

        for (size_t i = 0; i < to_write; ++i) data[read_bytes++] = value;
    }

    return read_bytes;
}

bool RleFile::seek(long offset) {
    if (last_count > 0) {
        unsigned char pair[2] = {(unsigned char)last_count, last_byte};
        BaseFile::write_raw(pair, 2);
        last_count = 0;
    }
    leftover_count = 0;
    return BaseFile::seek(offset);
}

// Реализация Base32File2
void Base32File2::init_tables(const char* table) {
    for (int i = 0; i < 32; ++i) encode_table[i] = table[i];
    for (int i = 0; i < 256; ++i) decode_table[i] = -1;
    for (int i = 0; i < 32; ++i) decode_table[(unsigned char)table[i]] = i;
}

int Base32File2::encoded32_size(int raw_size) const {
    if (raw_size < 0) return -1;
    return (raw_size * 8 + 4) / 5;
}

Base32File2::Base32File2(IFile* file, const char* table)
    : wrapped(file),
      read_bit_buffer(0), read_bits_in_buffer(0),
      write_bit_buffer(0), write_bits_in_buffer(0) {
    init_tables(table);
}

Base32File2::~Base32File2() {
    if (write_bits_in_buffer > 0) {
        int idx = (write_bit_buffer << (5 - write_bits_in_buffer)) & 0x1F;
        char ch = encode_table[idx];
        wrapped->write(&ch, 1);
    }
    delete wrapped;
}

bool Base32File2::is_open() const { return wrapped->is_open(); }
bool Base32File2::can_read() const { return wrapped->can_read(); }
bool Base32File2::can_write() const { return wrapped->can_write(); }

size_t Base32File2::write(const void* buf, size_t n_bytes) {
    if (not is_open() or buf == nullptr) return 0;

    const unsigned char* data = (const unsigned char*)buf;
    int& bit_buffer = write_bit_buffer;
    int& bits = write_bits_in_buffer;

    char* encoded = new char[encoded32_size(n_bytes) + 2];
    int dst = 0;

    for (size_t i = 0; i < n_bytes; ++i) {
        bit_buffer = (bit_buffer << 8) | data[i];
        bits += 8;

        while (bits >= 5) {
            int idx = (bit_buffer >> (bits - 5)) & 0x1F;
            encoded[dst++] = encode_table[idx];
            bits -= 5;
        }
    }

    size_t written = wrapped->write(encoded, dst);
    delete[] encoded;
    return (written == (size_t)dst) ? n_bytes : 0;
}

size_t Base32File2::read(void* buf, size_t max_bytes) {
    if (not is_open() or buf == nullptr) return 0;

    unsigned char* data = (unsigned char*)buf;
    size_t decoded = 0;
    char ch;

    while (decoded < max_bytes) {
        if (read_bits_in_buffer < 8) {
            size_t rd = wrapped->read(&ch, 1);
            if (rd == 0) break;

            int idx = decode_table[(unsigned char)ch];
            if (idx == -1) return 0;

            read_bit_buffer = (read_bit_buffer << 5) | idx;
            read_bits_in_buffer += 5;
        }

        while (read_bits_in_buffer >= 8 and decoded < max_bytes) {
            data[decoded++] = (read_bit_buffer >> (read_bits_in_buffer - 8)) & 0xFF;
            read_bits_in_buffer -= 8;
        }
    }

    return decoded;
}

bool Base32File2::seek(long offset) {
    if (write_bits_in_buffer > 0) {
        int idx = (write_bit_buffer << (5 - write_bits_in_buffer)) & 0x1F;
        char ch = encode_table[idx];
        wrapped->write(&ch, 1);
        write_bits_in_buffer = 0;
        write_bit_buffer = 0;
    }
    read_bit_buffer = 0;
    read_bits_in_buffer = 0;
    return wrapped->seek(offset);
}

// Реализация RleFile2
RleFile2::RleFile2(IFile* file)
    : wrapped(file),
      leftover_value(0), leftover_count(0),
      last_byte(0), last_count(0) {}

RleFile2::~RleFile2() {
    if (last_count > 0) {
        unsigned char pair[2] = {(unsigned char)last_count, last_byte};
        wrapped->write(pair, 2);
    }
    delete wrapped;
}

bool RleFile2::is_open() const { return wrapped->is_open(); }
bool RleFile2::can_read() const { return wrapped->can_read(); }
bool RleFile2::can_write() const { return wrapped->can_write(); }

size_t RleFile2::write(const void* buf, size_t n_bytes) {
    if (not is_open() or buf == nullptr) return 0;

    const unsigned char* data = (const unsigned char*)buf;
    size_t i = 0;

    if (last_count > 0) {
        if (last_byte == data[0]) {
            last_count++;
            if (last_count == 255) {
                unsigned char pair[2] = {255, last_byte};
                wrapped->write(pair, 2);
                last_count = 0;
            }
            i = 1;
        } else {
            unsigned char pair[2] = {(unsigned char)last_count, last_byte};
            wrapped->write(pair, 2);
            last_count = 0;
        }
    }

    while (i < n_bytes) {
        unsigned char current = data[i];
        unsigned char count = 1;
        while (i + count < n_bytes and data[i + count] == current and count < 255) {
            ++count;
        }

        unsigned char pair[2] = {count, current};
        wrapped->write(pair, 2);
        i += count;
    }

    return n_bytes;
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    if (not is_open() or buf == nullptr) return 0;

    unsigned char* data = (unsigned char*)buf;
    size_t read_bytes = 0;

    if (leftover_count > 0) {
        size_t to_copy = (leftover_count < max_bytes) ? leftover_count : max_bytes;
        for (size_t i = 0; i < to_copy; ++i) data[read_bytes++] = leftover_value;
        leftover_count -= to_copy;
        if (read_bytes == max_bytes) return read_bytes;
    }

    while (read_bytes < max_bytes) {
        unsigned char pair[2];
        size_t rd = wrapped->read(pair, 2);
        if (rd < 2) break;

        unsigned char count = pair[0];
        unsigned char value = pair[1];

        size_t to_write = count;
        if (read_bytes + to_write > max_bytes) {
            to_write = max_bytes - read_bytes;
            leftover_value = value;
            leftover_count = count - to_write;
        }

        for (size_t i = 0; i < to_write; ++i) data[read_bytes++] = value;
    }

    return read_bytes;
}

bool RleFile2::seek(long offset) {
    if (last_count > 0) {
        unsigned char pair[2] = {(unsigned char)last_count, last_byte};
        wrapped->write(pair, 2);
        last_count = 0;
    }
    leftover_count = 0;
    return wrapped->seek(offset);
}

// Вспомогательные функции
void write_int(IFile& file, int n) {
    if (n < 0) {
        file.write("-", 1);
        n = -n;
    }
    while (n > 0) {
        char digit = '0' + (n % 10);
        file.write(&digit, 1);
        n /= 10;
    }
}

int my_strcmp(const char* s1, const char* s2) {
    if (s1 == nullptr or s2 == nullptr) return -1;
    int i = 0;
    while (s1[i] != '\0' and s2[i] != '\0') {
        if (s1[i] != s2[i]) return s1[i] - s2[i];
        ++i;
    }
    return s1[i] - s2[i];
}