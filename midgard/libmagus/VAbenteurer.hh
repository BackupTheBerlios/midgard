// $Id: VAbenteurer.hh,v 1.4 2003/09/04 07:41:32 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
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

#ifndef CLASS_VABENTEURER_HH
#define CLASS_VABENTEURER_HH

#include "Abenteurer.hh"
#include "AbenteurerLernpunkte.hh"
#include "Undo.hh"
#include "VAbentModelProxy.hh"
#include <sigc++/object.h>

class VAbenteurer : public SigC::Object // um signale zu empfangen
{
   public:
      struct st_abenteurer{Abenteurer abenteurer;
       			   AbenteurerLernpunkte ab_lp;
      			   std::string filename;
      			   Midgard_Undo undo;
                           bool gespeichert;
             st_abenteurer(const Abenteurer &A,bool g) : abenteurer(A),ab_lp(abenteurer),gespeichert(g) {}
             st_abenteurer() : abenteurer(Abenteurer()),ab_lp(abenteurer),gespeichert(true){} 
             bool operator==(const st_abenteurer& a) const 
               {return abenteurer.Name_Abenteurer()==a.abenteurer.Name_Abenteurer() &&
                       abenteurer.Version() == a.abenteurer.Version() ;}
             };
   private:
      std::list<st_abenteurer> VA;

      class sort {
        public: sort() {}
        bool operator()(st_abenteurer x,st_abenteurer y) const
          { return x.abenteurer.Gw() < y.abenteurer.Gw() ;
          }
      };
      void divert_proxy();
      
      std::list<st_abenteurer>::iterator ai;
      SigC::Signal0<void> sig_anderer;
   public:
      VAbentModelProxy proxies;

   public:
      VAbenteurer();
      
      const std::list<st_abenteurer> &getList() const {return VA;}
      std::list<st_abenteurer> &getList() {return VA;}
      void sort_gw() {VA.sort(sort());}
      void push_back();
      bool unsaved_exist();
      bool empty() const {return VA.empty();}
      size_t size() const {return VA.size();}
      void delete_empty();

      // these operate on the concept of a current character
      std::list<st_abenteurer>::iterator actualIterator();
      std::list<st_abenteurer>::const_iterator actualIterator() const;
      const Abenteurer &getCAbenteurer() const {return actualIterator()->abenteurer;}
      const Abenteurer &getAbenteurer() const {return actualIterator()->abenteurer;}
      Abenteurer &getAbenteurer() {return actualIterator()->abenteurer;}
      void setAbenteurer(const std::list<VAbenteurer::st_abenteurer>::iterator &i);
//      void set_Abenteurer(const Abenteurer& A);
      SigC::Signal0<void> &signal_anderer_abenteurer() { return sig_anderer; }

      void modified() {actualIterator()->gespeichert=false;}
      void saved() {actualIterator()->gespeichert=true;}
      bool gespeichert() const {return actualIterator()->gespeichert;}
      void setFilename(std::string s) {actualIterator()->filename=s;}
      const std::string &getFilename() {return actualIterator()->filename;}
      AbenteurerLernpunkte &getLernpunkte() { return actualIterator()->ab_lp; }
      const AbenteurerLernpunkte &getLernpunkte() const { return actualIterator()->ab_lp; }
      void undosave(const std::string &s);
   const Abenteurer *operator->() const
   {  return &actualIterator()->abenteurer; }
   Abenteurer *operator->()
   {  return &actualIterator()->abenteurer; }
};

#endif
