#include "reader.hh"

Node *read(std::string path)
{
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) 
        return NULL;

    std::string word;
    int i = 0;
    int cpt = 1;
    Node *root = new Node();
    while (file >> word)
    {
        if (i == 0)
        {
            std::cout << cpt << std::endl;
            char* w = (char *)malloc((word.length() + 1) * sizeof(char));
            strcpy(w, word.c_str());
            insert(root, w);
            i++;
        }
        else
            i = 0;
        cpt++;
    }
    return root;
}