#pragma once

#include <string>
#include <map>
#include <iostream>

class Node
{
private:
    std::string value_;
    std::map<std::string, Node*> children_;
public:
    Node() = default;
    Node(std::string value);
    Node(Node* node, std::string value);
    ~Node();
    
    std::string get_value() const { return value_; };
    void set_value(std::string value) { value_ = value; };

    Node *get_child(std::string value);
    void set_child(std::string value, Node *node);

    void insert_child(std::string value);
    void insert_child(std::string value, Node *node);
    void set_child_key(std::string old_key, std::string new_key);

    std::string commun_prefix(std::string value);

    friend std::ostream& operator <<(std::ostream& os, const Node& node);
};

void insert(Node *node, std::string value);