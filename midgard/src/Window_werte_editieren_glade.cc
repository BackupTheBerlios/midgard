// generated 2001/5/3 22:45:18 CEST by thoma@linux.
// using glademm V0.6.2_cvs
//
// DO NOT EDIT THIS FILE ! It was created using
// /home/thoma/petig/cvs/christof/glade--/src/glade-- midgard.glade
// for gtk 1.2.8 and gtkmm 1.2.5
//
// Please modify the corresponding derived classes in ./src/Window_werte_editieren.cc

#include "config.h"
#include "Window_werte_editieren.hh"
#include <gtk--/label.h>
#include <gtk--/adjustment.h>
#include <gtk--/separator.h>
#include <gtk--/menu.h>
#include <gtk--/menuitem.h>
#include <gtk--/pixmap.h>
#include "../pixmaps/EditChar-trans-50.xpm"
#include <gtk--/button.h>
#include "../pixmaps/SchliessenIII-50.xpm"
#include <gtk--/toolbar.h>
#include <gtk--/table.h>
#include <gtk--/frame.h>

Window_werte_editieren_glade::Window_werte_editieren_glade(
) : Gtk::Window(GTK_WINDOW_TOPLEVEL)
{   Window_werte_editieren = this;
   
   Gtk::Label *label76 = manage(new class Gtk::Label("St"));
   Gtk::Adjustment *st_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   st_ein = manage(new class Gtk::SpinButton(*st_ein_adj, 1, 0));
   
   Gtk::Label *label77 = manage(new class Gtk::Label("Ge"));
   Gtk::Label *label78 = manage(new class Gtk::Label("Ko"));
   Gtk::Label *label79 = manage(new class Gtk::Label("In"));
   Gtk::Label *label80 = manage(new class Gtk::Label("Zt"));
   Gtk::Label *label81 = manage(new class Gtk::Label("Au"));
   Gtk::Label *label82 = manage(new class Gtk::Label("pA"));
   Gtk::Label *label83 = manage(new class Gtk::Label("Sb"));
   Gtk::Label *label84 = manage(new class Gtk::Label("RW"));
   Gtk::Label *label85 = manage(new class Gtk::Label("HGW"));
   Gtk::Adjustment *ge_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   ge_ein = manage(new class Gtk::SpinButton(*ge_ein_adj, 1, 0));
   
   Gtk::Adjustment *ko_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   ko_ein = manage(new class Gtk::SpinButton(*ko_ein_adj, 1, 0));
   
   Gtk::Adjustment *in_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   in_ein = manage(new class Gtk::SpinButton(*in_ein_adj, 1, 0));
   
   Gtk::Adjustment *zt_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   zt_ein = manage(new class Gtk::SpinButton(*zt_ein_adj, 1, 0));
   
   Gtk::Adjustment *au_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   au_ein = manage(new class Gtk::SpinButton(*au_ein_adj, 1, 0));
   
   Gtk::Adjustment *pa_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   pa_ein = manage(new class Gtk::SpinButton(*pa_ein_adj, 1, 0));
   
   Gtk::Adjustment *sb_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   sb_ein = manage(new class Gtk::SpinButton(*sb_ein_adj, 1, 0));
   
   Gtk::Adjustment *rw_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   rw_ein = manage(new class Gtk::SpinButton(*rw_ein_adj, 1, 0));
   
   Gtk::Adjustment *hgw_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   hgw_ein = manage(new class Gtk::SpinButton(*hgw_ein_adj, 1, 0));
   
   Gtk::Label *label86 = manage(new class Gtk::Label("B"));
   Gtk::Label *label87 = manage(new class Gtk::Label("LP"));
   Gtk::Adjustment *b_ein_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   b_ein = manage(new class Gtk::SpinButton(*b_ein_adj, 1, 0));
   
   Gtk::Adjustment *lp_ein_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   lp_ein = manage(new class Gtk::SpinButton(*lp_ein_adj, 1, 0));
   
   Gtk::Adjustment *ap_ein_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   ap_ein = manage(new class Gtk::SpinButton(*ap_ein_adj, 1, 0));
   
   Gtk::Label *label89 = manage(new class Gtk::Label("Grad"));
   Gtk::Adjustment *grad_ein_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   grad_ein = manage(new class Gtk::SpinButton(*grad_ein_adj, 1, 0));
   
   Gtk::Label *label90 = manage(new class Gtk::Label("AP"));
   Gtk::VSeparator *vseparator5 = manage(new class Gtk::VSeparator());
   Gtk::Label *label91 = manage(new class Gtk::Label("Alter"));
   Gtk::Label *label93 = manage(new class Gtk::Label("Gewicht (kg)"));
   Gtk::Label *label94 = manage(new class Gtk::Label("K�rpergr��e (cm)"));
   Gtk::Adjustment *alter_ein_adj = manage(new class Gtk::Adjustment(1, 0, 10000, 1, 10, 10));
   alter_ein = manage(new class Gtk::SpinButton(*alter_ein_adj, 1, 0));
   
   Gtk::Adjustment *gewicht_ein_adj = manage(new class Gtk::Adjustment(1, 0, 50000, 1, 10, 10));
   gewicht_ein = manage(new class Gtk::SpinButton(*gewicht_ein_adj, 1, 0));
   
   Gtk::Adjustment *groesse_ein_adj = manage(new class Gtk::Adjustment(1, 0, 10000, 1, 10, 10));
   groesse_ein = manage(new class Gtk::SpinButton(*groesse_ein_adj, 1, 0));
   
   Gtk::Label *label92 = manage(new class Gtk::Label("Gestalt"));
   gestalt_ein = manage(new class Gtk::Entry());
   
   Gtk::Label *label99 = manage(new class Gtk::Label("Spezialisierung"));
   Gtk::Label *label101 = manage(new class Gtk::Label("Herkunft"));
   Gtk::Label *label102 = manage(new class Gtk::Label("Glaube"));
   spezialisierung_ein = manage(new class Gtk::Entry());
   herkunft_ein = manage(new class Gtk::Entry());
   glaube_ein = manage(new class Gtk::Entry());
   name_spieler_ein = manage(new class Gtk::Entry());
   name_charakter_ein = manage(new class Gtk::Entry());
   
   Gtk::Label *label114 = manage(new class Gtk::Label("Name des\n"
		"Charakters"));
   Gtk::Label *label115 = manage(new class Gtk::Label("Name des\n"
		"Spielers"));
   Gtk::VSeparator *vseparator6 = manage(new class Gtk::VSeparator());
   Gtk::Label *label161 = manage(new class Gtk::Label("Boni f�r"));
   Gtk::Label *label162 = manage(new class Gtk::Label("Ausdauer"));
   Gtk::Label *label163 = manage(new class Gtk::Label("Schaden"));
   Gtk::Label *label164 = manage(new class Gtk::Label("Angriff"));
   Gtk::Label *label165 = manage(new class Gtk::Label("Abwehr"));
   Gtk::Label *label166 = manage(new class Gtk::Label("Zaubern"));
   Gtk::Label *label167 = manage(new class Gtk::Label("psyZR"));
   Gtk::Label *label168 = manage(new class Gtk::Label("phsZR"));
   Gtk::Label *label169 = manage(new class Gtk::Label("phkZR"));
   Gtk::Label *label170 = manage(new class Gtk::Label("Gift"));
   Gtk::Adjustment *bo_au_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   bo_au_ein = manage(new class Gtk::SpinButton(*bo_au_ein_adj, 1, 0));
   
   Gtk::Adjustment *bo_sc_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   bo_sc_ein = manage(new class Gtk::SpinButton(*bo_sc_ein_adj, 1, 0));
   
   Gtk::Adjustment *bo_an_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   bo_an_ein = manage(new class Gtk::SpinButton(*bo_an_ein_adj, 1, 0));
   
   Gtk::Adjustment *bo_ab_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   bo_ab_ein = manage(new class Gtk::SpinButton(*bo_ab_ein_adj, 1, 0));
   
   Gtk::Adjustment *bo_za_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   bo_za_ein = manage(new class Gtk::SpinButton(*bo_za_ein_adj, 1, 0));
   
   Gtk::Adjustment *bo_psy_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   bo_psy_ein = manage(new class Gtk::SpinButton(*bo_psy_ein_adj, 1, 0));
   
   Gtk::Adjustment *bo_phs_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   bo_phs_ein = manage(new class Gtk::SpinButton(*bo_phs_ein_adj, 1, 0));
   
   Gtk::Adjustment *bo_phk_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   bo_phk_ein = manage(new class Gtk::SpinButton(*bo_phk_ein_adj, 1, 0));
   
   Gtk::Adjustment *bo_gi_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   bo_gi_ein = manage(new class Gtk::SpinButton(*bo_gi_ein_adj, 1, 0));
   
   Gtk::Label *label100 = manage(new class Gtk::Label("Stand"));
   Gtk::HSeparator *hseparator4 = manage(new class Gtk::HSeparator());
   Gtk::Label *label171 = manage(new class Gtk::Label("KAW"));
   Gtk::Label *label172 = manage(new class Gtk::Label("WLW"));
   Gtk::Label *label173 = manage(new class Gtk::Label("LP Basis"));
   Gtk::Adjustment *lpbasis_ein_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   lpbasis_ein = manage(new class Gtk::SpinButton(*lpbasis_ein_adj, 1, 0));
   
   Gtk::Adjustment *wlw_ein_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   wlw_ein = manage(new class Gtk::SpinButton(*wlw_ein_adj, 1, 0));
   
   Gtk::Adjustment *kaw_ein_adj = manage(new class Gtk::Adjustment(1, 0, 100, 1, 10, 10));
   kaw_ein = manage(new class Gtk::SpinButton(*kaw_ein_adj, 1, 0));
   
   Gtk::VSeparator *vseparator7 = manage(new class Gtk::VSeparator());
   Gtk::HSeparator *hseparator7 = manage(new class Gtk::HSeparator());
   Gtk::HSeparator *hseparator6 = manage(new class Gtk::HSeparator());
   Gtk::HSeparator *hseparator9 = manage(new class Gtk::HSeparator());
   Gtk::HSeparator *hseparator5 = manage(new class Gtk::HSeparator());
   Gtk::Label *label174 = manage(new class Gtk::Label("Werte f�r"));
   Gtk::Label *label175 = manage(new class Gtk::Label("Abwehr"));
   Gtk::Label *label176 = manage(new class Gtk::Label("Zaubern"));
   Gtk::Label *label177 = manage(new class Gtk::Label("psyZR"));
   Gtk::Label *label178 = manage(new class Gtk::Label("phsZR"));
   Gtk::Label *label179 = manage(new class Gtk::Label("phkZR"));
   Gtk::Label *label180 = manage(new class Gtk::Label("Gift"));
   Gtk::Adjustment *gift_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   gift_ein = manage(new class Gtk::SpinButton(*gift_ein_adj, 1, 0));
   
   Gtk::Adjustment *phkZR_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   phkZR_ein = manage(new class Gtk::SpinButton(*phkZR_ein_adj, 1, 0));
   
   Gtk::Adjustment *phsZR_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   phsZR_ein = manage(new class Gtk::SpinButton(*phsZR_ein_adj, 1, 0));
   
   Gtk::Adjustment *psyZR_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   psyZR_ein = manage(new class Gtk::SpinButton(*psyZR_ein_adj, 1, 0));
   
   Gtk::Adjustment *zaubern_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   zaubern_ein = manage(new class Gtk::SpinButton(*zaubern_ein_adj, 1, 0));
   
   Gtk::Adjustment *abwehr_ein_adj = manage(new class Gtk::Adjustment(1, 0, 200, 1, 10, 10));
   abwehr_ein = manage(new class Gtk::SpinButton(*abwehr_ein_adj, 1, 0));
   
   Gtk::Label *label249 = manage(new class Gtk::Label("GFP"));
   Gtk::Adjustment *gfp_ein_adj = manage(new class Gtk::Adjustment(0, 0, 100000, 1, 10, 10));
   gfp_ein = manage(new class Gtk::SpinButton(*gfp_ein_adj, 1, 0));
   
   Gtk::Label *label250 = manage(new class Gtk::Label("Version"));
   version_ein = manage(new class Gtk::Entry());
   optionmenu_stand = manage(new class Gtk::OptionMenu());
   
   Gtk::Pixmap *pixmap25 = manage(new class Gtk::Pixmap(EditChar_trans_50_xpm));
   Gtk::Toolbar *toolbar18 = manage(new class Gtk::Toolbar(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS));
   Gtk::Button *button47 = Gtk::wrap((GtkButton*)gtk_toolbar_append_element(GTK_TOOLBAR(toolbar18->gtkobj()), GTK_TOOLBAR_CHILD_BUTTON, 0, "", 0, 0, GTK_WIDGET(manage(new Gtk::Pixmap(SchliessenIII_50_xpm))->gtkobj()), 0, 0));
   Gtk::Table *table3 = manage(new class Gtk::Table(19, 11, false));
   Gtk::Frame *frame13 = manage(new class Gtk::Frame("Werte editieren"));
   label76->set_alignment(0.5, 0.5);
   label76->set_padding(0, 0);
   st_ein->set_editable(true);
   label77->set_alignment(0.5, 0.5);
   label77->set_padding(0, 0);
   label78->set_alignment(0.5, 0.5);
   label78->set_padding(0, 0);
   label79->set_alignment(0.5, 0.5);
   label79->set_padding(0, 0);
   label80->set_alignment(0.5, 0.5);
   label80->set_padding(0, 0);
   label81->set_alignment(0.5, 0.5);
   label81->set_padding(0, 0);
   label82->set_alignment(0.5, 0.5);
   label82->set_padding(0, 0);
   label83->set_alignment(0.5, 0.5);
   label83->set_padding(0, 0);
   label84->set_alignment(0.5, 0.5);
   label84->set_padding(0, 0);
   label85->set_alignment(0.5, 0.5);
   label85->set_padding(0, 0);
   ge_ein->set_editable(true);
   ko_ein->set_editable(true);
   in_ein->set_editable(true);
   zt_ein->set_editable(true);
   au_ein->set_editable(true);
   pa_ein->set_editable(true);
   sb_ein->set_editable(true);
   rw_ein->set_editable(true);
   hgw_ein->set_editable(true);
   label86->set_alignment(0.5, 0.5);
   label86->set_padding(0, 0);
   label87->set_alignment(0.5, 0.5);
   label87->set_padding(0, 0);
   b_ein->set_editable(true);
   lp_ein->set_editable(true);
   ap_ein->set_editable(true);
   label89->set_alignment(0.5, 0.5);
   label89->set_padding(0, 0);
   grad_ein->set_editable(true);
   label90->set_alignment(0.5, 0.5);
   label90->set_padding(0, 0);
   label91->set_alignment(0.5, 0.5);
   label91->set_padding(0, 0);
   label93->set_alignment(0.5, 0.5);
   label93->set_padding(0, 0);
   label94->set_alignment(0.5, 0.5);
   label94->set_padding(0, 0);
   alter_ein->set_editable(true);
   gewicht_ein->set_editable(true);
   groesse_ein->set_editable(true);
   label92->set_alignment(0.5, 0.5);
   label92->set_padding(0, 0);
   gestalt_ein->set_editable(true);
   label99->set_alignment(0.5, 0.5);
   label99->set_padding(0, 0);
   label101->set_alignment(0.5, 0.5);
   label101->set_padding(0, 0);
   label102->set_alignment(0.5, 0.5);
   label102->set_padding(0, 0);
   spezialisierung_ein->set_editable(true);
   herkunft_ein->set_editable(true);
   glaube_ein->set_editable(true);
   name_spieler_ein->set_editable(true);
   name_charakter_ein->set_editable(true);
   label114->set_alignment(0.5, 0.5);
   label114->set_padding(0, 0);
   label115->set_alignment(0.5, 0.5);
   label115->set_padding(0, 0);
   label161->set_alignment(0.5, 0.5);
   label161->set_padding(0, 0);
   label162->set_alignment(0.5, 0.5);
   label162->set_padding(0, 0);
   label163->set_alignment(0.5, 0.5);
   label163->set_padding(0, 0);
   label164->set_alignment(0.5, 0.5);
   label164->set_padding(0, 0);
   label165->set_alignment(0.5, 0.5);
   label165->set_padding(0, 0);
   label166->set_alignment(0.5, 0.5);
   label166->set_padding(0, 0);
   label167->set_alignment(0.5, 0.5);
   label167->set_padding(0, 0);
   label168->set_alignment(0.5, 0.5);
   label168->set_padding(0, 0);
   label169->set_alignment(0.5, 0.5);
   label169->set_padding(0, 0);
   label170->set_alignment(0.5, 0.5);
   label170->set_padding(0, 0);
   bo_au_ein->set_editable(true);
   bo_sc_ein->set_editable(true);
   bo_an_ein->set_editable(true);
   bo_ab_ein->set_editable(true);
   bo_za_ein->set_editable(true);
   bo_psy_ein->set_editable(true);
   bo_phs_ein->set_editable(true);
   bo_phk_ein->set_editable(true);
   bo_gi_ein->set_editable(true);
   label100->set_alignment(0.5, 0.5);
   label100->set_padding(0, 0);
   label171->set_alignment(0.5, 0.5);
   label171->set_padding(0, 0);
   label172->set_alignment(0.5, 0.5);
   label172->set_padding(0, 0);
   label173->set_alignment(0.5, 0.5);
   label173->set_padding(0, 0);
   lpbasis_ein->set_editable(true);
   wlw_ein->set_editable(true);
   kaw_ein->set_editable(true);
   label174->set_alignment(0.5, 0.5);
   label174->set_padding(0, 0);
   label175->set_alignment(0.5, 0.5);
   label175->set_padding(0, 0);
   label176->set_alignment(0.5, 0.5);
   label176->set_padding(0, 0);
   label177->set_alignment(0.5, 0.5);
   label177->set_padding(0, 0);
   label178->set_alignment(0.5, 0.5);
   label178->set_padding(0, 0);
   label179->set_alignment(0.5, 0.5);
   label179->set_padding(0, 0);
   label180->set_alignment(0.5, 0.5);
   label180->set_padding(0, 0);
   gift_ein->set_editable(true);
   phkZR_ein->set_editable(true);
   phsZR_ein->set_editable(true);
   psyZR_ein->set_editable(true);
   zaubern_ein->set_editable(true);
   abwehr_ein->set_editable(true);
   label249->set_alignment(0, 0.5);
   label249->set_padding(0, 0);
   gfp_ein->set_editable(true);
   label250->set_alignment(0, 0.5);
   label250->set_padding(0, 0);
   version_ein->set_editable(true);
   {   
      
      Gtk::Menu *_m(manage(new Gtk::Menu()));
      Gtk::MenuItem *_mi;
      _mi = manage(new Gtk::MenuItem("STAND"));
      _m->append(*_mi);
      _mi->show();
      _mi->set_user_data((gpointer)0);
      _mi = manage(new Gtk::MenuItem("Unfrei"));
      _m->append(*_mi);
      _mi->show();
      _mi->set_user_data((gpointer)1);
      _mi = manage(new Gtk::MenuItem("Volk"));
      _m->append(*_mi);
      _mi->show();
      _mi->set_user_data((gpointer)2);
      _mi = manage(new Gtk::MenuItem("Mittelschicht"));
      _m->append(*_mi);
      _mi->show();
      _mi->set_user_data((gpointer)3);
      _mi = manage(new Gtk::MenuItem("Adel"));
      _m->append(*_mi);
      _mi->show();
      _mi->set_user_data((gpointer)4);
      optionmenu_stand->set_menu(*_m);
      optionmenu_stand->set_history(0);
   }
   pixmap25->set_alignment(0.5, 0.5);
   pixmap25->set_padding(0, 0);
   toolbar18->set_border_width(5);
   toolbar18->set_space_size(5);
   toolbar18->set_tooltips(true);
   table3->attach(*label76, 0, 1, 2, 3, 0, 0, 0, 0);
   table3->attach(*st_ein, 1, 2, 2, 3, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*label77, 0, 1, 3, 4, 0, 0, 0, 0);
   table3->attach(*label78, 0, 1, 4, 5, 0, 0, 0, 0);
   table3->attach(*label79, 0, 1, 5, 6, 0, 0, 0, 0);
   table3->attach(*label80, 0, 1, 6, 7, 0, 0, 0, 0);
   table3->attach(*label81, 0, 1, 8, 9, 0, 0, 0, 0);
   table3->attach(*label82, 0, 1, 9, 10, 0, 0, 0, 0);
   table3->attach(*label83, 0, 1, 10, 11, 0, 0, 0, 0);
   table3->attach(*label84, 0, 1, 11, 12, 0, 0, 0, 0);
   table3->attach(*label85, 0, 1, 12, 13, 0, 0, 0, 0);
   table3->attach(*ge_ein, 1, 2, 3, 4, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*ko_ein, 1, 2, 4, 5, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*in_ein, 1, 2, 5, 6, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*zt_ein, 1, 2, 6, 7, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*au_ein, 1, 2, 8, 9, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*pa_ein, 1, 2, 9, 10, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*sb_ein, 1, 2, 10, 11, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*rw_ein, 1, 2, 11, 12, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*hgw_ein, 1, 2, 12, 13, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*label86, 0, 1, 14, 15, 0, 0, 0, 0);
   table3->attach(*label87, 0, 1, 15, 16, 0, 0, 0, 0);
   table3->attach(*b_ein, 1, 2, 14, 15, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*lp_ein, 1, 2, 15, 16, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*ap_ein, 1, 2, 16, 17, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*label89, 0, 1, 0, 1, 0, 0, 0, 0);
   table3->attach(*grad_ein, 1, 2, 0, 1, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*label90, 0, 1, 16, 17, 0, 0, 0, 0);
   table3->attach(*vseparator5, 2, 3, 0, 18, GTK_FILL, GTK_FILL, 0, 0);
   table3->attach(*label91, 9, 10, 0, 1, 0, 0, 0, 0);
   table3->attach(*label93, 9, 10, 2, 3, 0, 0, 0, 0);
   table3->attach(*label94, 9, 10, 3, 4, 0, 0, 0, 0);
   table3->attach(*alter_ein, 10, 11, 0, 1, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*gewicht_ein, 10, 11, 2, 3, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*groesse_ein, 10, 11, 3, 4, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*label92, 9, 10, 4, 5, 0, 0, 0, 0);
   table3->attach(*gestalt_ein, 10, 11, 4, 5, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*label99, 9, 10, 8, 9, 0, 0, 0, 0);
   table3->attach(*label101, 9, 10, 10, 11, 0, 0, 0, 0);
   table3->attach(*label102, 9, 10, 11, 12, 0, 0, 0, 0);
   table3->attach(*spezialisierung_ein, 10, 11, 8, 9, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*herkunft_ein, 10, 11, 10, 11, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*glaube_ein, 10, 11, 11, 12, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*name_spieler_ein, 10, 11, 15, 16, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*name_charakter_ein, 10, 11, 14, 15, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*label114, 9, 10, 14, 15, 0, 0, 0, 0);
   table3->attach(*label115, 9, 10, 15, 16, 0, 0, 0, 0);
   table3->attach(*vseparator6, 5, 6, 0, 17, GTK_FILL, GTK_FILL, 0, 0);
   table3->attach(*label161, 3, 5, 0, 1, 0, 0, 0, 0);
   table3->attach(*label162, 3, 4, 2, 3, 0, 0, 0, 0);
   table3->attach(*label163, 3, 4, 3, 4, 0, 0, 0, 0);
   table3->attach(*label164, 3, 4, 4, 5, 0, 0, 0, 0);
   table3->attach(*label165, 3, 4, 5, 6, 0, 0, 0, 0);
   table3->attach(*label166, 3, 4, 6, 7, 0, 0, 0, 0);
   table3->attach(*label167, 3, 4, 8, 9, 0, 0, 0, 0);
   table3->attach(*label168, 3, 4, 9, 10, 0, 0, 0, 0);
   table3->attach(*label169, 3, 4, 10, 11, 0, 0, 0, 0);
   table3->attach(*label170, 3, 4, 11, 12, 0, 0, 0, 0);
   table3->attach(*bo_au_ein, 4, 5, 2, 3, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*bo_sc_ein, 4, 5, 3, 4, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*bo_an_ein, 4, 5, 4, 5, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*bo_ab_ein, 4, 5, 5, 6, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*bo_za_ein, 4, 5, 6, 7, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*bo_psy_ein, 4, 5, 8, 9, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*bo_phs_ein, 4, 5, 9, 10, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*bo_phk_ein, 4, 5, 10, 11, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*bo_gi_ein, 4, 5, 11, 12, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*label100, 9, 10, 9, 10, 0, 0, 0, 0);
   table3->attach(*hseparator4, 0, 2, 7, 8, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table3->attach(*label171, 3, 4, 14, 15, 0, 0, 0, 0);
   table3->attach(*label172, 3, 4, 15, 16, 0, 0, 0, 0);
   table3->attach(*label173, 3, 4, 16, 17, 0, 0, 0, 0);
   table3->attach(*lpbasis_ein, 4, 5, 16, 17, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*wlw_ein, 4, 5, 15, 16, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*kaw_ein, 4, 5, 14, 15, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*vseparator7, 8, 9, 0, 17, GTK_EXPAND|GTK_FILL, GTK_FILL, 0, 0);
   table3->attach(*hseparator7, 0, 11, 17, 18, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table3->attach(*hseparator6, 0, 11, 1, 2, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table3->attach(*hseparator9, 9, 11, 7, 8, GTK_FILL, GTK_FILL, 0, 0);
   table3->attach(*hseparator5, 0, 11, 13, 14, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
   table3->attach(*label174, 6, 8, 0, 1, 0, 0, 0, 0);
   table3->attach(*label175, 6, 7, 2, 3, 0, 0, 0, 0);
   table3->attach(*label176, 6, 7, 3, 4, 0, 0, 0, 0);
   table3->attach(*label177, 6, 7, 8, 9, 0, 0, 0, 0);
   table3->attach(*label178, 6, 7, 9, 10, 0, 0, 0, 0);
   table3->attach(*label179, 6, 7, 10, 11, 0, 0, 0, 0);
   table3->attach(*label180, 6, 7, 11, 12, 0, 0, 0, 0);
   table3->attach(*gift_ein, 7, 8, 11, 12, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*phkZR_ein, 7, 8, 10, 11, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*phsZR_ein, 7, 8, 9, 10, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*psyZR_ein, 7, 8, 8, 9, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*zaubern_ein, 7, 8, 3, 4, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*abwehr_ein, 7, 8, 2, 3, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*label249, 6, 7, 14, 15, GTK_FILL, 0, 0, 0);
   table3->attach(*gfp_ein, 7, 8, 14, 15, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*label250, 9, 10, 16, 17, GTK_FILL, 0, 0, 0);
   table3->attach(*version_ein, 10, 11, 16, 17, GTK_EXPAND|GTK_FILL, 0, 0, 0);
   table3->attach(*optionmenu_stand, 10, 11, 9, 10, GTK_FILL, 0, 0, 0);
   table3->attach(*pixmap25, 6, 8, 5, 8, GTK_FILL, GTK_FILL, 0, 0);
   table3->attach(*toolbar18, 10, 11, 18, 19, 0, 0, 0, 0);
   frame13->set_label_align(0, 0);
   frame13->set_shadow_type(GTK_SHADOW_ETCHED_IN);
   frame13->add(*table3);
   Window_werte_editieren->set_title("Werte editieren");
   Window_werte_editieren->add(*frame13);
   label76->show();
   st_ein->show();
   label77->show();
   label78->show();
   label79->show();
   label80->show();
   label81->show();
   label82->show();
   label83->show();
   label84->show();
   label85->show();
   ge_ein->show();
   ko_ein->show();
   in_ein->show();
   zt_ein->show();
   au_ein->show();
   pa_ein->show();
   sb_ein->show();
   rw_ein->show();
   hgw_ein->show();
   label86->show();
   label87->show();
   b_ein->show();
   lp_ein->show();
   ap_ein->show();
   label89->show();
   grad_ein->show();
   label90->show();
   vseparator5->show();
   label91->show();
   label93->show();
   label94->show();
   alter_ein->show();
   gewicht_ein->show();
   groesse_ein->show();
   label92->show();
   gestalt_ein->show();
   label99->show();
   label101->show();
   label102->show();
   spezialisierung_ein->show();
   herkunft_ein->show();
   glaube_ein->show();
   name_spieler_ein->show();
   name_charakter_ein->show();
   label114->show();
   label115->show();
   vseparator6->show();
   label161->show();
   label162->show();
   label163->show();
   label164->show();
   label165->show();
   label166->show();
   label167->show();
   label168->show();
   label169->show();
   label170->show();
   bo_au_ein->show();
   bo_sc_ein->show();
   bo_an_ein->show();
   bo_ab_ein->show();
   bo_za_ein->show();
   bo_psy_ein->show();
   bo_phs_ein->show();
   bo_phk_ein->show();
   bo_gi_ein->show();
   label100->show();
   hseparator4->show();
   label171->show();
   label172->show();
   label173->show();
   lpbasis_ein->show();
   wlw_ein->show();
   kaw_ein->show();
   vseparator7->show();
   hseparator7->show();
   hseparator6->show();
   hseparator9->show();
   hseparator5->show();
   label174->show();
   label175->show();
   label176->show();
   label177->show();
   label178->show();
   label179->show();
   label180->show();
   gift_ein->show();
   phkZR_ein->show();
   phsZR_ein->show();
   psyZR_ein->show();
   zaubern_ein->show();
   abwehr_ein->show();
   label249->show();
   gfp_ein->show();
   label250->show();
   version_ein->show();
   optionmenu_stand->show();
   pixmap25->show();
   toolbar18->show();
   table3->show();
   frame13->show();
   Window_werte_editieren->show();
   st_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   ge_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   ko_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   in_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   zt_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   au_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   pa_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   sb_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   rw_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   hgw_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   b_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   lp_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   ap_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   grad_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   alter_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   gewicht_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   groesse_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   gestalt_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   spezialisierung_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   herkunft_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   glaube_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   name_spieler_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   name_charakter_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   bo_au_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   bo_sc_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   bo_an_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   bo_ab_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   bo_za_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   bo_psy_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   bo_phs_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   bo_phk_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   bo_gi_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   lpbasis_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   wlw_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   kaw_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   gift_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   phkZR_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   phsZR_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   psyZR_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   zaubern_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   abwehr_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   gfp_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   version_ein->activate.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
   button47->clicked.connect(SigC::slot(static_cast<class Window_werte_editieren*>(this), &Window_werte_editieren::on_nwe_close_clicked));
}

Window_werte_editieren_glade::~Window_werte_editieren_glade()
{   
}
