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

#include "config.h"
#include "xml_fileselection.hh"
#include "midgard_CG.hh"

#ifdef __MINGW32__
# include <windows.h>
# include <commdlg.h>
#include <gdk/gdkwin32.h>
#endif

void xml_fileselection::on_ok_button1_clicked()
{   
try{
 if (ewas==Load)
   hauptfenster->xml_import(this->get_filename());
 else if (ewas==Save)
   hauptfenster->xml_export(this->get_filename());
 else if (ewas==Export)
   hauptfenster->spielleiter_export_save(this->get_filename());
 else if (ewas==Pix)
  {
    assert(Werte!=0);
    Werte->setBeschreibungPix(this->get_filename());
  }
#ifndef __MINGW32__  
 destroy();
#endif
}catch(std::exception &e) {cerr<<e.what()<<'\n';}
}

#ifndef __MINGW32__  
void xml_fileselection::on_cancel_button1_clicked()
{   
  destroy();
}
#endif

xml_fileselection::xml_fileselection(midgard_CG* h, eAction _was, Grundwerte *W)
: hauptfenster(h),ewas(_was),Werte(W)
{
 std::string path=hauptfenster->getOptionen()->getString(Midgard_Optionen::speicherpfad);
 if(ewas==Pix) set_filename(hauptfenster->getWerte().BeschreibungPix());
 else if (ewas==Save) set_filename(path+hauptfenster->Char.getFilename());
 else if (ewas==Load) set_filename(path);
 else if (ewas==Export) set_filename(path);
 
#ifdef __MINGW32__
std::cout << "Dateiname " << filename << '\n';
   OPENFILENAME ofn;
   char buf[10240];

   strncpy(buf,filename.c_str(),sizeof buf);

   ZeroMemory(&ofn, sizeof (OPENFILENAME));
   ofn.lStructSize = sizeof (OPENFILENAME);
   		// (GTK_WIDGET(h->gtkobj())->window )
//   ofn.hwndOwner = GDK_DRAWABLE_XID(h->get_window()->gdkobj()); 
		// GDK_WINDOW_HWND (win) 2.0
   ofn.lpstrFile = buf;
   ofn.nMaxFile = sizeof buf;
   if (ewas==Export) ofn.lpstrFilter = "Alle Dateien\0*.*\0Textdateien\0*.txt\0";
   else if (ewas==Pix) ofn.lpstrFilter = "Alle Dateien\0*.*\0Bilder\0*.png;*.jpg;*.tif\0";
   else ofn.lpstrFilter = "Alle Dateien\0*.*\0Midgard Abenteurer\0*.magus\0";
   ofn.nFilterIndex = 2;
   ofn.lpstrDefExt= ewas==Export ? "txt" : ewas==Pix ? "" : "magus";
   ofn.lpstrTitle = ewas==Export ? "Abenteurer exportieren" :
   		ewas==Pix ? "Bild einf�gen" :
   		ewas==Load ? "Abenteurer laden" : "Abenteurer speichern";
   ofn.Flags = OFN_PATHMUSTEXIST 
   		| (ewas==Pix||ewas==Load ? OFN_FILEMUSTEXIST : 0);

   bool res=false;
   if (ewas==Pix||ewas==Load) res=GetOpenFileName(&ofn);
   else res=GetSaveFileName(&ofn);
   
   if (res) 
   {  set_filename(buf);
      on_ok_button1_clicked();
   }

#endif
}
