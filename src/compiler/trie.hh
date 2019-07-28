#pragma once

#include <string.h>

#include <string>
#include <map>
#include <iostream>
#include <algorithm>

class Node
{
private:
    // string to char*
    // vtable ?
    char value_;
    int freq_ = 0;
    std::map<char, Node*> children_;
public:
    Node() = default;
    Node(char value);
    Node(char value, int freq);
    Node(Node* node, char value);
    ~Node();
    
    char get_value() { return value_; };
    void set_value(char value) { value_ = value; };

    Node *get_child(char value);
    void set_child(char value, Node *node);

    void insert_child(char value);
    void insert_child(char value, int freq);
    void insert_child(char value, Node *node);
    void set_child_key(char old_key, char new_key);

    char* commun_prefix(char* value);

    friend std::ostream& operator <<(std::ostream& os, const Node& node);
};

void insert(Node *node, std::string value, int freq);