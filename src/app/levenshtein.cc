#include "levenshtein.hh"
#include "file.hh"

#include <iostream>
#include <numeric>
#include <algorithm>

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

void searchRecursive(std::ifstream &is, char letter, std::string value,
                    std::vector<int> previousRow,
                    std::vector<std::tuple<std::string, int, int>> *results,
                    int maxCost, char prevLetter, std::vector<int> prePreviousRow,
                    int freq)
{
    int columns = value.length() + 1;
    std::vector<int> currentRow(columns);
    currentRow[0] = previousRow[0] + 1;

    for (int column = 1; column < columns; column++)
    {
        int insertCost = currentRow[column - 1] + 1;
        int deleteCost = previousRow[column] + 1;
        int replaceCost;
        
        if (value[column - 1] != letter)
            replaceCost = previousRow[column - 1] + 1;
        else
            replaceCost = previousRow[column - 1];
        
        currentRow[column] = std::min({insertCost, deleteCost, replaceCost});

        if (prevLetter != '\0' && column > 1 && letter == value[column - 2] &&
            prevLetter == value[column - 1] && value[column - 1] != letter)
        {
            currentRow[column] = std::min(currentRow[column], prePreviousRow[column - 2] + 1);
        }
    }

    if (currentRow[value.length()] <= maxCost && freq > 0)
        results->push_back(std::make_tuple(value, freq, currentRow[value.length()]));

    if (*std::min_element(currentRow.begin(), currentRow.end()) <= maxCost)
    {
        prevLetter = letter;

        size_t size_map = read_size_t(is);
        for (size_t i = 0; i < size_map; i++)
        {
            char val = read_char(is);
            int freq = read_int(is);
            size_t offset = read_size_t(is);
            size_t pos = is.tellg();
            searchRecursive(is, val, value, currentRow, results, maxCost, prevLetter, previousRow, freq);
            is.seekg (pos + offset - SIZE_NODE);
        }
    }
}


void search(std::ifstream &is, std::string value, int maxDistance)
{
    std::vector<int> currentRow(value.length() + 1);
    std::iota(std::begin(currentRow), std::end(currentRow), 0);

    std::vector<std::tuple<std::string, int, int>> *results = new std::vector<std::tuple<std::string, int, int>>();

    size_t size_map = read_size_t(is);

    for (size_t i = 0; i < size_map; i++)
    {
        char val = read_char(is);
        int freq = read_int(is);
        size_t offset = read_size_t(is);
        size_t pos = is.tellg();
        searchRecursive(is, val, value, currentRow, results, maxDistance, '\0', currentRow, freq);
        std::cout << pos + offset - SIZE_NODE << std::endl;
        is.seekg (pos + offset - SIZE_NODE);
        std:: cout << is.tellg() << std::endl;
    }

    std::cout << results << std::endl;

    delete results;
}