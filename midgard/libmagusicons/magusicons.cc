// $Id: magusicons.cc,v 1.6 2003/05/06 12:54:37 christof Exp $

#include <magusicons_p.h>
#include <gdkmm/pixbufloader.h>
#include <iostream>

static MagusIcons::style current_style=MagusIcons::Alessandro;
MagusIcons::map_t MagusIcons::images;

static void brighten(const Glib::RefPtr<Gdk::Pixbuf> &im, gfloat value)
{
  const GdkPixbuf *src=im->gobj();

  g_return_if_fail (GDK_IS_PIXBUF (src));
  g_return_if_fail (value<1.0);
  int i, j;
  int width, height, has_alpha, src_rowstride, bytes_per_pixel;
  guchar *src_line;
  guchar *src_pixel;

  has_alpha = gdk_pixbuf_get_has_alpha (src);
  bytes_per_pixel = has_alpha ? 4 : 3;
  width = gdk_pixbuf_get_width (src);
  height = gdk_pixbuf_get_height (src);
  src_rowstride = gdk_pixbuf_get_rowstride (src);
  src_line = gdk_pixbuf_get_pixels (src);
		
#define BRIGHTEN(p,v) (255-guchar((255-(p))*(v)))

  for (i = 0 ; i < height ; i++) {
	src_pixel = src_line;
	src_line += src_rowstride;

	for (j = 0 ; j < width ; j++) {
            src_pixel[0] = BRIGHTEN (src_pixel[0],value);
            src_pixel[1] = BRIGHTEN (src_pixel[1],value);
            src_pixel[2] = BRIGHTEN (src_pixel[2],value);
	    src_pixel += bytes_per_pixel;
        }
  }
}

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
      const gfloat brightfactor=0.4;
      {  Glib::RefPtr<Gdk::Pixbuf> pb;
         pb=images[key_t(Any,"Gross_ark_pre.xpm")];
         pb=pb->copy();
         brighten(pb,brightfactor);
         images[key_t(Any,"Gross_ark.light")]=pb;
         pb=images[key_t(Any,"Gross_dfr4_pre.xpm")];
         pb=pb->copy();
         brighten(pb,brightfactor);
         images[key_t(Any,"Gross_dfr4.light")]=pb;
         pb=images[key_t(Any,"Gross_kurai_pre.xpm")];
         pb=pb->copy();
         brighten(pb,brightfactor);
         images[key_t(Any,"Gross_kurai.light")]=pb;
         pb=images[key_t(Any,"Gross_dfr3_pre.xpm")];
         pb=pb->copy();
         brighten(pb,brightfactor);
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
