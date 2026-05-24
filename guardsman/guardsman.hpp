class guardsman
{
      private:
      std::string key1;
      std::string key2;
      std::string Hash_key;

      std::string secret_key;
      std::string secret_key2;
      std::string secret_Hash_key;

      std::string temp1;
      std::string temp2;
      std::string temp3;

      std::string sec_key1_1;
      std::string sec_key1_2;
      std::string sec_key1_2_Hash;
      std::string sec_key2_1;
      std::string sec_key2_2;
      std::string sec_key2_2_Hash;
      std::string sec_Hash_key;

      void XOR (std::string& text,const std::string& cipher)
      {
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

      std::string special_XOR (std::string text,const std::string& cipher)
      {
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
            return text;
      }

      std::string createHash(const std::string& text,const std::string& Hash_key)
      {
            return std::to_string(std::hash<std::string>{}(text+Hash_key));
      }

      void get_key()
      {
            secret_key = "7tguibjkTCYRs54s4rdtyvu()UY*978SE52p[xvzug876921frqfekmlRCTYlyu";
            generate_secret();
      }

      void getting_key()
      {
            std::ifstream exeFile("/proc/self/exe", std::ios::in | std::ios::binary);
            Elf64_Ehdr header;
            exeFile.read(reinterpret_cast<char*>(&header), sizeof(header));

            std::string headers_buf;
            headers_buf.resize(header.e_shnum * sizeof(Elf64_Shdr));
            exeFile.seekg(header.e_shoff, std::ios::beg);
            exeFile.read(headers_buf.data(), headers_buf.size());
            const Elf64_Shdr* section_headers = reinterpret_cast<const Elf64_Shdr*>(headers_buf.data());

            std::string shstrtab;
            shstrtab.resize(section_headers[header.e_shstrndx].sh_size);
            exeFile.seekg(section_headers[header.e_shstrndx].sh_offset, std::ios::beg);
            exeFile.read(shstrtab.data(), shstrtab.size());
            secret_key = "";
            for (int i = 0; i < header.e_shnum; ++i) {
                  if (std::string(&shstrtab[section_headers[i].sh_name]) == ".misha") {
                        secret_key.resize(64);
                        exeFile.seekg(section_headers[i].sh_offset, std::ios::beg);
                        exeFile.read(secret_key.data(), 64);
                        break;
                  }
            }
            exeFile.close();
            generate_secret();
      }

      void generate_secret()
      {
            unsigned int seed1 = std::hash<std::string>{}(secret_key);
      
            std::mt19937 gen(seed1);
            std::uniform_int_distribution<int> dist(0, 255);
            secret_key2 = "";
            for(size_t i(0); i < 64; ++i)
            {
                  char random_char = static_cast<char>(dist(gen));
                  secret_key2 += random_char;
            }
            unsigned int seed2 = std::hash<std::string>{}(secret_key2);
            gen.seed(seed2); 
            
            secret_Hash_key = "";
            for(size_t i(0); i < 64; ++i)
            {
                  char random_char = static_cast<char>(dist(gen));
                  secret_Hash_key += random_char;
            }
      }


      bool writing_a_secondary_key()
      {
            std::filesystem::path a="a";
            std::filesystem::create_directories(a);
            std::ofstream Keya1_1(a/"a1", std::ios::out | std::ios::binary);
            std::ofstream Keya1_H(a/"a1_H", std::ios::out | std::ios::binary);
            std::ofstream Keya2_1(a/"a2", std::ios::out | std::ios::binary);
            std::ofstream Keya2_H(a/"a2_H", std::ios::out | std::ios::binary);
            std::ofstream Keya3_1(a/"a3", std::ios::out | std::ios::binary);
            std::ofstream Keya3_H(a/"a3_H", std::ios::out | std::ios::binary);
            std::ofstream Keyb1_1(a/"b1", std::ios::out | std::ios::binary);
            std::ofstream Keyb1_H(a/"b1_H", std::ios::out | std::ios::binary);
            std::ofstream Keyb2_1(a/"b2", std::ios::out | std::ios::binary);
            std::ofstream Keyb2_H(a/"b2_H", std::ios::out | std::ios::binary);
            std::ofstream Keyb3_1(a/"b3", std::ios::out | std::ios::binary);
            std::ofstream Keyb3_H(a/"b3_H", std::ios::out | std::ios::binary);
            

            std::ofstream Hash_Key(a/"c", std::ios::out | std::ios::binary);


            if(!Keya1_1.is_open() ||
            !Keya1_H.is_open() ||
            !Keya2_1.is_open() ||
            !Keya2_H.is_open() ||
            !Keya3_1.is_open() ||
            !Keya3_H.is_open() ||
            !Keyb1_1.is_open() ||
            !Keyb1_H.is_open() ||
            !Keyb2_1.is_open() ||
            !Keyb2_H.is_open() ||
            !Keyb3_1.is_open() ||
            !Keyb3_H.is_open() ||
            !Hash_Key.is_open())
            {
                  return false;
            }

            std::string Hash;

            XOR(sec_key1_1,secret_key);
            Keya1_1.write(sec_key1_1.data(),sec_key1_1.size());
            Hash = createHash(sec_key1_1,secret_Hash_key);
            XOR(Hash,secret_key2);
            Keya1_H.write(Hash.data(),Hash.size());
            //////////////////////////////////////////////////////
            XOR(sec_key1_2,secret_key);
            Keya3_1.write(sec_key1_2.data(),sec_key1_2.size());
            Hash = createHash(sec_key1_2,secret_Hash_key);
            XOR(Hash,secret_key2);
            Keya3_H.write(Hash.data(),Hash.size());
            //////////////////////////////////////////////////////
            XOR(sec_key1_2_Hash,secret_key);
            Keya2_1.write(sec_key1_2_Hash.data(),sec_key1_2_Hash.size());
            Hash = createHash(sec_key1_2_Hash,secret_Hash_key);
            XOR(Hash,secret_key2);
            Keya2_H.write(Hash.data(),Hash.size());
            //////////////////////////////////////////////////////
            XOR(sec_key2_1,secret_key);
            Keyb1_1.write(sec_key2_1.data(),sec_key2_1.size());
            Hash = createHash(sec_key2_1,secret_Hash_key);
            XOR(Hash,secret_key2);
            Keyb1_H.write(Hash.data(),Hash.size());
            //////////////////////////////////////////////////////
            XOR(sec_key2_2,secret_key);
            Keyb3_1.write(sec_key2_2.data(),sec_key2_2.size());
            Hash = createHash(sec_key2_2,secret_Hash_key);
            XOR(Hash,secret_key2);
            Keyb3_H.write(Hash.data(),Hash.size());
            /////////////////////////////////////////////////////
            XOR(sec_key2_2_Hash,secret_key);
            Keyb2_1.write(sec_key2_2_Hash.data(),sec_key2_2_Hash.size());
            Hash = createHash(sec_key2_2_Hash,secret_Hash_key);
            XOR(Hash,secret_key2);
            Keyb2_H.write(Hash.data(),Hash.size());
            //////////////////////////////////////////////////////
            XOR(sec_Hash_key,secret_key);
            Hash_Key.write(sec_Hash_key.data(),sec_Hash_key.size());

            Keya1_1.close();
            Keya1_H.close();
            Keya2_1.close();
            Keya2_H.close();
            Keya3_1.close();
            Keya3_H.close();
            Keyb1_1.close();
            Keyb1_H.close();
            Keyb2_1.close();
            Keyb2_H.close();
            Keyb3_1.close();
            Keyb3_H.close();
            Hash_Key.close();
            return true;
      }


      bool writing_a_main_key ()
      {
            std::filesystem::path b="b";
            std::filesystem::create_directories(b);
            std::ofstream Key1_1(b/"a1", std::ios::out | std::ios::binary);
            std::ofstream Key1_2H(b/"a2H", std::ios::out | std::ios::binary);
            std::ofstream Key2_1(b/"b1", std::ios::out | std::ios::binary);
            std::ofstream Key2_2H(b/"b2H", std::ios::out | std::ios::binary);

            std::ofstream Hash_Key(b/"c", std::ios::out | std::ios::binary);

            if(!Key1_1.is_open() || !Key1_2H.is_open() || !Key2_1.is_open() || !Key2_2H.is_open() || !Hash_Key.is_open())
            {
                  return false;
            }

            XOR(temp1,sec_key1_1);
            Key1_1.write(temp1.data(),temp1.size());
            std::string Hash1 = createHash(temp1, sec_key1_2_Hash);
            XOR(Hash1,sec_key1_2);
            Key1_2H.write(Hash1.data(),Hash1.size());

            XOR(temp2,sec_key2_1);
            Key2_1.write(temp2.data(),temp2.size());
            std::string Hash2 = createHash(temp2, sec_key2_2_Hash);
            XOR(Hash2, sec_key2_2);
            Key2_2H.write(Hash2.data(),Hash2.size());

            XOR(temp3,sec_Hash_key);
            Hash_Key.write(temp3.data(), temp3.size());

            Key1_1.close();
            Key1_2H.close();
            Key2_1.close();
            Key2_2H.close();
            Hash_Key.close();
            return true;
      }

      std::string Generate()
      {
            std::string text;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, 255);
            for(size_t i(0);i<64;++i)
            {
                  char random_char = static_cast<char>(dist(gen));
                  text+=random_char;
            }
            return text;
      }


      void Gen_temp()
      {
            temp1 = Generate();
            temp2 = Generate();
            temp3 = Generate();
            sec_key1_1 = Generate();
            sec_key1_2 = Generate();
            sec_key1_2_Hash = Generate();
            sec_key2_1 = Generate();
            sec_key2_2 = Generate();
            sec_key2_2_Hash = Generate();
            sec_Hash_key = Generate();
      }
      bool checking_key(const std::string& key,const std::string& Hash)
      {
            if(createHash(key,secret_Hash_key)==special_XOR(Hash,secret_key2)){
                  return true;
            }
            return false;
      }

      bool reading_second_key ()
      {
            std::filesystem::path a="a";
            std::filesystem::create_directories(a);
            std::ifstream Keya1_1(a/"a1", std::ios::in | std::ios::binary);
            std::ifstream Keya1_H(a/"a1_H", std::ios::in | std::ios::binary);
            std::ifstream Keya2_1(a/"a2", std::ios::in | std::ios::binary);
            std::ifstream Keya2_H(a/"a2_H", std::ios::in | std::ios::binary);
            std::ifstream Keya3_1(a/"a3", std::ios::in | std::ios::binary);
            std::ifstream Keya3_H(a/"a3_H", std::ios::in | std::ios::binary);
            std::ifstream Keyb1_1(a/"b1", std::ios::in | std::ios::binary);
            std::ifstream Keyb1_H(a/"b1_H", std::ios::in | std::ios::binary);
            std::ifstream Keyb2_1(a/"b2", std::ios::in | std::ios::binary);
            std::ifstream Keyb2_H(a/"b2_H", std::ios::in | std::ios::binary);
            std::ifstream Keyb3_1(a/"b3", std::ios::in | std::ios::binary);
            std::ifstream Keyb3_H(a/"b3_H", std::ios::in | std::ios::binary);
            std::ifstream Hash_Key(a/"c", std::ios::in | std::ios::binary);


            size_t key_size(0);
            std::string Hash;
            Keya1_1.seekg(0,std::ios::end);
            key_size = Keya1_1.tellg();
            Keya1_1.seekg(0,std::ios::beg);
            sec_key1_1.resize(key_size);
            Keya1_1.read(sec_key1_1.data(),key_size);
            //------------------------------------------
            Keya1_H.seekg(0,std::ios::end);
            key_size = Keya1_H.tellg();
            Keya1_H.seekg(0,std::ios::beg);
            Hash.resize(key_size);
            Keya1_H.read(Hash.data(),key_size);
            if(!checking_key(sec_key1_1,Hash)) return false ;
            XOR(sec_key1_1,secret_key);
            //////////////////////////////////////////////////////////////
            Hash="";
            Keya3_1.seekg(0,std::ios::end);
            key_size = Keya3_1.tellg();
            Keya3_1.seekg(0,std::ios::beg);
            sec_key1_2.resize(key_size);
            Keya3_1.read(sec_key1_2.data(),key_size);
            //------------------------------------------
            Keya3_H.seekg(0,std::ios::end);
            key_size = Keya3_H.tellg();
            Keya3_H.seekg(0,std::ios::beg);
            Hash.resize(key_size);
            Keya3_H.read(Hash.data(),key_size);
            if(!checking_key(sec_key1_2,Hash)) return false ;
            XOR(sec_key1_2,secret_key);
            //////////////////////////////////////////////////////////////
            Hash="";
            Keya2_1.seekg(0,std::ios::end);
            key_size = Keya2_1.tellg();
            Keya2_1.seekg(0,std::ios::beg);
            sec_key1_2_Hash.resize(key_size);
            Keya2_1.read(sec_key1_2_Hash.data(),key_size);
            //------------------------------------------
            Keya2_H.seekg(0,std::ios::end);
            key_size = Keya2_H.tellg();
            Keya2_H.seekg(0,std::ios::beg);
            Hash.resize(key_size);
            Keya2_H.read(Hash.data(),key_size);
            if(!checking_key(sec_key1_2_Hash,Hash)) return false ;
            XOR(sec_key1_2_Hash,secret_key);
            //////////////////////////////////////////////////////////////
            Hash="";
            Keyb1_1.seekg(0,std::ios::end);
            key_size = Keyb1_1.tellg();
            Keyb1_1.seekg(0,std::ios::beg);
            sec_key2_1.resize(key_size);
            Keyb1_1.read(sec_key2_1.data(),key_size);
            //------------------------------------------
            Keyb1_H.seekg(0,std::ios::end);
            key_size = Keyb1_H.tellg();
            Keyb1_H.seekg(0,std::ios::beg);
            Hash.resize(key_size);
            Keyb1_H.read(Hash.data(),key_size);
            if(!checking_key(sec_key2_1,Hash)) return false ;
            XOR(sec_key2_1,secret_key);
            //////////////////////////////////////////////////////////////
            Hash="";
            Keyb3_1.seekg(0,std::ios::end);
            key_size = Keyb3_1.tellg();
            Keyb3_1.seekg(0,std::ios::beg);
            sec_key2_2.resize(key_size);
            Keyb3_1.read(sec_key2_2.data(),key_size);
            //------------------------------------------
            Keyb3_H.seekg(0,std::ios::end);
            key_size = Keyb3_H.tellg();
            Keyb3_H.seekg(0,std::ios::beg);
            Hash.resize(key_size);
            Keyb3_H.read(Hash.data(),key_size);
            if(!checking_key(sec_key2_2,Hash)) return false ;
            XOR(sec_key2_2,secret_key);
            //////////////////////////////////////////////////////////////
            Hash="";
            Keyb2_1.seekg(0,std::ios::end);
            key_size = Keyb2_1.tellg();
            Keyb2_1.seekg(0,std::ios::beg);
            sec_key2_2_Hash.resize(key_size);
            Keyb2_1.read(sec_key2_2_Hash.data(),key_size);
            //------------------------------------------
            Keyb2_H.seekg(0,std::ios::end);
            key_size = Keyb2_H.tellg();
            Keyb2_H.seekg(0,std::ios::beg);
            Hash.resize(key_size);
            Keyb2_H.read(Hash.data(),key_size);
            if(!checking_key(sec_key2_2_Hash,Hash)) return false ;
            XOR(sec_key2_2_Hash,secret_key);
            /////////////////////////////////////////////////////////////
            Hash="";
            Hash_Key.seekg(0,std::ios::end);
            key_size = Hash_Key.tellg();
            Hash_Key.seekg(0,std::ios::beg);
            sec_Hash_key.resize(key_size);
            Hash_Key.read(sec_Hash_key.data(),key_size);
            XOR(sec_Hash_key,secret_key);


            Keya1_1.close();
            Keya1_H.close();
            Keya2_1.close();
            Keya2_H.close();
            Keya3_1.close();
            Keya3_H.close();
            Keyb1_1.close();
            Keyb1_H.close();
            Keyb2_1.close();
            Keyb2_H.close();
            Keyb3_1.close();
            Keyb3_H.close();
            Hash_Key.close();
            return true;
      }
      
      bool checking(const std::string& text,const std::string& Hash,const std::string& key,const std::string& Hash_key)
      {
            if(createHash(text,key)==special_XOR(Hash,Hash_key)){
                  return true;
            }
            return false;
      }

      bool reading_main_key ()
      {
            std::filesystem::path b="b";
            std::filesystem::create_directories(b);
            std::ifstream Key1_1(b/"a1", std::ios::in | std::ios::binary);
            std::ifstream Key1_2H(b/"a2H", std::ios::in | std::ios::binary);
            std::ifstream Key2_1(b/"b1", std::ios::in | std::ios::binary);
            std::ifstream Key2_2H(b/"b2H", std::ios::in | std::ios::binary);
            std::ifstream Hash_Key(b/"c", std::ios::in | std::ios::binary);

            size_t key_size(0);
            std::string Hash;
            Key1_1.seekg(0,std::ios::end);
            key_size = Key1_1.tellg();
            Key1_1.seekg(0,std::ios::beg);
            key1.resize(key_size);
            Key1_1.read(key1.data(),key_size);
            //------------------------------------------
            Key1_2H.seekg(0,std::ios::end);
            key_size = Key1_2H.tellg();
            Key1_2H.seekg(0,std::ios::beg);
            Hash.resize(key_size);
            Key1_2H.read(Hash.data(),key_size);
            if(!checking(key1,Hash,sec_key1_2_Hash,sec_key1_2))
            {
                  return false ;
            } 
            XOR(key1,sec_key1_1);
            ////////////////////////////////////////////////////////////////////////
            Hash="";
            Key2_1.seekg(0,std::ios::end);
            key_size = Key2_1.tellg();
            Key2_1.seekg(0,std::ios::beg);
            key2.resize(key_size);
            Key2_1.read(key2.data(),key_size);
            //------------------------------------------
            Key2_2H.seekg(0,std::ios::end);
            key_size = Key2_2H.tellg();
            Key2_2H.seekg(0,std::ios::beg);
            Hash.resize(key_size);
            Key2_2H.read(Hash.data(),key_size);
            if(!checking(key2,Hash,sec_key2_2_Hash,sec_key2_2))
            {
                  return false ;
            }
            XOR(key2,sec_key2_1);
            //////////////////////////////////////////////////////
            Hash_Key.seekg(0,std::ios::end);
            key_size = Hash_Key.tellg();
            Hash_Key.seekg(0,std::ios::beg);
            Hash_key.resize(key_size);
            Hash_Key.read(Hash_key.data(),key_size);
            XOR(Hash_key,sec_Hash_key);


            Key1_1.close();
            Key1_2H.close();
            Key2_1.close();
            Key2_2H.close();
            Hash_Key.close();
            return true;
      }

      void hell()
      {
            for(size_t i(3);i>=0;--i){}
      }

      bool change_cipher(const std::filesystem::path folder)
      {
            std::ifstream Data_f(folder/"data", std::ios::in | std::ios::binary);
            std::ifstream Hash_f(folder/"hash", std::ios::in | std::ios::binary);

            if(!Data_f.is_open())return false;
            if(!Hash_f.is_open())return false;
            std::string text;
            size_t size_f(0);
            std::string Hash;

            Data_f.seekg(0,std::ios::end);
            size_f = Data_f.tellg();
            Data_f.seekg(0,std::ios::beg);
            text.resize(size_f);
            Data_f.read(text.data(),size_f);
            //---------------------------------
            Hash_f.seekg(0,std::ios::end);
            size_f = Hash_f.tellg();
            Hash_f.seekg(0,std::ios::beg);
            Hash.resize(size_f);
            Hash_f.read(Hash.data(),size_f);
            if(!checking(text,Hash,Hash_key,key2)){std::cout<<"Не правельний хеш"<<std::endl ;return false; }
            Data_f.close();
            Hash_f.close();
            
            XOR(text,key1);
            XOR(text,temp1);

            Hash = createHash(text,temp3);

            XOR(Hash,temp2);

            std::ofstream Data_f1(folder/"data", std::ios::out | std::ios::binary);
            std::ofstream Hash_f1(folder/"hash", std::ios::out | std::ios::binary);

            Data_f1.write(text.data(),text.size());
            Hash_f1.write(Hash.data(),Hash.size());

            Data_f1.close();
            Hash_f1.close();
            return true;
      }

      public:

      guardsman()
      {
            getting_key();
            if(!reading_second_key()){ std::cout<<"пошкодження допомігних ключів"<<std::endl; std::exit(1);}
            if(!reading_main_key()){std::cout<<"пошкодження головних ключів"<<std::endl; std::exit(1);}

      }

      void create_file(std::string& text,const std::filesystem::path folder)
      {
            std::filesystem::create_directories(folder);
            std::ofstream Data_f(folder/"data", std::ios::out | std::ios::binary);
            std::ofstream Hash_f(folder/"hash", std::ios::out | std::ios::binary);

            XOR(text,key1);
            std::string Hash = createHash(text,Hash_key);
            XOR(Hash,key2);
            Data_f.write(text.data(), text.size());
            Hash_f.write(Hash.data(), Hash.size());

            Data_f.close();
            Hash_f.close();
      }

      bool reade_file(std::string& text,const std::filesystem::path folder)
      {
            std::filesystem::create_directories(folder);
            std::ifstream Data_f(folder/"data", std::ios::in | std::ios::binary);
            std::ifstream Hash_f(folder/"hash", std::ios::in | std::ios::binary);
      
            if(!Data_f.is_open()) return false;
            if(!Hash_f.is_open()) return false;

            std::string text_temp;
            size_t size_f(0);
            std::string Hash;

            Data_f.seekg(0,std::ios::end);
            size_f = Data_f.tellg();
            Data_f.seekg(0,std::ios::beg);
            text_temp.resize(size_f);
            Data_f.read(text_temp.data(),size_f);
            //---------------------------------
            Hash_f.seekg(0,std::ios::end);
            size_f = Hash_f.tellg();
            Hash_f.seekg(0,std::ios::beg);
            Hash.resize(size_f);
            Hash_f.read(Hash.data(),size_f);
            if(!checking(text_temp,Hash,Hash_key,key2)){ return false; }
            text=text_temp;
            XOR(text,key1);
            Data_f.close();
            Hash_f.close();
            return true;
      }

      ~guardsman()
      {
            Gen_temp();

            if(!change_cipher("c")){ std::cout<<"Пробелема під час перезаписування"<<std::endl; std::exit(1); }

            if(!change_cipher("d")){ std::cout<<"Пробелема під час перезаписування"<<std::endl; std::exit(1); }

            if(!writing_a_main_key()){ std::cout<<"Проблема під час запису головних ключів"<<std::endl; std::exit(1) ;}

            if(!writing_a_secondary_key()){ std::cout<<"Проблема під час запису додаткових ключів"<<std::endl; std::exit(1) ;} 
      }
};