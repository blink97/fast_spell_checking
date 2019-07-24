#include "reader.hh"

Node *read(std::string path)
{
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) 
        return NULL;

    std::string word;
    int i = 0;
    Node *root = new Node();
    while (file >> word)
    {
        if (i == 0)
        {
            insert(root, word);
            i++;
        }
        else
            i = 0;
    }
    return root;
}