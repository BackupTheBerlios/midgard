// $Id: magusicons_p.h,v 1.1 2003/04/25 07:13:19 christof Exp $

#include "magusicons.h"
#include <map>
#include <vector>

namespace MagusIcons {
struct key_t
{  style s; std::string name;

   bool operator<(const key_t &b) const
   {  return int(s)<int(b.s) || (s==b.s && name<b.name); }
   bool operator==(const key_t &b) const
   {  return s==b.s && name==b.name; }
   key_t(style _s, const std::string &n) : s(_s), name(n) {}
   key_t(const std::string &n) : s(Any), name(n) {}
};

typedef std::map<key_t,Glib::RefPtr<Gdk::Pixbuf> > map_t;
extern map_t images;

struct data_registry
{  unsigned length;
   const void *address;
   style st;
   const char *name;
   const data_registry *next;
   
   static const data_registry *first;
   
	data_registry(const char *_name, const char * const *xpmdata) 
		: length(0), address(xpmdata), st(Any), name(_name), next(first)
	{ first=this; }
	data_registry(const char *_name, unsigned len, const unsigned char *data) 
		: length(len), address(data), st(Any), name(_name), next(first)
	{ first=this; }
	data_registry(style _st,const char *_name, const char * const *xpmdata) 
		: length(0), address(xpmdata), st(_st), name(_name), next(first)
	{ first=this; }
	
	bool is_xpm() const { return !length; }
	unsigned Length() const { return length; }
	const unsigned char *Data() const 
	{ return length ? (const unsigned char *)address : 0; }
	const char * const *XpmData() const 
	{ return !length ? (const char * const *)address : 0; }
};

}
