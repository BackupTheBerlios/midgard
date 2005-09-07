/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2004 Christof Petig
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

#ifndef _TABLE_STEIGERN_HH
#  include "table_steigern_glade.hh"
#  define _TABLE_STEIGERN_HH
class midgard_CG;
#include "MidgardBasicElement.hh"
#include <list>
#include "Enums.hh"
#include <BaseObjects/Model.h>
#include <gtkmm/liststore.h>
#include "Ruestung.hh"
#include "Waffe.hh"

class table_steigern : public table_steigern_glade
{  
        
//        friend class midgard_CG;
//        friend class Magus_Optionen; // Zum Speichern der Handle-Fenster Positionen
        midgard_CG *hauptfenster;
        bool block_update;

        std::list<MBEmlt> list_Fertigkeit_neu;
        std::list<MBEmlt> list_WaffenGrund_neu;
        std::list<MBEmlt> list_Waffen_neu;
        std::list<H_WaffeBesitz> list_WaffenBesitz_neu;
        std::list<MBEmlt> list_Zauber_neu;
        std::list<MBEmlt> list_Zauberwerk_neu;
        std::list<MBEmlt> list_Kido_neu;
        std::list<MBEmlt> list_Sprache_neu;
        std::list<MBEmlt> list_Schrift_neu;

//        Model<bool> steigern_mit_EP_bool; // nur das Model für die Oberfläche
              // muss synchron mit Grundwerte gehalten werden
        enum enum_notebook_lernen{PAGE_FERTIGKEITEN,PAGE_WAFFEN,PAGE_ZAUBER,
                                  PAGE_KIDO,PAGE_SPRACHE,PAGE_BESITZ};

        Glib::RefPtr<Gtk::ListStore> RuestungStore;
        struct RuestungColumns : public Gtk::TreeModelColumnRecord
        {  Gtk::TreeModelColumn<Glib::ustring> name,abkz;
           Gtk::TreeModelColumn<int> lp_verlust,min_staerke,rw_verlust,b_verlust;
           Gtk::TreeModelColumn<cH_Ruestung> ruestung;
           RuestungColumns();
        };
        RuestungColumns ruestung_columns;
                                  
        enum { Button_Steigern, Button_Verlernen, Button_PP_eingeben };
        // button_sonder
        enum { Button_GoldEP, Button_1Drittel, Button_1Halb, Button_2Drittel, Button_Ohne };
        enum { Button_Unterweisung, Button_Selbststudium, Button_Praxis,
               Button_Spruchrolle };
public:
        
        table_steigern(GlademmData *_data) ;
        void init(midgard_CG *hauptfenster);
        
        void clean_up(); // stop pending editing

private:
        const MBEmlt &getSelectedNotebookLernen() throw(SimpleTree::noRowSelected); 
        void load_for_page(guint pagenr);
        void zeige_werte();
        void neuer_charakter();
        void refresh();
        // subparts
        void refresh_moeglich();
        void refresh_werte();
        void refresh_faehigkeiten();
        void refresh_gesteigert();

        // neu: passende Widgets
        MidgardBasicTree *getKnownTree(MidgardBasicElement::MBEE was);
        MidgardBasicTree *getLearnTree(MidgardBasicElement::MBEE was);
        std::list<MBEmlt> &getLearnList(MidgardBasicElement::MBEE was);
        
        // Main
        // in dialog wandeln
        void fillClistZusatz(MBEmlt &MBE);
        void set_zusatz_sensitive(bool an);
        void on_radio_steigern_all();
        std::string SpruecheMitPP();
        void on_radiobutton_pp_all_toggled();
        bool MidgardBasicElement_leaf_alt(const cH_RowDataBase &d);
        // übernimmt jetzt auch das Redisplay
        void MidgardBasicElement_leaf_neu(const cH_RowDataBase &d);
        // true: gelernt
        bool neu_lernen(MBEmlt &MBE,const int bonus=-99);
        void show_goldeingabe(bool b,int button=0);
        void show_EPeingabe(bool b,int button=0);
        void kaempfer_lernt_zaubern() ;
        void zaubern_klasse_gewaehlt() ;
        void zaubern_klasse_gewaehlt_abbrechen();
        bool fert_col_changed(cH_RowDataBase row,unsigned idx,const std::string &newval);
        
        // Grad anstieg
private:
        void get_grundwerte(int wurf);
        void get_ab_re_za(ResistenzUndCo::was_t was);//,bool verschenke_pp=false);


        // EP
        void steigern_gtk();

        // Fertigkeiten
        void fertigkeiten_zeigen();
        void alte_fertigkeiten_zeigen();
        void neue_fertigkeiten_zeigen();
        
        // Waffen
        void on_waffen_laden_clicked();
        void neue_waffen_zeigen();
        void alte_waffen_zeigen();
        void waffen_zeigen();
        void waffengrund_zeigen();

        // Zauber
        void on_zauber_laden_clicked();
        void zauber_zeigen();
        void zauberwerk_laden();
        void zauberwerk_zeigen();
        void wuerfel_lesen_von_zauberschrift();
   public:
        void lernen_von_spruchrolle_fragen(const int bonus);
   private:

        // Sprache
       void schriften_zeigen();
       void sprachen_zeigen();
       void alte_sprache_zeigen();
       void alte_schrift_zeigen();
       void neue_sprache_zeigen();
       void neue_schrift_zeigen();
        void neue_schrift_wegen_sprache();
        int andereSprache_gleicheSchriftart(std::string art);


        // KiDo
        bool kido_steigern_check(int wert);
        void on_kido_laden_clicked();
        void kido_zeigen();

