
#include "class_sound.h"

void soundmap::Set(const vector<std::string>& vst)
{
 for(vector<std::string>::const_iterator i=vst.begin();i!=vst.end();++i)
  {
   std::string sb(*i,0,1); // erster Buchstabe
   std::string::size_type st_ = (*i).find("_");
   std::string si(*i,1,st_-1);
   int ii=atoi(si.c_str());
   std::string sbk = Kategorie(sb);
   st_index index(sbk,ii);
   std::string::size_type stp = (*i).rfind(".mp3");
   std::string sn(*i,st_+1,stp-st_-1);
   while(sn.find("_") != std::string::npos) // '_' durch ' ' in Namen ersetzen
      sn.replace(sn.find("_"),1," "); 
   st_menge menge(*i,sn);
   map_sound[index]=menge;
  }
}

std::string soundmap::Kategorie(std::string s)
{
 if (s=="a") return "Animal";
 if (s=="c") return "Crowd";
 if (s=="d") return "Doors";
 if (s=="e") return "Effects";
 if (s=="f") return "Famous Songs";
 if (s=="h") return "Horror";
 if (s=="m") return "Music";
 if (s=="n") return "Nature";
 if (s=="r") return "Rain";
 if (s=="s") return "Songs (Mid-Age)";
 if (s=="t") return "Thunder";
 if (s=="v") return "Voices";
 if (s=="w") return "Wind";
 return "?";
}
