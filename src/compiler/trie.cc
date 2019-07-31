#include "trie.hh"

#include <fstream>

Node::Node() : freq_(0)
{}

Node::Node(int freq) : freq_(freq)
{}

Node::~Node()
{
    for(auto it = (*this).children_.begin(); it != (*this).children_.end(); ++it)
    {
        delete it->second;
    }
}

Node *Node::get_child(char value)
{
    auto res = (*this).children_.find(value);
    if (res == (*this).children_.end())
        return NULL;
    return res->second;
}

void Node::set_freq(int freq)
{
    freq_ = freq;
}

void Node::set_child(char value, Node *node)
{
    auto it = (*this).children_.find(value);
    it->second = node;
}

void Node::insert_child(char value)
{
    (*this).children_.insert(std::pair<char, Node*>(value, new Node()));
}

void Node::insert_child(char value, int freq)
{
    (*this).children_.insert(std::pair<char, Node*>(value, new Node(freq)));
}

void Node::insert_child(char value, Node *node)
{
    (*this).children_.insert(std::pair<char, Node*>(value, node));
}

void Node::set_child_key(char old_key, char new_key)
{
    auto nodeHandler = (*this).children_.extract(old_key);
    nodeHandler.key() = new_key;
    (*this).children_.insert(std::move(nodeHandler));
}

std::ostream& operator <<(std::ostream& os, const Node& node)
{
    os << "{";
    os << "\"freq\":" << node.freq_ << ",";
    os << "\"children\":{";
    for(auto it = node.children_.begin(); it != node.children_.end(); ++it)
    {
        if (it != node.children_.begin())
            os << ",";
        os << "\"" << it->first << "\":";
        os << *(it->second);
    }
    os << "}}";
    return os;
}

void insert(Node *node, std::string value, int freq)
{
    for (size_t i = 0; i < value.length(); i++)
    {
        char c = value[i];
        if (node->get_child(c) == NULL) 
        {
            if (i == value.length() - 1)
                node->insert_child(c, freq);
            else
                node->insert_child(c);
        }
        else if (i == value.length() - 1)
        {
            node->get_child(c)->set_freq(freq);
        }
        node = node->get_child(c);
    }
}

size_t writeNodeToFile(std::ofstream &f, Node &node, char val)
{
    size_t size = sizeof(int) + sizeof(size_t) + sizeof(char) + sizeof(size_t);
    auto map = node.get_children();
    size_t map_size = map.size();
    int freq = node.get_freq();
    char value = val;
    size_t off = 0;
    
    f.write(reinterpret_cast<const char *>(&map_size), sizeof(size_t));
    f.write((&value), sizeof(char));
    f.write(reinterpret_cast<const char *>(&freq), sizeof(int));
    long pos = f.tellp();
    f.write(reinterpret_cast<const char *>(&off), sizeof(size_t));

    for(auto it = map.begin(); it != map.end(); ++it)
    {
        off += writeNodeToFile(f, *(it->second), it->first);
    }
    long end = f.tellp();
    f.seekp(pos);
    f.write(reinterpret_cast<const char *>(&off), sizeof(size_t));
    f.seekp(end);
    size += off;
    return size;
}