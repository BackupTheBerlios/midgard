// $Id: Window_Waffenbesitz.hh,v 1.27 2001/11/08 10:15:43 thoma Exp $
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

// generated 2001/3/14 8:34:43 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_Waffenbesitz.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _WINDOW_WAFFENBESITZ_HH
#  include "Window_Waffenbesitz_glade.hh"
#  define _WINDOW_WAFFENBESITZ_HH

#include <list>
#include <string>
#include <Aux/EntryValueIntString.h>
#include <Waffe.hh>

class midgard_CG;
//class H_Data_waffen;
//class H_WaffeBesitz;
//class cH_Waffe;
#include "MidgardBasicElement.hh"
class Grundwerte;
class Typen;

class Window_Waffenbesitz : public Window_Waffenbesitz_glade
{   
        midgard_CG* hauptfenster;
        std::list<cH_MidgardBasicElement> list_Waffen;
        std::list<H_WaffeBesitz> Waffe_Besitz;
        std::list<H_WaffeBesitz> Waffe_Besitz_neu;
        Grundwerte& Werte;
        vector<cH_Typen> Typ;
        H_WaffeBesitz selected_weapon;
        friend class Window_Waffenbesitz_glade;
        void on_leaf_selected_alt(cH_RowDataBase d);
        void on_leaf_selected_neu(cH_RowDataBase d);
        void show_alte_waffen();
        void show_neue_waffen();
        void on_button_neuladen_clicked();
        void lade_waffen();
        void zeige_waffen();
        void move_waffe(std::list<H_WaffeBesitz>& von,std::list<H_WaffeBesitz>& nach,std::string name);
        void on_button_close_clicked();
        void on_button_sort_clicked();
        void on_checkbutton_mag_waffenbonus_toggled();
        void on_spinbutton_av_bonus_activate();
        void on_spinbutton_sl_bonus_activate();
        void on_entry_magisch_activate();
   public:
        Window_Waffenbesitz(midgard_CG* h,const std::list<cH_MidgardBasicElement>& vw,std::list<H_WaffeBesitz>& wb,
            Grundwerte& We,const vector<cH_Typen>& T);
};

class Data_waffenbesitz :  public RowDataBase
{
      H_WaffeBesitz waffe;
      Grundwerte Werte;
//      std::string alias;
  public:
      Data_waffenbesitz(const H_WaffeBesitz& w,const Grundwerte& g)
         : waffe(w), Werte(g) {}

      enum SPALTEN_A {NAME_A,SCHADEN_A,REGION,MAGBONUS,MAGTEXT};
      virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
       {
          switch(seqnr) {
            case NAME_A : return cH_EntryValueIntString(waffe->Name());
            case SCHADEN_A : return cH_EntryValueIntString(waffe->Schaden(Werte,waffe->Name()));
            case REGION : return cH_EntryValueIntString(waffe->Region());
            case MAGBONUS : return cH_EntryValueIntString(waffe->Bonus());
            case MAGTEXT : return cH_EntryValueIntString(waffe->Magisch());
           }
         return cH_EntryValueIntString("?");
       }
      H_WaffeBesitz get_Waffe() const {return waffe;}
//      std::string get_Alias() const {return alias;}
};

class cH_Data_waffenbesitz : public Handle<const Data_waffenbesitz>
{
protected:
 cH_Data_waffenbesitz() {}
public:
 cH_Data_waffenbesitz(const Data_waffenbesitz *r) : Handle<const Data_waffenbesitz>(r){}
};

#endif

