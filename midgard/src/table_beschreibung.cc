// generated 2002/5/13 20:46:12 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_beschreibung.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "table_beschreibung.hh"
#include "midgard_CG.hh"
#include "xml_fileselection.hh"
#include "Windows_Linux.hh"

void table_beschreibung::init(midgard_CG *h)
{
  hauptfenster=h;
  show_beschreibung();
}

void table_beschreibung::save_beschreibung()
{
  std::string b=text_charakter_beschreibung->get_chars(0,text_charakter_beschreibung->get_length());
  hauptfenster->getWerte().setBeschreibung(b);
  hauptfenster->undosave("Beschreibung geändert");
}

gint table_beschreibung::on_text_charakter_beschreibung_focus_out_event(GdkEventFocus *ev)
{  
  save_beschreibung();
  return 0;
}

void table_beschreibung::on_button_beschreibung_drucken_clicked()
{  
  hauptfenster->on_beschreibung_drucken();
}

gint table_beschreibung::on_button_grafik_button_release_event(GdkEventButton *ev)
{
  if (ev->button==1) on_button_grafik_clicked();
  if (ev->button==3) 
   { label_grafik->set_text("");
     hauptfenster->getWerte().setBeschreibungPix("");
   }
  return false;
}


void table_beschreibung::on_button_grafik_clicked()
{  
#ifndef __MINGW32__
  manage 
#else    
  delete 
#endif   
  (new xml_fileselection(hauptfenster,xml_fileselection::Pix));
  hauptfenster->undosave("Bild geändert");
}

gint table_beschreibung::on_spinbutton_pix_breite_focus_out_event(GdkEventFocus *ev)
{ 
 hauptfenster->getWerte().setBeschreibungPixSize(spinbutton_pix_breite->get_value_as_int());
 hauptfenster->undosave("Bildgröße geändert");
 return 0;
}

gint table_beschreibung::on_spinbutton_pix_breite_focus_in_event(GdkEventFocus *ev)
{  
  spinbutton_pix_breite->select_region(0,-1);   
  return 0;
}

void table_beschreibung::show_beschreibung()
{
  text_charakter_beschreibung->delete_text(0,text_charakter_beschreibung->get_length());
  gint pos=0;
  text_charakter_beschreibung->insert_text(hauptfenster->getWerte().Beschreibung().c_str()
      , hauptfenster->getWerte().Beschreibung().size(), &pos);

  std::string s="Bild";
  if(hauptfenster->getWerte().BeschreibungPix()!="")
   {
      s+=":\n"+hauptfenster->getWerte().BeschreibungPix();
cout <<"s ="<< s<<'\t'<<s.rfind(WinLux::dirsep)<<'\n';
      std::string ss(s,s.rfind(WinLux::dirsep)+1,s.size());
      s=ss;
   }
  label_grafik->set_text(s);
  spinbutton_pix_breite->set_value(hauptfenster->getWerte().BeschreibungPixSize());
}

void table_beschreibung::insert_into_beschreibung(const std::string &s,const gint select_start,const gint select_end)
{
  gint pos=text_charakter_beschreibung->get_point();
  text_charakter_beschreibung->insert_text(s.c_str(), s.size(), &pos);
  
  if(select_start!=select_end)
     text_charakter_beschreibung->select_region(pos-select_start,pos-select_end);
  if(select_start)
     text_charakter_beschreibung->set_point(pos-select_start);
  text_charakter_beschreibung->grab_focus();

}

void table_beschreibung::on_button_fett_clicked()
{
  std::string s="\\textbf{  }";
  insert_into_beschreibung(s,3,1);
}

void table_beschreibung::on_button_kursiv_clicked()
{
  std::string s="\\textit{  }";
  insert_into_beschreibung(s,3,1);
}

void table_beschreibung::on_button_liste_clicked()
{
 std::string s="\n\n\\begin{punkte}\n\\item   \n\\item\n\\end{punkte}\n\n";
 insert_into_beschreibung(s,23,21);
}

void table_beschreibung::on_button_liste2_clicked()
{
 std::string s="\n\n\\begin{punkte2}\n\\item   \n\\item\n\\end{punkte2}\n\n";
 insert_into_beschreibung(s,23,21);
}

