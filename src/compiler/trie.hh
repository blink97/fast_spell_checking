#pragma once

class Node
{
private:
    std::string value_;
    std::map<std::string, Node> children_;
public:
    std::string get_value() const { return value_; };
    Node get_child(std::string);

    void insert(std::string);
}
