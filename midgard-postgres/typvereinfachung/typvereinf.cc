#include <Misc/FetchIStream.h>
#include <vector>

class Gruppe
{  std::vector<std::string> typen;
   std::string name;
public:
   Gruppe(const std::string &n);
   bool member(const std::string &b) const
   {  return std::find(
};

Gruppe::Gruppe(const std::string &n)
 : name(n)
{  typen=Query("select typ from typen_gruppe where gruppe='"+n+"' order by typ")
	.FetchArray<std::string>();
}

class Gruppen
{  std::vector<Gruppe> gruppen;
public:
   Gruppen();
};

Gruppen::Gruppen()
 : name(n)
{  typen=Query("select typ from typen_gruppe where gruppe='"+n+"' order by typ")
	.FetchArray<std::string>();
}
