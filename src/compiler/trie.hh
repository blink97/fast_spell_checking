#pragma once

#include <string.h>

#include <string>
#include <map>
#include <iostream>
#include <algorithm>

class Node
{
private:
    // string to std::string*
    // vtable ?
    int freq_;
    std::map<std::string, Node*> children_;
public:
    Node();
    Node(int freq);
    Node(Node* node);
    ~Node();

    Node *get_child(std::string value);
    void set_child(std::string value, Node *node);

    void insert_child(std::string value);
    void insert_child(std::string value, int freq);
    void insert_child(std::string value, Node *node);
    void set_child_key(std::string old_key, std::string new_key);

    std::string commun_prefix(std::string value);

    friend std::ostream& operator <<(std::ostream& os, const Node& node);
};

void insert(Node *node, std::string value, int freq);