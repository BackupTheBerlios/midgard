// $Id: TagStream.cc,v 1.13 2001/04/25 07:59:16 christof Exp $
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

std::string TagStream::de_xml(const std::string &cont)
{  std::string ret;
   std::string::const_iterator i(cont.begin());
   while (i!=cont.end())
   {  std::string::const_iterator verbatim(::find(i,cont.end(),'&'));
      ret+=std::string(i,verbatim);
      if (verbatim!=cont.end())
      {  std::string::const_iterator endtag(::find(verbatim,cont.end(),';'));
         if (endtag!=cont.end()) ++endtag;
         std::string tag(verbatim,endtag);
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

TagStream::TagStream(const std::string &path) 
	: Tag(""), read_again(false), pointer(0), end_pointer(0), is(0), ifs(0), iss(0)
{  ifs=new ifstream(path.c_str());
   is=ifs;
   is->read(buffer,GB_BUFFER_SIZE);
   end_pointer=is->gcount();
   load_project_file(this);
}

TagStream::TagStream(const char *str) 
	: Tag(""), read_again(false), pointer(0), end_pointer(0), is(0), ifs(0), iss(0)
{  iss=new istrstream(str,strlen(str));
   is=iss;
   is->read(buffer,GB_BUFFER_SIZE);
   end_pointer=is->gcount();
   load_project_file(this);
}

TagStream::TagStream(istream &i) 
	: Tag(""), read_again(false), pointer(0), end_pointer(0), is(0), ifs(0), iss(0)
{  is=&i;
   is->read(buffer,GB_BUFFER_SIZE);
   end_pointer=is->gcount();
   load_project_file(this);
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
char *TagStream::next_tag_pointer(Tag *parent)
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
   if (bra>buffer+pointer) parent->push_back(Tag("",de_xml(std::string(buffer+pointer,bra-(buffer+pointer)))));
   set_pointer(bra);
   return result;
}

#if 0
#define ERROR3(name,ptr,end) \
	{ std::cerr << name " @'"; \
	  std::cerr.write(ptr,ptr+10>end?end-ptr:10); \
	  std::cerr << "'\n"; \
	  return 0; \
	}
#endif	
#define ERROR2(name,ptr) \
	({ std::cerr << name " @'"; \
	  std::cerr.write(ptr,10); \
	  std::cerr << "'\n"; \
	  return 0; \
	})

static bool isword(unsigned char x)
// accepting d7 and f7 violates standard ... who cares
{  return isalnum(x)||strchr(".-_:",x)||x>=0xc0;
}

static bool isword0(unsigned char x)
// accepting d7 and f7 violates standard ... who cares
{  return isalnum(x)||strchr("_:",x)||x>=0xc0;
}

char *TagStream::find_wordend(char *ptr)
{  while (ptr<buffer+end_pointer && isword(*ptr)) ++ptr;
   return ptr>=buffer+end_pointer ? 0 : ptr;
}

// returns unmatched </tag> or 0
// set pointer should wind
// unify the errors
char *TagStream::next_tag(Tag *parent)
{  char *tag;
   while ((tag=next_tag_pointer(parent)))
   {  if (tag[1]=='?') // meta tag
      {  char *tagend=find_wordend(tag+2);
         if (!tagend) ERROR2("tag doesn't end",tag);
         
         Tag *newtag(&parent->push_back(Tag(std::string(tag+1,tagend-(tag+1)),"")));
         while (tagend)
         {  while (isspace(*tagend)) tagend++;
            if (*tagend=='?')
            {  if (tagend[1]!='>') ERROR2("strange tag end (?[^>])",tag);
               set_pointer(tagend+2);
               goto continue_outer;
            }
            if (isword0(*tagend))
            {  char *attrend=find_wordend(tagend);
               if (!attrend || *attrend!='=' || 
               	(attrend[1]!='"' && attrend[1]!='\''))
                  ERROR2("strange attribute",tagend);
               char *valuestart(attrend+2);
               char *valueend(find(valuestart,attrend[1]));
               if (valueend)
               {  newtag->push_back(Tag(std::string(tagend,attrend-tagend),
               		de_xml(std::string(valuestart,valueend-valuestart))));
                  tagend=valueend+1;
               }
               else ERROR2("value does not end",valuestart);
            }
            else ERROR2("strange attribute char",tag);
         }         
         continue; // outer
      }
      if (tag[1]=='-' && tag[2]=='-')
      {  char *endcomment=find(tag+3,'-');
         while (endcomment && endcomment[1]!='-' && endcomment[2]!='>')
            endcomment=find(endcomment+1,'-');
         if (!endcomment) ERROR2("Comment does not end",tag);
         parent->push_back(Tag("--",std::string(tag+3,endcomment-(tag+3))));
         set_pointer(endcomment+3);
         continue; // outer
      }
      if (tag[1]=='/') 
         return tag; // unmatched </tag>
      // normal tag
      {  char *tagend=find_wordend(tag+1);
         if (!tagend) ERROR2("tag doesn't end",tag);
         
         Tag *newtag(&parent->push_back(Tag(std::string(tag+1,tagend-(tag+1)),"")));
         // read attributes
         while (tagend)
         {  while (isspace(*tagend)) tagend++;
            if (*tagend=='/')
            {  if (tagend[1]!='>') ERROR2("strange tag end (/[^>])",tag);
               set_pointer(tagend+2);
               goto continue_outer;
            }
            if (*tagend=='>') break;
            if (isword0(*tagend))
            {  char *attrend=find_wordend(tagend);
               if (!attrend || *attrend!='=' || 
               	(attrend[1]!='"' && attrend[1]!='\''))
                  ERROR2("strange attribute",tagend);
               char *valuestart(attrend+2);
               char *valueend(find(valuestart,attrend[1]));
               if (valueend)
               {  newtag->push_back(Tag(std::string(tagend,attrend-tagend),
               		de_xml(std::string(valuestart,valueend-valuestart))));
                  tagend=valueend+1;
               } else ERROR2("value does not end",valuestart);
            }
            else ERROR2("strange attribute char",tagend);
         }
         char *tagvalue=tagend+1;
         char *valueend=find(tagvalue,'<');
         if (!valueend) ERROR2("premature value end",tagvalue);
         newtag->Value(de_xml(std::string(tagvalue,valueend-tagvalue)));
         set_pointer(valueend);
         if (valueend[1]!='/') tagvalue=next_tag(newtag); // recurse
         else tagvalue=valueend;
         
         if (!tagvalue) ERROR2("premature nested value end",tagvalue);
         if (tagvalue[1]!='/') ERROR2("not ending?",tagvalue);
         char *endtagend=find(tagvalue+1,'>');
         if (!endtagend) ERROR2("endtag doesn't end",valueend);
         if (memcmp(tagvalue+2,newtag->Type().c_str(),newtag->Type().size()))
         {  std::cerr << "tag <" << newtag->Type() << "> ended with </";
            std::cerr.write(tagvalue+2,endtagend-tagvalue-2-1) << ">\n";
         }
         set_pointer(endtagend+1);
       }
       continue_outer: ;
   }
   return 0;
}

