// $Id: Ausgabe.hh,v 1.7 2006/01/08 08:46:28 christof Exp $
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

#ifndef _MIDGARD_AUSGABE_HH
#  define _MIDGARD_AUSGABE_HH

#include <string>
#include "NotFound.h"

// grundsätzlich in UTF-8 codiert

struct Ausgabe
{	enum Level { Debug, Log, Warning, ActionNeeded, Error, Fatal, MaxLevel };
	
	typedef void Ausgabe_cb(Level l,const std::string &text);
	static void set(Ausgabe_cb *cb=0);
	Ausgabe(Level l,const std::string &text);
	Ausgabe(Level l,const NotFound &NF);
	// für den Standard-callback
	static void setLogLevel(Level l);
};

#endif
