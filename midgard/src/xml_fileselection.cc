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

#include "config.h"
#include "xml_fileselection.hh"
#include <WinFileReq.hh>
#include <midgard_CG.hh>
#include <Windows_Linux.hh>
#include <libmagus/Ausgabe.hh>
#include <libmagus/spielleiter_export.hh>
#include <libmagus/magus_paths.h>

void xml_fileselection::on_ok_button1_clicked(const std::string &filename)
{  if (!filename.empty()) // this means cancel was clicked
   {try{
     if (ewas==Load)
       hauptfenster->xml_import(filename);
     else if (ewas==Save)
     { hauptfenster->xml_export(filename);
     }
     else if (ewas==Export)
       spielleiter_export_save(hauptfenster->getAben(),filename);
     else if (ewas==ExportFull)
       spielleiter_export_save(hauptfenster->getAben(),filename,true); 
#warning hier fehlts   
#if 0   
     else if (ewas==Pix)
       {
        VA->setBeschreibungPix(filename);
        hauptfenster->table_beschreibung->init(hauptfenster);
       }
     else if (ewas==html)
       hauptfenster->table_optionen->html_browser_selected(filename);
     else if (ewas==temp)
       hauptfenster->table_optionen->tmp_selected(filename);
     else if (ewas==speichern)
       hauptfenster->table_optionen->speicherplatz_selected(filename);
     else if (ewas==pdfviewer)
       hauptfenster->table_optionen->frame_drucken->pdf_viewer_selected(filename);
#endif   
    }catch(std::exception &e) {Ausgabe(Ausgabe::Error,e.what());}
  }
#ifndef __MINGW32__  
  Glib::signal_idle().connect(SigC::slot(*this,&xml_fileselection::idle_delete));
#endif  
}

std::string xml_fileselection::defFileName(const std::string &s)
{  std::string res;
   for (std::string::const_iterator i=s.begin();i!=s.end();++i)
      if (('0' <= *i && *i <= '9') || ('A' <= *i && *i <= 'Z')
      	|| ('a' <= *i && *i <= 'z') || *i=='_')
      	 res+=*i;
   return res;
}

// den aktuellen Abenteurer zu übergeben wäre deutlich sinnvoller! CP

// die members werden zu spät initialisiert, da der callback schon im ctor
// des parents aufgerufen werden kann (Win32) ... ???

// ein cancel callback wäre notwendig um dieses Objekt zu zerstören
xml_fileselection::xml_fileselection(midgard_CG* h, eAction _was)
: 
    hauptfenster(h),ewas(_was),VA(hauptfenster->getChar())
{
 std::string path=Programmoptionen->getString(Magus_Optionen::speicherpfad);
 std::string fname=path;

 // path mit / (oder \) beenden, damit der Dateiname einfach dahinter kann
 if (!path.empty() && path[path.size()-1]!=WinLux::dirsep) 
    path+=WinLux::dirsep;

 if(ewas==Pix) 
 {  fname=VA->getAbenteurer().BeschreibungPix();
    if (fname.empty()) fname=path;
 }
 else if (ewas==Save) 
 {  fname=VA->getFilename();
    if (fname.empty()) 
       fname=path+defFileName(VA->getAbenteurer().Name_Abenteurer())+".magus";
#ifdef __MINGW32__
    magus_paths::register_magus();
#endif 
 }
 else if (ewas==Load) 
 {  // path is ok
 }
 else if (ewas==Export) 
 {  fname=path+defFileName(VA->getAbenteurer().Name_Abenteurer())+".txt";
 }
// set_filename(fname);
 
 Ausgabe(Ausgabe::Debug,"Dateiname " +fname);
 
   // TODO was ist mit '\\' am Ende ?
   // TODO path erzeugen?
   const char *filter=0;
   if (ewas==Export) filter = "Textdateien (*.txt)\0*.txt\0Alle Dateien (*.*)\0*.*\0";
   else if (ewas==Pix) filter = "Bilder (*.png,*.jpg,*.tif)\0*.png;*.jpg;*.tif\0Alle Dateien (*.*)\0*.*\0";
   else filter = "Midgard Abenteurer (*.magus)\0*.magus\0Alle Dateien (*.*)\0*.*\0";
   
   const char *extension= ewas==Export ? "txt" : ewas==Pix ? "" : "magus";
   const char *title = ewas==Export ? "Abenteurer exportieren" :
   		ewas==Pix ? "Bild einfügen" :
   		ewas==Load ? "Abenteurer laden" : "Abenteurer speichern";
   const bool pass_cancel=
#ifdef __MINGW32__
        false
#else
        true
#endif
              ;

  WinFileReq::create(SigC::slot(*this,&xml_fileselection::on_ok_button1_clicked),
        fname,filter,extension,title,(ewas==Pix||ewas==Load),h,pass_cancel);
}

void xml_fileselection::create(midgard_CG* h, eAction _was)
{  // deletes itself after use (during idle)
   (void)
#ifndef __MINGW32__
     new 
#endif
       xml_fileselection(h,_was);
}

bool xml_fileselection::idle_delete()
{  delete this;
   return false;
}