        // Besitz
        void fill_ruestung();
        void show_label();
        void init_waffenbesitz();
//        void lade_waffenbesitz();
        void show_neue_waffen();
        void show_alte_waffen();

         // Ab hier die automatischen Methoden von glade erzeugt
private:
        void on_steigern_zusatz_leaf_selected(cH_RowDataBase d);
        void on_leaf_selected_alte_fert(cH_RowDataBase d);
        void on_leaf_selected_alte_fert2(cH_RowDataBase d,bool &handled);
        void on_alte_waffen_clicked(cH_RowDataBase row,bool &handled);
        void on_neue_waffen_clicked(cH_RowDataBase row,bool &handled);
        void on_alte_grund_clicked(cH_RowDataBase row,bool &handled);
        void on_neue_grund_clicked(cH_RowDataBase row,bool &handled);
        void on_alte_sprache_clicked(cH_RowDataBase row,bool &handled);
        void on_neue_sprache_clicked(cH_RowDataBase row,bool &handled);
        void on_alte_schrift_clicked(cH_RowDataBase row,bool &handled);
        void on_neue_schrift_clicked(cH_RowDataBase row,bool &handled);
        
        void on_alte_fert_reorder();
        void on_leaf_selected_neue_fert(cH_RowDataBase d);
        void on_leaf_selected_alte_waffen(cH_RowDataBase d);
        void on_alte_waffen_reorder();
        void on_leaf_selected_neue_waffen(cH_RowDataBase d);
        void on_leaf_selected_alte_grund(cH_RowDataBase d);
        void on_leaf_selected_neue_grund(cH_RowDataBase d);
        void on_leaf_selected_alte_zauber(cH_RowDataBase d);
        void on_alte_zauber_reorder();
        void on_leaf_selected_neue_zauber(cH_RowDataBase d);
        void on_leaf_selected_alte_zauberwerk(cH_RowDataBase d);
        void on_alte_zaubermittel_reorder();
        void on_leaf_selected_neue_zauberwerk(cH_RowDataBase d);
        void on_leaf_selected_alte_kido(cH_RowDataBase d);
        void on_alte_kido_reorder();
        void on_leaf_selected_neue_kido(cH_RowDataBase d);
        void on_leaf_selected_alte_sprache(cH_RowDataBase d);
        void on_alte_sprache_reorder();
        void on_leaf_selected_neue_sprache(cH_RowDataBase d);
        void on_leaf_selected_alte_schrift(cH_RowDataBase d);
        void on_leaf_selected_neue_schrift(cH_RowDataBase d);
        void on_notebook_lernen_switch_page(GtkNotebookPage *p0, guint p1);
        bool vscale_value_changed(GdkEventButton *ev);
        void on_checkbutton_EP_Geld_toggled();
        void on_radio_selbst_toggled();
        void on_radio_praxis_toggled();
        void on_radio_unterweisung_toggled();
        void on_spruchrolle_toggled();
        void on_togglebutton_alle_zauber_toggled();
        void on_togglebutton_zaubersalze_toggled();
        void on_radio_reduzieren_toggled();
        void on_radio_verlernen_toggled();
        void on_radio_steigern_toggled();
        void on_spinbutton_pp_eingeben_activate();
        void on_togglebutton_praxispunkte_toggled();
        void on_radiobutton_pp_fertigkeit_toggled();
        void on_radiobutton_pp_abwehr_toggled();
        void on_radiobutton_pp_zauber_toggled();
        void on_radiobutton_pp_spezial_toggled();
        void on_radiobutton_pp_resistenz_toggled();
        void on_clist_landauswahl_select_row(gint row, gint column, GdkEvent *event);
        void on_button_grad_clicked();
        void on_button_grad_ausdauer_clicked();
        void on_button_grad_abwehr_clicked();
        void on_button_grad_zaubern_clicked();
        void on_button_grad_resistenz_clicked();
        void on_grad_anstieg_clicked();
        void on_button_grad_basiswerte_clicked();
        void on_button_grad_basiswerte();
        void on_spinbutton_eigenschaften_grad_anstieg_activate();
        void on_button_alter_clicked();
        void on_LabelSpin_gfp_activate();
        void on_LabelSpin_gold_activate();
        void on_LabelSpin_silber_activate();
        void on_LabelSpin_kupfer_activate();
        void on_LabelSpin_aep_activate();
        void on_LabelSpin_kep_activate();
        void on_LabelSpin_zep_activate();
        void on_checkbutton_gfp();
        void on_button_gold_eingeben();
        void on_button_EP_eingeben();
        void on_ruestung_selection_changed();
        void on_button_ruestung_1_toggled();
        void on_button_ruestung_2_toggled();
        void on_leaf_waffenbesitz_selected_alt(cH_RowDataBase d);
        void on_leaf_waffenbesitz_selected_neu(cH_RowDataBase d);
        void on_checkbutton_mag_waffenbonus_toggled();
        void on_alte_waffenbesitz_reorder();
        void on_spinbutton_av_bonus_activate();
        void on_spinbutton_sl_bonus_activate();
        void on_entry_magisch_activate();
        void on_togglebutton_pp_verfallen_toggled();
        void on_togglebutton_pp_aep_fuellen_toggled();
        bool pp_eingeben_click(GdkEventButton*);
        void button_sonder_changed();
        void button_wie_tun_changed();
        void button_rolle_changed();
        void button_ppvar_changed();
        void button_was_tun_changed();
           
        // wie_steigern, *anteil
        void Window2Abenteurer();
        void Abenteurer2Window();
};
#endif
