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
void text_to_BinaryCode(std::string& text)
{
      std::string binary_code;
      for(char& c : text)
      {
            for(int i(7);i>=0;--i)
            {
                  binary_code+=std::to_string((c>>i)&1);
            }
      }
      text=binary_code;
}
void BinaryCode_to_text(std::string& binary_code) 
{
      std::string text;
      for(size_t i(0);i<binary_code.size();i+=8) 
      {
            char c(0);
            for(int j(0);j<8;++j) 
            {
                  c=c<<1;
                  if(binary_code[i+j]=='1') c=c|1;
            }
            text+=c;
      }
      binary_code=text;
}
void Entry(std::string& text,const std::string& key1,const std::string& key2,const std::string& Hash_key)
{
      std::filesystem::path data = "data";
      std::ofstream Data(data/"info.txt");
      std::ofstream Hash(data/"Hash.txt");
      //
      XOR(text,key1);
      std::string H=createHash(text,Hash_key);
      text_to_BinaryCode(text);
      Data<<text;
      //
      XOR(H,key2);
      text_to_BinaryCode(H);
      Hash<<H;
      //
      Data.close();
      Hash.close();
}
bool Cheking(std::string& text,const std::string key1,const std::string key2,const std::string Hash_key)
{
      std::filesystem::path data = "data";
      std::ifstream Hash(data/"Hash.txt");
      if(!Hash.is_open()) return false;
      //
      std::string H;
      Hash>>H;
      BinaryCode_to_text(H);
      XOR(H,key2);
      //
      Hash.close();
      //
      if(H==createHash(text,Hash_key)) XOR(text,key1); return true;
      //
      return false;
}
bool Reading(std::string& text,const std::string& key1,const std::string& key2,const std::string& Hash_key)
{
      std::filesystem::path data = "data";
      std::ifstream Data(data/"info.txt");
      if(!Data.is_open()) return false;
      //
      std::string temp;
      while(std::getline(Data, temp)) text+=temp;
      BinaryCode_to_text(text);
      //
      Data.close();
      //
      return Cheking(text,key1,key2,Hash_key);
}
int main ()
{
      std::string key1 = "(RDiqh8r411cIu9YFU#hjsjoiagy412ZilkhXuIOH43vxzDerTuig85yTY23GUh142UFUTp6ze";
      std::string key2 = "7tguibjkTCYRs54s4rdtyvu()UY*978SE52p[xvzug876921frqfekmlRCTYlyuf";
      std::string Hash_key = "7623GYfeUBIerHh8ion";
      std::string text;
      //
      if(Reading(text,key1,key2,Hash_key))
      {
            std::cout<<text<<std::endl;
      }
      return 0;
}