#pragma once

/*!
 * \file app/file.cc
 * \brief small API to read binary file containing the words
 *  
 * For each node you need to use in order "read_size_t -> read_char -> read_int -> read_size_t"
 * 
 * \author Etienne G. (gandil_e)
 * \version 1.0
 * \date 31/07/2019
 */

#include <fstream>

/*!
 *  \brief Int reader
 *
 *  Read the binary file for a size of int
 *
 *  \param is : Stream of the binary dictionay
 */
int read_int(std::ifstream &is);
/*!
 *  \brief Size_t reader
 *
  *  Read the binary file for a size of size_t
 *
 *  \param is : Stream of the binary dictionay
 */
size_t read_size_t(std::ifstream &is);
/*!
 *  \brief Char reader
 *
 *  Read the binary file for a size of char
 *
 *  \param is : Stream of the binary dictionay
 */
char read_char(std::ifstream &is);