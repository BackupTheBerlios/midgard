// $Id: Window_hilfe.cc,v 1.14 2001/05/29 06:27:58 thoma Exp $
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

// generated 2001/3/9 7:14:20 CET by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// newer (non customized) versions of this file go to Window_hilfe.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "Window_hilfe.hh"
#include <string>

void Window_hilfe::on_button_hilfe_schliessen_clicked()
{   
   destroy();
}

Window_hilfe::Window_hilfe()
{
// text_hilfe->delete_text(0,text_hilfe->get_length());
 gint pos=0;
 string s=hilfetext();
 text_hilfe->insert_text(s.c_str() , s.size(), &pos);
}

string Window_hilfe::hilfetext()
{
string s="
1. Generierung eines neuen Charakters

* Spezies wählen
* Grundwerte würfeln (eventuell editieren)
* Geschlecht wählen
* Charaktertyp wählen
* Abgeleitete Werte würfeln (eventuell editieren)
* Werte editieren: 'Name des Charakters' und 'Version' eintragen, unter diesen
   beiden Angaben wird der Charakter in der Datenbank gespeichert.
* Herkunftsland wählen
* Muttersprache(n) wählen
* Lernschema
* Lernpunkte würfeln (eventuell editieren)
* Beruf wählen
* Erfolgswert für Beruf würfeln
* Fertigkeiten auswählen
* Angeborene Fertigkeit auswürfeln
* Waffen auswählen
* Spezialwaffe wählen (nicht für Zauberer und Barden)
* Zauber auswählen (nicht für Kämpfer außer Barde und Ordenskrieger)
* Magier wählen einen Spezialbereich
* Geld und Waffen würfeln (oder aussuchen)
* Rüstung auswürfeln (kann über 'Steigern' auch ausgesucht werden)
* bei Bedarf Charakterbeschreibung eingeben und ausdrucken.
* Charakter speichern (in der Datenbank unter dem Schlüssel 
   'Charaktername und Version'
* Charakter drucken (Es wird ein druckfertiges Postscriptdokument mit 'gv'
   angezeigt, der Ausdruck kann dann aus diesem Programm heraus erfolgen. 

2. Steigern eines Charakters 

* Charakter laden (Wenn ein Charaktername und eine Version eingetragen sind,
    wird der entsprechende Charakter geladen, ansonsten erscheint eine 
    Auswahlliste aller gespeicherter Charaktere. In diesem Fenster ist 
    es auch möglich Charaktere aus der Datenbank zu löschen)
* Steigern
* Fertigkeiten (Fertigkeiten laden)
   Im oberen Fenster sind die Fertigkeiten, die der Charakter kann mit
   dem jeweiligen Erfolgswert angegeben. Außerdem ist angegeben, wieviele
   GFP die nächste Stufe (nach oben bzw nach unten) kostet. Beherrscht ein
   Charakter eine Fertigkeit auf dem niedrigsten Erfolgswert, so kannn er 
   diese auch 'verlernen'.
   Im untern Fenster sind die erlernbaren Fertigkeiten mit entsprechenden 
   Kosten angegeben.
* Waffen (Waffen laden)
   Im rechten Bereich sind die Grundkenntnisse der Waffen aufgeführt.
   oben die, die der Charakter bereits kann, unten die, die er lernen kann
   (mit Lernkosten in GFP).
   Im linken Bereich stehen oben die Waffen, die der Charakter schon 
   beherrscht (mit Erfolgswert und Kosten für die nächst höhere bzw. 
   niedirgere Stufe), unten stehen die Waffen, die der Charakter mit dem
   Erfolgswert +4 beherrscht, weil er die Grundkenntnisse in der jeweiligen
   Waffenart besitzt. Durch ancklicken kann man Waffen steigern und lernen,
   bzw. Grundkenntnisse lernen.
* Zauber (Zauber laden)
   Oben die Zauber, die ein Charakter kann, unten die, die er lernen darf
   (mit Kosten). Wählt man einen Zauber aus der oberen Liste, so wird dieser
   'verlernt'.
* Sprachen und Schriften
   Links die Sprachen, rechts die Schriften. Oben jeweils die, die ein 
   Charakter beherrscht, unten die, die er lernen kann.

Anmerkungen:
  Einige Funktionen, die nur selten benutzt werden, können über die rechte 
  Maustaste aufgrufen werden. Dies sind im Einzelnen:
* Charakter speichern      -> xml-Format exportieren 
* LaTeX Charakterblatt     -> Export im Format für Midgard Abenteuer
* angeborene Fertigkeiten  -> eingeben (statt würfeln) der angeborenen Fertigkeiten

";
return s;
}
