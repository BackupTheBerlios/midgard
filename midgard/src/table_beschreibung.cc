/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2004 Christof Petig
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
#include "table_beschreibung.hh"
#include "midgard_CG.hh"
#include "WinFileReq.hh"
#include "Windows_Linux.hh"

extern Glib::RefPtr<Gdk::Pixbuf> MagusImage(const std::string &name);

void table_beschreibung::init(midgard_CG *h)
{
  hauptfenster=h;
  h->getChar().signal_anderer_abenteurer().connect(SigC::slot(*this,&table_beschreibung::show_beschreibung));
  h->getChar().proxies.undo_changed.connect(SigC::slot(*this,&table_beschreibung::show_beschreibung));
}

void table_beschreibung::save_beschreibung()
{
  hauptfenster->getChar()->begin_undo();
  std::string b=text_charakter_beschreibung->get_buffer()->get_text(
  	text_charakter_beschreibung->get_buffer()->begin(),
  	text_charakter_beschreibung->get_buffer()->end());
  hauptfenster->getAben().setBeschreibung(b);
  hauptfenster->getChar()->name_undo("Beschreibung geändert");
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
     hauptfenster->getAben().setBeschreibungPix("");
   }
  return false;
#endif  
}

void table_beschreibung::setBeschreibungPix(const std::string &s)
{ hauptfenster->getChar()->begin_undo();
  hauptfenster->getAben().setBeschreibungPix(s);
  hauptfenster->getChar()->name_undo(s.empty()?"Bild gelöscht":"Bild geändert");
}

void table_beschreibung::on_button_grafik_clicked()
{ hauptfenster->getChar()->begin_undo();
  WinFileReq::create(SigC::slot(*this,&table_beschreibung::setBeschreibungPix),
      hauptfenster->getAben().BeschreibungPix().empty() 
      ? Programmoptionen->getString(Magus_Optionen::speicherpfad)
      : hauptfenster->getAben().BeschreibungPix(),
      "Bilder (*.png,*.jpg,*.tif)\0*.png;*.jpg;*.tif\0Alle Dateien (*.*)\0*.*\0",
      std::string(),"Welche Grafik soll auf dem Ausdruck erscheinen?",true,
      hauptfenster,true);
}

bool table_beschreibung::on_spinbutton_pix_breite_focus_out_event(GdkEventFocus *ev)
{hauptfenster->getChar()->begin_undo();
 hauptfenster->getAben().setBeschreibungPixSize(spinbutton_pix_breite->get_value_as_int());
 hauptfenster->getChar()->name_undo("Bildgröße geändert");
 return 0;
}

bool table_beschreibung::on_spinbutton_pix_breite_focus_in_event(GdkEventFocus *ev)
{  
  spinbutton_pix_breite->select_region(0,-1);   
  return 0;
}

void table_beschreibung::show_beschreibung()
{ if (hauptfenster->get_current_page()!=midgard_CG::PAGE_BESCHREIBUNG) return;
  text_charakter_beschreibung->get_buffer()->erase(
  	text_charakter_beschreibung->get_buffer()->begin(),
  	text_charakter_beschreibung->get_buffer()->end());
  Gtk::TextBuffer::iterator pos=text_charakter_beschreibung->get_buffer()->begin();
  text_charakter_beschreibung->get_buffer()->insert(pos, hauptfenster->getAben().Beschreibung());

  std::string s="Bild";
  if(!hauptfenster->getAben().BeschreibungPix().empty())
   {
      s=hauptfenster->getAben().BeschreibungPix();
      std::string ss=s.substr(s.rfind(WinLux::dirsep)+1);
      s="Bild:\n"+ss;
      try
      {
      Glib::RefPtr<Gdk::Pixbuf> pb=Gdk::Pixbuf::create_from_file(hauptfenster->getAben().BeschreibungPix());
      if (!bool(pb)) pb=MagusImage("Portrait-32.xpm");
      else if (pb->get_height()>32)
         pb=pb->scale_simple(int(pb->get_width()*32.0/pb->get_height()+.5),
                                            32,Gdk::INTERP_BILINEAR);
      grafik_image->set(pb);
      } catch (...)
      {  grafik_image->set(MagusImage("Portrait-32.xpm"));
      }
   }
  else grafik_image->set(MagusImage("Portrait-32.xpm"));
  label_grafik->set_text(s);
  spinbutton_pix_breite->set_value(hauptfenster->getAben().BeschreibungPixSize());
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

