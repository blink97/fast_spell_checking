#pragma once

/*!
 * \file compiler/reader.cc
 * \brief Read the words
 * \author Etienne G. (gandil_e)
 * \version 1.0
 * \date 31/07/2019
 */

#include <fstream>

#include "trie.hh"

/*!
 *  \brief Word reader
 *
 *  Read all the words of a file and transform them
 *  in Trie
 *
 *  \param path : path of the file
 *  \return the root of the trie
 */
Node *read(std::string path);