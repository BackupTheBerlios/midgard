// $Id: Picture.h,v 1.3 2002/01/21 17:16:59 christof Exp $
/*  Gtk--addons: a collection of gtk-- addons
    Copyright (C) 1998-1999  Adolf Petig GmbH. & Co. KG
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

#include <gdk/gdk.h>

class Picture
{
    public:
        const GdkPixmap *mask,*pmap;

        Picture(GdkPixmap *msk=0,GdkPixmap *mp=0)
                : mask(msk), pmap(mp)
    {}
        Picture(const Picture &tmpl);
        Picture(char **xpm_data,GdkWindow *win=0,GdkColor *trans=0);
        ~Picture();
        Picture &operator=(const Picture&source);
        bool operator!()
        {
            return !mask && !pmap;
        }
};
