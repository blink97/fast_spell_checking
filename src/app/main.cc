/*!
 * \file app/main.hh
 * \brief Launch the app
 * \author Etienne G. (gandil_e)
 * \version 1.0
 * \date 31/07/2019
 */

#include <unistd.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "file.hh"
#include "levenshtein.hh"

int main(int argc, char *argv[]) {
    if (argc != 2){
        std::cerr << "Usage: echo \"approx n word\" | ./TextMiningApp /path/to/dict.bin" << std::endl;
        std::cerr << "Usage: ./TextMiningApp /path/to/dict.bin" << std::endl;
        return 1;
    }

    FILE* fp = stdin;
    std::ifstream is(argv[1], std::ios::binary);

    if(isatty(fileno(fp)))
    {
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
    while(content == "approx" && is.is_open())
    {
        std::cin >> content;
        int number;
        std::istringstream iss(content);
        iss >> number;
        if (iss.fail())
        return 0;
        std::cin >> content;
        search(is, content, number);
        is.seekg(0);

        std::cin >> content;
    }

    return 0;
}
