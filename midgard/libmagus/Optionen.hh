// $Id: Optionen.hh,v 1.1 2003/05/08 06:16:11 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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

#ifndef _MIDGARD_OPTIONEN_HH
#  define _MIDGARD_OPTIONEN_HH
#include <list>
#include <string>
#include <BaseObjects/Model.h>

class Optionen
{
   public:
      enum OptionenCheckIndex {Original,NSC_only};
      enum HausIndex {Gold,Werte100};

      struct st_OptionenCheck{OptionenCheckIndex index;std::string text;
               Model<bool> active;
               st_OptionenCheck(OptionenCheckIndex i,std::string t,bool a)
                  :index(i),text(t),active(a)
                  {}
               // this is only sensible for push_back!
               st_OptionenCheck(const st_OptionenCheck &b)
               	  : index(b.index), text(b.text), active(b.active.get_value()) {}
              };
      struct st_Haus{HausIndex index;std::string text;
               Model<bool> active;
               st_Haus(HausIndex i,std::string t,bool a)
                      :index(i),text(t),active(a) {}
               st_Haus(const st_Haus &b)
                     :index(b.index),text(b.text),active(b.active.get_value()){}
                   };
   private:
      std::list<st_Haus> list_Hausregeln;
      std::list<st_OptionenCheck> list_OptionenCheck; 

      void Optionen_init();
      void Hausregeln_init();

   public:
      Optionen();

      void set_Original(bool active,OptionenCheckIndex index);

      std::list<st_Haus> &getHausregeln()  {return list_Hausregeln;}
      std::list<st_OptionenCheck> &getOptionenCheck() {return list_OptionenCheck;}

      void setOptionCheck(std::string os,bool b);
      void setHausregeln(std::string hs,bool b);
      void setAllHausregeln(bool b);

      st_OptionenCheck &OptionenCheck(OptionenCheckIndex oi) ;
      st_Haus &HausregelCheck(HausIndex hi) ;
};

#endif
