// $Id: Optionen.hh,v 1.2 2002/04/14 09:04:23 thoma Exp $
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
#include <gtk--/menu.h>
#include <list.h>
#include "WindowInfo.hh"
class midgard_CG;


class Midgard_Optionen
{
   public:
      enum pdfViewerIndex {gv,acroread,xpdf};
      enum OptionenIndex {Original,Info,showPics,LernschemaSensitive,
                            WizardStarten,Wizard_immer_starten,gw_wuerfeln,
                            LernschemaZusaetzeLoeschen,show_InfoWindow,
                            NSC_only};
      enum HausIndex {Gold};


      struct st_pdfViewer {pdfViewerIndex index; 
                             Gtk::RadioMenuItem *radio_menu_item;
                             std::string text;
                             bool active;
             st_pdfViewer(pdfViewerIndex i,Gtk::RadioMenuItem *r,
                            std::string t, bool a) 
                  : index(i),radio_menu_item(r),text(t),active(a) {} };

        struct st_OptionenM{OptionenIndex index;
                           Gtk::MenuItem *menuitem;
                           std::string text;
                           const char * const *bild;
               st_OptionenM(OptionenIndex i,
                           Gtk::MenuItem *m,
                           std::string t,   
                           const char * const * const b)
                  :index(i),menuitem(m),text(t),bild(b) 
                    {}};
        struct st_Optionen{OptionenIndex index;
                           Gtk::CheckMenuItem *checkmenuitem;
                           std::string text;
                           bool active;const char * const *bild;
               st_Optionen(OptionenIndex i,
                           Gtk::CheckMenuItem *cm,
                           std::string t,
                           bool a, const char * const * const b)
                  :index(i),checkmenuitem(cm),text(t),active(a),bild(b)
                  {}};

        Gtk::MenuItem *haus_menuitem;
        struct st_Haus{HausIndex index; Gtk::CheckMenuItem *menu;std::string text;bool active;
               st_Haus(HausIndex i,Gtk::CheckMenuItem *m,std::string t,bool a)
                      :index(i),menu(m),text(t),active(a) {}
                      };

   private:
      std::list<st_Haus> list_Hausregeln;
      std::list<st_Optionen>  list_Optionen;
      std::list<st_OptionenM> list_OptionenM; 
      std::list<st_pdfViewer> list_pdfViewer;

      void Optionen_init();
      void Hausregeln_init();
      void pdfViewer_init();

      midgard_CG* hauptfenster;
   public:
      Midgard_Optionen(midgard_CG* h);

      std::list<st_Haus> getHausregeln() {return list_Hausregeln;}
      std::list<st_Optionen> getOptionen() {return list_Optionen;}
      std::list<st_OptionenM> getOptionenM() {return list_OptionenM;}
      std::list<st_pdfViewer> getPDF() {return list_pdfViewer;}

      void save_options(WindowInfo *InfoFenster);
      void load_options();

      void setOption(std::string os,bool b);
      void setHausregeln(std::string hs,bool b);
      void setpdfViewer(std::string is,bool b); 
      void setAllHausregeln(bool b);


      st_Optionen OptionenCheck(OptionenIndex oi);
      st_Haus HausregelCheck(HausIndex hi);
      st_pdfViewer pdfViewerCheck(pdfViewerIndex pi);

      void Hausregeln_setzen_from_menu(HausIndex index);
      void Optionen_setzen_from_menu(OptionenIndex index);
      void OptionenM_setzen_from_menu(OptionenIndex index);
      void pdfViewer_setzen_from_menu(pdfViewerIndex index);


};

#endif
