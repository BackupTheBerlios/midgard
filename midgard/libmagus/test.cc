#include "Datenbank.hh"
#include "magustrace.h"
#include <Misc/Trace.h>
#include "magus_paths.h"
#include <fstream>
#include "Abenteurer.hh"
#include <Misc/TagStream.h>
#include <NotFound.h>
#include "Ausgabe.hh"
#include <Misc/itos.h>

void progress(double d)
{  Ausgabe(Ausgabe::Warning, "Progress " +itos(d)+ "%");
}

int main(int argc,char **argv)
{  ManuProC::Tracer::Enable(LibMagus::trace_channel,true);
   Datenbank db;
   if (argc>1) TagStream::host_encoding=argv[1];
   magus_paths::init(argv[0]);
 try {  
   db.load(&progress);
   
   std::ifstream fi("../../charaktere/Christof Petig/Aneren.magus");
   Abenteurer a;
   if (!a.xml_import_stream(fi,db)) 
      Ausgabe(Ausgabe::Error, "Laden fehlgeschlagen");
 } catch (NotFound &e)
 {  Ausgabe(Ausgabe::Error, "NotFound "+ e.Name());  }
}
