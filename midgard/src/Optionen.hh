// $Id: Optionen.hh,v 1.9 2002/04/27 15:11:43 thoma Exp $
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
   public:
      enum StringIndex{pdf_viewer,html_viewer,tmppfad,speicherpfad};
      enum pdfViewerIndex {gv,acroread,xpdf,anderer};
      enum OptionenCheckIndex {Original,Info,//showPics,
                            Wizard_immer_starten,gw_wuerfeln,
                            NSC_only};
      enum OptionenExecuteIndex {LernschemaSensitive,
                            WizardStarten,
                            LernschemaZusaetzeLoeschen,show_InfoWindow};
      enum HausIndex {Gold};
      enum OberIndex {Bilder,Menueleiste,Knopfleiste,Icons,Beschriftungen,Status};

      struct st_strings{StringIndex index; std::string text; std::string name;
             st_strings(StringIndex i,std::string t,std::string n)
               : index(i),text(t),name(n) {} };
      struct st_pdfViewer{pdfViewerIndex index;std::string text;bool active;
             st_pdfViewer(pdfViewerIndex i,std::string t, bool a) 
                  : index(i),text(t),active(a) {} };
      struct st_OptionenExecute{OptionenExecuteIndex index;std::string text;const char * const *bild;
               st_OptionenExecute(OptionenExecuteIndex i,std::string t,const char * const * const b)
                  :index(i),text(t),bild(b) {} };
      struct st_OptionenCheck{OptionenCheckIndex index;std::string text;bool active;const char * const *bild;
               st_OptionenCheck(OptionenCheckIndex i,std::string t,bool a, const char * const * const b)
                  :index(i),text(t),active(a),bild(b)
                  {}};
      struct st_Haus{HausIndex index;std::string text;bool active;
               st_Haus(HausIndex i,std::string t,bool a)
                      :index(i),text(t),active(a) {} };
      struct st_Ober{OberIndex index;std::string text;bool active;
               st_Ober(OberIndex i,std::string t,bool a)
                      :index(i),text(t),active(a) {} };

   private:
      std::list<st_strings> list_Strings;
      std::list<st_Haus> list_Hausregeln;
      std::list<st_Ober> list_Ober;
      std::list<st_OptionenExecute>  list_OptionenExecute;
      std::list<st_OptionenCheck> list_OptionenCheck; 
      std::list<st_pdfViewer> list_pdfViewer;

      void Strings_init();
      void Optionen_init();
      void Hausregeln_init();
      void Ober_init();
      void pdfViewer_init();

      midgard_CG* hauptfenster;
   public:
      Midgard_Optionen(midgard_CG* h);

      std::string Viewer() ;

      std::string getString(StringIndex index);
      void setString(StringIndex index,std::string n);

      std::list<st_Haus> getHausregeln() {return list_Hausregeln;}
      std::list<st_Ober> getOber() {return list_Ober;}
      std::list<st_OptionenCheck> getOptionenCheck() {return list_OptionenCheck;}
      std::list<st_OptionenExecute> getOptionenExecute() {return list_OptionenExecute;}
      std::list<st_pdfViewer> getPDF() {return list_pdfViewer;}

      void save_options(WindowInfo *InfoFenster);
      void load_options();

      void setString(std::string os,std::string name);
      void setOptionCheck(std::string os,bool b);
      void setHausregeln(std::string hs,bool b);
      void setOber(std::string hs,bool b);
      void setpdfViewer(std::string is,bool b); 
      void setAllHausregeln(bool b);


      st_OptionenCheck OptionenCheck(OptionenCheckIndex oi);
      st_Haus HausregelCheck(HausIndex hi);
      st_Ober OberCheck(OberIndex hi);
      st_pdfViewer pdfViewerCheck(pdfViewerIndex pi);

      void Hausregeln_setzen_from_menu(HausIndex index,bool b);
      void Ober_setzen_from_menu(OberIndex index,bool b);
      void OptionenCheck_setzen_from_menu(OptionenCheckIndex index,bool b);
      void OptionenExecute_setzen_from_menu(OptionenExecuteIndex index);
      void pdfViewer_setzen_from_menu(pdfViewerIndex index);
};

#endif
