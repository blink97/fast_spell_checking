#include "file.hh"

int read_int(std::ifstream &is)
{
    int freq;
    is.read((char*)&freq, sizeof(int));
    return freq;
}

size_t read_size_t(std::ifstream &is)
{
    size_t size;
    is.read((char*)&size, sizeof(size_t));
    return size;
}

char read_char(std::ifstream &is)
{
    char value;
    is.read((char*)&value, sizeof(char));
    return value;
}