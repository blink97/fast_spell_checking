// read words
// create patricia trie
// compile trie in binary

#include "trie.hh"


int main(int argc, char *argv[]) {
  Node *root = new Node();
  insert(root, "tester");
  insert(root, "teaser");
  std::cout << *root << std::endl;

  delete root;

  return 0;
}
