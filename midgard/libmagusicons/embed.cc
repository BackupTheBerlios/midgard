// $Id: embed.cc,v 1.10 2005/10/04 09:38:29 christof Exp $

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <map>
#include <sys/stat.h>
#include <Misc/itos.h>

static std::string path="../pixmaps/";

const std::string CName(const std::string &tag) throw()
{  std::string ret("");
   std::string::const_iterator i=tag.begin();
   // first char [_a-zA-Z]
   if (i!=tag.end()) 
   {  if (!(*i=='_' || isalpha((unsigned char)*i))) ret+='_';
      else ret+=*i;
      ++i;
   }
   // now [_a-zA-Z0-9]
   for (;i!=tag.end();++i) 
   {  if (!(*i=='_' || isalnum((unsigned char)*i))) ret+='_';
      else ret+=*i;
   }
   return ret;
}

static unsigned embed_binary(const std::string &file, std::istream &is, const std::string &domain="")
{  std::cout << "static const unsigned char " << CName(domain+file) << "_data[]"
   	<< " = \n{";
   	
   size_t filesize=0;
   {  while (is.good())
      {  /* unsigned ... hmmm g++3.1 does not like this ... */ char buf[16];
         is.read(buf,sizeof buf);
         size_t read=is.gcount();
         std::cout << '\t';
         for (size_t x=0;x<read;++x) std::cout << (unsigned int)(unsigned char)buf[x] << ',';
         std::cout << '\n';
         filesize+=read;
      }
   }
   std::cout << "};\n";
   std::cout << "static MagusIcons::data_registry " << CName(domain+file) << "_reg(";
   if (!domain.empty()) std::cout << "MagusIcons::" << domain << ", ";
   std::cout << '"' << file << "\", " << filesize << ", " << CName(domain+file) 
   	<< "_data);\n";
   return filesize;
}

struct payload
{  std::string name;
   unsigned size;
   
   payload() : size() {}
   payload(const std::string &n, unsigned s=0) : name(n), size(s) {}
};

static std::map<std::string,payload> already_there;

static void embed_one_file(const std::string &file, const std::string &name, const std::string &domain="", int size=0)
{  // file schon drin? dann muss nur noch unter anderem Namen registriert werden
   std::map<std::string,payload>::const_iterator it=already_there.find(file);
   if (it!=already_there.end())
   {  std::cout << "static MagusIcons::data_registry " << CName(domain+name) << "_reg(";
      if (!domain.empty()) std::cout << "MagusIcons::" << domain << ", ";
      std::cout << '"' << name << "\", ";
      if (it->second.size) std::cout << it->second.size << ", ";
      std::cout << it->second.name;
      std::cout << ");\n";
      return;
   }
   
   std::cout << "\n// ------------ " << file << " ----------------\n";
   std::string filename=path+file;
   std::ifstream is(filename.c_str());
   if (!is.good() && !domain.empty())
   {  filename=path+domain+"/"+file;
      is.clear();
      is.open(filename.c_str(),std::ios_base::in);
   }
   if (!is.good())
   { std::cerr << "error opening image " << file << '\n'; return; }
   char buf[8];
   memset(buf,0,sizeof buf);
   is.read(buf,sizeof buf); // why not get?
   if (!memcmp(buf,"/* XPM *",8))
   {  // xpm image ...
      is.close();
      system(("xpmtoppm --alphaout tmp_alpha.pbm \""+filename+"\" >tmp.ppm").c_str());
      system("pnmtopng -alpha tmp_alpha.pbm -compression 9 tmp.ppm >tmp.png");
      struct stat st;
      if (stat("tmp.png",&st) || !st.st_size)
      {  std::cerr << "png (netpbm) conversion failed for " << filename << '\n';
         system(("convert \""+filename+"\" tmp.png").c_str());
         if (stat("tmp.png",&st) || !st.st_size)
         {  std::cerr << "png (imagemagick) conversion failed for " << filename << '\n';
            return;
         }
      }
      if (size)
      { std::cerr << "scaling to " << size << "\n";
        system(("convert -scale x"+itos(size)+" tmp.png tmp2.png").c_str());
        if (!stat("tmp2.png",&st) && st.st_size)
        { if (rename("tmp2.png","tmp.png")) 
            std::cerr << "rename after resize failed\n";
        }
      }
      system("pngcrush -q tmp.png tmp2.png >/dev/null");
      if (!stat("tmp2.png",&st) && st.st_size)
      { if (rename("tmp2.png","tmp.png")) 
          std::cerr << "rename after pngcrush failed\n";
      }
      is.clear();
      is.open("tmp.png",std::ios_base::in);
      unsigned sz=embed_binary(name,is,domain);
      already_there[file]=payload(CName(domain+name)+"_data",sz);
   }
   else // if (!memcmp(buf,"‰PNG",4) || !memcmp(buf,"ÿØ",2))
   {  is.seekg(0, std::ios_base::beg);
      if (size)
      { is.close();
        std::cerr << "scaling to " << size << "\n";
        system(("convert -scale x"+itos(size)+" \""+filename+"\" tmp.png").c_str());
        system("pngcrush -q tmp.png tmp2.png >/dev/null");
        struct stat st;
        if (!stat("tmp2.png",&st) && st.st_size)
        { if (rename("tmp2.png","tmp.png")) 
            std::cerr << "rename after pngcrush failed\n";
        }
        is.clear();
        is.open("tmp.png",std::ios_base::in);
      }
      unsigned sz=embed_binary(name,is,domain);
      already_there[file]=payload(CName(domain+name)+"_data",sz);
   }
}

static void read_file(const std::string &file, const std::string &domain="")
{  char buf[10240];
   std::ifstream is(file.c_str());
   if (!is.good()) { std::cerr << "error opening " << file << '\n'; return; }
   while (is.getline(buf,sizeof buf).good())
   {  int size=0;
      char *tab_pos=strchr(buf,'\t'), *size_pos=0;
      if (tab_pos) 
      { *tab_pos=0; 
        ++tab_pos;
        size_pos=strchr(tab_pos,'\t');
        if (size_pos)
        { *size_pos=0;
          ++size_pos;
          size=atoi(size_pos);
        }
      }
      embed_one_file(buf,tab_pos?tab_pos:buf,domain,size);
   }
}

int main(int argc, char **argv)
{  std::cout << "// embedded images, generated by embed\n"
	"\n"
	"#include \"magusicons_p.h\"\n"
	"\n"
	// initialize it first so that Win32 does work
	"const MagusIcons::data_registry *MagusIcons::data_registry::first;\n";

   // datei iconlist einlesen, für jede Zeile embed_one_file
   read_file("iconlist"); // ,"Alessandro");
   // datei iconlist.ulf einlesen, für jede Zeile embed_one_file
   read_file("iconlist.ulf","Ulf");
}
