// $Id: Datenbank.cc,v 1.1 2002/01/19 17:09:33 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2002 Christof Petig
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

#include  <Aux/SQLerror.h>   
#include <Aux/Transaction.h>
#include "Datenbank.hh"

#include <MidgardBasicElement.hh>
#include <vector>
#include <string>
//#include <gtk--/progressbar.h>
#include "Grundwerte.hh"
#include "Land.hh"   
#include "Pflicht.hh"
#include "Spezies.hh"
#include "Typen.hh"
#include "Grad_anstieg.hh"
#include "Lernschema.hh"
#include "Beruf.hh" 
#include "Preise.hh"
#include "Ausruestung.hh"
#include "class_lernpunkte.hh"
#include "Zauber.hh"
#include "Zauberwerk.hh"  
#include "Fertigkeiten.hh"
#include "Waffe.hh"
#include "WaffeGrund.hh"
#include "KiDo.hh"    
#include "Region.hh"  
#include "Ruestung.hh"
#include "Fertigkeiten_angeboren.hh"
#include "Midgard_Info.hh"
#include "Sprache.hh"
#include "Schrift.hh"

Datenbank::Datenbank()
{
    Midgard_Info *MI = manage(new Midgard_Info(true));
#ifndef USE_XML    
    try{
    Transaction tr;
#endif    
    Regionen = Regionen_All(MI->get_progressbar_regionen()).get_All();
    Laender = Laender_All(MI->get_progressbar_laender()).get_All();
    Ruestung = Ruestung_All(MI->get_progressbar_ruestung()).get_All();
    lernschema = Lernschema(MI->get_progressbar_lernschema());
    Beruf = Beruf_All(MI->get_progressbar_beruf()).get_All();
    Fertigkeit_ang = Fertigkeiten_angeborene_All(MI->get_progressbar_ang_fert()).get_All();
    Fertigkeit = Fertigkeiten_All(MI->get_progressbar_fertigkeiten()).get_All();
    WaffeGrund = WaffeGrund_All(MI->get_progressbar_grundkenntnisse()).get_All();
    Waffe = Waffe_All(MI->get_progressbar_waffen()).get_All();
    Waffe_from_Alias = Waffe::fill_map_alias_waffe(MI->get_progressbar_aliaswaffen());
    Zauber = Zauber_All(MI->get_progressbar_zauber()).get_All();
    Zauberwerk = Zauberwerk_All(MI->get_progressbar_zauberwerk()).get_All();
    Kido = KiDo_All(MI->get_progressbar_kido()).get_All();
    Sprache = Sprachen_All(MI->get_progressbar_sprache()).get_All();
    Schrift = Schriften_All(MI->get_progressbar_schrift()).get_All();
    pflicht = Pflicht(MI->get_progressbar_pflicht());
    ausnahmen = Ausnahmen(MI->get_progressbar_ausnahmen());
    Spezies = Spezies_All(MI->get_progressbar_spezies()).get_All();
    Typen = Typen_All(MI->get_progressbar_typen()).get_All();
    GradAnstieg = Grad_anstieg(MI->get_progressbar_grad());
    Spezialgebiet = Spezialgebiet_All(MI->get_progressbar_spezial()).get_All();
    preise = Preise_All(MI->get_progressbar_preise()).get_All();
    preisemod = PreiseMod_All(MI->get_progressbar_preise()).get_All();
#ifndef USE_XML    
    tr.close();
   }
   catch(SQLerror &e) {cerr<< e.what()<<'\n'; return;}
#endif  
    MI->on_button_close_clicked();
}