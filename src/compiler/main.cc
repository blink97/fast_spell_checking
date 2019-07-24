// read words
// create patricia trie
// compile trie in binary

#include "trie.hh"
#include "reader.hh"


int main(int argc, char *argv[]) {
  if (argc == 2){
    Node *root = read(argv[1]);

    delete root;

    return 0;
  }

  Node *root = new Node();
  insert(root, "test");
  insert(root, "slow");
  insert(root, "water");
  insert(root, "slower");
  insert(root, "team");
  insert(root, "toast");
  std::cout << *root << std::endl;

  delete root;

  return 0;
}
