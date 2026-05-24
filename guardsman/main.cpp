#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <random>
#include <elf.h>
#include "guardsman.hpp"

__attribute__((section(".m"))) const char hey[] = "Hi,_this_is_my_cryptographic_file_protection_system;_it’s_not_particularly optimised,_but_it_works";

int main ()
{

      std::cout<<hey<<std::endl<<std::endl;
      guardsman g;
      std::string text;
      if(!g.reade_file(text,"c")) return 1;
      std::cout<<text<<std::endl;


      std::string article;

      g.reade_file(article, "d");

      std::cout<<article<<std::endl;

      return 0;
}

