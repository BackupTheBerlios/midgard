#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdio.h>
#include "translate.hh"

void usage(const std::string &s)
{
  std::cerr << s <<" hast to be called with LaTeX file to be translated\n";
  exit(1);
}


void get_replacelist(std::map<std::string,std::string> &RM)
{
    const std::string table=PACKAGE_DATA_DIR+"magus_translate_table.uk";
    std::ifstream fi(table.c_str());
    if(!fi) {std::cerr << "Table "<<table<<" not found\n"; exit(EXIT_FAILURE);}

    while(true)
     {
       std::string zeile;
       std::getline(fi,zeile);
       if(!fi.good()) break;  
       std::string::size_type c=zeile.find("=");
       if (c==std::string::npos) continue;  // line without '='
       std::string was(zeile,0,c); 
       if(was.find("#")!=std::string::npos) continue; // line with '#'
       if(was.find("!")!=std::string::npos) continue; // line with '#'
       std::string womit(zeile,c+1,std::string::npos);
       // remove leading and ending blankes
       while(was[0]==' ')              was.replace(0, 1, ""); 
       while(was[was.size()-1]==' ')   was.replace(was.size()-1, 1, "");
       while(womit[0]==' ')            womit.replace(0, 1, ""); 
       while(womit[was.size()-1]==' ') womit.replace(womit.size()-1, 1, "");
//       while(was.find(" ")!=std::string::npos) was.replace(was.find(" "), 1, "");
//       while(womit.find(" ")!=std::string::npos) womit.replace(womit.find(" "), 1, ""); 
       RM[was] = womit ;
     }
//std::cerr << "SSSS "<<RM.size()<<'\n';

}

void do_translation(const std::string &file,
                    std::map<std::string,std::string> &RM,
                     std::stringstream &outstream)
{
    std::ifstream fi(file.c_str());
    if(!fi) {std::cerr << "File "<<file<<" not found\n"; exit(EXIT_FAILURE);}

    int counter=0;
    while(true)
     {
       std::string zeile;
       std::getline(fi,zeile);
       if(!fi.good()) break;  
       
//std::cerr << RM.size()<<'\n';
       for(std::map<std::string,std::string>::const_iterator i=RM.begin();i!=RM.end();++i)
         {
//std::cerr << i->first <<'\t'<<zeile.find(i->first)<<'\n';
           if( zeile.find(i->first) != std::string::npos )
             if(zeile[zeile.find(i->first)-1] != '\\' ) 
               {
                 zeile.replace( zeile.find(i->first), i->first.size() , i->second );
                 ++counter;
               }
         }
//       std::cout << zeile<<'\n';
         outstream << zeile <<'\n';
     }
    std::cout << "\nReplaced "<<counter<<" occurences in "<<file<<"\n\n"; 
}


void replace_old_file(const std::stringstream &outstream,const std::string &infile)
{
   const std::string tempfile="tmp.tex";
   std::ofstream of(tempfile.c_str());
   of << outstream.str();
   rename(tempfile.c_str(),infile.c_str());
}


int main(int argc, char *argv[])
{
    if(argc != 2) usage(argv[0]) ;

    std::map<std::string,std::string> RM;    
    get_replacelist(RM);
    std::stringstream outstream;
    do_translation(argv[1],RM,outstream);
    replace_old_file(outstream,argv[1]);
    return 0;
}

