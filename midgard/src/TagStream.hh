// $Id: TagStream.hh,v 1.11 2000/08/28 12:34:56 christof Exp $
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

#include <config.h>
#include "Tag.hh"
#include <fstream>
#include <strstream>

class TagStream
{	// copied from _GbWidgetLoadData
	static const int GB_BUFFER_SIZE=10240;
	// int line_number;
	char buffer[GB_BUFFER_SIZE];
	bool read_again;
	int pointer,end_pointer;
	
	istream *is;
	ifstream *ifs;
	istrstream *iss;

	char *next_tag(Tag *parent);
	char *next_tag_pointer();
	bool good();
	
	char *find(const char *start,char what)
	{  return (char*)memchr(start,what,end_pointer-(start-buffer)); }
#if 0	
	// careful: no range checking done - may BOOOM
	char *find(const char *start,const char *one_of)
	{  char *res=strpbrk(start,one_of); 
	   if (!res || res>end_pointer) return 0;
	}
#endif
	char *find(char what)
	{  return (char*)memchr(buffer+pointer,what,end_pointer-pointer); }
	char *find_wordend(char *ptr);
	void set_pointer(char *ptr) // test for valid range
	{  pointer=ptr-buffer; }
	void write(ostream &o,const char *ptr)
	{  int size=end_pointer-(ptr-buffer);
	   if (size>40) size=40;
	   o.write(ptr,size);
	}
	static string de_xml(const string &cont);
public:
	TagStream(const string &path);
	TagStream(const char *buf);
	~TagStream();
//	char *next_line();
	void load_project_file(Tag *top);
};
