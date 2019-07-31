#pragma once

/*!
 * \file app/levenshtein.cc
 * \brief Search function
 * \author Etienne G. (gandil_e)
 * \version 1.0
 * \date 31/07/2019
 */

#include <fstream>
#include <vector>

/*!
 *  \brief Searcher
 *
 *  Search recursively all the word at the good distance
 *  Use the Demarau-Levenshtein algorithm
 *
 *  \param is : Stream of the binary dictionay
 *  \param letter : Current letter
 *  \param value : Word searched
 *  \param previousRow : The row coresponding at the previous letter in the levenshtein algorithm
 *  \param results : The map containing the good word
 *  \param maxCost : The maximun D-L distance
 *  \param prevLetter : The letter before the actual letter (for the transposition part)
 *  \param prePreviousRow : The row coresponding of the n-2 letter (for the transposition part)
 *  \param freq : Frequency of the actual letter
 *  \param map_size : Number of children of the node
 *  \param prefix : The actual complet word
 */
void searchRecursive(std::ifstream &is, char letter, std::string value,
                    std::vector<int> previousRow,
                    std::vector<std::tuple<std::string, int, int>> *results,
                    int maxCost, char prevLetter, std::vector<int> prePreviousRow,
                    int freq, size_t map_size, std::string prefix);
/*!
 *  \brief Searcher
 *
 *  Search all the word at the good distance
 *  Call searchRecurvive
 *
 *  \param is : Stream of the binary dictionay
 *  \param value : Word searched
 *  \param maxDistance : The maximun D-L distance
 */
void search(std::ifstream &is, std::string value, int maxDistance);
