#ifndef _CLASS_SOUND_HH
#  define _CLASS_SOUND_HH
#include<map>
#include<string>
#include<vector>

class soundmap
{
    struct st_index{std::string buchstabe; int zahl;
         bool operator == (const st_index& b) const 
               {return (buchstabe==b.buchstabe && zahl==b.zahl );}
         bool operator <  (const st_index& b) const 
               {return buchstabe < b.buchstabe || 
                        (buchstabe==b.buchstabe && zahl < b.zahl );}
         st_index(std::string s, int i):buchstabe(s),zahl(i){}
         st_index(){}
            };

    struct st_menge{std::string filename; std::string name;
         st_menge():filename(""),name("") {}
         st_menge(std::string f, std::string n):filename(f),name(n){}
            };
    map<st_index,st_menge> map_sound;
 public:
//      soundmap(const vector<std::string>& vsf);
    soundmap() {};
    void Set(const vector<std::string>& vsf);
    static std::string Kategorie(std::string s);

      int Zahl(map<st_index,st_menge>::const_iterator i) const {return i->first.zahl ;}
      std::string Kategorie(map<st_index,st_menge>::const_iterator i) const {return i->first.buchstabe;}
//      std::string Buchstabe(map<st_index,st_menge>::const_iterator i) const {return i->first.buchstabe;}
      std::string Titel(map<st_index,st_menge>::const_iterator i) const {return i->second.name;}
      std::string Filename(map<st_index,st_menge>::const_iterator i) const {return i->second.filename;}
        
      int size() const {return map_sound.size();}
      
      typedef map<st_index,st_menge>::const_iterator const_iterator;
      typedef map<st_index,st_menge>::iterator iterator;
        
      const_iterator begin() const {return map_sound.begin();}
      const_iterator end() const {return map_sound.end();}
      iterator begin() {return map_sound.begin();}
      iterator end()  {return map_sound.end();}
      
};

#endif

