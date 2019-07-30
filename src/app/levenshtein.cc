#include "levenshtein.hh"
#include "file.hh"

#include <iostream>

#define SIZE_NODE 21

void search0(std::ifstream &is, std::string value)
{
    size_t i = 0;
    size_t size_map = 0;
    size_t cpt = 0;
    while(i < value.length() && cpt != size_map && cpt != 0)
    {
        size_t size = read_size_t(is);
        if (size_map == 0)
            size_map = size;
        char val = read_char(is);
        int freq = read_int(is);
        size_t offset = read_size_t(is);
        if (val == value[i])
        {
            std::cout << val;
            if (i == value.length() - 1)
            {
                if (freq > 0)
                    std::cout << " : " << freq << std::endl;
                else
                    std::cout << " not a real word" << std::endl;
            }
            cpt = 0;
            size_map = 0;
            i++;
        }
        else
        {
            size_t pos = is.tellg();
            is.seekg (pos + offset - SIZE_NODE);
            cpt++;
        }
    }
    return;
}