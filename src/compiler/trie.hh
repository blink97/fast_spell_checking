#pragma once

/*!
 * \file compiler/trie.hh
 * \brief Function concerning the trie
 * \author Etienne G. (gandil_e)
 * \version 1.0
 * \date 31/07/2019
 */

#include <string.h>

#include <string>
#include <map>
#include <iostream>
#include <algorithm>


/*! \class Node
 * \brief Trie node class
 *
 *  The class contains one node of the trie
 *  The trie is forms with multiple node
 */
class Node
{
private:
    int freq_; /*!< Frequency of the word, if 0 the node isn't a word*/
    std::map<char, Node*> children_; /*!< A map containing the children, the key is the char of the child */
public:

    /*!
     *  \brief Constructor
     *
     *  Constructor of the Node class
     */
    Node();
    /*!
     *  \brief Constructor
     *
     *  Constructeur of the Node class
     *
     *  \param freq : Frequency of the word
     */
    Node(int freq);
    /*!
     *  \brief Destructor
     *
     *  Destructor of the Node class
     */
    ~Node();

    /*!
     *  \brief Frequency getter
     * 
     *  Get the frequency
     *
     *  \return The Frequency of the node
     */
    int get_freq() {return freq_; };
    /*!
     *  \brief Frequency setter
     *
     *  Set the frequency
     * 
     *  \param freq : Frequency of the word
     */
    void set_freq(int freq);

    /*!
     *  \brief Child getter
     *
     *  Get the child corresponding at the good key
     * 
     *  \param value : The key of the child
     * 
     *  \return The child
     */
    Node *get_child(char value);
    /*!
     *  \brief Child setter
     *
     *  Set the child corresponding at the good key
     * 
     *  \param value : The key of the child
     *  \param node : The value in the map
     */
    void set_child(char value, Node *node);

    /*!
     *  \brief Children getter
     *
     *  Get the children map
     * 
     *  \return The children
     */
    std::map<char, Node*> get_children() {return children_; };

    /*!
     *  \brief Insert Child
     *
     *  Insert a new child in the map
     * 
     *  \param value : The key of the new child
     */
    void insert_child(char value);
    /*!
     *  \brief Insert Child
     *
     *  Insert a new child in the map
     * 
     *  \param value : The key of the new child
     *  \param freq : The frequency of the new child
     */
    void insert_child(char value, int freq);
    /*!
     *  \brief Insert Child
     *
     *  Insert a new child in the map
     * 
     *  \param value : The key of the new child
     *  \param node : The existing node of the new child
     */
    void insert_child(char value, Node *node);
    /*!
     *  \brief Character Setter
     *
     *  Change the character of a node
     * 
     *  \param old_key : The old key of the child
     *  \param new_key : The new key of the child
     */
    void set_child_key(char old_key, char new_key);

    /*!
     *  \brief Operator <<
     *
     *  Pretty printer of the class
     * 
     *  \param os : Stream wanted
     *  \param node : node displayed
     */
    friend std::ostream& operator <<(std::ostream& os, const Node& node);
};

/*!
 *  \brief Insert word
 *
 *  Insert a new word in the trie
 * 
 *  \param node : the root of the trie
 *  \param value : word to add
 *  \param frea : frequency of the word
 */
void insert(Node *node, std::string value, int freq);
/*!
 *  \brief Serialize
 *
 *  Wrtie the trie in a binary file
 * 
 *  \param f : Stream of the file
 *  \param node : node the write
 *  \param val : character of the node
 */
size_t writeNodeToFile(std::ofstream &f, Node &node, char val);