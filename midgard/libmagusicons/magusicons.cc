// $Id: magusicons.cc,v 1.15 2004/06/08 10:36:36 christof Exp $

#include <magusicons_p.h>
#include <gdkmm/pixbufloader.h>
#include <iostream>
#include <libmagus/Magus_Optionen.hh>
#include <gtk/gtkstock.h>
#include <gtk/gtkiconfactory.h>
#include <gtk/gtkwidget.h>

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

#define GTK_ICON(name,stock) \
	images[key_t(MagusIcons::Gtk,(name))]= \
		Glib::wrap(gtk_icon_set_render_icon(gtk_icon_factory_lookup_default \
		(GTK_STOCK_##stock),gtk_widget_get_default_style(),GTK_TEXT_DIR_NONE, \
         		GTK_STATE_NORMAL, GTK_ICON_SIZE_LARGE_TOOLBAR, \
        		0,0))

Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name)
{  using namespace MagusIcons;
   using MagusIcons::key_t;
   if (images.empty())
   {  Magus_Optionen::IconIndex current_option=Programmoptionen->getIconIndex();
      if (current_option==Magus_Optionen::Self) current_style=Alessandro;
      else if (current_option==Magus_Optionen::Ulf) current_style=Ulf;
      else if (current_option==Magus_Optionen::Gtk2) current_style=MagusIcons::Gtk;
      else current_style=Alessandro;
      
      for (const data_registry *iter=data_registry::first; iter; iter=iter->next)
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
      if (images.empty())
      {  std::cerr << "Image registration failed\n";
         return Glib::RefPtr<Gdk::Pixbuf>();
      }
      // gtk style
      {  GTK_ICON("LoadChar-trans-50.xpm",OPEN);
         GTK_ICON("Exit-trans-50.xpm",QUIT);
         GTK_ICON("Help-trans-50.xpm",HELP); // HOME
         GTK_ICON("Info-trans-50.xpm",DIALOG_INFO);
         GTK_ICON("PrintChar-trans-50.xpm",PRINT);
         GTK_ICON("SaveChar-trans-50.xpm",SAVE);
         GTK_ICON("Ja-32.xpm",YES);
         GTK_ICON("Nein-32.xpm",NO);
         GTK_ICON("Excl-32.xpm",DIALOG_WARNING);
         GTK_ICON("NewChar-trans-50.xpm",NEW);
         GTK_ICON("redo.xpm",REDO);
         GTK_ICON("Undo.xpm",UNDO);
         GTK_ICON("Regio_Hausregel-50.xpm",PREFERENCES); // ?
//         GTK_ICON("Info-trans-50.xpm",CANCEL);
//         GTK_ICON("Info-trans-50.xpm",APPLY);
         GTK_ICON("New_Art-50.xpm",ADD);
//         GTK_ICON("Info-trans-50.xpm",REMOVE);
         GTK_ICON("Trash-32.xpm",DELETE);
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
         pb=images[key_t(Any,"MAGUS_Logo_Tiny.xpm")];
         pb=pb->copy();
         brighten(pb,0.5);
         images[key_t(Any,"MAGUS_Logo_Tiny.light")]=pb;
      }
   }
   map_t::const_iterator res=images.find(key_t(current_style,name));
   if (res!=images.end()) return res->second;
   Glib::RefPtr<Gdk::Pixbuf> pb=images[key_t(Any,name)];
   if (!pb) std::cerr << "MagusImage(\"" << name << "\") not found\n";
   return pb;
}
