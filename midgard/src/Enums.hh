// $Id: Enums.hh,v 1.5 2002/12/11 12:19:19 thoma Exp $               
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

#ifndef CLASS_ENUMS
#define CLASS_ENUMS

namespace Enums
{
   enum geschlecht{NoFM,Mann,Frau};
   enum StadtLand{NoSL,Stadt,Land};
   enum e_wie_steigern{eUnterweisung,eSelbststudium,ePraxis,eSpruchrolle};
   enum e_was_steigern{eMBEm,eAusdauer,eAbwehr,eZaubern,eResistenz};
   struct st_bool_steigern{bool mitEP;bool HausG1;bool Spruchrolle; bool
                        SpruchrolleAuto;
                        bool hoch_wie_geht; bool pp_verfallen; bool aep_fuellen;
                        bool neue_sprache_pp;
          st_bool_steigern(bool m,bool H,bool S,bool Sa,bool h,bool v,bool a,bool n)
              : mitEP(m),HausG1(H),Spruchrolle(S),SpruchrolleAuto(Sa),
                  hoch_wie_geht(h),
                  pp_verfallen(v),aep_fuellen(a),neue_sprache_pp(n)
                  {}
                    };

   enum MBEListen {sFert,sWaff,sZaub,sSpra,sSchr,sWGru,sZWerk,sKiDo};

};



class H_MidgardBasicElement_mutable;

typedef H_MidgardBasicElement_mutable MBEmlt;



#endif
