// $Id: Geheimzeichen.hh,v 1.1 2002/02/09 16:14:06 thoma Exp $               
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

#ifndef GEHEIMZEICHENCLASS
#define GEHEIMZEICHENCLASS
#include <Aux/Handles.h>
#include <Aux/CacheStatic.h>
#include <vector>
#include <string>
#include <gtk--/progressbar.h>
#include "xml.h"

class Geheimzeichen  : public HandleContent
{
   std::string name; 
//   Geheimzeichen() {};

  public:
   Geheimzeichen(const Tag *tag);

   std::string Name() const   {return name; }
};

class cH_Geheimzeichen : public Handle<const Geheimzeichen>
{
    typedef CacheStatic<std::string,cH_Geheimzeichen> cache_t;
    static cache_t cache;
    friend class std::map<std::string,cH_Geheimzeichen>;
    cH_Geheimzeichen(){}
  public:
   cH_Geheimzeichen(const Geheimzeichen *s) : Handle<const Geheimzeichen>(s) {};
   cH_Geheimzeichen(const Tag *tag);
   cH_Geheimzeichen(const std::string& name ,bool create=false);
//   cH_Geheimzeichen() {*this=new Geheimzeichen();}
};

class Geheimzeichen_All
{
   std::vector<cH_Geheimzeichen> list_All;
  public:
   Geheimzeichen_All(Gtk::ProgressBar *progressbar);
   std::vector<cH_Geheimzeichen> get_All() const {return list_All;}
};

#endif
