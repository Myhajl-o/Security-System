#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <random>
#include <elf.h>
#include "guardsman.hpp"

const char hey[] = "Hi,_this_is_my_cryptographic_file_protection_system;_it’s_not_particularly optimised,_but_it_works";

int main ()
{
      guardsman g;
      std::string text;
      if(!g.reade_file(text,"c")) return 1;
      std::cout<<text<<std::endl;

      std::string stattya;

      if(!g.reade_file(stattya,"d")) return 1;

      std::cout<<stattya<<std::endl;


      return 0;
}

