// $Id: magusicons.cc,v 1.4 2003/05/06 07:46:41 christof Exp $

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
      {  Glib::RefPtr<Gdk::Pixbuf> pb;
         pb=images[key_t(Any,"Gross_ark_pre.xpm")];
         pb=pb->copy();
         pb->saturate_and_pixelate(pb,2.0,false);
         images[key_t(Any,"Gross_ark.light")]=pb;
         pb=images[key_t(Any,"Gross_dfr4_pre.xpm")];
         pb=pb->copy();
         pb->saturate_and_pixelate(pb,2.0,false);
         images[key_t(Any,"Gross_dfr4.light")]=pb;
         pb=images[key_t(Any,"Gross_kurai_pre.xpm")];
         pb=pb->copy();
         pb->saturate_and_pixelate(pb,2.0,false);
         images[key_t(Any,"Gross_kurai.light")]=pb;
         pb=images[key_t(Any,"Gross_dfr3_pre.xpm")];
         pb=pb->copy();
         pb->saturate_and_pixelate(pb,2.0,false);
         images[key_t(Any,"Gross_dfr3.light")]=pb;
      }
   }
   map_t::const_iterator res=images.find(key_t(current_style,name));
   if (res!=images.end()) return res->second;
   Glib::RefPtr<Gdk::Pixbuf> pb=images[key_t(Any,name)];
   if (!pb) std::cerr << "MagusImage(\"" << name << "\") not found\n";
   return pb;
}

void MagusIcons::set_icon_style(style st)
{  current_style=st;
}

const MagusIcons::data_registry *MagusIcons::data_registry::first;
