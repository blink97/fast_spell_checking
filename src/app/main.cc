#include <unistd.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void pretty_print(std::ifstream &is)
{
    int freq;
    size_t size;

    is.read((char*)&freq, sizeof(int));
    is.read((char*)&size, sizeof(size_t));

    if (freq > 0)
        std::cout << " (" << freq << ")" << std::endl;
    for(size_t i = 0; i < size; i++)
    {
        char value;
        size_t offset;
        is.read((char*)&value, sizeof(char));
        is.read((char*)&offset, sizeof(size_t));
        //std::streampos pos = is.tellg();
        std::cout << value;
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
