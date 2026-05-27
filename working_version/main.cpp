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
      std::string password;
      std::string temp;
      if(!g.reade_file(password,"c")) std::exit(1);
      std::cout<<"Enter the password:  ";
      std::getline(std::cin,temp);
      if(password==temp)
      {
            std::cout<<"\nCorrect password"<<std::endl;
      }
      else
      {
            std::cout<<"\nIncorrect passord"<<std::endl;
      }

/*
      std::string iop = "";
      g.create_file(iop,"e");

      g.reade_file(iop, "e");
*/
      return 0;
}

