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
// newer (non customized) versions of this file go to xml-fileselection.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "xml_fileselection.hh"
#include "midgard_CG.hh"

void xml_fileselection::on_ok_button1_clicked()
{   
 if (ewas==Load)
   hauptfenster->xml_import(this->get_filename());
 else if (ewas==Save)
   hauptfenster->xml_export(this->get_filename());
 else if (ewas==Export)
   hauptfenster->spielleiter_export_save(this->get_filename());
 else if (ewas==Pix)
  {
    Grundwerte W=hauptfenster->getWerte();
    W.setBeschreibungPix(this->get_filename());
    hauptfenster->show_beschreibung();
  }
 destroy();
}

void xml_fileselection::on_cancel_button1_clicked()
{   
  destroy();
}

xml_fileselection::xml_fileselection(midgard_CG* h, eAction _was)
: hauptfenster(h),ewas(_was)
{
 if(ewas==Pix) set_filename(hauptfenster->getWerte().BeschreibungPix());
}
