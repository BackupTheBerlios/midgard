/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "midgard_CG.hh"
#include "export_common.h"
#include <fstream>
#include "Waffe.hh"
// for XML export
#include "xml_fileselection.hh"
#include "TagStream.hh"
#include <Aux/itos.h>


gint midgard_CG::on_speichern_release_event(GdkEventButton *ev)
{
  if (ev->button==3 && !filename.empty())
     xml_export(filename);
  else //(ev->button == 1)
     xml_export_auswahl();
  return false;
}

void midgard_CG::xml_export_auswahl()
{ 
 modify_bool=false;
 manage (new xml_fileselection(this,xml_fileselection::Save/*"Abenteurer speichern"*/))
	->set_filename(filename);
}

void midgard_CG::xml_export(const std::string& dateiname)
{  
  frame_steigern->set_sensitive(true);

/*   
  // eigentlich Unsinn da nur Version 8, aber besser als nichts zu tun
  std::string cname   = Werte.Name_Abenteurer();
  std::string version = Werte.Version(OptionBool.version);
  std::string command = "midgard_xmlexport '"+cname+"' '"+version+"' > '"+dateiname+"'";
  system(command.c_str());
  std::string strinfo = "Abenteurer "+cname+" exportiert\n";
  InfoFenster->AppendShow(strinfo);
*/
   ofstream datei(dateiname.c_str());
   if (!datei.good())
   { 
      InfoFenster->AppendShow("Ich kann die Datei '"+dateiname
                               +"' nicht beschreiben");
      return;
   }
  speicherstream(datei);
}


void midgard_CG::speicherstream(ostream &datei)
{
   datei << "<?xml";
   write_string_attrib(datei, "version", "1.0");
   write_string_attrib(datei, "encoding", TagStream::host_encoding);
   datei << "?>\n\n";
   datei << "<MAGUS-data>\n";

// Vielleicht hier eingegebene Ausrüstung speichern wie in anderen Dateien
// oder ganz unten?
   datei << " <Preise>\n";
   for (std::list<cH_Preise>::const_iterator i=Database.preise.begin();
   		i!=Database.preise.end();++i)
   {  if ((*i)->ist_eigener_Artikel())
      {  datei << "  <Kaufpreis";
         write_string_attrib(datei, "Ware", (*i)->Name());
         write_string_attrib(datei, "Art", (*i)->Art());
         write_string_attrib(datei, "Art2", (*i)->Art2());
         write_float_attrib(datei, "Preis", (*i)->Kosten());
         write_string_attrib(datei, "Währung", (*i)->Einheit());
         write_float_attrib(datei, "Gewicht", (*i)->Gewicht());
         datei << "/>\n";
      }
   }
   datei << " </Preise>\n\n";
   
   datei << " <Midgard-Abenteurer";
   write_int_attrib(datei,"Version",10);
   datei << ">\n";

   grundwerte_speichern(datei);
   datei << "  <Ausrüstung>\n"; // oder Besitz?
   write_string(datei, "Rüstung", Werte.Ruestung()->Name(), 4);
   // Waffen Besitz
   for (std::list<cH_MidgardBasicElement>::const_iterator i=list_Waffen_besitz.begin();
         i!=list_Waffen_besitz.end();++i)
      {  cH_WaffeBesitz WB(*i);
         datei << "    <Waffe";
         write_string_attrib(datei, "Bezeichnung", WB->Name());
         write_int_attrib(datei, "AngriffVerteidigung_Bonus", WB->av_Bonus());
         write_int_attrib(datei, "SchadenLebenspunkte_Bonus", WB->sl_Bonus());
         write_string_attrib(datei, "Region", WB->Region());
         if (WB->Magisch().empty()) datei << "/>\n";
         else datei << '>' << WB->Magisch() << "</Waffe>\n";
      }
   save_ausruestung(datei, besitz.getChildren());
   datei << "  </Ausrüstung>\n";
   
   datei << "  <Fertigkeiten>\n";   

   MidgardBasicElement::saveElementliste(datei,Werte.Sinne(),Werte,Typ);
   MidgardBasicElement::saveElementliste(datei,list_Beruf,Werte,Typ);
   MidgardBasicElement::saveElementliste(datei,list_Fertigkeit_ang,Werte,Typ);
   MidgardBasicElement::saveElementliste(datei,list_Fertigkeit,Werte,Typ);
   MidgardBasicElement::saveElementliste(datei,list_Waffen,Werte,Typ);
   MidgardBasicElement::saveElementliste(datei,list_Zauber,Werte,Typ);
   MidgardBasicElement::saveElementliste(datei,list_Zauberwerk,Werte,Typ);
   MidgardBasicElement::saveElementliste(datei,list_Kido,Werte,Typ);
   MidgardBasicElement::saveElementliste(datei,list_WaffenGrund,Werte,Typ);
   MidgardBasicElement::saveElementliste(datei,list_Sprache,Werte,Typ);
   MidgardBasicElement::saveElementliste(datei,list_Schrift,Werte,Typ);

   // Regionen & Ähnliches
  for(std::vector<cH_Region>::const_iterator i=Database.Regionen.begin();i!=Database.Regionen.end();++i)
   {  if (!(*i)->Active()) continue;
      datei << "    <Region";
      write_string_attrib(datei, "Name", (*i)->Name());
      write_string_attrib(datei, "Region", (*i)->Abkuerzung());
      datei << "/>\n";
   }
   // Optionen
   std::list<Midgard_Optionen::st_OptionenCheck> LO=MOptionen->getOptionenCheck();
   for(std::list<Midgard_Optionen::st_OptionenCheck>::iterator i=LO.begin();i!=LO.end();++i)
   {
     // Option, die mit dem C. gespeichert werden müssen
     if(i->index!=Midgard_Optionen::Original && i->index!=Midgard_Optionen::NSC_only) continue; 
     datei << "    <Optionen";
     write_string_attrib(datei, "Name", i->text);
     write_bool_attrib_force(datei, "Wert", i->active);
     datei << "/>\n";
   }
   datei << "  </Fertigkeiten>\n";   
   datei << " </Midgard-Abenteurer>\n";
   datei << "</MAGUS-data>\n";
}


