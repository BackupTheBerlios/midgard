// $Id: Optionen_GUI.hh,v 1.2 2003/09/01 06:47:58 christof Exp $
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

#ifndef _MIDGARD_OPTIONEN_HH
#  define _MIDGARD_OPTIONEN_HH
//#include <gtkmm/menu.h>
//#include <list>
//#include <string>
//#include "WindowInfo.hh"
//#include <gtkmm/spinbutton.h>
class midgard_CG;
//#include <Model.h>
#include <libmagus/Magus_Optionen.hh>

class Midgard_Optionen
{
   public:
      // Glib::RefPtr<Gdk::Pixbuf> bild in st_OptionenExecute, st_OptionenCheck
      //			st_Haus

   private:
      void Strings_init();
      void Optionen_init();
      void Hausregeln_init();
      void Ober_init();


      midgard_CG* hauptfenster;
   public:
      Midgard_Optionen(midgard_CG* h);

      void set_Original(bool active,OptionenCheckIndex index); //???

      void Hausregeln_setzen_from_menu(HausIndex index);
      void Ober_setzen_from_menu(OberIndex index);
      void Icon_setzen_from_menu(IconIndex index);
      void OptionenCheck_setzen_from_menu(OptionenCheckIndex index);
      void OptionenExecute_setzen_from_menu(OptionenExecuteIndex index);
      void pdfViewer_setzen_from_menu(pdfViewerIndex index);
};

#endif
