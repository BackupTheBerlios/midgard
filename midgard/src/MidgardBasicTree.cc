// $Id: MidgardBasicTree.cc,v 1.18 2002/06/27 09:01:21 thoma Exp $
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
     case (ANGEBFERT):      return 3;
     case (GELERNTES):      return 4;
     case (LERNSCHEMA):     return 9;
     case (LERNSCHEMAZUSATZ):return 3;
     case (LONG_ALT):       return 8;
     case (LONG_NEU):       return 6;
     case (LONG_NEU_WAFFE): return 4;
     case (SPRACHE_NEU):    return 3;
     case (SCHRIFT_ALT):    return 8;
     case (SCHRIFT_NEU):    return 3;
     case (WAFFEGRUND):     return 4;
     case (ZAUBER):         return 6;
     case (ZAUBERWERK):     return 7;
     case (KIDO):           return 6;
     case (WAFFE_LERNSCHEMA):return 4;
     case (STEIGERNZUSATZ): return 1;
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
      vs.push_back("W�rfelergebnis");
      vs.push_back("Fertigkeit");
      vs.push_back("Wert");  
   }
/*
  else if(V==LERNSCHEMA)
   {
      vs.push_back("LP");    
      vs.push_back("Fertigkeit");
      vs.push_back("Wert");  
      vs.push_back("Voraussetzung");    
      vs.push_back("Grundkenntnnis");    
      vs.push_back("Kosten");    
   }
*/
  else if(V==LONG_ALT)
   {
      vs.push_back("Fertigkeit");
      vs.push_back("Wert");
      vs.push_back("PP");  
      vs.push_back("Art");    
      vs.push_back("Steigern\n(n�chste Stufe)");
      vs.push_back("Reduzieren\n(eine Stufe)"); 
      vs.push_back("Verlernen");
      vs.push_back("Region");
   }
  else if(V==LONG_NEU)
   {
      vs.push_back("Fertigkeit");
      vs.push_back("Wert");
      vs.push_back("Lernkosten");  
      vs.push_back("Art");    
      vs.push_back("Voraussetzungen");
      vs.push_back("Region");
   }
  else if(V==LONG_NEU_WAFFE)
   {
      vs.push_back("Fertigkeit");
//      vs.push_back("Wert");
//      vs.push_back("Lernkosten");  
      vs.push_back("Art");    
      vs.push_back("Voraussetzungen");
      vs.push_back("Region");
   }
  else if(V==WAFFEGRUND)
   {
      vs.push_back("Grundkenntnisse");
      vs.push_back("Art");
      vs.push_back("Kosten");
      vs.push_back("Region");
   }
  else if(V==SPRACHE_NEU)
   {
      vs.push_back("Sprache");
      vs.push_back("Schrift");
      vs.push_back("Lernkosten");  
   }
  else if(V==SCHRIFT_ALT)
   {
      vs.push_back("Fertigkeit");
      vs.push_back("Schrifttyp");
      vs.push_back("Wert");
      vs.push_back("PP");  
      vs.push_back("Art");    
      vs.push_back("Steigern\n(n�chste Stufe)");
      vs.push_back("Reduzieren\n(eine Stufe)"); 
      vs.push_back("Verlernen");
   }
  else if(V==SCHRIFT_NEU)
   {
      vs.push_back("Schrift");
      vs.push_back("Schrifttyp");
      vs.push_back("Lernkosten");  
   }
  else if(V==ZAUBER)
   {
     vs.push_back("Name");   
     vs.push_back("Stufe");
     vs.push_back("Ursprung");
     vs.push_back("Lernkosten");
     vs.push_back("Art");
      vs.push_back("Region");
   }
  else if(V==ZAUBERWERK)
   {
     vs.push_back("Name");   
     vs.push_back("Stufe");
     vs.push_back("Art");
     vs.push_back("Kosten");
     vs.push_back("Preis");
     vs.push_back("Zeitaufwand");
      vs.push_back("Region");
   }
  else if(V==KIDO)
   {
     vs.push_back("HoHo");   
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
