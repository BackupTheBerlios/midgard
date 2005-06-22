/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2004-2005 Christof Petig
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
        void on_button_pdf_browser_clicked();
        void pdf_viewer_selected(const std::string& dateiname);
};
#endif
