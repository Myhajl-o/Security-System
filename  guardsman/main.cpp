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
      std::string text;
      if(!g.reade_file(text,"c")) return 1;
      std::cout<<text<<std::endl;
      return 0;
}

