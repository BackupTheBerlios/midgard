// $Id: Window_hilfe.cc,v 1.22 2001/08/23 20:11:45 thoma Exp $
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
1. Generierung eines neuen Charakters

* Spezies w�hlen (wenn es KEIN Mensch sein soll)
* Grundwerte w�rfeln (eventuell editieren)
* Geschlecht w�hlen (wenn es KEIN Mann sein soll)
* Charaktertyp w�hlen (wenn es KEIN Assassine sein soll)
* Abgeleitete Werte w�rfeln (eventuell editieren)
* Werte editieren: 'Name des Charakters' und 'Version' eintragen, unter diesen
   beiden Angaben wird der Charakter in der Datenbank gespeichert.
* Herkunftsland w�hlen
* Muttersprache(n) w�hlen
* Lernschema
* Lernpunkte w�rfeln (eventuell editieren)
* Beruf w�hlen
* Erfolgswert f�r Beruf w�rfeln
* Fertigkeiten ausw�hlen 
* Angeborene Fertigkeit ausw�rfeln (mit der RECHTEN Maustaste k�nenn die Fertigkeiten 
   explizit gew�hlt werden.)
* Waffen ausw�hlen
* Spezialwaffe w�hlen (nicht f�r Zauberer und Barden)
* Zauber ausw�hlen (nicht f�r K�mpfer au�er Barde und Ordenskrieger)
* Magier w�hlen einen Spezialbereich
* Geld und Waffen w�rfeln (oder aussuchen)
* R�stung ausw�rfeln (kann �ber 'Steigern' auch ausgesucht werden 
   wenn der Charakter vorher abgespeichert wird)
* bei Bedarf Charakterbeschreibung eingeben und ausdrucken.
   Es ist zu beachten, da� die Beschriebung als LaTeX Dokument verarbeitet wird.
   Dadurch ist gew�hrleistet, da� man nahezu alle Zeichen darstellen kann.
   Allerdings sind einige Symbole nur �ber LaTeX Komandos erh�ltlich.
   F�r Anf�hrungszeichen mu� man bspw. '\\glqq' bzw '\\grqq' verwenden.
* Charakter speichern (in der Datenbank unter dem Schl�ssel 
   'Charaktername und Version'
* Charakter drucken (Es wird ein druckfertiges Postscriptdokument mit 'gv'
   angezeigt, der Ausdruck kann dann aus diesem Programm heraus erfolgen. 
   
2. Steigern eines Charakters 
(Generell gilt: W�hrend des Steigerns wird der Charakter ST�NDIG in der 
Datenbank abgespeichert. Daher ist es nocht n�tig, den Charakter nach dem
steigern noch einmal zu speichern.)
Bitte lest die unten aufgef�hret Anleitung zur Bedienung der Treebaselisten

* Charakter laden (Wenn ein Charaktername und eine Version eingetragen sind,
    wird der entsprechende Charakter geladen, ansonsten erscheint eine 
    Auswahlliste aller gespeicherter Charaktere. In diesem Fenster ist 
    es auch m�glich Charaktere aus der Datenbank zu l�schen)
* Steigern mit oder ohne Einsatz von Gold und Erfahrungspunkten
* .... an Grad anpassen
   Mit diesem Knopf werden die AP, die Abwehr, die Resistenzen und der Zaubernwert
   an den Grad angepa�t. Die AP-Zahl kann zu jedem Zeitpunkt neu berechnet werden
   (mit entsprechender Erh�hung der GFP). Au�erdem wird f�r eine Steigerung der 
   Basiseigenschaften gew�rfelt. �blicherweise wird dieser Knopf bet�tigt,
   wenn die GFP-Grenze f�r einen neuen Grad �bersprungen ist.
* Fertigkeiten (Fertigkeiten laden)
   Im oberen Fenster sind die Fertigkeiten, die der Charakter kann mit
   dem jeweiligen Erfolgswert angegeben. Au�erdem ist angegeben, wieviele
   GFP die n�chste Stufe (nach oben bzw nach unten) kostet. Beherrscht ein
   Charakter eine Fertigkeit auf dem niedrigsten Erfolgswert, so kannn er 
   diese auch 'verlernen'.
   Im untern Fenster sind die erlernbaren Fertigkeiten mit entsprechenden 
   Kosten angegeben.
* Waffen (Waffen laden)
   Im rechten Bereich sind die Grundkenntnisse der Waffen aufgef�hrt.
   oben die, die der Charakter bereits kann, unten die, die er lernen kann
   (mit Lernkosten in GFP).
   Im linken Bereich stehen oben die Waffen, die der Charakter schon 
   beherrscht (mit Erfolgswert und Kosten f�r die n�chst h�here bzw. 
   niedirgere Stufe), unten stehen die Waffen, die der Charakter mit dem
   Erfolgswert +4 beherrscht, weil er die Grundkenntnisse in der jeweiligen
   Waffenart besitzt. Durch ancklicken kann man Waffen steigern und lernen,
   bzw. Grundkenntnisse lernen.
* Zauber (Zauber laden)
   Oben die Zauber, die ein Charakter kann, unten die, die er lernen darf
   (mit Kosten). W�hlt man einen Zauber aus der oberen Liste, so wird dieser
   'verlernt'.
* Sprachen und Schriften
   Links die Sprachen, rechts die Schriften. Oben jeweils die, die ein 
   Charakter beherrscht, unten die, die er lernen kann.

Einigen selten benutzte Features lassen sich durch das Menu erreichen,
das aufklappt, wenn man den RECHTEN Mausknopf bet�tigt.

Anleitung zur TreeBase-Liste (= Tabellen f�rs Steigern und die Waffen)

* Die Listen k�nnen durch Anklicken der Kopfzeile in beliebiger Reinfolge
   sortiert werden
* Mit der rechten Maustaste �ffnet man ein (hoffentlich selbsterkl�rendes) Men�

";
return s;
}
