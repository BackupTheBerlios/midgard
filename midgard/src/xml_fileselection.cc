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
#include "Windows_Linux.hh"

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
 { hauptfenster->xml_export(this->get_filename());
 }
 else if (ewas==Export)
   hauptfenster->spielleiter_export_save(this->get_filename(),false);
 else if (ewas==ExportFull)
   hauptfenster->spielleiter_export_save(this->get_filename(),true); 
 else if (ewas==Pix)
   {
    VA->getWerte().setBeschreibungPix(this->get_filename());
    hauptfenster->table_beschreibung->init(hauptfenster);
   }
 else if (ewas==html)
   hauptfenster->table_optionen->html_browser_selected(this->get_filename());
 else if (ewas==temp)
   hauptfenster->table_optionen->tmp_selected(this->get_filename());
 else if (ewas==speichern)
   hauptfenster->table_optionen->speicherplatz_selected(this->get_filename());
 else if (ewas==pdfviewer)
   hauptfenster->table_optionen->frame_drucken->pdf_viewer_selected(this->get_filename());
 delete this;
}catch(std::exception &e) {std::cerr<<e.what()<<'\n';}
}

#ifndef __MINGW32__  
void xml_fileselection::on_cancel_button1_clicked()
{   
  delete this;
}
#endif

static std::string defFileName(const std::string &s)
{  std::string res;
   for (std::string::const_iterator i=s.begin();i!=s.end();++i)
      if (('0' <= *i && *i <= '9') || ('A' <= *i && *i <= 'Z')
      	|| ('a' <= *i && *i <= 'z') || *i=='_')
      	 res+=*i;
   return res;
}

#ifdef __MINGW32__
#include "registry.h"

static void register_magus(const std::string &argv0)
{  reg_key cl(HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE", "Classes",0);
   char buf[10240];
   
   reg_key magusf(cl.get_key(), KEY_ALL_ACCESS, "magusfile",0);
   if (magusf.get_string(0,buf,sizeof buf,"")!=ERROR_SUCCESS || !*buf)
   {  magusf.set_string(0,"Midgard Abenteurer");
      magusf.set_int("EditFlags",0);
   }
   
   reg_key maguscmd(magusf.get_key(), KEY_ALL_ACCESS, "Shell", "Magus", "command", 0);
   std::string command="\""+argv0+"\" %1";
   if (maguscmd.get_string(0,buf,sizeof buf,"")!=ERROR_SUCCESS || buf!=command)
      maguscmd.set_string(0,command.c_str());
   
   reg_key magusicon(magusf.get_key(), KEY_ALL_ACCESS, "DefaultIcon", 0);
   if (magusicon.get_string(0,buf,sizeof buf,"")!=ERROR_SUCCESS || buf!=argv0+",0")
      magusicon.set_string(0,(argv0+",0").c_str());
   
   reg_key magusextension(cl.get_key(), KEY_ALL_ACCESS, ".magus", 0);
   if (magusextension.get_string(0,buf,sizeof buf,"")!=ERROR_SUCCESS || buf!="magusfile")
      magusextension.set_string(0,"magusfile");
}

#endif

#if 0 // Dateien mit magus verknüpfen
+[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\magusfile]
+@="Midgard Abenteurer"
+"EditFlags"=hex:00,00,00,00
+
+[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\magusfile\Shell]
+@=""
+
+[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\magusfile\Shell\Magus]
+
+[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\magusfile\Shell\Magus\command]
+@="E:\\magus\\magus2.exe %1"
+
+[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\magusfile\DefaultIcon]
+@="E:\\magus\\magus2.exe,0"
+
+[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\.magus]
+@="magusfile"
+
#endif

// den aktuellen Abenteurer zu übergeben wäre deutlich sinnvoller! CP
xml_fileselection::xml_fileselection(midgard_CG* h, eAction _was)
: hauptfenster(h),ewas(_was),VA(hauptfenster->getChar())
{
 std::string path=hauptfenster->getOptionen()->getString(Magus_Optionen::speicherpfad);
 std::string fname=path;

 // path mit / (oder \) beenden, damit der Dateiname einfach dahinter kann
 if (!path.empty() && path[path.size()-1]!=WinLux::dirsep) 
    path+=WinLux::dirsep;
 if(ewas==Pix) 
 {  fname=VA->getWerte().BeschreibungPix();
    if (fname.empty()) fname=path;
 }
 else if (ewas==Save) 
 {  fname=VA.getFilename();
    if (fname.empty()) 
       fname=path+defFileName(VA->getWerte().Name_Abenteurer())+".magus";
#ifdef __MINGW32__
    register_magus(h->argv0);
#endif 
 }
 else if (ewas==Load) 
 {  // path is ok
 }
 else if (ewas==Export) 
 {  fname=path+defFileName(VA->getWerte().Name_Abenteurer())+".txt";
 }
 set_filename(fname);
 
std::cout << "Dateiname " << fname << "->" << get_filename() << '\n';
#ifdef __MINGW32__
   // TODO was ist mit '\\' am Ende ?
   // TODO path erzeugen?
   
   OPENFILENAME ofn;
   char buf[10240];

   strncpy(buf,filename.c_str(),sizeof buf);

   ZeroMemory(&ofn, sizeof (OPENFILENAME));
   ofn.lStructSize = sizeof (OPENFILENAME);
   		// (Gtk::WIDGET(h->gobj())->window )
//   ofn.hwndOwner = GDK_DRAWABLE_XID(h->get_window()->gdkobj()); 
		// GDK_WINDOW_HWND (win) 2.0
   ofn.lpstrFile = buf;
   ofn.nMaxFile = sizeof buf;
   if (ewas==Export) ofn.lpstrFilter = "Alle Dateien (*.*)\0*.*\0Textdateien (*.txt)\0*.txt\0";
   else if (ewas==Pix) ofn.lpstrFilter = "Alle Dateien (*.*)\0*.*\0Bilder (*.png,*.jpg,*.tif)\0*.png;*.jpg;*.tif\0";
   else ofn.lpstrFilter = "Alle Dateien (*.*)\0*.*\0Midgard Abenteurer (*.magus)\0*.magus\0";
   ofn.nFilterIndex = 2;
   ofn.lpstrDefExt= ewas==Export ? "txt" : ewas==Pix ? "" : "magus";
   ofn.lpstrTitle = ewas==Export ? "Abenteurer exportieren" :
   		ewas==Pix ? "Bild einfügen" :
   		ewas==Load ? "Abenteurer laden" : "Abenteurer speichern";
   ofn.Flags = OFN_PATHMUSTEXIST 
   		| (ewas==Pix||ewas==Load ? OFN_FILEMUSTEXIST : 0);
   if (!filename.empty() && filename[filename.size()-1]==WinLux::dirsep)
   {  *buf=0;
      ofn.lpstrInitialDir = filename.c_str();
   }

   bool res=false;
   if (ewas==Pix||ewas==Load) res=GetOpenFileName(&ofn);
   else res=GetSaveFileName(&ofn);

   if (res) 
   {  set_filename(buf);
      on_ok_button1_clicked();
   }
   else delete this;

#endif
}
