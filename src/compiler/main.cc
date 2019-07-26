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

  char* test = (char *)malloc(5 * sizeof(char));
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
  strcpy(toast, "toast");



  std::cout << test << std::endl;
  insert(root, test);
  std::cout << slow << std::endl;
  insert(root, slow);
  std::cout << water << std::endl;
  insert(root, water);
  std::cout << slower << std::endl;
  insert(root, slower);
  std::cout << team << std::endl;
  insert(root, team);
  std::cout << toast << std::endl;
  insert(root, toast);

  //std::cout << *root << std::endl;

  std::cout << "delete" << std::endl;
  delete root;

  return 0;
}
