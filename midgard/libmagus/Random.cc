/* $Id: Random.cc,v 1.1 2003/08/03 01:44:00 christof Exp $ */
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "Random.hh"
#include <stdlib.h>
#include <time.h>

int Random::integer(int min, int max)
{return min + int(((max-min+1.)*rand())/(RAND_MAX+1.0)); }

namespace { struct dummy { dummy() { srand(time(0)); } }; }
static struct dummy dummy;
