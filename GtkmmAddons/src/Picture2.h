// $Id: Picture2.h,v 1.6 2002/09/24 15:17:31 christof Exp $
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
#ifndef PICTURE2_H
#define PICTURE2_H


#include <gtkmm/imageloader.h>

class Picture2 : public Gtk::ImageLoaderData 
{	static const char * const empty_image[];
public:
        Picture2(const char * const *  const xpm_data)
		: Gtk::ImageLoaderData(xpm_data)
        {}
        Picture2()
        	: Gtk::ImageLoaderData(empty_image)
        {}
        Gdk_Pixmap pmap() const
        {  return const_cast<Picture2&>(*this).pix();
        }
        Gdk_Pixmap map() const // dangerous name
        {  return const_cast<Picture2&>(*this).pix();
        }
        Gdk_Bitmap mask() const
        {  return const_cast<Picture2&>(*this).bit();
        }
};

#endif
