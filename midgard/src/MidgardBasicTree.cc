// $Id: MidgardBasicTree.cc,v 1.21 2002/09/23 06:34:08 thoma Exp $
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

// generated 2001/2/2 11:29:18 CET by thoma@ig23.
// using glademm V0.5_11c
  
#include "MidgardBasicTree.hh"



MidgardBasicTree::MidgardBasicTree(variante V)
: SimpleTree(Cols(V),Attr(V))
{
  set_tree_titles(V);
  set_value_data(gpointer(V));
}

int MidgardBasicTree::Cols(variante V)
{
  switch(V) {
     case (STEIGERNZUSATZ)  : return 3;
     case (ANGEBFERT):  
     case (LERNSCHEMAZUSATZ): return 3;
     case (LONG_NEU_WAFFE): 
     case (SPRACHE_NEU):    
     case (SCHRIFT_NEU):    
     case (WAFFEGRUND_ALT): 
     case (WAFFE_LERNSCHEMA): return 4;
     case (GELERNTES):      return 5;
     case (LONG_NEU):
     case (ZAUBER_ALT):
     case (ZAUBER_NEU):
     case (KIDO_NEU):        
     case (KIDO_ALT):         return 6;
     case (WAFFEGRUND_NEU):
     case (ZAUBERWERK_NEU): 
     case (ZAUBERWERK_ALT):   return 7;
     case (SPRACHEN_ALT):
     case (WAFFE_ALT):        
     case (LONG_ALT_):        return 8;
     case (LERNSCHEMA):
     case (SCHRIFT_ALT):      return 9;
   }
  assert(!"MidgardBasicTree::Cols:     Falsche Variante \n");
  abort();
}

void MidgardBasicTree::set_tree_titles(variante V)
{
  vector<std::string> vs;
  if(V==GELERNTES)
   {
      vs.push_back("Art");
      vs.push_back("Fertigkeit");
      vs.push_back("Wert");  
      vs.push_back("LP");    
   }
  else if(V==ANGEBFERT)
   {
      vs.push_back("Würfelergebnis");
      vs.push_back("Fertigkeit");
      vs.push_back("Wert");  
   }
  else if(V==LONG_ALT_ || V==SPRACHEN_ALT || V==WAFFE_ALT)
   {
      if(V==LONG_ALT_) vs.push_back("Fertigkeit (gelernt)");
      else if(V==WAFFE_ALT) vs.push_back("Waffe (gesteigert)");
      else vs.push_back("Sprache (gelernt)");
      vs.push_back("Wert");
      vs.push_back("PP");  
      vs.push_back("Art");    
      vs.push_back("Steigern\n(nächste Stufe)");
      vs.push_back("Reduzieren\n(eine Stufe)"); 
      vs.push_back("Verlernen");
      vs.push_back("Region");
   }
  else if(V==LONG_NEU)
   {
      vs.push_back("Fertigkeit (ungelernt)");
      vs.push_back("Wert");
      vs.push_back("Lernkosten");  
      vs.push_back("Art");    
      vs.push_back("Voraussetzungen");
      vs.push_back("Region");
   }
  else if(V==LONG_NEU_WAFFE)
   {
      vs.push_back("(ungesteigert) Waffe)");
      vs.push_back("Art");    
      vs.push_back("Voraussetzungen");
      vs.push_back("Region");
   }
  else if(V==WAFFEGRUND_NEU || V==WAFFEGRUND_ALT)
   {
      if(V==WAFFEGRUND_ALT) vs.push_back("Grundkenntnisse (gelernt)");
      else vs.push_back("Grundkenntnisse (ungelernt)");
      vs.push_back("Art");
      vs.push_back("Kosten");
      vs.push_back("Region");
   }
  else if(V==SPRACHE_NEU)
   {
      vs.push_back("Sprache (ungelernt)");
      vs.push_back("Schrift");
      vs.push_back("Lernkosten");  
      vs.push_back("Region");  
   }
  else if(V==SCHRIFT_ALT)
   {
      vs.push_back("Schrift (gelernt)");
      vs.push_back("Schrifttyp");
      vs.push_back("Wert");
      vs.push_back("PP");  
      vs.push_back("Art");    
      vs.push_back("Steigern\n(nächste Stufe)");
      vs.push_back("Reduzieren\n(eine Stufe)"); 
      vs.push_back("Verlernen");
      vs.push_back("Region");  
   }
  else if(V==SCHRIFT_NEU)
   {
      vs.push_back("Schrift (ungelernt)");
      vs.push_back("Schrifttyp");
      vs.push_back("Lernkosten");  
      vs.push_back("Region");  
   }
  else if(V==ZAUBER_ALT || V==ZAUBER_NEU)
   {
     if(V==ZAUBER_ALT) vs.push_back("Spruch (gelernt)");   
     else vs.push_back("Spruch (ungelernt)");
     vs.push_back("Stufe");
     vs.push_back("Ursprung");
     vs.push_back("Lernkosten");
     vs.push_back("Art");
      vs.push_back("Region");
   }
  else if(V==ZAUBERWERK_ALT || V==ZAUBERWERK_NEU)
   {
     if(V==ZAUBERWERK_ALT) vs.push_back("Zaubermittel (gelernt)");   
     else vs.push_back("Zaubermittel (ungelernt)");
     vs.push_back("Stufe");
     vs.push_back("Art");
     vs.push_back("Kosten");
     vs.push_back("Preis");
     vs.push_back("Zeitaufwand");
     vs.push_back("Region");
   }
  else if(V==KIDO_ALT || V==KIDO_NEU)
   {
     if(V==KIDO_ALT) vs.push_back("HoHo (gelernt)");   
     else vs.push_back("HoHo (ungelernt)");
     vs.push_back("Technik");
     vs.push_back("Stufe");
     vs.push_back("AP");
     vs.push_back("Kosten");
     vs.push_back("Stil");
   }
  else if(V==WAFFE_LERNSCHEMA)
   {
     vs.push_back("Art");   
     vs.push_back("Waffe");
     vs.push_back("Grundkenntnisse");
     vs.push_back("Schaden");
   }
  setTitles(vs);
}
