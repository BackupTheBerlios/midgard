// $Id: MidgardBasicTree.hh,v 1.11 2003/09/01 06:47:58 christof Exp $
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

// generated 2001/2/2 11:29:18 CET by thoma@ig23.
// using glademm V0.5_11c

#ifndef _MIDGARDBASICTREE_HH
#  define _MIDGARDBASICTREE_HH 

#include <libmagus/MidgardBasicElement.hh>
#include <SimpleTree.hh>
class midgard_CG;
class Abenteurer;
#include <Misc/compiler_ports.h>

class MidgardBasicTree : public SimpleTree
{
  public: 
      enum variante {GELERNTES,LERNSCHEMA,ANGEBFERT,LERNSCHEMAZUSATZ,
                     LONG_ALT_,LONG_NEU,LONG_NEU_WAFFE,WAFFE_ALT,SPRACHEN_ALT,SPRACHE_NEU,SCHRIFT_ALT,
                     SCHRIFT_NEU,WAFFEGRUND_NEU,WAFFEGRUND_ALT,
                     ZAUBER_ALT,ZAUBER_NEU,ZAUBERWERK_ALT,ZAUBERWERK_NEU,
                     KIDO_ALT,KIDO_NEU,WAFFE_LERNSCHEMA,STEIGERNZUSATZ};
      MidgardBasicTree(variante V);
  private:
      void set_tree_titles(variante V);
      static int Attr(variante V) {return Cols(V);}
      static int Cols(variante V);
  public:
      static void show_list_in_tree(
            const std::list<MBEmlt>& BasicList,
            SimpleTree *Tree, const Abenteurer *a);
//            bool clear_me=true);
};

#endif
