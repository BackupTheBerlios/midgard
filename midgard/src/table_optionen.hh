// generated 2002/4/16 8:33:14 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_optionen.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _TABLE_OPTIONEN_HH
#  include "table_optionen_glade.hh"
#  define _TABLE_OPTIONEN_HH
class table_optionen : public table_optionen_glade
{  
        
        friend class table_optionen_glade;
        friend class xml_fileselection;
        midgard_CG *hauptfenster;
public:
        
        table_optionen(GlademmData *_data) : table_optionen_glade(_data)
        {  
        }
        void set_Hauptfenster(midgard_CG *h); 
        void init();        
private:
        void on_entry_html_changed();
        void on_entry_tmp_verz_changed();
        void on_entry_speicher_verz_changed();
        void on_spinbutton_datei_history_changed();

        void on_button_html_browser_clicked();
        void html_browser_selected(const std::string& dateiname);
        void on_button_tmp_clicked();
        void tmp_selected(const std::string& dateiname);
        void on_button_speicherplatz_clicked();
        void speicherplatz_selected(const std::string& dateiname);
};
#endif
