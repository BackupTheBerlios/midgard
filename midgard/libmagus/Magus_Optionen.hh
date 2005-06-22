// $Id: Magus_Optionen.hh,v 1.27 2005/06/22 13:51:08 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003-2004 Christof Petig
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
#include <Misc/compiler_ports.h>
#include "libmagus_dll.h"
#include <map>
//class cH_Region;
#include "Region.hh"
//#include "Abenteurer.hh"
class Abenteurer;

class Magus_Optionen
{
   public:
      enum StringIndex{pdf_viewer,html_viewer,tmppfad,speicherpfad};
      enum OptionenCheckIndex {Info,//RegionenAuswahlSpeichern,
                            Wizard_immer_starten,
                            Notebook_start, Hintergrund_Kontrast,
                            OneClick};
      enum OptionenExecuteIndex {LernschemaSensitive,show_InfoWindow};
      enum OberIndex {AutoShrink,SaveFenster,Bilder,Menueleiste,Knopfleiste,
               Icons,Beschriftungen,Customize_Icons,Customize_Text,
               Customize_Tab,Status,NoInfoFenster,BegruessungsFenster,
               UTF8TeX,AvoidDialogues};
      enum IconIndex{Self,Ulf,Gtk2};

      template <class X>
      struct st_base 
      { X index; std::string text;
        st_base(const X &i, const std::string &t) : index(i), text(t) {}
      };
      struct st_strings : st_base<StringIndex>
      { Model_copyable<std::string> name;
             st_strings(StringIndex i,const std::string &t,const std::string &n)
               : st_base<StringIndex>(i,t),name(n) {} 
      };
      typedef st_base<OptionenExecuteIndex> st_OptionenExecute;
      template <class X>
      struct st_base_bool : st_base<X>
      { Model_copyable<bool> active;
        st_base_bool(const X &i, const std::string &t, bool a)
        : st_base<X>(i,t), active(a) {}
        st_base_bool(const st_base_bool<X> &b)
        : st_base<X>(b.index,b.text), active(b.active.get_value()) {}
      };
      // mit Wert!!!
      struct st_OptionenCheck : st_base_bool<OptionenCheckIndex>
      {	Model_copyable<int> wert; 

        st_OptionenCheck(OptionenCheckIndex i,const std::string &t,bool a,int w=-1)
        : st_base_bool<OptionenCheckIndex>(i,t,a),wert(w)
        {}
        // this is only sensible for push_back!
        st_OptionenCheck(const st_OptionenCheck &b)
        : st_base_bool<OptionenCheckIndex>(b.index,b.text,b.active.get_value()), 
            wert(b.wert.get_value()) {}
      };
      struct st_Ober : st_base_bool<OberIndex>
      { bool show;
        st_Ober(OberIndex i,const std::string &t,bool a,bool s=true) // show=false => Wird nicht angezeigt
        : st_base_bool<OberIndex>(i,t,a),show(s) {}
        st_Ober(const st_Ober &b) 
        : st_base_bool<OberIndex>(b.index,b.text,b.active.get_value()),show(b.show) 
        {}
      };
      typedef st_base_bool<IconIndex> st_Icon;
	struct st_WindowPosition
	{	std::string name;
		unsigned width,height;
		int x,y;
		
		st_WindowPosition(const std::string &n,int _x,int _y,unsigned w,unsigned h)
		 : name(n), width(w), height(h), x(_x), y(_y) {}
	};
	
	struct st_Global_Settings_key
	{	unsigned userid;
		std::string program;
		std::string name;
		
		st_Global_Settings_key(unsigned u,const std::string &p, const std::string &n)
		: userid(u), program(p), name(n) {}
		bool operator<(const st_Global_Settings_key &b) const
		{  return userid<b.userid || (userid==b.userid 
			&& (program<b.program || (program==b.program 
			&& name<b.name)));
		}
	};
	
	static const int NOPAGE=-1;
   private:

      Model<int> datei_history;
      std::list<st_strings> list_Strings;
      std::list<st_Ober> list_Ober;
      std::list<st_Icon> list_Icon;
      std::list<st_OptionenExecute>  list_OptionenExecute;
      std::list<st_OptionenCheck> list_OptionenCheck; 
      std::list<st_WindowPosition> list_Windows;
      std::list<std::string> LDateien;
      std::map<st_Global_Settings_key,std::string> my_global_settings;
      bool geaendert;
      
      std::list<RadioModel> ausschluesse;
      
      void Strings_init();
      void Optionen_init();
      void Ober_init();
      void Icon_init();
      void init_all();
      
      static void global_settings_save(int userid,const std::string& program,
      		const std::string& name, const std::string& value);
      static std::string global_settings_load(int userid,const std::string& program,
      		const std::string& name);
      		
      void operator=(const Magus_Optionen &);
      Magus_Optionen(const Magus_Optionen &);

   public: 
      Magus_Optionen();
      
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
      int DateiHistory() const {return datei_history.Value();}
      Model_ref<int> DateiHistory() {return datei_history;}

      void save_options(const std::string &filename);
      void load_options(const std::string &filename);

      void setString(std::string os,std::string name);
      void setOptionCheck(std::string os,bool b,int wert);
      void setOber(std::string hs,bool b);
      void setIcon(std::string hs,bool b);
      void setpdfViewer(std::string is,bool b); 
      __deprecated void setDateiHistory(int i) {datei_history=i;}
      void setWindowPosition(const std::string &name,int x,int y,unsigned w,unsigned h);
      void setLetzteDatei(const std::string &path);

      st_OptionenCheck &OptionenCheck(OptionenCheckIndex oi) ;
      st_Ober &OberCheck(OberIndex hi)  ;
      st_Icon &IconCheck(IconIndex i) ;
      IconIndex getIconIndex() const;
      const st_WindowPosition &WindowPosition(const std::string &name) const;
      const std::list<std::string> &LetzteDateien() const 
      { return LDateien; }
      std::list<std::string> &LetzteDateien() 
      { return LDateien; }

      void Ober_setzen_from_menu(OberIndex index);
      void Icon_setzen_from_menu(IconIndex index);
      void OptionenCheck_setzen_from_menu(OptionenCheckIndex index);
      void OptionenExecute_setzen_from_menu(OptionenExecuteIndex index);
      
      typedef std::map<std::string,bool > regionen_t;
      regionen_t standard_regionen;  // aktive Standardregionen
      void setStandardRegionen(const Abenteurer &A) ;
};

extern LIBMAGUS_API Magus_Optionen *Programmoptionen;
#endif
