// $Id: Picture.cc,v 1.3 2002/01/21 17:16:59 christof Exp $
/*  Gtk--addons: a collection of gtk-- addons
    Copyright (C) 1998  Adolf Petig GmbH. & Co. KG
    Developed by Christof Petig <christof.petig@wtal.de>
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <Picture.h>

Picture::Picture(const Picture &tmpl) : mask(tmpl.mask), pmap(tmpl.pmap)
{
    if (mask) gdk_bitmap_ref((GdkPixmap*)mask);
    if (pmap) gdk_pixmap_ref((GdkPixmap*)pmap);
}

Picture::Picture(char **xpm_data,GdkWindow *win,GdkColor *trans)
{
    pmap = gdk_pixmap_create_from_xpm_d (win,(GdkPixmap**)&mask,trans,xpm_data);
}

Picture::~Picture()
{
    if (mask) gdk_bitmap_unref((GdkPixmap*)mask);
    if (pmap) gdk_pixmap_unref((GdkPixmap*)pmap);
}

Picture &Picture::operator=(const Picture &src)
{
    if (src.mask) gdk_bitmap_ref((GdkPixmap*)src.mask);
    if (src.pmap) gdk_pixmap_ref((GdkPixmap*)src.pmap);
    if (mask) gdk_bitmap_unref((GdkPixmap*)mask);
    if (pmap) gdk_pixmap_unref((GdkPixmap*)pmap);
    mask=src.mask; pmap=src.pmap;
    return *this;
}
