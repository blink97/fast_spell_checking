// read words
// create patricia trie
// compile trie in binary

#include "trie.hh"
#include "reader.hh"

#include <fstream>


int main(int argc, char *argv[]) {
  if (argc == 3){
    std::string path = argv[2];
    Node *root = read(argv[1]);

    std::ofstream f(path, std::ios::binary);

    if (f.is_open())
      writeNodeToFile(f, *root, '\0');
    f.close();

    delete root;

    return 0;
  }

  std::cerr << "Usage: ./TextMiningCompiler /path/to/words.txt /path/to/dict.bin" << std::endl;

  return 1;
}
