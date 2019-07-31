#include <unistd.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "file.hh"
#include "levenshtein.hh"

void pretty_print(std::ifstream &is, std::string prefix)
{
    size_t size = read_size_t(is);
    char value = read_char(is);
    int freq = read_int(is);
    size_t offset = read_size_t(is);

    size_t pos = is.tellg();

    std::string new_prefix = prefix;
    new_prefix.append(1, value);

    if (freq > 0)
        std::cout << new_prefix << " (" << freq << ")" << std::endl;

    for(size_t i = 0; i < size; i++)
    {
        pretty_print(is, new_prefix);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2){
        std::cerr << "Usage: echo \"approx n word\" | ./TextMiningApp /path/to/dict.bin" << std::endl;
        std::cerr << "Usage: ./TextMiningApp /path/to/dict.bin" << std::endl;
        return 1;
    }

    FILE* fp = stdin;

    if(isatty(fileno(fp)))
    {
        std::ifstream is(argv[1], std::ios::binary);

        while (1)
        {
            std::string content;
            std::string number;
            int n;
            std::string word;
            std::cin >> content >> number >> word;
            std::istringstream iss(number);
            iss >> n;
            if (!iss.fail() && content == "approx")
            {
                if (is.is_open())
                {
                    search(is, word, n);
                    is.seekg(0);
                }
            }
        }
    }

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

    std::ifstream is(argv[1], std::ios::binary);
    if (is.is_open())
        search(is, content, number);

    return 0;
}
