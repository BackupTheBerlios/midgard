// $Id: Window_Waffenbesitz.hh,v 1.21 2001/08/14 13:26:59 thoma Exp $
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

#include <vector>
#include <string>
#include "Window_mag_bonus.hh"
#include <Aux/EntryValueIntString.h>


class midgard_CG;
class H_Data_waffen;
class Grundwerte;

class Window_Waffenbesitz : public Window_Waffenbesitz_glade
{   
        midgard_CG* hauptfenster;
        std::vector<H_Data_waffen>& vec_Waffen;
        std::vector<H_Data_waffen>& Waffe_Besitz;
        Grundwerte& Werte;
        bool mag_bonus_bool;
        int memwaffe;
        friend class Window_Waffenbesitz_glade;
        void on_leaf_selected_alt(cH_RowDataBase d);
        void on_leaf_selected_neu(cH_RowDataBase d);
        void on_waffe_alt_select(std::string waffe,std::string bonus);
        void on_waffe_neu_select(std::string waffe,std::string region);
        void show_alte_waffen();
        void show_neue_waffen();
        void on_button_close_clicked();
        void on_button_sort_clicked();
        void on_checkbutton_mag_waffenbonus_toggled();
   public:
        Window_Waffenbesitz(midgard_CG* h,std::vector<H_Data_waffen>& vw,std::vector<H_Data_waffen>& wb,Grundwerte& We);
        void mag_boni_uebernehmen(H_Data_waffen& wa);
};

class Data_waffenbesitz :  public RowDataBase
{
      std::string name,schaden,magbonus,region;
  public:
      Data_waffenbesitz(std::string n,std::string s,std::string m,std::string r)
         :name(n),schaden(s),magbonus(m),region(r) {} 

      enum SPALTEN_A {NAME_A,SCHADEN_A,MAGBONUS};
      enum SPALTEN_N {NAME_N,SCHADEN_N,REGION};
      virtual const cH_EntryValue Value(guint seqnr,gpointer gp) const
       {
         if (reinterpret_cast<int>(gp)=='A')
          switch(seqnr) {
            case NAME_A : return cH_EntryValueIntString(name);
            case SCHADEN_A : return cH_EntryValueIntString(schaden);
            case MAGBONUS : return cH_EntryValueIntString(magbonus);
           }
         if (reinterpret_cast<int>(gp)=='N')
          switch(seqnr) {
            case NAME_N : return cH_EntryValueIntString(name);
            case SCHADEN_N : return cH_EntryValueIntString(schaden);
            case REGION : return cH_EntryValueIntString(region);
           }
         return cH_EntryValueIntString("?");
       }
   
      std::string Name() const {  return name; }
      std::string Region() const {  return region; }
//      std::string Schaden() const {  return schaden; }
      std::string Magbonus() const {  return magbonus; }
};
class H_Data_waffenbesitz : public Handle<Data_waffenbesitz>
{
protected:
 H_Data_waffenbesitz() {}
public:
 H_Data_waffenbesitz(Data_waffenbesitz *r) : Handle<Data_waffenbesitz>(r){}
};

#endif

