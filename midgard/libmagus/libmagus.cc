// $Id: libmagus.cc,v 1.1 2003/08/05 08:55:18 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2003 Christof Petig
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

void libmagus_init0(int argc,const char **argv)
{  magus_paths::init(argv[0]);
   Magus_Optionen::init();
}

void libmagus_init1(void (*progress)(double))
{  Datenbank::init(progress);
}

void libmagus_init(int argc,const char **argv,void (*progress)(double))
{  libmagus_init0(argc,argv);
   libmagus_init1(progress);
}
