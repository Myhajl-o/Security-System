#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <random>
#include <elf.h>
#include " guardsman.hpp"

int main ()
{
      guardsman g;
      std::string hey = "Wello world";
      g.create_file(hey,"c");
      std::cout<<g.reade_file("c")<<std::endl;
      return 0;
}

