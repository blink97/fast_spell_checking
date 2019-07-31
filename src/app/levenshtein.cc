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
                    int freq, size_t map_size, std::string prefix)
{
    //std::cout << prefix << ": " << freq << std::endl;
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
        results->push_back(std::make_tuple(prefix, freq, currentRow[value.length()]));

    if (*std::min_element(currentRow.begin(), currentRow.end()) <= maxCost)
    {
        prevLetter = letter;

        for (size_t i = 0; i < map_size; i++)
        {
            size_t new_map_size = read_size_t(is);
            char val = read_char(is);
            int freq = read_int(is);
            size_t offset = read_size_t(is);
            size_t pos = is.tellg();
            std::string new_prefix = prefix;
            new_prefix.append(1, val);
            searchRecursive(is, val, value, currentRow, results, maxCost, prevLetter, previousRow, freq, new_map_size, new_prefix);
            is.seekg (pos + offset);
        }
    }
}


void search(std::ifstream &is, std::string value, int maxDistance)
{
    std::vector<int> currentRow(value.length() + 1);
    std::iota(std::begin(currentRow), std::end(currentRow), 0);

    std::vector<std::tuple<std::string, int, int>> *results = new std::vector<std::tuple<std::string, int, int>>();

    size_t size_map = read_size_t(is);
    read_char(is);
    read_int(is);
    read_size_t(is);

    for (size_t i = 0; i < size_map; i++)
    {
        size_t new_map_size = read_size_t(is);
        char val = read_char(is);
        int freq = read_int(is);
        size_t offset = read_size_t(is);
        size_t pos = is.tellg();
        //std::cout << "val is " << val << std::endl;
        std::string prefix;
        prefix.append(1, val);
        searchRecursive(is, val, value, currentRow, results, maxDistance, '\0', currentRow, freq, new_map_size, prefix);
        is.seekg (pos + offset);
        //std::cout << pos + offset << std::endl;
    }

    // DISPLAY
    std::cout << "[";
    for(auto it = results->begin(); it != results->end(); ++it)
    {
        if (it != results->begin())
            std::cout << ",";
        std::cout << "{";
        std::cout << "\"word\":\"" << std::get<0>(*it) << "\",";
        std::cout << "\"freq\":\"" << std::get<1>(*it) << "\",";
        std::cout << "\"distance\":" << std::get<2>(*it);
        std::cout << "}";
    }
    std::cout << "]" << std::endl;

    delete results;
}