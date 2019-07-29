#include "trie.hh"

#include <fstream>

Node::Node() : freq_(0)
{}

Node::Node(int freq) : freq_(freq)
{}

/*Node::Node(Node *node)
{
    children_.insert(std::pair<std::string, Node*>(node->get_value(), node));
}*/

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

// std::string commonPrefixUtil(std::string str1, std::string str2) 
// { 
//     std::string result; 
//     int n1 = str1.length();
//     int n2 = str2.length(); 

//     for (int i=0, j=0; i <= n1 - 1 && j <= n2 - 1; i++, j++) 
//     { 
//         if (str1[i] != str2[j]) 
//             break; 
//         result.push_back(str1[i]); 
//     } 
  
//     return (result);
// } 

// std::string Node::commun_prefix(std::string value)
// {
//     for (auto it = (*this).children_.begin(); it != (*this).children_.end(); ++it)
//     {
//         std::string prefix = commonPrefixUtil(value, it->first);
//         if (prefix != "")
//         {
//             return it->first;
//         }
//     }
//     return "";
// }

std::ostream& operator <<(std::ostream& os, const Node& node)
{
    //os << node.value_;
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

// void insert(Node *node, std::string value, int freq)
// {
//     std::string prefix = node->commun_prefix(value);
//     if (prefix != "") // Word as a commun prcefix with value
//     {
//         std::string real_prefix = commonPrefixUtil(value, prefix);
//         std::string suffix = value.substr(real_prefix.length(), value.length() - real_prefix.length());
//         /*size_t index = strlen(prefix) - strlen(real_prefix);

//         char* suffix = (char *)malloc(index * sizeof(char));
//         memcpy(suffix, &value[strlen(real_prefix)], index);*/

//         std::string rest = prefix.substr(real_prefix.length(), prefix.length() - real_prefix.length());
//         /*char* rest = (char *)malloc(index * sizeof(char));
//         memcpy(rest, &prefix[strlen(real_prefix)], index);*/

//         if (node->get_child(real_prefix) != NULL) { // Word is a prefix of value
//             insert(node->get_child(real_prefix), suffix, freq);
//         }
//         else
//         {   
//             Node *old_part = node->get_child(prefix);

//             Node *new_node  = new Node();
//             node->set_child_key(prefix, real_prefix);

//             new_node->insert_child(rest, old_part);
//             new_node->insert_child(suffix, freq);

//             node->set_child(real_prefix, new_node);
//         }
//     }
//     else {
//         node->insert_child(value, freq);
//     }

// }

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
        node = node->get_child(c);
    }
}

size_t writeNodeToFile(std::ofstream &f, Node &node)
{
    size_t size = 0;
    int freq = node.get_freq();
    f.write(reinterpret_cast<const char *>(&freq), sizeof(int));
    size  += sizeof(int);
    auto map = node.get_children();
    size_t map_size = map.size();
    f.write(reinterpret_cast<const char *>(&map_size), sizeof(size_t));
    size += sizeof(size_t);
    for(auto it = map.begin(); it != map.end(); ++it)
    {
        f.write(&(it->first), sizeof(char));
        size += sizeof(char);
        size += sizeof(size_t);
        f.write(reinterpret_cast<const char *>(&size), sizeof(size_t));
        size += writeNodeToFile(f, *(it->second));
    }
    return size;
}