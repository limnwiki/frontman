#include <iostream>
#include <filesystem>
#include <unordered_map>
#include "parser.hpp"
#include "file.hpp"

std::string get_meta(const std::string& name, const std::string& file)
{
   String md = read_file(file);
   auto str = md.inside("---\n", "\n---\n");

   for (auto s : str.split('\n'))
   {
      auto pair = s.split(':');

      if (pair[0].str != name)
         continue;

      auto value = pair[1];

      if (value.has_inside("[", "]"))
         value = {value.inside("[", "]").remove(' ').split(','), "\n"};
      else 
         value = value.remove_padding();

      return value;
   }

   return "";
}

int main(int argc, char** argv)
{
   std::string file;

   for (int i = 1; i < argc; i++)
   {
      const std::string& arg = argv[i];

      if (arg == "-g")
      {
         if (file.empty())
         {
            std::cerr << "no input file provided to get command\n";
            exit(1);
         }

         i++;
         std::cout << get_meta(argv[i], file);
      }
      else if (arg == "-i")
      {
         i++;
         file = argv[i];
         
         if (file.empty() || !std::filesystem::exists(file))
         {
            std::cerr << "input file does not exist\n";
            exit(1);
         }
      }
      else if (arg == "-t")
      {
         i++;
         file = argv[i];
         const std::string& field = argv[i+1], tmpl_file = argv[i+2], tmpl_find = argv[i+3];
         i+=3;

         if (file.empty() || !std::filesystem::exists(file))
         {
            std::cerr << "input file does not exist\n";
            exit(1);
         }

         if (tmpl_file.empty() || !std::filesystem::exists(tmpl_file))
         {
            std::cerr << "template file does not exist\n";
            exit(1);
         }

         const std::string& value = get_meta(field, file);

         String str = read_file(tmpl_file);
         const auto& tmpl = str.replace(tmpl_find, value);

         if (argc >= 7)
         {
            i++;
            write_file(argv[i], tmpl.str);
         }
         else std::cout << tmpl;
      }
      else if (arg == "-r")
      {
         i++;
         const std::string& value = argv[i], tmpl_file = argv[i+1], tmpl_find = argv[i+2];
         i+=2;

         if (tmpl_file.empty() || !std::filesystem::exists(tmpl_file))
         {
            std::cerr << "template file does not exist\n";
            exit(1);
         }

         String str = read_file(tmpl_file);
         const auto& tmpl = str.replace(tmpl_find, value);

         if (argc >= 6)
         {
            i++;
            write_file(argv[i], tmpl.str);
         }
         else std::cout << tmpl;
      }
      else if (arg == "-v")
      {
         if (file.empty())
         {
            std::cerr << "no input file provided to view command\n";
            exit(1);
         }

         std::cout << String(read_file(file)).outside("---\n", "\n---\n");
      }
      else
      {
         std::cerr << "unknown command '"+arg+"'\n";
         exit(1);
      }
   }
}