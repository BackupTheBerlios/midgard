// $Id: Magus_Optionen.hh,v 1.8 2003/09/15 08:27:38 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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

#ifndef _MAGUS_OPTIONEN_HH
#  define _MAGUS_OPTIONEN_HH
#include <list>
#include <string>
#include <BaseObjects/Model.h>
#include <BaseObjects/RadioModel.h>

class Magus_Optionen
{
   public:
      enum StringIndex{pdf_viewer,html_viewer,tmppfad,speicherpfad};
      enum pdfViewerIndex {gv,acroread,xpdf,anderer};
      enum OptionenCheckIndex {Info,
                            Wizard_immer_starten,Drei_Tasten_Maus,
                            Notebook_start};
      enum OptionenExecuteIndex {LernschemaSensitive,show_InfoWindow};
      enum OberIndex {AutoShrink,SaveFenster,Bilder,Menueleiste,Knopfleiste,
               Icons,Beschriftungen,Customize_Icons,Customize_Text,
               Customize_Tab,Status,NoInfoFenster,BegruessungsFenster};
      enum IconIndex{Self,Ulf,Gtk2};

      struct st_strings{StringIndex index; std::string text; Model_copyable<std::string> name;
             st_strings(StringIndex i,std::string t,std::string n)
               : index(i),text(t),name(n) {} };

      struct st_OptionenExecute{OptionenExecuteIndex index;std::string text;
               st_OptionenExecute(OptionenExecuteIndex i,std::string t)
                  :index(i),text(t) {} };

      struct st_pdfViewer{pdfViewerIndex index;std::string text;Model_copyable<bool> active;
             st_pdfViewer(pdfViewerIndex i,std::string t, bool a) 
                  : index(i),text(t),active(a) {}
             st_pdfViewer(const st_pdfViewer &b) 
                      :index(b.index),text(b.text),active(b.active.get_value()) {}
                   };
      // mit Wert!!!
      struct st_OptionenCheck
      {		OptionenCheckIndex index;
      		std::string text;
      		Model_copyable<bool> active;
      		Model_copyable<int> wert; 

               st_OptionenCheck(OptionenCheckIndex i,std::string t,bool a,int w=-1)
                  :index(i),text(t),active(a),wert(w)
                  {}
               // this is only sensible for push_back!
               st_OptionenCheck(const st_OptionenCheck &b)
               	  : index(b.index), text(b.text), active(b.active.get_value()), 
               	  	wert(b.wert.get_value()) {}
              };
      struct st_Ober{OberIndex index;std::string text;Model_copyable<bool> active;bool show;
               st_Ober(OberIndex i,std::string t,bool a,bool s=true) // show=false => Wird nicht angezeigt
                      :index(i),text(t),active(a),show(s) {}
               st_Ober(const st_Ober &b) 
                      :index(b.index),text(b.text),active(b.active.get_value()),show(b.show) {}
                       };
      struct st_Icon{IconIndex index;std::string text;Model_copyable<bool> active;
               st_Icon(IconIndex i,std::string t,bool a)
                      :index(i),text(t),active(a) {}
               st_Icon(const st_Icon &b)
                     :index(b.index),text(b.text),active(b.active.get_value()){}
                };
	struct st_WindowPosition
	{	std::string name;
		unsigned width,height;
		int x,y;
		
		st_WindowPosition(const std::string &n,int _x,int _y,unsigned w,unsigned h)
		 : name(n), width(w), height(h), x(_x), y(_y) {}
	};
	
	static const int NOPAGE=-1;
   private:
      int datei_history;
      std::list<st_strings> list_Strings;
      std::list<st_Ober> list_Ober;
      std::list<st_Icon> list_Icon;
      std::list<st_OptionenExecute>  list_OptionenExecute;
      std::list<st_OptionenCheck> list_OptionenCheck; 
      std::list<st_pdfViewer> list_pdfViewer;
      std::list<st_WindowPosition> list_Windows;
      Model_ref<bool> werte_eingeben;
      std::list<std::string> LDateien;
      
      std::list<RadioModel> ausschluesse;

      void Strings_init();
      void Optionen_init();
      void Ober_init();
      void Icon_init();
      void pdfViewer_init();
      void init_all();

   public: 
      // erst nachdem magus_paths initialisiert ist
      static void init();

      std::string Viewer() const;

      std::string getString(StringIndex index) const;
      Model_ref<std::string> getString(StringIndex index);
      void setString(StringIndex index,std::string n);

      std::list<st_Ober> &getOber()  {return list_Ober;}
      std::list<st_Icon> &getIcon()  {return list_Icon;}
      std::list<st_OptionenCheck> &getOptionenCheck() {return list_OptionenCheck;}
      std::list<st_OptionenExecute> &getOptionenExecute()  {return list_OptionenExecute;}
      std::list<st_pdfViewer> &getPDF()  {return list_pdfViewer;}
      int DateiHistory() const {return datei_history;}

      void save_options(const std::string &filename);
      void load_options(const std::string &filename);

      void setString(std::string os,std::string name);
      void setOptionCheck(std::string os,bool b,int wert);
      void setOber(std::string hs,bool b);
      void setIcon(std::string hs,bool b);
      void setpdfViewer(std::string is,bool b); 
      void setDateiHistory(int i) {datei_history=i;}
      void setWindowPosition(const std::string &name,int x,int y,unsigned w,unsigned h);
      void setLetzteDatei(const std::string &path);

      st_OptionenCheck &OptionenCheck(OptionenCheckIndex oi) ;
      st_Ober &OberCheck(OberIndex hi)  ;
      st_Icon &IconCheck(IconIndex i) ;
      IconIndex getIconIndex() const;
      st_pdfViewer &pdfViewerCheck(pdfViewerIndex pi);
      const st_pdfViewer &pdfViewerCheck(pdfViewerIndex pi) const;
      const st_WindowPosition &WindowPosition(const std::string &name) const;
      const std::list<std::string> &LetzteDateien() const 
      { return LDateien; }
      std::list<std::string> &LetzteDateien() 
      { return LDateien; }

      void Ober_setzen_from_menu(OberIndex index);
      void Icon_setzen_from_menu(IconIndex index);
      void OptionenCheck_setzen_from_menu(OptionenCheckIndex index);
      void OptionenExecute_setzen_from_menu(OptionenExecuteIndex index);
      void pdfViewer_setzen_from_menu(pdfViewerIndex index);
      
      
      Model_ref<bool> WerteEingebenModel() { return werte_eingeben; }
};

extern Magus_Optionen Programmoptionen;
#endif
