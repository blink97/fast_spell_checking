#pragma once

#include <string.h>

#include <string>
#include <map>
#include <iostream>
#include <algorithm>

class Node
{
private:
    int freq_;
    std::map<char, Node*> children_;
public:
    Node();
    Node(int freq);
    Node(Node* node);
    ~Node();

    int get_freq() {return freq_; };
    void set_freq(int freq);

    Node *get_child(char value);
    void set_child(char value, Node *node);

    std::map<char, Node*> get_children() {return children_; };

    void insert_child(char value);
    void insert_child(char value, int freq);
    void insert_child(char value, Node *node);
    void set_child_key(char old_key, char new_key);

    char commun_prefix(char value);

    friend std::ostream& operator <<(std::ostream& os, const Node& node);
};

void insert(Node *node, std::string, int freq);
size_t writeNodeToFile(std::ofstream &f, Node &node, char val);