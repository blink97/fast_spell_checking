#include <unistd.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc != 2){
    return 1;
  }

  FILE* fp = stdin;

  if(isatty(fileno(fp)))
  {
    while (1) {
      std::string test;
      std::cin >> test;
      std::cout << test << std::endl;
    }
  }

  std::string content;
  std::cin >> content;
  if (content != "approx")
    return 0;
  std::cin >> content;
  int number;
  std::istringstream iss(content);
  iss >> number;
  if (iss.fail())
    return 0;
  std::cin >> content;
  //TODO distance 

}
