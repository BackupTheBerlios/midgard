// $Id: MagusAusgabe.hh,v 1.1 2003/09/01 06:48:57 christof Exp $
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

#ifndef _MAGUS_AUSGABE_HH
#define _MAGUS_AUSGABE_HH

#include <libmagus/Ausgabe.hh>
#include <vector>
class midgard_CG;

struct Magus_Ausgabe
{	struct entry
	{	Ausgabe::Level l;
		std::string text;
		
		entry(Ausgabe::Level lv,const std::string &t)
			: l(lv), text(t) {}
	};
	static std::vector<entry> remembered;
	
	void attach(midgard_CG *);
	void callback(Ausgabe::Level l,const std::string &text);
	void replay(const entry &e);
};

#endif