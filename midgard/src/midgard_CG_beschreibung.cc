#include "midgard_CG.hh"
#include "xml_fileselection.hh"

gint midgard_CG::on_text_charakter_beschreibung_focus_out_event(GdkEventFocus *ev)
{
 std::string b=text_charakter_beschreibung->get_chars(0,text_charakter_beschreibung->get_length());
 Werte.setBeschreibung(b);
 modify_bool=true;
 return 0;
}

void midgard_CG::on_button_beschreibung_drucken_clicked()
{
  latex_beschreibung_drucken();
}

void midgard_CG::show_beschreibung()
{
  text_charakter_beschreibung->delete_text(0,text_charakter_beschreibung->get_length());
  gint pos=0;
  text_charakter_beschreibung->insert_text(Werte.Beschreibung().c_str() , Werte.Beschreibung().size(), &pos);
  std::string s="Grafik";
  if(Werte.BeschreibungPix()!="")
    s+="\n"+Werte.BeschreibungPix();
  label_grafik->set_text(s);
}

void midgard_CG::on_button_grafik_clicked()
{
  manage (new xml_fileselection(this,xml_fileselection::Pix));
}

