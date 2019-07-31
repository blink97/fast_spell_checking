#pragma once

#include <fstream>
#include <vector>

void search0(std::ifstream &is, std::string value);

void searchRecursive(std::ifstream &is, char letter, std::string value,
                    std::vector<int> previousRow,
                    std::vector<std::tuple<std::string, int, int>> *results,
                    int maxCost, char prevLetter, std::vector<int> prePreviousRow,
                    int freq, size_t map_size, std::string prefix);
void search(std::ifstream &is, std::string value, int maxDistance);
