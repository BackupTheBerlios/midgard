#include "midgard_CG.hh"
#include "xml_fileselection.hh"

gint midgard_CG::on_text_charakter_beschreibung_focus_out_event(GdkEventFocus *ev)
{
 std::string b=text_charakter_beschreibung->get_chars(0,text_charakter_beschreibung->get_length());
 Werte.setBeschreibung(b);
 undosave("Beschreibung geändert");
 return 0;
}

gint midgard_CG::on_spinbutton_pix_breite_focus_in_event(GdkEventFocus *ev)
{ spinbutton_pix_breite->select_region(0,-1); return false; }

gint midgard_CG::on_spinbutton_pix_breite_focus_out_event(GdkEventFocus *ev)
{
 Werte.setBeschreibungPixSize(spinbutton_pix_breite->get_value_as_int());
 undosave("Bildgröße geändert");
 return 0;
}

void midgard_CG::on_beschreibung_drucken()
{ latex_beschreibung_drucken();}

void midgard_CG::on_button_beschreibung_drucken_clicked()
{
  latex_beschreibung_drucken();
}

void midgard_CG::show_beschreibung()
{
  text_charakter_beschreibung->delete_text(0,text_charakter_beschreibung->get_length());
  gint pos=0;
  text_charakter_beschreibung->insert_text(Werte.Beschreibung().c_str() , Werte.Beschreibung().size(), &pos);

  std::string s="Bild";
  if(Werte.BeschreibungPix()!="")
    s+=":\n"+Werte.BeschreibungPix();
  label_grafik->set_text(s);

  spinbutton_pix_breite->set_value(Werte.BeschreibungPixSize());
}

void midgard_CG::on_button_grafik_clicked()
{
#ifndef __MINGW32__
  manage 
#else
  delete
#endif  
  (new xml_fileselection(this,xml_fileselection::Pix,&Werte));
  undosave("Bild geändert");
}

