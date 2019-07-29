#include <string>

#include "reader.hh"

Node *read(std::string path)
{
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) 
        return NULL;

    std::string word;
    std::string freq;
    Node *root = new Node();
    while (file >> word)
    {
        file >> freq;
        insert(root, word, std::stoi(freq));
    }
    return root;
}