/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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
 
#ifndef _TABLE_ZUFALL_HH
#  include "table_ausruestung_glade.hh"
#  define _TABLE_ZUFALL_HH

class midgard_CG;
#include "table_zufall_glade.hh"
#include "Prozente100.hh"
#include "Zufall.hh"

class Zufall;

class table_zufall : public table_zufall_glade
{
      friend class table_zufall_glade;
      friend class midgard_CG;

      midgard_CG *hauptfenster;
      Prozente100 prozente100;
      Grund_Standard_Ausnahme_MBE GSA_MBE;
      
      void zeige_werte();
      void fill_combos();
      void fill_combo_steigern();
      bool entry_is_a_prototyp(const std::string &e);
      void set_bereiche_spinbuttons();
      int get_spezialbildung();
      Zufall::e_Vorgabe getVorgaben(Abenteurer& oldAben) const ;
   public:
      table_zufall(GlademmData *_data)
         : table_zufall_glade(_data) , hauptfenster(0) {}


      void init(midgard_CG *hauptfenster);

   private:
      // automatisch von glade erzeugte Methoden

        void on_checkbutton_spezies_toggled();
        void on_checkbutton_herkunft_toggled();
        void on_checkbutton_typ_toggled();
        void on_checkbutton_werte_toggled();
        void on_checkbutton_st_toggled();
        void on_checkbutton_gs_toggled();
        void on_checkbutton_gw_toggled();
        void on_checkbutton_ko_toggled();
        void on_checkbutton_in_toggled();
        void on_checkbutton_zt_toggled();
        void on_checkbutton_au_toggled();
        void on_checkbutton_pa_toggled();
        void on_checkbutton_wk_toggled();
        void on_checkbutton_sb_toggled();
        void on_checkbutton_b_toggled();
        void on_combo_spezies_activate();
        gint on_combo_spezies_focus_out_event(GdkEventFocus *ev);
        void on_combo_spezies_changed();
        void on_combo_typ_activate();
        gint on_combo_typ__focus_out_event(GdkEventFocus *ev);
        void on_combo_typ__changed();
        void on_button_zufall_voll_clicked();
        void on_togglebutton_vorgaben_toggled();
        void on_button_steigern_clicked();

        void on_radiobutton_steigern_grad_toggled();
        void on_radiobutton_steigern_gfp_toggled();
        void on_button_check100_clicked();
        void on_combo_prototyp_activate();
        gint on_combo_prototyp_focus_out_event(GdkEventFocus *ev);
        void on_combo_prototyp_changed();

        void on_scale_fert_activate();
        void on_scale_waffen_activate();
        void on_scale_sprachen_activate();
        void on_scale_schriften_activate();

        void on_spinbutton_fertigkeit_activate();
        void on_spinbutton_waffen_activate();
        void on_spinbutton_waffen_grund_activate();
        void on_spinbutton_zauber_activate();
        void on_spinbutton_zauberwerk_activate();
        void on_spinbutton_sprachen_activate();
        void on_spinbutton_schriften_activate();

        void on_togglebutton_prototyp_toggled();
        void on_spinbutton_grund_activate();
        void on_spinbutton_standard_activate();
        void on_spinbutton_ausnahme_activate();

};

#endif
