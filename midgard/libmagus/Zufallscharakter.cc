/*  Midgard Character Generator
 *  Copyright (C) 2003-2004 Christof Petig 
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

#undef libmagus_COMPILATION
#include "Datenbank.hh"
#include "magustrace.h"
#include <Misc/Trace.h>
//#include "magus_paths.h"
#include <fstream>
#include "Abenteurer.hh"
#include <Misc/TagStream.h>
#include "NotFound.h"
#include "Ausgabe.hh"
#include <Misc/itos.h>
#include "Zufall.hh"
#include "LaTeX_drucken.hh"
#include "spielleiter_export.hh"
//#include "Magus_Optionen.hh"
#include "libmagus.hh"
#include "zufall_steigern.hh"
#include "Random.hh"
#include <getopt.h>

enum { OPT_HERKUNFT=0x200, OPT_TYP, OPT_SPEZIES, OPT_NAME, OPT_GFP, OPT_GRAD };

static struct option long_options[] = {
                   {"Herkunft", 1, 0, OPT_HERKUNFT},
                   {"Typ", 1, 0, OPT_TYP},
                   {"Spezies", 1, 0, OPT_SPEZIES},
                   {"Name", 1, 0, OPT_NAME},
                   {"GFP", 1, 0, OPT_GFP},
                   {"Grad", 1, 0, OPT_GRAD},
                   {0, 0, 0, 0}};

static void progress(double d)
{  Ausgabe(Ausgabe::Log, "Progress " +itos(int(d*100))+ "%");
}

int main(int argc,char **argv)
{  ManuProC::Tracer::Enable(LibMagus::trace_channel,true);
   Ausgabe::setLogLevel(Ausgabe::Debug);
 try {  
   libmagus_init(argc,const_cast<const char**>(argv),&progress);

   Abenteurer a,vorgabe;
   vorgabe.setNameC("random");
   int GFP=zufall_steigern::GFPvonGrad(Random::integer(1,12));
   Zufall::e_Vorgabe was;
   int option_index;
   try
   {int c;
    while ((c = getopt_long(argc, argv, "", long_options, &option_index))!=-1)
    { switch (c)
      {  case OPT_NAME: vorgabe.setNameC(optarg);
            break;
         case OPT_GFP: GFP=atoi(optarg);
            break;
         case OPT_GRAD: GFP=zufall_steigern::GFPvonGrad(atoi(optarg));
            break;
         case OPT_TYP:
            try // Abkürzung
            {  vorgabe.setTyp1(cH_Typen(optarg));
            }
            catch (NotFound &n)
            {  // Langbezeichnung
               vorgabe.setTyp1(Typen::getTyp(optarg));
            }
            was|=Zufall::B_Typ;
            break;
         case OPT_HERKUNFT: vorgabe.setHerkunft(cH_Land(optarg));
            was|=Zufall::B_Herkunft;
            break;
         case OPT_SPEZIES: vorgabe.setSpezies(cH_Spezies(optarg));
            was|=Zufall::B_Spezies;
            break;
      }
    }
   }
   catch (NotFound &n)
   {  Ausgabe(Ausgabe::Error,std::string(long_options[option_index].name)+" "+optarg+" unbekannt");
      exit(1);
   }
   
   Zufall z(a);
   z.Teil(was,vorgabe);
   a.setNameC(vorgabe.Name_Abenteurer());
   
   zufall_steigern zs;
   zs.steigern(a,GFP);
   
   { std::ofstream datei((a.Name_Abenteurer()+".magus").c_str());
     if (!datei.good()) Ausgabe(Ausgabe::Error,"Kann "+a.Name_Abenteurer()+".magus nicht beschreiben");
     else a.speicherstream(datei);
   }
   
   LaTeX_drucken dr;
   dr.Ausdrucken(a);
   
   spielleiter_export_save(a,a.Name_Abenteurer()+".txt");
 } catch (NotFound &e)
 {  Ausgabe(Ausgabe::Error, "NotFound "+ e.Name());  }
}
