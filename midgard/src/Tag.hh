// $Id: Tag.hh,v 1.14 2001/04/25 07:59:16 christof Exp $
/*  glade--: C++ frontend for glade (Gtk+ User Interface Builder)
 *  Copyright (C) 1998  Christof Petig
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

#ifndef TAG_HH
#define TAG_HH
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <string>
#include <vector>
#include <algo.h> // for find

class Tag {
    	std::string type;
    	std::string value;
    	std::vector <Tag> sub_specifications;
public:
    	Tag(const std::string &t,const std::string &v="") throw()
		: type(t), value(v)
	{}
	Tag &push_back(const Tag t) throw()
	{  sub_specifications.push_back(t);
	   return *(sub_specifications.end()-1);
	}
	typedef std::vector<Tag>::iterator iterator;
	typedef std::vector<Tag>::const_iterator const_iterator;
	const_iterator begin() const throw()
	{  return sub_specifications.begin(); }
	const_iterator end() const throw()
	{  return sub_specifications.end(); }
	iterator begin() throw()
	{  return sub_specifications.begin(); }
	iterator end() throw()
	{  return sub_specifications.end(); }
	
	const std::string Type() const throw()
	{  return type; }
	const std::string Value() const throw()
	{  return value; }
	void Value(const std::string &val) throw()
	{  value=val; }
	bool        parse_bool_value() const;
	int         parse_int_value() const;
	long        parse_long_value() const;
	float       parse_float_value() const;
	double      parse_double_value() const;
	
	// slow variants
	const Tag *find(const std::string &type) const;
	Tag *find(const std::string &type);
	// please prefer these finds, they are faster!
	const_iterator find(const_iterator it,const std::string &type) const
	{  return ::find(it,end(),type); }
	iterator find(iterator it,const std::string &type)
	{  return ::find(it,end(),type); }
	
	// values of substructures
	bool hasTag(const std::string &typ) const throw();
	const std::string getString(const std::string &typ,const std::string &def="") const throw();
	bool getBool(const std::string &typ,bool def=false) const throw();
	int getInt(const std::string &typ,int def=-1) const throw();
	float getFloat(const std::string &typ,float def=0) const throw();
	void mark(const std::string &tg,const std::string &value) throw();
	
	bool operator==(const std::string &tp) const
	{  return type==tp; }
	bool operator!=(const std::string &tp) const
	{  return type!=tp; }
	
	void debug(int recursion_depth=2,int indent=0) const;
};
#endif
