// $Id: MidgardBasicTree.hh,v 1.13 2004/12/16 08:24:52 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *  Copyright (C) 2004 Christof Petig
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

#ifndef _MIDGARDBASICTREE_HH
#  define _MIDGARDBASICTREE_HH 

#include <libmagus/MidgardBasicElement.hh>
#include <SimpleTree.hh>
#include <Misc/compiler_ports.h>
#include <libmagus/VAbenteurer.hh>

class MidgardBasicTree : public SimpleTree
{
  public: 
      enum variante {GELERNTES,LERNSCHEMA,ANGEBFERT,LERNSCHEMAZUSATZ,
                     LONG_ALT_,LONG_NEU,LONG_NEU_WAFFE,WAFFE_ALT,
                     SPRACHEN_ALT,SPRACHE_NEU,SCHRIFT_ALT,
                     SCHRIFT_NEU,WAFFEGRUND_NEU,WAFFEGRUND_ALT,
                     ZAUBER_ALT,ZAUBER_NEU,ZAUBERWERK_ALT,ZAUBERWERK_NEU,
                     KIDO_ALT,KIDO_NEU,WAFFE_LERNSCHEMA,STEIGERNZUSATZ,
                     
                     FERT_ALT=LONG_ALT_,FERT_NEU=LONG_NEU, 
                     WAFFE_NEU=LONG_NEU_WAFFE,
                    };
      MidgardBasicTree(variante V);
  private:
// nette Idee, ich brauche aber zum aktualisieren cH_RowDataBase!
//      SigC::Signal1<void,const MBEmlt &> _clicked;
      SigC::Signal1<void,cH_RowDataBase> _clicked;
      variante was_isses;
      
      void set_tree_titles(variante V);
      static int Attr(variante V) {return Cols(V);}
      static int Cols(variante V);
      static bool clicked_impl(SimpleTree_Basic *_this, const cH_RowDataBase &row, int col_idx);
  public:
      static void show_list_in_tree(
            const std::list<MBEmlt>& BasicList,
            SimpleTree *Tree, VAbenteurer::const_iterator a);
//            bool clear_me=true);
      SigC::Signal1<void,cH_RowDataBase> &signal_clicked()
      {  return _clicked; }
};

#endif
