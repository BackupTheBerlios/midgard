// generated 2002/9/19 10:40:01 CEST by thoma@Tiger.(none)
// using glademm V1.1.1c_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/thoma/rollenspiel/midgard/programme/gcc_3.0/midgard/midgard.glade
// for gtk 1.2.10 and gtkmm 1.2.10
//
// Please modify the corresponding derived classes in ./src/table_zufall.hh and./src/table_zufall.cc

#ifndef _TABLE_ZUFALL_GLADE_HH
#  define _TABLE_ZUFALL_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtk--/accelgroup.h>

class GlademmData
{  
        
        Gtk::AccelGroup *accgrp;
public:
        
        GlademmData(Gtk::AccelGroup *ag) : accgrp(ag)
        {  
        }
        
        Gtk::AccelGroup * getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtk--/table.h>
#include <gtk--/checkbutton.h>
#include <gtk--/spinbutton.h>
#include <gtk--/frame.h>
#include <gtk--/combo.h>
#include <gtk--/togglebutton.h>
#include <gtk--/radiobutton.h>

class table_zufall_glade : public Gtk::Table
{  
protected:
        
        class Gtk::Table *table_zufall;
        class Gtk::CheckButton *checkbutton_spezies;
        class Gtk::CheckButton *checkbutton_herkunft;
        class Gtk::CheckButton *checkbutton_typ;
        class Gtk::CheckButton *checkbutton_werte;
        class Gtk::CheckButton *checkbutton_ange_fert;
        class Gtk::CheckButton *checkbutton_st;
        class Gtk::CheckButton *checkbutton_gs;
        class Gtk::CheckButton *checkbutton_gw;
        class Gtk::CheckButton *checkbutton_ko;
        class Gtk::CheckButton *checkbutton_in;
        class Gtk::CheckButton *checkbutton_zt;
        class Gtk::CheckButton *checkbutton_au;
        class Gtk::CheckButton *checkbutton_pa;
        class Gtk::CheckButton *checkbutton_wk;
        class Gtk::CheckButton *checkbutton_sb;
        class Gtk::CheckButton *checkbutton_b;
        class Gtk::SpinButton *spinbutton_st;
        class Gtk::SpinButton *spinbutton_au;
        class Gtk::SpinButton *spinbutton_pa;
        class Gtk::SpinButton *spinbutton_wk;
        class Gtk::SpinButton *spinbutton_sb;
        class Gtk::SpinButton *spinbutton_b;
        class Gtk::SpinButton *spinbutton_gs;
        class Gtk::SpinButton *spinbutton_gw;
        class Gtk::SpinButton *spinbutton_ko;
        class Gtk::SpinButton *spinbutton_in;
        class Gtk::SpinButton *spinbutton_zt;
        class Gtk::Frame *frame_werte_vorgaben;
        class Gtk::Combo *combo_spezies;
        class Gtk::Combo *combo_typ;
        class Gtk::Combo *combo_herkunft;
        class Gtk::Frame *frame_vorgaben;
        class Gtk::ToggleButton *togglebutton_vorgaben;
        class Gtk::RadioButton *radiobutton_steigern_grad;
        class Gtk::RadioButton *radiobutton_steigern_gfp;
        class Gtk::SpinButton *spinbutton_gfp;
        class Gtk::SpinButton *spinbutton_grad;
        
        table_zufall_glade(GlademmData *_data);
        
        ~table_zufall_glade();
};
#endif
