// $Id: midgard_CG_oberflaeche.cc,v 1.2 2002/05/11 06:51:31 thoma Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "midgard_CG.hh"


void midgard_CG::setWindowPosition(int x,int y)
{
  Gdk_Window fenster=get_window();
  fenster.move(x,y);
}

void midgard_CG::setWindowSize(int width,int height)
{
  set_default_size(width,height);
}
               
void midgard_CG::autoshrink(bool b)
{
  //set_policy(gint allow_shrink,gint allow_grow,gint auto_shrink);
  set_policy(true,true,b);
}

               