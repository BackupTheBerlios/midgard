// $Id: TagStream.hh,v 1.12 2001/04/25 07:59:16 christof Exp $
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Tag.hh"
#include <fstream>
#include <strstream>

class TagStream : public Tag
{	// copied from _GbWidgetLoadData
	static const int GB_BUFFER_SIZE=10240;
	// int line_number;
	char buffer[GB_BUFFER_SIZE];
	bool read_again;
	int pointer,end_pointer;
	std::string encoding;
	
	istream *is;
	ifstream *ifs;
	istrstream *iss;

	char *next_tag(Tag *parent);
	char *next_tag_pointer(Tag *parent);
	bool good();
	
	char *find(const char *start,char what)
	{  return (char*)memchr(start,what,end_pointer-(start-buffer)); }
	char *find(char what)
	{  return (char*)memchr(buffer+pointer,what,end_pointer-pointer); }
	char *find_wordend(char *ptr);
	char *find_wordend2(char *ptr);
	char *find_tagend2(char *ptr);
	void set_pointer(char *ptr) // test for valid range
	{  pointer=ptr-buffer; }
	void write(std::ostream &o,const char *ptr)
	{  int size=end_pointer-(ptr-buffer);
	   if (size>40) size=40;
	   o.write(ptr,size);
	}
	static std::string de_xml(const std::string &cont);
	void load_project_file(Tag *top);
	// encoding -> host_encoding
	std::string recode(const std::string &in) const;
public:
	static std::string host_encoding;

	const Tag *find(const std::string &type) const
	{  return Tag::find(type); }
	Tag::const_iterator find(Tag::const_iterator it,const std::string &type) const
	{  return Tag::find(it,type); }
	TagStream(const std::string &path);
	TagStream(const char *buf);
	TagStream(istream &i);
	~TagStream();
	
	const Tag &getContent() const;
	Tag &getContent();
};
