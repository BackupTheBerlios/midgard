// $Id: Window_hilfe.cc,v 1.26 2002/02/25 10:04:26 thoma Exp $
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
 std::string s=hilfetext();
 text_hilfe->insert_text(s.c_str() , s.size(), &pos);
}

std::string Window_hilfe::hilfetext()
{
std::string s="
1. Generierung eines neuen Abenteurers

* Spezies wählen (nur wenn es kein Mensch sein soll)
* Grundwerte würfeln (und eventuell editieren)
   - linke Maustaste: 2x würfeln, höheres Ergebnis zählt
   - rechte Maustaste: 9x würfeln und die betsen sechs Ergebnisse frei verteilen
* Geschlecht wählen (wenn es kein Mann sein soll)
* Abenteurertyp wählen (wenn es kein Assassine sein soll)
* Abgeleitete Werte würfeln (eventuell editieren)
* Werte editieren: 'Name des Abenteurers' und 'Version' eintragen, unter diesen
   beiden Angaben wird der Abenteurer in gespeichert.
* Lernschema (oberer Reiter)
* Herkunftsland wählen
* Angeborene Fertigkeit auswürfeln (mit der RECHTEN Maustaste können die Fertigkeiten 
   explizit gewählt werden.)
* Lernpunkte würfeln (eventuell editieren)
* Fertigkeiten, Waffen und Zauber in beliebiger Reinfolge auswählen 
* Spezialwaffe wählen (nicht für Zauberer und Barden)
* Beruf wählen (mit der rechten Maustaste kann ein bestimmtes W% Ergebnis 
   eingegeben vorgegeben.
* Magier wählen einen Spezialbereich
* Geld und Waffen würfeln (oder aussuchen)
* Rüstung auswürfeln (kann über 'Steigern' auch ausgesucht werden 
   wenn der Abenteurer vorher abgespeichert wird)
* bei Bedarf Abenteurerbeschreibung eingeben und ausdrucken.
   Es ist zu beachten, daß die Beschreibung als LaTeX Dokument verarbeitet wird.
   Dadurch ist gewährleistet, daß nahezu alle Zeichen darstellen werden können.
   Allerdings sind einige Symbole nur über LaTeX Komandos erhältlich.
   Für Anführungszeichen muß man bspw. '\\glqq' bzw '\\grqq' verwenden.
   Für Aufzählungen habe ich zwei neue Listenumgebungen bereitgestellt, die mit
   \\begin{punkte} 
   \\item text
   \\item text
   ....
   \\end{punkte}
   bzw. dasselbe für 'punkte2' angesprochen werden können.
* Abenteurer speichern 
* Abenteurer drucken (Es wird ein (mehrere) druckfertige(s) 
   Postscriptdokument(e) mit 'gv' angezeigt, der Ausdruck kann dann 
   aus diesem Programm heraus erfolgen. 
   
2. Steigern eines Abenteurers 
(Generell gilt: Während des Steigerns wird der Abenteurer STÄNDIG in der 
gesichert. Daher ist es nocht nötig, den Abenteurer nach dem
steigern zu speichern.) Bitte beachtet auch die unten aufgeführet Anleitung 
zur Bedienung der 'TreeBaseListen'

* Abenteurer laden (Wenn ein Abenteurername und eine Version eingetragen sind,
    wird der entsprechende Abenteurer geladen, ansonsten erscheint eine 
    Auswahlliste aller gespeicherter Abenteurer. In diesem Fenster ist 
    es auch möglich Abenteurer aus der Datenbank zu löschen)
* Steigern mit oder ohne Einsatz von Gold und Erfahrungspunkten
* .... an Grad anpassen
   Mit diesem Knopf werden die AP, die Abwehr, die Resistenzen und der Zaubernwert
   an den Grad angepaßt. Die AP-Zahl kann zu jedem Zeitpunkt neu berechnet werden
   (mit entsprechender Erhöhung der GFP). Außerdem wird für eine Steigerung der 
   Basiseigenschaften gewürfelt. Üblicherweise wird dieser Knopf betätigt,
   wenn die GFP-Grenze für einen neuen Grad übersprungen ist.
   Es ist auch möglich, die STeigerungen für die jeweiligen Aspekte einzeln 
   durchzuführen.
* Fertigkeiten (Fertigkeiten laden)
   Im oberen Fenster sind die Fertigkeiten, die der Abenteurer kann mit
   dem jeweiligen Erfolgswert angegeben. Außerdem ist angegeben, wieviele
   GFP die nächste Stufe (nach oben bzw nach unten) kostet. Beherrscht ein
   Abenteurer eine Fertigkeit auf dem niedrigsten Erfolgswert, so kannn er 
   diese auch 'verlernen'. Dadurch ist es möglich Eingabefehler rückgängig 
   zu machen.
   Im unteren Fenster sind die erlernbaren Fertigkeiten mit entsprechenden 
   Kosten angegeben.
* Waffen (Waffen laden)
   Im rechten Bereich sind die Grundkenntnisse der Waffen aufgeführt.
   oben die, die der Abenteurer bereits kann, unten die, die er lernen kann
   (mit Lernkosten in GFP).
   Im linken Bereich stehen oben die Waffen, die der Abenteurer schon 
   beherrscht (mit Erfolgswert und Kosten für die nächst höhere bzw. 
   niedrigere Stufe), unten stehen die Waffen, die der Abenteurer mit dem
   Erfolgswert +4 beherrscht, weil er die Grundkenntnisse in der jeweiligen
   Waffenart besitzt. Durch Anklicken kann man Waffen steigern und lernen,
   bzw. Grundkenntnisse lernen.
* Zauber (Zauber laden)
   Oben die Zauber, die ein Abenteurer kann, unten die, die er lernen darf
   (mit Kosten). Wählt man einen Zauber aus der oberen Liste, so wird dieser
   'verlernt'.
* KiDo funktioniert genauso wie bei den Zaubern
* Sprachen und Schriften
   Links die Sprachen, rechts die Schriften. Oben jeweils die, die ein 
   Abenteurer beherrscht, unten die, die er lernen kann.

Einigen selten benutzte Features lassen sich durch das Menu erreichen,
das aufklappt, wenn man den RECHTEN Mausknopf betätigt.

Anleitung zur TreeBaseListe (= Tabellen fürs Steigern und die Waffen)
* Die Listen können durch Anklicken der Kopfzeile in beliebiger Reinfolge
   sortiert werden
* Mit der rechten Maustaste öffnet man ein (hoffentlich selbsterklärendes) Menü

";
return s;
}
