// $Id: TagStream.hh,v 1.16 2002/06/03 09:53:11 christof Exp $
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
{	// ---- for reading -----
	// copied from _GbWidgetLoadData
	static const int GB_BUFFER_SIZE=10240;
	char buffer[GB_BUFFER_SIZE];
	bool read_again;
	int pointer,end_pointer;

	std::istream *is;
	std::ifstream *ifs;
	std::istrstream *iss;

	char *next_tag(Tag *parent);
	char *next_tag_pointer(Tag *parent);

	char *find_wordend(char *ptr);
	char *find_wordend2(char *ptr);
	char *find_tagend2(char *ptr);
	void set_pointer(char *ptr) // test for valid range
	{  pointer=ptr-buffer; }

	char *find(const char *start,char what)
	{  return (char*)memchr(start,what,end_pointer-(start-buffer)); }
	char *find(char what)
	{  return (char*)memchr(buffer+pointer,what,end_pointer-pointer); }

	static std::string de_xml(const std::string &cont);
	void load_project_file(Tag *top);
	// encoding -> host_encoding
	std::string recode_load(const std::string &in) const;

	// ------ normal operation --------
	std::string encoding;
	std::string file_name;
	
	// ------ saving ------
	std::string recode_save(const std::string &in) const;
	
	// ------ debugging -------
	void write(std::ostream &o,const char *ptr)
	{  int size=end_pointer-(ptr-buffer);
	   if (size>40) size=40;
	   o.write(ptr,size);
	}
public:
	// this is the encoding used in the internal data structures
	static std::string host_encoding;

	TagStream(const std::string &path);
	TagStream(const char *buf);
	TagStream(std::istream &i);
	TagStream();
	~TagStream();
	
	// deprecated, use getContent !
	const Tag *find(const std::string &type) const
	{  return Tag::find(type); }
	Tag::const_iterator find(Tag::const_iterator it,const std::string &type) const
	{  return Tag::find(it,type); }
	
	// throws std::exception if not found
	const Tag &getContent() const;
	Tag &getContent();
	
	bool good();
	
	// writing Tags to a file
	void setFileName(const std::string &s)
	{  file_name=s; }
	void setEncoding(const std::string &s)
	{  encoding=s; }
	bool write(const std::string &filename="",const std::string &_encoding="");
	void write(std::ostream &o) const;
	void write(std::ostream &o, const Tag &t, int indent=0, bool indent_first=true) const;
};
