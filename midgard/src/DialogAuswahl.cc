/*  MAGuS: Midgard Abenteurer Generieren Und Steigern
 *  Copyright (C) 2006 Christof Petig
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

#include "DialogAuswahl.hh"
#include "class_SimpleTree_LernschemaZusatz.hh"

void DialogAuswahl::clicked(cH_RowDataBase const& row,int idx,bool &handled)
{ result=row;
  response(Gtk::RESPONSE_OK);
  handled=true;
}

DialogAuswahl::DialogAuswahl(Gtk::Window *parent,int spalten,std::string const& text)
  : MagusDialog(parent), tree(spalten)
{ set_text(text);
  get_vbox()->pack_start(tree);
  set_style(b_Close);
  tree.signal_clicked().connect(sigc::mem_fun(*this,&DialogAuswahl::clicked));
}

cH_RowDataBase DialogAuswahl::run()
{ MagusDialog::run();
  return result;
}

void DialogZusatz::einschraenkung_anwenden()
{ std::vector<cH_RowDataBase> datavec;
  for(std::vector<cH_RowDataBase>::const_iterator i=alles.begin();i!=alles.end();++i)
   {
        Handle<const Data_Zusatz> dt=i->cast_dynamic<const Data_Zusatz>();
        if(!!dt) 
        {  if(cb.get_active() || dt->Erlaubt())
              datavec.push_back(*i);
        }
        else
        {  Handle<const Data_Herkunft>dt2=i->cast_dynamic<const Data_Herkunft>();
           if(cb.get_active() || dt2->Erlaubt())
              datavec.push_back(*i);
        }
   }
  get_tree().getModel()=datavec;
}

// könnte auch in libmagus!
std::string DialogZusatz::text(MidgardBasicElement::eZusatz was,MBEmlt MBE)
{ switch (was)
  { case MidgardBasicElement::ZHerkunft: return "Herkunftsland wählen";
    case MidgardBasicElement::ZUeberleben: 
       return "In welcher Gegend beherrscht dieser Abenteurer 'Überleben' "
           "als Universelle Fertigkeit";
    case MidgardBasicElement::ZWaffe: return "Fernkampfwaffe auswählen";
      // FIXME: MBE name?
    case MidgardBasicElement::ZTabelle: return "Zusatz auswählen";
    case MidgardBasicElement::ZSchrift: return "Schrift auswählen";
      // FIXME: Mutter ja/nein angeben!
    case MidgardBasicElement::ZSprache: if ((*MBE)->Name()=="Muttersprache")
        return "Muttersprache wählen";
      return "Sprache auswählen";
    default: return (*MBE)->Name()+" auswählen";
  }
}

std::vector<std::string> DialogZusatz::titles(MidgardBasicElement::eZusatz was,MBEmlt MBE)
{ std::vector<std::string> result;
  switch (was)
  { case MidgardBasicElement::ZHerkunft: result.push_back("Land");
      result.push_back("Kontinent");
      result.push_back("Sprache(n)");
      return result;
    case MidgardBasicElement::ZUeberleben: 
    case MidgardBasicElement::ZWaffe:
    case MidgardBasicElement::ZSchrift:
    case MidgardBasicElement::ZSprache:
    default: 
      result.push_back((*MBE)->Name());
      return result;
    case MidgardBasicElement::ZTabelle:
      result.push_back((*MBE)->Name());
      // ""?
      result.push_back("Region");
      return result;
  }
}

int DialogZusatz::spalten(MidgardBasicElement::eZusatz was)
{ switch (was)
  { case MidgardBasicElement::ZHerkunft:
      return 3;
    case MidgardBasicElement::ZUeberleben: 
    case MidgardBasicElement::ZWaffe:
    case MidgardBasicElement::ZSchrift:
    case MidgardBasicElement::ZSprache:
    default: 
      return 1;
    case MidgardBasicElement::ZTabelle:
      return 2; // ?
  }
}

// vermutlich brauche ich noch MBE (und Abent?)
DialogZusatz::DialogZusatz(Gtk::Window *parent,MidgardBasicElement::eZusatz was, MBEmlt MBE)
 : DialogAuswahl(parent,spalten(was),text(was,MBE)), cb("Beschränkung aufheben")
{ get_vbox()->pack_start(cb);
  tree.set_titles(titles(was,MBE));
  // Auswahl hinterlegen
  cb.signal_toggled().connect(sigc::mem_fun(*this,&DialogZusatz::einschraenkung_anwenden));
  einschraenkung_anwenden();
}
