// $Id: Tag.hh,v 1.14 2001/04/25 07:59:16 christof Exp $
/*  glade--: C++ frontend for glade (Gtk+ User Interface Builder)
 *  Copyright (C) 1998-2002  Christof Petig
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
    	typedef std::vector <std::pair<std::string,std::string> > attvec_t;
    	attvec_t attributes;
    	std::vector <Tag> sub_specifications;

	static bool parse_bool_value(const std::string &val, bool def=false);
	static int parse_int_value(const std::string &val, int def=0);
	static long parse_long_value(const std::string &val, long def=0);
	static float parse_float_value(const std::string &val, float def=0);
	static double parse_double_value(const std::string &val, double def=0);
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
	
	bool        parse_bool_value() const
	{  return parse_bool_value(Value()); }
	int         parse_int_value() const
	{  return parse_int_value(Value()); }
	long        parse_long_value() const
	{  return parse_long_value(Value()); }
	float       parse_float_value() const
	{  return parse_float_value(Value()); }
	double      parse_double_value() const
	{  return parse_double_value(Value()); }
	
	// slow variants
	const Tag *find(const std::string &type) const;
	Tag *find(const std::string &type);
	// please prefer these finds, they are faster!
	const_iterator find(const_iterator it,const std::string &type) const
	{  return ::find(it,end(),type); }
	iterator find(iterator it,const std::string &type)
	{  return ::find(it,end(),type); }

	// values of attributes
	attvec_t::iterator attend() { return attributes.end(); }
	attvec_t::const_iterator attend() const { return attributes.end(); }
	attvec_t::iterator attfind(const std::string &name);
	attvec_t::const_iterator attfind(const std::string &name) const;
	
	const std::string &getAttr(const std::string &name, const std::string &def="") const throw();
	void setAttr(const std::string &name, const std::string &value);
	
	bool getBoolAttr(const std::string &typ,bool def=false) const throw();
	int getIntAttr(const std::string &typ,int def=-1) const throw();
	float getFloatAttr(const std::string &typ,float def=0) const throw();
	
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
