// $Id: readxml.cc,v 1.2 2003/05/19 06:10:34 christof Exp $
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

// Simple TagStream testing program

#include <Misc/TagStream.h>
#include <iostream>

int main(int argc, char ** argv)
{  if (argc<2) TagStream ts(std::cin);
   else
   {  for (int i=1;i<argc;++i) 
      {  // std::cout << argv[i] << '\n';
         TagStream ts((0,std::string(argv[i])));
      }
   }
   return 0;
}
