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

// generated 2001/5/24 12:36:04 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to xml-fileselection.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _XML_FILESELECTION_HH
#  include "xml_fileselection_glade.hh"
#  define _XML_FILESELECTION_HH
#include "glademm_support.hh"

class midgard_CG;
class Grundwerte;

class xml_fileselection : public xml_fileselection_glade
{   
  public:
        enum eAction {Save,Load,Export,Pix};
  private:
        midgard_CG* hauptfenster;        
        eAction ewas;
        Grundwerte* Werte;
        
        friend class xml_fileselection_glade;
        void on_ok_button1_clicked();
        void on_cancel_button1_clicked();
   public:
        xml_fileselection(midgard_CG* h,eAction _was,Grundwerte *W=0);
};
#endif
