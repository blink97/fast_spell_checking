// read words
// create patricia trie
// compile trie in binary

#include "trie.hh"
#include "reader.hh"

#include <fstream>


int main(int argc, char *argv[]) {
  if (argc == 2){
    Node *root = read(argv[1]);

    // std::ofstream f("dict.bin", std::ios::binary);

    // if (f.is_open())
    //   writeNodeToFile(f, *root);
    // f.close();

    delete root;

    return 0;
  }

  Node *root = new Node();

  insert(root, "test", 1);
  insert(root, "slow", 2);
  insert(root, "water", 3);
  insert(root, "slower", 4);
  insert(root, "team", 5);
  insert(root, "toast", 6);

  //std::cout << *root << std::endl;

  std::ofstream f("dict.bin", std::ios::binary);

  if (f.is_open())
    writeNodeToFile(f, *root);
  f.close();

  delete root;

  return 0;
}
