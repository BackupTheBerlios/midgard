// $Id: VAbenteurer.hh,v 1.1 2003/08/11 06:26:55 christof Exp $               
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

class VAbenteurer
{
   public:
      struct st_abenteurer{Abenteurer abenteurer;
       			   AbenteurerLernpunkte ab_lp;
      			   std::string filename;
                           bool gespeichert;
             st_abenteurer(const Abenteurer &A,bool g) : abenteurer(A),ab_lp(abenteurer),gespeichert(g) {}
             st_abenteurer() : abenteurer(Abenteurer()),ab_lp(abenteurer),gespeichert(true){} 
             bool operator==(const st_abenteurer& a) const 
               {return abenteurer.getWerte().Name_Abenteurer()==a.abenteurer.getWerte().Name_Abenteurer() &&
                       abenteurer.getWerte().Version() == a.abenteurer.getWerte().Version() ;}
             };
   private:
      std::list<st_abenteurer> VA;
      std::list<st_abenteurer>::iterator ai;

      class sort {
        public: sort() {}
        bool operator()(st_abenteurer x,st_abenteurer y) const
          { return x.abenteurer.getWerte().Gw() < y.abenteurer.getWerte().Gw() ;
          }
      };
      
      SigC::Signal0<void> sig_anderer;

   public:
      VAbenteurer() {}
      
      const std::list<st_abenteurer> &getList() const {return VA;}
      std::list<st_abenteurer> &getList() {return VA;}
      const Abenteurer &getCAbenteurer() const {return ai->abenteurer;}
      Abenteurer &getAbenteurer() {return ai->abenteurer;}
      void sort_gw() {VA.sort(sort());}
      void push_back();
      void setAbenteurer(const std::list<VAbenteurer::st_abenteurer>::iterator &i);
//      void set_Abenteurer(const Abenteurer& A);

      SigC::Signal0<void> &signal_anderer_abenteurer() { return sig_anderer; }
      void modified() {ai->gespeichert=false;}
      void saved() {ai->gespeichert=true;}
      bool gespeichert() const {return ai->gespeichert;}
      void setFilename(std::string s) {ai->filename=s;}
      const std::string &getFilename() {return ai->filename;}

      bool unsaved_exist();
      bool empty() const {return VA.empty();}
      size_t size() const {return VA.size();}
      void delete_empty();

   const Abenteurer *operator->() const
   {  return &ai->abenteurer; }
   Abenteurer *operator->()
   {  return &ai->abenteurer; }

};

#endif
