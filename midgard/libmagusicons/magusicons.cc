// $Id: magusicons.cc,v 1.2 2003/04/25 07:12:08 christof Exp $

#include <magusicons_p.h>
#include <gdkmm/pixbufloader.h>

static MagusIcons::style current_style=MagusIcons::Alessandro;
MagusIcons::map_t MagusIcons::images;

Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name)
{  using namespace MagusIcons;
   using MagusIcons::key_t;
   if (images.empty())
   {  for (const data_registry *iter=data_registry::first; iter; iter=iter->next)
      {  if (iter->is_xpm())
            images[key_t(iter->st,iter->name)]=
 		Gdk::Pixbuf::create_from_xpm_data(iter->XpmData());
 	 else
 	 {  Glib::RefPtr<Gdk::PixbufLoader> loader=Gdk::PixbufLoader::create();
 	    loader->write(iter->Data(), iter->Length());
 	    loader->close();
 	    images[key_t(iter->st,iter->name)]=loader->get_pixbuf();
         }
      }
   }
   map_t::const_iterator res=images.find(key_t(current_style,name));
   if (res!=images.end()) return res->second;
   return images[key_t(Any,name)];
}

void MagusIcons::set_icon_style(style st)
{  current_style=st;
}

const MagusIcons::data_registry *MagusIcons::data_registry::first;
