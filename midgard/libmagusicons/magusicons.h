// $Id: magusicons.h,v 1.4 2003/04/25 07:12:08 christof Exp $

#include <gdkmm/pixbuf.h>

namespace MagusIcons {
enum style { Alessandro, Ulf, Gtk, Any };
extern void set_icon_style(style);
}

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);
