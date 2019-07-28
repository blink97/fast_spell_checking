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
    std::string freq = 0;
    Node *root = new Node();
    while (file >> word)
    {
        file >> freq;
        std::cout << cpt << std::endl;
        char* w = (char *)malloc((word.length() + 1) * sizeof(char));
        strcpy(w, word.c_str());
        insert(root, w, std::stoi(freq));
        cpt++;
    }
    return root;
}