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
 
// generated 2002/5/20 8:42:42 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_ausruestung.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _TABLE_AUSRUESTUNG_HH
#  include "table_ausruestung_glade.hh"
#  define _TABLE_AUSRUESTUNG_HH

class midgard_CG;
#include <gtk--/ctree.h>
#include <map>
#include <Preise.hh>
#include <Ausruestung.hh>

class table_ausruestung : public table_ausruestung_glade
{  
        
        friend class table_ausruestung_glade;
        friend class midgard_CG;
        midgard_CG *hauptfenster;
        AusruestungBaum *besitz;
        Gtk::CTree *Ausruestung_tree;

   public:
        enum e_spalten{None,Farbe,Material,Stand,Max};
   private:
        void fill_new_tree_titles(const std::map<e_spalten,std::string> &VSpalten);
        std::pair<e_spalten,std::string> enum_from_string(const std::string &s);
        std::string spaltentitel(e_spalten e);

       struct st_ausruestung{std::string name;double kosten; std::string einheit; double gewicht;
         st_ausruestung(std::string n,double k, std::string e, double g)
           : name(n),kosten(k),einheit(e),gewicht(g) {}
          bool operator<(const st_ausruestung& b) const
             { return name<b.name;}
          };

public:
        
        table_ausruestung(GlademmData *_data) ;
        void init(midgard_CG *hauptfenster);

private:
        void ausruestung_laden();
        void showAusruestung();
        void showChildren(Gtk::CTree_Helpers::RowList::iterator r,const std::list<AusruestungBaum> &AB);
        bool tree_valid(Gtk::CTree_Helpers::SelectionList &selectionList) ;
        void on_Ausruestung_tree_unselect_row(Gtk::CTree::Row row,gint column);
        void on_Ausruestung_tree_select_row(Gtk::CTree::Row row,gint column);
        void on_checkbutton_sichtbar_toggled();
        void fill_new_preise();
        void fill_all_Combos_Art_Einheit_Region();
        bool fill_all_Combo_Art2();
        void save_new_arikel();
private:
        SigC::Connection sichtbarConnection;
        void zeige_werte();
        

        // Ab hier die automatischen Methoden von glade erzeugt
private:
        void on_preise_tree_neu_leaf_selected(cH_RowDataBase d);
        void on_checkbutton_ausruestung_geld_toggled();
        void on_ausruestung_loeschen_clicked();
        gint on_button_ausruestung_druck_release_event(GdkEventButton *ev);
        void on_togglebutton_gruppe_neu_toggled();
        void on_togglebutton_artikel_neu_toggled();
        void on_combo_entry_artikel_art_activate();
        void on_entry_typ_activate();
        void on_entry_eigenschaft_activate();
        void on_spinbutton_preis_activate();
        void on_spinbutton_gewicht_activate();
        void on_entry_name_activate();
        void on_combo_entry_art2_activate();
        gint on_combo_entry_art2_focus_out_event(GdkEventFocus *ev);
        gint on_combo_entry_art_focus_out_event(GdkEventFocus *ev);
        void on_togglebutton_unverkauflich_toggled();
        void on_combo_entry_einheit_activate();
        void on_combo_entry_region_activate();
        void on_button_artikel_speichern_clicked();

        // drag & drop
        enum {TARGET_STRING,TARGET_ROOTWIN,TARGET_URL};
        static const GtkTargetEntry target_table[4];
        std::vector<st_ausruestung> vec_aus;

        guint n_targets;// = sizeof(target_table) / sizeof(target_table[0]);       

        void on_preise_tree_neu_drag_data_get(GdkDragContext *context,
                                     GtkSelectionData   *selection_data,
                                     guint               info,
                                     guint32             time );
        void tree_drag_data_received(GdkDragContext *context,
                                  gint x,gint y,
                                  GtkSelectionData   *data,
                                  guint info,guint32 time);


/*
        gboolean target_drag_drop(GdkDragContext *context,
                                  gint            x,
                                  gint            y,
                                  guint           time );

*/
};
#endif
