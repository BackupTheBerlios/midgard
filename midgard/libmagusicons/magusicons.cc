// $Id: magusicons.cc,v 1.1 2003/04/23 14:01:03 christof Exp $

#include <magusicons.h>

Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name)
{  return Glib::RefPtr<Gdk::Pixbuf>();
}

void MagusIcons::set_icon_style(style)
{
}

safemap<MagusIcons::key_t,Glib::RefPtr<Gdk::Pixbuf> > MagusIcons::images;
