// $Id: TagStream.cc,v 1.12 2001/02/18 21:26:05 christof Exp $
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

#include "TagStream.hh"
#include <cstring>
#include <unistd.h>
#include <algo.h>

string TagStream::de_xml(const string &cont)
{  string ret;
   string::const_iterator i(cont.begin());
   while (i!=cont.end())
   {  string::const_iterator verbatim(::find(i,cont.end(),'&'));
      ret+=string(i,verbatim);
      if (verbatim!=cont.end())
      {  string::const_iterator endtag(::find(verbatim,cont.end(),';'));
         if (endtag!=cont.end()) ++endtag;
         string tag(verbatim,endtag);
         if (tag=="&amp;") ret+='&';
         else if (tag=="&lt;") ret+='<';
         else if (tag=="&gt;") ret+='>';
         else if (tag=="&quot;") ret+='"';
         else if (tag=="&auml;") ret+='ä'; // and so on ... but glade simply passes them
         else
         {  ret+=tag;
         }
         i=endtag;
      }
      else break;
   }
   return ret;
}

TagStream::TagStream(const string &path) 
	: read_again(false), pointer(0), end_pointer(0), is(0), ifs(0), iss(0)
{  ifs=new ifstream(path.c_str());
   is=ifs;
   is->read(buffer,GB_BUFFER_SIZE);
   end_pointer=is->gcount();
}

TagStream::TagStream(const char *str) 
	: read_again(false), pointer(0), end_pointer(0), is(0), ifs(0), iss(0)
{  iss=new istrstream(str,strlen(str));
   is=iss;
   is->read(buffer,GB_BUFFER_SIZE);
   end_pointer=is->gcount();
}

TagStream::~TagStream()
{  if (ifs) {  delete ifs; ifs=0; }
   if (iss) {  delete iss; iss=0; }
   is=0;
}

void TagStream::load_project_file(Tag *top)
{  while (good() && next_tag(top));
}

bool TagStream::good()
{  return pointer<end_pointer;
}

// winding
// make next tag pointer return the characters in between
// and next tag use it everywhere
char *TagStream::next_tag_pointer()
{  if (pointer>GB_BUFFER_SIZE/2 && end_pointer==GB_BUFFER_SIZE)
   {  memmove(buffer,buffer+pointer,GB_BUFFER_SIZE-pointer);
      end_pointer-=pointer;
      pointer=0;
      is->read(buffer+end_pointer,GB_BUFFER_SIZE-end_pointer);
      end_pointer+=is->gcount();
   }
   char *bra=find('<');
   char *result=bra;
   if (!bra) bra=buffer+end_pointer;
   // kill this nonsense!!! append string to topmost Tag
   for (const char *test=buffer+pointer;test<bra;test++)
   {  if (!isspace((unsigned char)*test))
      {  cerr << "strange chars @'";
         write(cerr,test);
         cerr << "'\n";
         break;
      }
   }
   set_pointer(bra);
   return result;
}

// returns unmatched </tag> or 0
// set pointer should wind
// unify the errors
char *TagStream::next_tag(Tag *parent)
{  // string tag_name="",tag_value="";
   char *tag;
   while ((tag=next_tag_pointer()))
   {  if (tag[1]=='?') // ignore meta-information
      {  char *endtagend=find(tag,'>');
         if (!endtagend) 
         {  cerr << "comment doesn't end @'";
            write(cerr,tag);
            cerr << "'\n";
            return 0;
         }
         set_pointer(endtagend+1);
         continue;
      }
      if (tag[1]=='/') return tag; // unmatched </tag>
      char *tagend=find_wordend(tag);
      if (!tagend) 
      {  cerr << "tag doesn't end @'";
         write(cerr,tag);
         cerr << "'\n";
         return 0;
      }
      Tag *newtag(&parent->push_back(Tag(string(tag+1,tagend-tag-1),"")));
      // read attributes
      while (*tagend!='>')
      {  if (isspace(*tagend)) continue
         if (*tagend=='/')
         {  if (tagend[1]!='>') 
            {  cerr << "strange tag end @'";
               write(cerr,tag);
               cerr << "'\n";
               return 0;
            }
            set_pointer(tagend+2);
            return 0;
         }
         if (isalnum(*tagend))
         {  char *attrend=find_wordend(tagend);
            if (!attrend || *attrend!='=' || 
            	(attrend[1]!='"' && attrend[1]!='\''))
            {  cerr << "strange attribute @'";
               write(cerr,tag);
               cerr << "'\n";
               return 0;
            }
            char *valuestart(attrend+2);
            char *valueend(find(valuestart,attrend[1]));
            newtag->push_back(Tag(string(tagend,attrend-tagend-1),
            		de_xml(string(valuestart,valueend-valuestart-1))));
            tagend=valueend+1;
         }
         else
         {  cerr << "strange attribute char @'"; 
            write(cerr,tag);
            cerr << "'\n";
            return 0;
         }
      }
      char *tagvalue=tagend+1;
      char *valueend=find(tagvalue,'<');
      if (!valueend) 
      {  cerr << __FILE__ << ":" << __LINE__ << "\n";
         return 0;
      }
      newtag->Value(de_xml(string(tagvalue,valueend-tagvalue)));
      // unify
      while (valueend[1]!='/') // this is a nested tag
      {  set_pointer(tagvalue);
         tagvalue=next_tag(newtag); // append children, return pointer
         if (!tagvalue) return 0;
         valueend=find(tagvalue,'<');
         if (!valueend) 
         {  cerr << __FILE__ << ":" << __LINE__ << "\n";
            return 0;
         }
         newtag->push_back(Tag("",de_xml(string(tagvalue,valueend-tagvalue))));
      }
      char *endtagend=find(valueend,'>');
      if (!endtagend) 
      {  cerr << "endtag doesn't end @'";
         write(cerr,valueend);
         cerr << "'\n";
         return 0;
      }
      if (memcmp(valueend+2,newtag->Type().c_str(),newtag->Type().size()))
      {  cerr << "tag <";
         newtag->Type() << "> ended with <";
         cerr.write(valueend+1,endtagend-valueend-2) << ">\n";
      }
      set_pointer(endtagend+1);
   }
   return 0;
}

char *TagStream::find_wordend(char *ptr)
{  while (ptr<end_pointer  && isalnum((unsigned char)*ptr)) ++ptr;
   return ptr>=end_pointer ? 0 : ptr;
}
