#include "Datenbank.hh"
#include <iostream>
#include "magustrace.h"
#include <Misc/Trace.h>
#include "magus_paths.h"
#include <fstream>
#include "Abenteurer.hh"
#include <Misc/TagStream.h>

void progress(double d)
{  std::cout << "Progress " << d << "%\n";
}

void meldung(const std::string &d)
{  std::cout << "Msg: " << d << "\n";
}

int main(int argc,char **argv)
{  ManuProC::Tracer::Enable(LibMagus::trace_channel,true);
   Datenbank db;
   if (argc>1) TagStream::host_encoding=argv[1];
   magus_paths::init(argv[0]);
   db.load(&progress,&meldung);
   
   std::ifstream fi("../../charaktere/Christof Petig/Aneren.magus");
   Abenteurer a;
   if (!a.xml_import_stream(fi,db)) 
      std::cerr << "Laden fehlgeschlagen\n";
}
