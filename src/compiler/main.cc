// read words
// create patricia trie
// compile trie in binary

#include "trie.hh"


int main(int argc, char *argv[]) {
  Node *root = new Node();
  insert(root, "test");
  insert(root, "slow");
  insert(root, "water");
  insert(root, "slower");
  insert(root, "team");
  std::cout << *root << std::endl;

  delete root;

  return 0;
}
