// $Id: xml.h,v 1.6 2003/05/26 06:23:35 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001-2003 Christof Petig
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

#ifndef MCG_XML_H
#define MCG_XML_H

#include <string>
#include <Misc/Model.h> // for easily getting SigC::Slot*
class Datenbank;

void xml_init(SigC::Slot1<void,double> progress,SigC::Slot1<void,const std::string &> meldungen, Datenbank &db);
void xml_free();
#endif
