/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2002-2004 Christof Petig
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
#  define _XML_FILESELECTION_HH

// #  include "WinFileReq.hh"

class midgard_CG;
class AbenteurerAuswahl;
class WinFileReq;

#include <string>
#include <sigc++/object.h>

class xml_fileselection : public SigC::Object
{   
  public:
        enum eAction {Save,Load,Export,ExportFull,
                      Pix,html,temp,speichern,pdfviewer};
  private:
        midgard_CG* hauptfenster;        
        eAction ewas;
        AbenteurerAuswahl &VA;
        WinFileReq *reqwin;

        void on_ok_button1_clicked(const std::string &);
        bool idle_delete();
   public:
        xml_fileselection(midgard_CG* h,eAction _was);
        static void create(midgard_CG* h,eAction _was);
        
        // utility function to omit all nonalphanumeric characters
        static std::string defFileName(const std::string &s);
};
#endif
