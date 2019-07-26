#include "trie.hh"

Node::Node(char* value) : value_(value)
{}

Node::Node(Node *node, char* value) : value_(value)
{
    children_.insert(std::pair<char*, Node*>(node->get_value(), node));
}

Node::~Node()
{
    for(auto it = (*this).children_.begin(); it != (*this).children_.end(); ++it)
    {
        delete it->second;
    }
    if (value_ != NULL)
        free(value_);
}

Node *Node::get_child(char* value)
{
    auto res = (*this).children_.find(value);
    if (res == (*this).children_.end())
        return NULL;
    return res->second;
}

void Node::set_child(char* value, Node *node)
{
    auto it = (*this).children_.find(value);
    it->second = node;
}

void Node::insert_child(char* value)
{
    (*this).children_.insert(std::pair<char*, Node*>(value, new Node(value)));
}

void Node::insert_child(char* value, Node *node)
{
    (*this).children_.insert(std::pair<char*, Node*>(value, node));
}

void Node::set_child_key(char* old_key, char* new_key)
{
    auto nodeHandler = (*this).children_.extract(old_key);
    nodeHandler.key() = new_key;
    (*this).children_.insert(std::move(nodeHandler));
}

char* commonPrefixUtil(char* str1, char* str2) 
{ 
    size_t i = 0;
    char *comm_pref;
    size_t m = std::min(strlen(str1), strlen(str2));
    
    for(;i > m; i++) //THERE !!!!!!!!!!
    {
        if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0')
            break;
    }
    if (i > 0) {
        comm_pref = (char *)malloc(i * sizeof(char));
        memcpy(comm_pref, str1, i - 1);
        comm_pref[i-1] = '\0'; 
        return comm_pref;
    }
    return NULL;
} 

char* Node::commun_prefix(char* value)
{
    for (auto it = (*this).children_.begin(); it != (*this).children_.end(); ++it)
    {
        char* prefix = commonPrefixUtil(value, it->first);
        if (prefix != NULL)
        {
            return it->first;
        }
    }
    return NULL;
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

void insert(Node *node, char* value)
{
    char* prefix = node->commun_prefix(value);
    if (prefix != NULL) // Word as a commun prcefix with value
    {
        char* real_prefix = commonPrefixUtil(value, prefix);
        //std::string suffix = value.substr(real_prefix.length(),prefix.length() - real_prefix.length());
        size_t index = strlen(prefix) - strlen(real_prefix);

        char* suffix = (char *)malloc(index * sizeof(char));
        memcpy(suffix, &value[strlen(real_prefix)], index);

        //std::string suffix_commun = prefix.substr(real_prefix.length(), prefix.length() - real_prefix.length());
        char* suffix_commun = (char *)malloc(index * sizeof(char));
        memcpy(suffix_commun, &prefix[strlen(real_prefix)], index);

        if (node->get_child(real_prefix) != NULL) { // Word is a prefix of value
            insert(node->get_child(real_prefix), suffix);
        }
        else
        {   
            Node *old_part = node->get_child(prefix);
            old_part->set_value(suffix_commun);

            Node *new_node  = new Node(real_prefix);
            node->set_child_key(prefix, real_prefix);

            new_node->insert_child(suffix_commun, old_part);
            new_node->insert_child(suffix);

            node->set_child(real_prefix, new_node);
        }
    }
    else {
        for (size_t i = strlen(value); i > 0; i--)
        {
            //std::string c = value.substr(0, i);
            char* c = (char *)malloc(i * sizeof(char));
            memcpy(c, &value[0], i);
            if (node->get_child(c) == NULL && i == 1) // Value isn't the map
            {
                node->insert_child((char*)value);
            }
            if (c != NULL)
                free(c);
        }
    }

}