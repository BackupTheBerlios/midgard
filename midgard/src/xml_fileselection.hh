/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2002 Christof Petig
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

#ifndef _XML_FILESELECTION_HH
#  ifndef __MINGW32__
#    include "xml_fileselection_glade.hh"
#  endif
#  define _XML_FILESELECTION_HH

class midgard_CG;
class VAbenteurer;
#ifdef __MINGW32__
#include <string>
#endif

class xml_fileselection 
#ifndef __MINGW32__
			: public xml_fileselection_glade
#endif
{   
  public:
        enum eAction {Save,Load,Export,Pix,html,temp,speichern,pdfviewer};
  private:
        midgard_CG* hauptfenster;        
        eAction ewas;
        VAbenteurer &VA;

#ifndef __MINGW32__        
        friend class xml_fileselection_glade;
        void on_cancel_button1_clicked();
#else
	std::string filename;
	std::string get_filename() const { return filename; }
	void set_filename(const std::string &s) { filename=s; }
#endif        
        void on_ok_button1_clicked();
   public:
        xml_fileselection(midgard_CG* h,eAction _was);
};
#endif
