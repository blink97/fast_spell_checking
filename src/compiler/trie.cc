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

void Node::insert_child(std::string value)
{
    (*this).children_.insert(std::pair<std::string, Node*>(value, new Node(value)));
}

std::string commonPrefixUtil(std::string str1, std::string str2) 
{ 
    std::string result = ""; 
    int n1 = str1.length();
    int n2 = str2.length();
  
    // Compare str1 and str2 
    for (int i = 0, j = 0; i <= n1 - 1 && j <= n2 - 1; i++ ,j++) 
    { 
        if (str1[i] != str2[j]) 
            break; 
        result.push_back(str1[i]); 
    } 
    return result; 
} 

std::string Node::commun_prefix(std::string value)
{
    for (auto it = (*this).children_.begin(); it != (*this).children_.end(); ++it)
    {
        std::string prefix = commonPrefixUtil(value, it->first);
        if (prefix != "")
        {
            return it->first;
        }
    }
    return "";
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
    std::string prefix = node->commun_prefix(value);
    if (prefix != "") // Word as a commun prefix with value
    {
        std::string real_prefix = commonPrefixUtil(prefix, value);
        if (node->get_child(real_prefix) != NULL) { // Word is a prefix of value
            insert(node->get_child(real_prefix), value.substr(real_prefix.length(), value.length() - real_prefix.length()));
        }
    }
    else {
        for (size_t i = value.length(); i > 0; i--)
        {
            std::string c = value.substr(0, i);
            if (node->get_child(c) == NULL && i == 1) // Value isn't the map
            {
                node->insert_child(value);
            }
            //node = node->get_child(c);
        }
    }

}