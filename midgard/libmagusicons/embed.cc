// $Id: embed.cc,v 1.8 2004/06/08 10:36:36 christof Exp $

#define MAKE_PNG

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <map>
#include <sys/stat.h>

static std::string path="../pixmaps/";

#ifndef MAKE_PNG
// parts taken from
/* xpmtoppm.c - read an X11 pixmap file and produce a portable pixmap
**
** Copyright (C) 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
*/

#define MAX_LINE 2048
  /* The maximum size XPM input line we can handle. */
  
static std::string
readXpm3Header(FILE * const stream)
{   char line[MAX_LINE],w[MAX_LINE];
    
    /* Read the assignment line */
    fgets(line, sizeof(line), stream);
    
    *w=0;
    sscanf(line,"static char%*[ *]%[_A-Za-z0-9]",w);
    return w;
}

static std::string ReadXPMFile(FILE * const stream)
{  char line[MAX_LINE], str1[MAX_LINE];
   int rc;

    /* Read the header line */
    fgets(line, sizeof(line), stream);
    
    rc = sscanf(line, "/* %s */", str1);
    if (rc == 1 && strncmp(str1, "XPM", 3) == 0) {
        /* It's an XPM version 3 file */
        return readXpm3Header(stream);
    }
    // we don't care about Version 1 files, the parsing is too
    // complicated and we should reasonably never encounter one
    return "";
}

static std::string xpmname2(const std::string &file_with_path)
{  FILE *f;
   if (!(f=fopen(file_with_path.c_str(),"r"))) return "";
   std::string res=ReadXPMFile(f);
   fclose(f);
   return res;
}
#endif

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

static void embed_one_file(const std::string &file, const std::string &name, const std::string &domain="")
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
#ifndef MAKE_PNG
      std::string xpmname=xpmname2(filename);
      if (xpmname.empty())
      { std::cerr << "error parsing xpm image " << file << '\n'; return; }
      std::cout << "#include \"" << filename << "\"\n";
      std::cout << "static MagusIcons::data_registry " << CName(domain+name) << "_reg(";
      if (!domain.empty()) std::cout << "MagusIcons::" << domain << ", ";
      std::cout << '"' << name << "\", " << xpmname << ");\n";
      already_there[file]=payload(xpmname);
#else
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
      is.clear();
      is.open("tmp.png",std::ios_base::in);
      unsigned sz=embed_binary(name,is,domain);
      already_there[file]=payload(CName(domain+name)+"_data",sz);
#endif      
   }
   else // if (!memcmp(buf,"‰PNG",4) || !memcmp(buf,"ÿØ",2))
   {  is.seekg(0, std::ios_base::beg);
      unsigned sz=embed_binary(name,is,domain);
      already_there[file]=payload(CName(domain+name)+"_data",sz);
   }
}

static void read_file(const std::string &file, const std::string &domain="")
{  char buf[10240];
   std::ifstream is(file.c_str());
   if (!is.good()) { std::cerr << "error opening " << file << '\n'; return; }
   while (is.getline(buf,sizeof buf).good())
   {  char *tab_pos=strchr(buf,'\t');
      if (tab_pos) { *tab_pos=0; ++tab_pos; }
      embed_one_file(buf,tab_pos?tab_pos:buf,domain);
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
