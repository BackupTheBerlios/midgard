// $Id: Tag.hh,v 1.13 2001/01/31 12:13:51 christof Exp $
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
#include <config.h>
#include <string>
#include <vector>
#include <algo.h> // for find

class Tag {
    	string type;
    	string value;
    	vector <Tag> sub_specifications;
public:
    	Tag(const string &t,const string &v="") throw()
		: type(t), value(v)
	{}
	Tag &push_back(const Tag t) throw()
	{  sub_specifications.push_back(t);
	   return *(sub_specifications.end()-1);
	}
	typedef vector<Tag>::iterator iterator;
	typedef vector<Tag>::const_iterator const_iterator;
	const_iterator begin() const throw()
	{  return sub_specifications.begin(); }
	const_iterator end() const throw()
	{  return sub_specifications.end(); }
	iterator begin() throw()
	{  return sub_specifications.begin(); }
	iterator end() throw()
	{  return sub_specifications.end(); }
	
	const string Type() const throw()
	{  return type; }
	const string Value() const throw()
	{  return value; }
	void Value(const string &val) throw()
	{  value=val; }
	bool        parse_bool_value() const;
	int         parse_int_value() const;
	long        parse_long_value() const;
	float       parse_float_value() const;
	double      parse_double_value() const;
	
	// slow variants
	const Tag *find(const string &type) const;
	Tag *find(const string &type);
	// please prefer these finds, they are faster!
	const_iterator find(const_iterator it,const string &type) const
	{  return ::find(it,end(),type); }
	iterator find(iterator it,const string &type)
	{  return ::find(it,end(),type); }
	
	// values of substructures
	bool hasTag(const string &typ) const throw();
	const string getString(const string &typ,const string &def="") const throw();
	bool getBool(const string &typ,bool def=false) const throw();
	int getInt(const string &typ,int def=-1) const throw();
	float getFloat(const string &typ,float def=0) const throw();
	void mark(const string &tg,const string &value) throw();
	
	bool operator==(const string &tp) const
	{  return type==tp; }
	bool operator!=(const string &tp) const
	{  return type!=tp; }
	
	void debug(int recursion_depth=2,int indent=0) const;
};
#endif
