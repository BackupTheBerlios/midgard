// $Id: magusicons.h,v 1.3 2003/04/23 14:01:03 christof Exp $

#include <gdkmm/pixbuf.h>
#include <Misc/safemap.h>

namespace MagusIcons {
enum style { Alessandro, Ulf, Gtk, Any };

struct key_t
{  style s; std::string name;

   bool operator<(const key_t &b) const
   {  return int(s)<int(b.s) || (s==b.s && name<b.name); }
   bool operator==(const key_t &b) const
   {  return s==b.s && name==b.name; }
   key_t(style _s, const std::string &n) : s(_s), name(n) {}
   key_t(const std::string &n) : s(Any), name(n) {}
};

extern safemap<key_t,Glib::RefPtr<Gdk::Pixbuf> > images;

extern void set_icon_style(style);
}

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

