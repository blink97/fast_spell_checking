#include "levenshtein.hh"
#include "file.hh"

#include <iostream>
#include <numeric>
#include <algorithm>

#define SIZE_NODE 21

bool sort_vector(std::tuple<std::string, int, int> tuple1,
                std::tuple<std::string, int, int> tuple2){
    if (std::get<2>(tuple1) != std::get<2>(tuple2)) 
        return std::get<2>(tuple1) < std::get<2>(tuple2);
    if (std::get<1>(tuple1) != std::get<1>(tuple2))
        return std::get<1>(tuple1) > std::get<1>(tuple2);
    return std::get<0>(tuple1) > std::get<0>(tuple2);

       
}

void searchRecursive(std::ifstream &is, char letter, std::string value,
                    std::vector<int> previousRow,
                    std::vector<std::tuple<std::string, int, int>> *results,
                    int maxCost, char prevLetter, std::vector<int> prePreviousRow,
                    int freq, size_t map_size, std::string prefix)
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
        std::string prefix;
        prefix.append(1, val);
        searchRecursive(is, val, value, currentRow, results, maxDistance, '\0', currentRow, freq, new_map_size, prefix);
        is.seekg (pos + offset);
    }

    // DISPLAY
    std::sort(results->begin(), results->end(), sort_vector);
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