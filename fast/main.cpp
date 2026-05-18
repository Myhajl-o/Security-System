#include <iostream>
#include <fstream>
#include <filesystem>
void XOR (std::string& text,const std::string& cipher)
{
      if((text.size()<4)||cipher.size()<10){ text="Is that a joke?"; return;}
      size_t j(0);
      for(size_t i(0);i<text.size();++i)
      {
            if((text[i]!='\n')&&((text[i]^cipher[j])!='\n'))
            {
                  text[i]=(text[i]^cipher[j]);
            }
            ++j;
            if(j==cipher.size())
            {
                  j=0;
            }
      }
}
std::string createHash(const std::string& text,const std::string& IOP)
{
      return std::to_string(std::hash<std::string>{}(text+IOP));
}
void WriteBinaryFile(std::string& text,const std::string& key1,const std::string& key2,const std::string& Hash_key) 
{
      std::filesystem::path data = "data";
      std::ofstream Data(data/"info.bin", std::ios::out | std::ios::binary);
      std::ofstream Hash(data/"Hash.bin", std::ios::out | std::ios::binary);

      XOR(text,key1);

      std::string H=createHash(text,Hash_key);

      XOR(H,key2);

      //
      Data.write(text.data(), text.size());
      Hash.write(H.data(), H.size());
      //
      Data.close();
      Hash.close();
}

bool ReadBinaryFile(std::string& text,const std::string& key1,const std::string& key2,const std::string& Hash_key) 
{
      std::filesystem::path data = "data";
      std::ifstream Data(data/"info.bin", std::ios::in | std::ios::binary);
      std::ifstream Hash(data/"Hash.bin", std::ios::in | std::ios::binary);
      //
      if(!Data.is_open()) return false;
      if(!Hash.is_open()) return false;
      //
      Data.seekg(0, std::ios::end);
      size_t DataSize = Data.tellg();
      Data.seekg(0, std::ios::beg);
      text.resize(DataSize);
      Data.read(text.data(), DataSize);
      //
      Hash.seekg(0, std::ios::end);
      size_t HashSize = Hash.tellg();
      Hash.seekg(0, std::ios::beg);
      std::string H;
      H.resize(HashSize);
      Hash.read(H.data(), HashSize);
      //
      Data.close();
      Hash.close();
      //
      XOR(H,key2);
      if(H==createHash(text,Hash_key))
      {
            XOR(text,key1);
            return true;
      }
      return false;
}
int main () 
{
      std::string key1 = "(RDiqh8r411cIu9YFU#hjsjoiagy412ZilkhXuIOH43vxzDerTuig85yTY23GUh142UFUTp6ze";
      std::string key2 = "7tguibjkTCYRs54s4rdtyvu()UY*978SE52p[xvzug876921frqfekmlRCTYlyuf";
      std::string Hash_key = "7623GYfeUBIerHh8ion";
      std::string text;

      if(ReadBinaryFile(text,key1,key2,Hash_key))
      {
            std::cout<<text<<std::endl;
      }
      return 0;
}