#pragma once

#include <string>
#include <map>

class Node
{
private:
    std::string value_;
    std::map<std::string, Node> children_;
public:
    Node() = default;
    Node(std::string value);
    std::string get_value() const { return value_; };
    Node *get_child(std::string value);
    void insert_child(std::string value);
};

void insert(Node &node, std::string value);