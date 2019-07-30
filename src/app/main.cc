#include <unistd.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "file.hh"
#include "levenshtein.hh"

void pretty_print(std::ifstream &is)
{
    std::cout << is.tellg();
    size_t size = read_size_t(is);
    char value = read_char(is);
    int freq = read_int(is);
    size_t offset = read_size_t(is);

    std::cout << " " << value <<std::endl;
    size_t pos = is.tellg();
    std::cout << "end is at " << pos + offset << std::endl;

    for(size_t i = 0; i < size; i++)
    {
        pretty_print(is);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2){
        return 1;
    }

    FILE* fp = stdin;

    if(isatty(fileno(fp)))
    {
        std::ifstream is(argv[1], std::ios::binary);

        if (is.is_open())
        {
            pretty_print(is);
            //search0(is, "bou");
            //search(is, "slowe", 1);
        }
    }

    return 0;

    // while (1) {
    //   std::string test;
    //   std::cin >> test;
    //   std::cout << test << std::endl;
    // }

    std::string content;
    std::cin >> content;
    if (content != "approx")
    return 0;
    std::cin >> content;
    int number;
    std::istringstream iss(content);
    iss >> number;
    if (iss.fail())
    return 0;
    std::cin >> content;
    //TODO distance 

}
