#include "trie.hh"

Node::Node(std::string value) : value_(value)
{}

Node::~Node()
{
    for(auto it = (*this).children_.begin(); it != (*this).children_.end(); ++it)
    {
        delete it->second;
    }
}

Node *Node::get_child(std::string value)
{
    auto res = (*this).children_.find(value);
    if (res == (*this).children_.end())
        return NULL;
    return res->second;
}

void Node::insert_child(std::string value){
    (*this).children_.insert(std::pair<std::string, Node*>(value, new Node(value)));
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
        os << *(it->second);
    }
    return os;
}

void insert(Node *node, std::string value)
{
    std::cout << value.length() << std::endl;
    for (size_t i = value.length(); i > 0; i--)
    {
        std::string c = value.substr(0, i);
        if (node->get_child(c) != NULL) {
            std::cout << value.substr(i, value.length() - i) << std::endl;
            insert(node->get_child(c), value.substr(i, value.length() - i));
            i = 1;
        }
        else if (node->get_child(c) == NULL && i == 1) 
        {
            node->insert_child(value);
        }
        //node = node->get_child(c);
    }
}