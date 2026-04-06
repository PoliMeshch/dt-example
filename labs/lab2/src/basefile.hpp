#ifndef BASEFILE_HPP
#define BASEFILE_HPP

#include <cstdio>

class IFile {
public:
    virtual bool is_open() const = 0;
    virtual bool can_read() const = 0;
    virtual bool can_write() const = 0;
    virtual size_t write(const void* buf, size_t n_bytes) = 0;
    virtual size_t read(void* buf, size_t max_bytes) = 0;
    virtual bool seek(long offset) = 0;
    virtual ~IFile() {}
};

class BaseFile : public IFile {
private:
    FILE* file;
    const char* open_mode;  // Режим открытия

public:
    BaseFile();
    BaseFile(const char* filename, const char* mode);
    BaseFile(FILE* existing_file);
    virtual ~BaseFile();

    // Запрет копирования, так как два объекта не могут владеть одним файлом
    BaseFile(const BaseFile&) = delete;
    BaseFile& operator=(const BaseFile&) = delete;

    // Разрешение перемещения, чтобы возвращать объект из функции
    BaseFile(BaseFile&&) = default;
    BaseFile& operator=(BaseFile&&) = default;

    bool is_open() const;
    bool can_read() const;
    bool can_write() const;

    size_t write_raw(const void* buf, size_t n_bytes);
    size_t read_raw(void* buf, size_t max_bytes);

    long tell() const;
    bool seek(long offset) override;

    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

class Base32File : public BaseFile {
private:
    char encode_table[32];
    char decode_table[256];
    int read_bit_buffer;      // Накопленные биты для чтения
    int read_bits_in_buffer;  // Количество бит для чтения в буфере
    int write_bit_buffer;     // Накопленные биты для записи
    int write_bits_in_buffer; // Количество бит для записи в буфере

    void init_tables(const char* table);
    int encoded32_size(int raw_size) const;

public:
    Base32File(const char* filename, const char* mode, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    Base32File(FILE* existing_file, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    ~Base32File();

    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
    bool seek(long offset) override;
};

class RleFile : public BaseFile {
private:
    unsigned char leftover_value;   // Для чтения: остаток значения из пары
    size_t leftover_count;          // Для чтения: сколько байт осталось
    unsigned char last_byte;        // Для записи: последний байт незавершённой последовательности
    size_t last_count;              // Для записи: количество байт в незавершённой последовательности
    // last_byte и last_count используются для продолжения последовательности из предыдущего вызова,
    // но не сохраняют новую последовательность для следующего

public:
    RleFile(const char* filename, const char* mode);
    RleFile(FILE* existing_file);
    ~RleFile();

    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
    bool seek(long offset) override;
};

class Base32File2 : public IFile {
private:
    IFile* wrapped;
    char encode_table[32];
    char decode_table[256];
    int read_bit_buffer;
    int read_bits_in_buffer;
    int write_bit_buffer;
    int write_bits_in_buffer;

    void init_tables(const char* table);
    int encoded32_size(int raw_size) const;

public:
    Base32File2(IFile* file, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    ~Base32File2();

    Base32File2(const Base32File2&) = delete;
    Base32File2& operator=(const Base32File2&) = delete;
    Base32File2(Base32File2&&) = default;
    Base32File2& operator=(Base32File2&&) = default;

    bool is_open() const;
    bool can_read() const;
    bool can_write() const;
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
    bool seek(long offset) override;
};

class RleFile2 : public IFile {
private:
    IFile* wrapped;
    unsigned char leftover_value;
    size_t leftover_count;
    unsigned char last_byte;
    size_t last_count;

public:
    RleFile2(IFile* file);
    ~RleFile2();

    RleFile2(const RleFile2&) = delete;
    RleFile2& operator=(const RleFile2&) = delete;
    RleFile2(RleFile2&&) = default;
    RleFile2& operator=(RleFile2&&) = default;

    bool is_open() const;
    bool can_read() const;
    bool can_write() const;
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
    bool seek(long offset) override;
};

// Вспомогательные функции
void write_int(IFile& file, int n);
int my_strcmp(const char* s1, const char* s2);

#endif