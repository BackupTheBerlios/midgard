// $Id: midgard.cc,v 1.79 2004/01/23 10:02:42 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gtkmm/main.h>
#include "midgard_CG.hh"
#include <libmagus/Ausgabe.hh>
#include <libmagus/libmagus.hh>
#include <libmagusicons/magusicons.h>
#include <gtkmm/enums.h>
#include <Misc/itos.h>
#include "WindowInfo.hh"
#ifdef __MINGW32__
#include <io.h>
#endif
#include <iostream>
#include <libmagus/magus_paths.h>
#include "BegruessungsWindow.hh"
#include "MagusAusgabe.hh"
#include <libmagus/AbenteurerAuswahl.h>
#include <fstream>

static const unsigned steps=8;
static Gtk::Window *progresswin;
static Glib::RefPtr<Gdk::Pixbuf> Load0,Load1;
static unsigned current_n;
static Gtk::Image *imag;

static void progress(double d)
{  if (!imag)
   {  Ausgabe(Ausgabe::Log, "Progress " +itos(int(d*100))+ "%");
      return;
   }
   unsigned n=unsigned(steps*d+.5);
   if (n!=current_n)
   {  // von Load0 nach Load1 morphen
      double beta=(steps-n)/double(steps-current_n);
      double gamma=(n-beta*current_n)/double(steps);
      guchar *b_pixel,*dest_pixel;
      guchar *b_line,*dest_line;
      unsigned rowstride = Load0->get_rowstride ();
      unsigned bytes_per_pixel = Load0->get_has_alpha() ? 4 : 3;
      b_line=Load1->get_pixels();
      dest_line=Load0->get_pixels();
      for (unsigned y=0;y<Load1->get_height();++y)
      {  b_pixel=b_line;
         dest_pixel=dest_line;
         for (unsigned x=0;x<Load1->get_width();++x)
         {  if (dest_pixel[0]!=b_pixel[0]) dest_pixel[0]= beta*dest_pixel[0]+ gamma*b_pixel[0];
            if (dest_pixel[1]!=b_pixel[1]) dest_pixel[1]= beta*dest_pixel[1]+ gamma*b_pixel[1];
            if (dest_pixel[2]!=b_pixel[2]) dest_pixel[2]= beta*dest_pixel[2]+ gamma*b_pixel[2];
            if (bytes_per_pixel==4 && dest_pixel[3]!=b_pixel[3])
               dest_pixel[3]= beta*dest_pixel[3]+ gamma*b_pixel[3];
            dest_pixel+=bytes_per_pixel;
            b_pixel+=bytes_per_pixel;
         }
         b_line+=rowstride;
         dest_line+=rowstride;
      }
      imag->set(Load0);
      while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
      current_n=n;
   }
}

int main(int argc, char **argv)
{
#ifdef __MINGW32__ // Dr MinGW als Exception Handle (debugging Ausgabe!)
   LoadLibrary("exchndl.dll");
#endif
   if (!getenv("DEBUG")) Magus_Ausgabe::register_Ausgabe();
   Ausgabe::setLogLevel(Ausgabe::Debug);
   libmagus_init0(argc,const_cast<const char **>(argv));
#ifdef __MINGW32__ // gtkrc als Standard Ressourcen Datei
   std::string gtkrc;
   if (!getenv("GTK_RC_FILES"))
   {  gtkrc="GTK_RC_FILES="+magus_paths::with_path("gtkrc");
      Ausgabe(Ausgabe::Debug,gtkrc);
      putenv(gtkrc.c_str());
   }
#endif

#warning Zeitmessung wegen Anzahl der Zwischenschritte?
   Gtk::Main m(&argc, &argv,true); 
   if (!getenv("NOSPLASH")) 
  {
//std::cerr << "composing images\n";
   Load0=MagusImage("MAGUS-Logo.png")->copy();
   Load1=Load0->copy();
   MagusImage("Loading.png")->composite(Load0,0,0,Load0->get_width(),Load0->get_height(),
   		0,0,1,1,Gdk::INTERP_NEAREST,255);
   MagusImage("Version.png")->composite(Load1,0,0,Load1->get_width(),Load1->get_height(),
   		0,0,1,1,Gdk::INTERP_NEAREST,255);
//std::cerr << "displaying images\n";
   progresswin=new Gtk::Window(Gtk::WINDOW_POPUP);
   progresswin->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
   progresswin->set_type_hint(Gdk::WINDOW_TYPE_HINT_SPLASHSCREEN);
   progresswin->set_title("MAGuS");
   imag=manage(new Gtk::Image(Load0));
   progresswin->add(*imag);
   imag->show();
   progresswin->show();
   while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
  }
   libmagus_init1(progress);
   if (progresswin) progress(1.0);

   // WindowInfo erzeugen und an midgard_CG übergeben
   WindowInfo *info=new WindowInfo();
   Magus_Ausgabe::attach(info);

   for (int i=1;i<argc;++i) 
   {  try
      {  AbenteurerAuswahl::Chars.load(argv[i]);
      }
      catch (...)
      {
      }
   }

//   setlocale(LC_ALL, "de_DE");
   if(!Programmoptionen.OberCheck(Magus_Optionen::BegruessungsFenster).active
      && AbenteurerAuswahl::Chars.empty())
         AbenteurerAuswahl::Chars.push_back();
   midgard_CG *magus=new midgard_CG(info,AbenteurerAuswahl::Chars.begin());
   // darf nicht eher geschehen wegen realize (background) als virtuellem callback
   magus->show();
   if (progresswin) { delete progresswin; progresswin=0; imag=0; }
   if (argc>1)
   {  if(Programmoptionen.OberCheck(Magus_Optionen::BegruessungsFenster).active)
         manage(new BegruessungsWindow(magus));
   }
   m.run(*magus);
#warning nur wenn geändert ...
   Programmoptionen.save_options(magus_paths::MagusVerzeichnis()+"magus_optionen.xml");
   delete magus;
   delete info;
   return 0;
}
