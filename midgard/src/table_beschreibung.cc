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
  std::string b=text_charakter_beschreibung->get_buffer()->get_text(
  	text_charakter_beschreibung->get_buffer()->begin(),
  	text_charakter_beschreibung->get_buffer()->end());
  hauptfenster->getWerte().setBeschreibung(b);
  hauptfenster->undosave("Beschreibung geändert");
}

bool table_beschreibung::on_text_charakter_beschreibung_focus_out_event(GdkEventFocus *ev)
{  
  save_beschreibung();
  return 0;
}

void table_beschreibung::on_button_beschreibung_drucken_clicked()
{  
  hauptfenster->on_beschreibung_drucken();
}

void table_beschreibung::on_button_grafik()
{
  on_button_grafik_clicked();
#if 0  
  if (ev->button==3) 
   { label_grafik->set_text("");
     hauptfenster->getWerte().setBeschreibungPix("");
   }
  return false;
#endif  
}


void table_beschreibung::on_button_grafik_clicked()
{  
  (new xml_fileselection(hauptfenster,xml_fileselection::Pix));
  hauptfenster->undosave("Bild geändert");
}

bool table_beschreibung::on_spinbutton_pix_breite_focus_out_event(GdkEventFocus *ev)
{ 
 hauptfenster->getWerte().setBeschreibungPixSize(spinbutton_pix_breite->get_value_as_int());
 hauptfenster->undosave("Bildgröße geändert");
 return 0;
}

bool table_beschreibung::on_spinbutton_pix_breite_focus_in_event(GdkEventFocus *ev)
{  
  spinbutton_pix_breite->select_region(0,-1);   
  return 0;
}

void table_beschreibung::show_beschreibung()
{
  text_charakter_beschreibung->get_buffer()->erase(
  	text_charakter_beschreibung->get_buffer()->begin(),
  	text_charakter_beschreibung->get_buffer()->end());
  Gtk::TextBuffer::iterator pos=text_charakter_beschreibung->get_buffer()->begin();
  text_charakter_beschreibung->get_buffer()->insert(pos, hauptfenster->getWerte().Beschreibung());

  std::string s="Bild";
  if(hauptfenster->getWerte().BeschreibungPix()!="")
   {
      s+=":\n"+hauptfenster->getWerte().BeschreibungPix();
      std::string ss(s,s.rfind(WinLux::dirsep)+1,s.size());
      s=ss;
   }
  label_grafik->set_text(s);
  spinbutton_pix_breite->set_value(hauptfenster->getWerte().BeschreibungPixSize());
}

void table_beschreibung::insert_into_beschreibung(const std::string &s,const gint select_start,const gint select_end)
{
  text_charakter_beschreibung->get_buffer()->insert_at_cursor(s);

#if 0 // was taete das denn wenn es gehen wuerde? CP
  if(select_start!=select_end)
     text_charakter_beschreibung->select_region(pos-select_start,pos-select_end);
  if(select_start)
     text_charakter_beschreibung->set_point(pos-select_start);
#endif     
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

