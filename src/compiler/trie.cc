#include "trie.hh"

Node::Node(std::string value) : value_(value)
{}

Node::Node(Node *node, std::string value) : value_(value)
{
    children_.insert(std::pair<std::string, Node*>(node->get_value(), node));
}

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

void Node::set_child(std::string value, Node *node)
{
    auto it = (*this).children_.find(value);
    it->second = node;
}

void Node::insert_child(std::string value)
{
    (*this).children_.insert(std::pair<std::string, Node*>(value, new Node(value)));
}

void Node::insert_child(std::string value, Node *node)
{
    (*this).children_.insert(std::pair<std::string, Node*>(value, node));
}

void Node::set_child_key(std::string old_key, std::string new_key)
{
    auto nodeHandler = (*this).children_.extract(old_key);
    nodeHandler.key() = new_key;
    (*this).children_.insert(std::move(nodeHandler));
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
        std::string suffix = value.substr(real_prefix.length(), value.length() - real_prefix.length());
        std::string suffix_commun = prefix.substr(real_prefix.length(), prefix.length() - real_prefix.length());
        if (node->get_child(real_prefix) != NULL) { // Word is a prefix of value
            insert(node->get_child(real_prefix), suffix);
        }
        else
        {   
            std::cout << "old_part" << std::endl;
            Node *old_part = node->get_child(prefix);
            old_part->set_value(suffix_commun);

            std::cout << "new_node" << std::endl;
            Node *new_node  = new Node(real_prefix);
            node->set_child_key(prefix, real_prefix);

            std::cout << "insert" << std::endl;
            new_node->insert_child(suffix_commun, old_part);
            new_node->insert_child(suffix);

            std::cout << "set" << std::endl;
            node->set_child(real_prefix, new_node);
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