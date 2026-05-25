#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <random>
#ifdef _WIN32
      #include <windows.h>
#elif __linux__
      #include <elf.h>
      #include <unistd.h>
#endif
#include "guardsman.hpp"

int main ()
{
      guardsman g;
      std::string text;
      if(!g.reade_file(text,"c")) return 1;
      std::cout<<text<<std::endl;
      std::string article;
      g.reade_file(article, "d");
      std::cout<<article<<std::endl;
      return 0;
}

