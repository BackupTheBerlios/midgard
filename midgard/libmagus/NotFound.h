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

#ifndef LIBMAGUS_NOTFOUND_H
#define LIBMAGUS_NOTFOUND_H

#include <stdexcept>
#include <string>

class NotFound : public std::exception
{	std::string name;
public:
	virtual const char* what() const throw() { return "NotFound"; }
	const std::string &Name() const throw() { return name; }
	NotFound(const std::string &n) : name(n) {}
	virtual ~NotFound() throw() {}
};

#endif
