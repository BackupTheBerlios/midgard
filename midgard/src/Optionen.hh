// $Id: Optionen.hh,v 1.34 2002/09/19 08:16:21 thoma Exp $
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
#include <gtk--/spinbutton.h>
class midgard_CG;
#include <MVC.h>

class Midgard_Optionen
{
   public:
      enum StringIndex{pdf_viewer,html_viewer,tmppfad,speicherpfad};
      enum pdfViewerIndex {gv,acroread,xpdf,anderer};
      enum OptionenCheckIndex {Original,Info,
                            Wizard_immer_starten,Drei_Tasten_Maus,
                            NSC_only,Notebook_start};
      enum OptionenExecuteIndex {LernschemaSensitive,show_InfoWindow};
      enum HausIndex {Gold};
      enum OberIndex {AutoShrink,SaveFenster,Bilder,Menueleiste,Knopfleiste,
               Icons,Beschriftungen,Customize_Icons,Customize_Text,
               Customize_Tab,Status,NoInfoFenster};
      enum IconIndex{Self,Ulf};

      struct st_strings{StringIndex index; std::string text; std::string name;
             st_strings(StringIndex i,std::string t,std::string n)
               : index(i),text(t),name(n) {} };
      struct st_pdfViewer{pdfViewerIndex index;std::string text;bool active;
             st_pdfViewer(pdfViewerIndex i,std::string t, bool a) 
                  : index(i),text(t),active(a) {} };
      struct st_OptionenExecute{OptionenExecuteIndex index;std::string text;const char * const *bild;
               st_OptionenExecute(OptionenExecuteIndex i,std::string t,const char * const * const b)
                  :index(i),text(t),bild(b) {} };

      struct st_OptionenCheck{OptionenCheckIndex index;std::string text;
               MVC<bool> active;
               const char * const *bild;
               MVC<int> wert; 
               st_OptionenCheck(OptionenCheckIndex i,std::string t,bool a,
                   const char * const * const b,int w=-1)
                  :index(i),text(t),active(a),bild(b),wert(w)
                  {}
               // this is only sensible for push_back!
               st_OptionenCheck(const st_OptionenCheck &b)
               	  : index(b.index), text(b.text), active(b.active.get_value()), 
               	  	bild(b.bild), wert(b.wert.get_value()) {}
              };
      struct st_Haus{HausIndex index;std::string text;const char * const *bild;bool active;
               st_Haus(HausIndex i,std::string t,const char * const *b,bool a)
                      :index(i),text(t),bild(b),active(a) {} };
      struct st_Ober{OberIndex index;std::string text;bool active;bool show;
               st_Ober(OberIndex i,std::string t,bool a,bool s=true) // show=false => Wird nicht angezeigt
                      :index(i),text(t),active(a),show(s) {} };
      struct st_Icon{IconIndex index;std::string text;bool active;
               st_Icon(IconIndex i,std::string t,bool a)
                      :index(i),text(t),active(a) {} };

   private:
      int datei_history;
      std::list<st_strings> list_Strings;
      std::list<st_Haus> list_Hausregeln;
      std::list<st_Ober> list_Ober;
      std::list<st_Icon> list_Icon;
      std::list<st_OptionenExecute>  list_OptionenExecute;
      std::list<st_OptionenCheck> list_OptionenCheck; 
      std::list<st_pdfViewer> list_pdfViewer;

      void Strings_init();
      void Optionen_init();
      void Hausregeln_init();
      void Ober_init();
      void Icon_init();
      void pdfViewer_init();

      midgard_CG* hauptfenster;
   public:
      Midgard_Optionen(midgard_CG* h);

      std::string Viewer() const;

      std::string getString(StringIndex index) const;
      void setString(StringIndex index,std::string n);

      std::list<st_Haus> getHausregeln() const {return list_Hausregeln;}
      std::list<st_Ober> getOber() const {return list_Ober;}
      std::list<st_Icon> getIcon() const {return list_Icon;}
      std::list<st_OptionenCheck> &getOptionenCheck() {return list_OptionenCheck;}
      std::list<st_OptionenExecute> getOptionenExecute() const {return list_OptionenExecute;}
      std::list<st_pdfViewer> getPDF() const {return list_pdfViewer;}
      int DateiHistory() const {return datei_history;}

      void save_options(const std::string &filename,WindowInfo *InfoFenster);
      void load_options(const std::string &filename);

      void setString(std::string os,std::string name);
      void setOptionCheck(std::string os,bool b,int wert);
      void setHausregeln(std::string hs,bool b);
      void setOber(std::string hs,bool b);
      void setIcon(std::string hs,bool b);
      void setpdfViewer(std::string is,bool b); 
      void setAllHausregeln(bool b);
      void setDateiHistory(int i) {datei_history=i;}


      const st_OptionenCheck &OptionenCheck(OptionenCheckIndex oi) const ;
      st_Haus HausregelCheck(HausIndex hi) const ;
      st_Ober OberCheck(OberIndex hi) const ;
      st_Icon IconCheck(IconIndex i) const ;
      IconIndex getIconIndex() const;
      st_pdfViewer pdfViewerCheck(pdfViewerIndex pi) const ;

      void Hausregeln_setzen_from_menu(HausIndex index,bool b);
      void Ober_setzen_from_menu(OberIndex index,bool b);
      void Icon_setzen_from_menu(IconIndex index,bool b);
      void OptionenCheck_setzen_from_menu(OptionenCheckIndex index);
      void OptionenExecute_setzen_from_menu(OptionenExecuteIndex index);
      void pdfViewer_setzen_from_menu(pdfViewerIndex index);
};

#endif
