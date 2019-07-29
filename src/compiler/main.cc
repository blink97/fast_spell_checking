// read words
// create patricia trie
// compile trie in binary

#include "trie.hh"
#include "reader.hh"

#include <fstream>


int main(int argc, char *argv[]) {
  if (argc == 2){
    Node *root = read(argv[1]);

    std::ofstream f("dict.bin", std::ios::binary);

    if (f.is_open())
      writeNodeToFile(f, *root);
    f.close();

    delete root;

    return 0;
  }

  Node *root = new Node();

  /*char* test = (char *)malloc(5 * sizeof(char));
  strcpy(test, "test");
  char* slow = (char *)malloc(5 * sizeof(char));
  strcpy(slow, "slow");
  char* water = (char *)malloc(6 * sizeof(char));
  strcpy(water, "water");
  char* slower = (char *)malloc(7 * sizeof(char));
  strcpy(slower, "slower");
  char* team = (char *)malloc(5 * sizeof(char));
  strcpy(team, "team");
  char* toast= (char *)malloc(6 * sizeof(char));
  strcpy(toast, "toast");*/


  insert(root, "test", 2);
  insert(root, "slow", 4);
  insert(root, "water", 5);
  insert(root, "slower", 4);
  insert(root, "team", 3);
  insert(root, "toast", 1);

  //std::cout << *root << std::endl;

  std::ofstream f("dict.bin", std::ios::binary);

  if (f.is_open())
    writeNodeToFile(f, *root);
  f.close();

  delete root;

  return 0;
}
