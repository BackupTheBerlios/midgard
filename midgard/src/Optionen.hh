// $Id: Optionen.hh,v 1.3 2002/04/14 15:32:14 thoma Exp $
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
#include <string>
#include "WindowInfo.hh"
class midgard_CG;


class Midgard_Optionen
{
      std::string viewer;
   public:
      std::string Viewer() ;
      void setViewer(std::string s) {viewer=s;}
      enum pdfViewerIndex {gv,acroread,xpdf,anderer};

      enum OptionenIndex {Original,Info,showPics,LernschemaSensitive,
                            WizardStarten,Wizard_immer_starten,gw_wuerfeln,
                            LernschemaZusaetzeLoeschen,show_InfoWindow,
                            NSC_only};
      enum HausIndex {Gold};


      struct st_pdfViewer{pdfViewerIndex index;std::string text;bool active;
             st_pdfViewer(pdfViewerIndex i,std::string t, bool a) 
                  : index(i),text(t),active(a) {} };
      struct st_OptionenM{OptionenIndex index;std::string text;const char * const *bild;
               st_OptionenM(OptionenIndex i,std::string t,const char * const * const b)
                  :index(i),text(t),bild(b) {} };
      struct st_Optionen{OptionenIndex index;std::string text;bool active;const char * const *bild;
               st_Optionen(OptionenIndex i,std::string t,bool a, const char * const * const b)
                  :index(i),text(t),active(a),bild(b)
                  {}};
      struct st_Haus{HausIndex index;std::string text;bool active;
               st_Haus(HausIndex i,std::string t,bool a)
                      :index(i),text(t),active(a) {} };

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
