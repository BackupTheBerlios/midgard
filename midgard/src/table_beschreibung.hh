// generated 2002/5/13 20:46:12 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_beschreibung.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _TABLE_BESCHREIBUNG_HH
#  include "table_beschreibung_glade.hh"
#  define _TABLE_BESCHREIBUNG_HH

class midgard_CG;

class table_beschreibung : public table_beschreibung_glade
{  
        
        friend class table_beschreibung_glade;
        midgard_CG *hauptfenster;
public:
        
        table_beschreibung(GlademmData *_data) : table_beschreibung_glade(_data)
        {}
        void init(midgard_CG *hauptfenster);
private:
        void show_beschreibung();        
        gint on_text_charakter_beschreibung_focus_out_event(GdkEventFocus *ev);
        void on_button_beschreibung_drucken_clicked();
        void on_button_grafik_clicked();
        gint on_spinbutton_pix_breite_focus_out_event(GdkEventFocus *ev);
        gint on_spinbutton_pix_breite_focus_in_event(GdkEventFocus *ev);
};
#endif