void midgard_CG::grundwerte_speichern(IF_XML(ostream &datei))
{
   datei << "  <Figur";
   write_string_attrib(datei, "Name", Werte.Name_Abenteurer());
   write_string_attrib(datei, "Spieler", Werte.Name_Spieler());
   write_string_attrib(datei, "Zeitpunkt", Werte.Version());
   write_int_attrib(datei, "Grad", Werte.Grad());
   datei << "/>\n";
   datei << "  <Typ";
   write_string_attrib(datei, "Spezies", Werte.Spezies()->Name());
   write_string_attrib(datei, "Geschlecht", Werte.Geschlecht());
   write_string_attrib(datei, "Abkürzung", Typ[0]->Short());
   write_string_attrib(datei, "Abkürzung2", Typ[1]->Short());
   write_string_attrib(datei, "Spezialgebiet", Werte.Spezialgebiet()->Name());
   write_string_attrib(datei, "Spezialisierung", Werte.Spezialisierung());
   write_string_attrib(datei, "Stadt_Land", Werte.Stadt_Land()); // ???
   write_string_attrib(datei, "Hand", Werte.Hand());
   datei << "/>\n";
   datei << "  <Basiseigenschaften";
   write_int_attrib(datei, "St", Werte.St());
   write_int_attrib(datei, "Gw", Werte.Gw());
   write_int_attrib(datei, "Gs", Werte.Gs());
   write_int_attrib(datei, "Ko", Werte.Ko());
   write_int_attrib(datei, "In", Werte.In());
   write_int_attrib(datei, "Zt", Werte.Zt());
   datei << "/>\n";
   datei << "  <abgeleiteteEigenschaften";
   write_int_attrib(datei, "Au", Werte.Au());
   write_int_attrib(datei, "pA", Werte.pA());
   write_int_attrib(datei, "Wk", Werte.Wk());
   write_int_attrib(datei, "Sb", Werte.Sb());
   write_int_attrib(datei, "B", Werte.B());
//   write_int_attrib(datei, "KAW", Werte.St());
//   write_int_attrib(datei, "WLW", Werte.St());
   write_int_attrib(datei, "GG", Werte.GG());
   write_int_attrib(datei, "SG", Werte.SG());
   datei << "/>\n";
   datei << "  <Erfolgswerte";
   write_int_attrib(datei, "Abwehr", Werte.Abwehr_wert());
   write_int_attrib(datei, "Zaubern", Werte.Zaubern_wert());
   write_int_attrib(datei, "ZauberResistenz", Werte.Resistenz());
   datei << "/>\n";
   datei << "  <Gesundheit"; // schlechter Name ?
//   write_int_attrib(datei, "LP_Basis");
   write_int_attrib(datei, "LP", Werte.LP());
   write_int_attrib(datei, "AP", Werte.AP());
   datei << "/>\n";
   datei << "  <Beschreibung"; // soziale?
   write_int_attrib(datei, "Alter", Werte.Alter());
   write_string_attrib(datei, "Gestalt", Werte.Gestalt());
   write_int_attrib(datei, "Gewicht", Werte.Gewicht());
   write_int_attrib(datei, "Größe", Werte.Groesse());
   write_string_attrib(datei, "Stand", Werte.Stand());
   write_string_attrib(datei, "Bezeichnung", Werte.Bezeichnung());
   write_string_attrib(datei, "Herkunft", Werte.Herkunft()->Name());
   write_string_attrib(datei, "Glaube", Werte.Glaube());
   datei << "/>\n";
#if 0    // nicht mehr notwendig???
   datei << "  <Boni"; 
   write_int_attrib(datei, "Ausdauer");
   write_int_attrib(datei, "Schaden");
   write_int_attrib(datei, "Angriff");
   write_int_attrib(datei, "Abwehr");
   write_int_attrib(datei, "Zaubern");
   datei << ">\n";
   datei << "    <Resistenzen"; // Würde ich unter BONI fassen MAT
   write_int_attrib(datei, "psy");
   write_int_attrib(datei, "phs");
   write_int_attrib(datei, "phk");
   write_int_attrib(datei, "Gift");
   datei << "/>\n";
   datei << "  </Boni>\n";
#endif
   datei << "  <Vermögen";
   write_int_attrib(datei, "GS", Werte.Gold());
   write_int_attrib(datei, "SS", Werte.Silber());
   write_int_attrib(datei, "KS", Werte.Kupfer());
   datei << "/>\n";
   datei << "  <Steigern";
   write_int_attrib(datei, "GFP", Werte.GFP());
   write_int_attrib(datei, "AEP", Werte.AEP());
   write_int_attrib(datei, "KEP", Werte.KEP());
   write_int_attrib(datei, "ZEP", Werte.ZEP());
//   write_bool_attrib(datei, "EPabziehen", , false); ???
   write_int_attrib(datei, "EPproGFP", Database.GradAnstieg.get_Steigern_EP_Prozent(), 50);
   write_int_attrib(datei, "Basiswerte", Database.GradAnstieg.get_Grad_Basiswerte(), Werte.Grad());
//   write_int_attrib(datei, "Abwehr", , Werte.Grad());
//   write_int_attrib(datei, "Resistenz", , Werte.Grad());
//   write_int_attrib(datei, "Zaubern", , Werte.Grad());
   write_float_attrib(datei, "benötigte_Tage", Werte.Steigertage());
   datei << "><Praxispunkte";
   write_int_attrib(datei, "Abwehr", Werte.AbwehrPP());
   write_int_attrib(datei, "Zaubern", Werte.ZaubernPP());
   write_int_attrib(datei, "Resistenz", Werte.ResistenzPP());
   datei << "/></Steigern>\n";
   write_string(datei, "Text", Werte.Beschreibung(), 2);
   write_string(datei, "TextPix", Werte.BeschreibungPix(), 2);
   write_string(datei, "TextPixSize", itos(Werte.BeschreibungPixSize()), 2);
}


void midgard_CG::save_ausruestung(ostream &datei,const list<AusruestungBaum> &AB, const int indent)
{  
  for(AusruestungBaum::const_iterator i=AB.begin();i!=AB.end();++i)
   {  datei << string(indent,' ') << "<Gegenstand";
      write_string_attrib(datei, "Bezeichnung", i->getAusruestung().Name());
      write_string_attrib(datei, "Besonderheit", i->getAusruestung().Material());
      write_bool_attrib(datei, "sichtbar", i->getAusruestung().Sichtbar());
      if (i->empty()) datei << "/>\n";
      else
      {  datei << ">\n";
         save_ausruestung(datei, i->getChildren(), indent+2);
         datei << string(indent,' ') << "</Gegenstand>\n";
      }
   }
}

