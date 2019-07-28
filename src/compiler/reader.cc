#include <string>

#include "reader.hh"

Node *read(std::string path)
{
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) 
        return NULL;

    std::string word;
    int cpt = 1;
    std::string freq;
    Node *root = new Node();
    while (file >> word)
    {
        file >> freq;
        std::cout << cpt << std::endl;
        insert(root, word, std::stoi(freq));
        cpt++;
    }
    return root;
}