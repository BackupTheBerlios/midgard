// $Id: libmagus.cc,v 1.6 2004/08/30 13:17:56 christof Exp $               
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

#include "libmagus.hh"
#include "magus_paths.h"
#include "Magus_Optionen.hh"
#include "Datenbank.hh"
#include "AbenteurerAuswahl.h"
#include "magustrace.h"
#include <Misc/Trace.h>

void libmagus_init0(int argc,const char **argv)
{  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__,argv[0]);
  magus_paths::init(argv[0]);
   Magus_Optionen::init();
   Programmoptionen->load_options(magus_paths::with_path("magus_optionen.xml",false,true));
}

void libmagus_init1(void (*progress)(double))
{  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  Datenbank::init(progress);
   AbenteurerAuswahl::Chars=new VAbenteurer;
}

void libmagus_init(int argc,const char **argv,void (*progress)(double))
{  ManuProC::Trace _t(LibMagus::trace_channel,__FUNCTION__);
  libmagus_init0(argc,argv);
   libmagus_init1(progress);
}
