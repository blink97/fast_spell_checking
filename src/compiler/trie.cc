#include "trie.hh"

Node::Node(std::string value) : value_(value)
{}

Node *Node::get_child(std::string value)
{
    auto res = (*this).children_.find(value);
    if (res == (*this).children_.end())
        return NULL;
    return &(res->second);
}

void Node::insert_child(std::string value){
    (*this).children_.insert(std::pair<std::string, Node>(value, Node(value)));
}

std::ostream& operator <<(std::ostream& os, const Node& node)
{
    os << node.value_;
    os << " : {";
    for(auto it = node.children_.begin(); it != node.children_.end(); ++it)
    {
        os << it->first << ", ";
    }
    os << "}\n";
    for(auto it = node.children_.begin(); it != node.children_.end(); ++it)
    {
        os << it->second;
    }
    return os;
}

void insert(Node &node, std::string value)
{
    for (size_t i = 0; i < value.length(); i++)
    {
        std::string c = value.substr(i, 1);
        if (node.get_child(c) == NULL) 
        {
            node.insert_child(c);
        }
        node = *(node.get_child(c));
    }
    
}