/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
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
 
#ifndef _TABLE_ZUFALL_HH
#  include "table_ausruestung_glade.hh"
#  define _TABLE_ZUFALL_HH

class midgard_CG;
#include "table_zufall_glade.hh"


class table_zufall : public table_zufall_glade
{
      friend class table_zufall_glade;
      friend class midgard_CG;

      midgard_CG *hauptfenster;

   public:
      table_zufall(GlademmData *_data)
         : table_zufall_glade(_data) , hauptfenster(0) {}


      void init(midgard_CG *hauptfenster);

   private:
      // automatisch von grale erzeugte Methoden
      void on_button_zufall_voll_clicked();

};

#endif
