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

#ifndef _GRADANSTIEG_HH
#  define _GRADANSTIEG_HH
#include <map>
#include <Grundwerte.hh>

class Grad_anstieg{
public:
      static const int AP_Maximum_Tage=28;
      enum ewas{Grad_,Grad_fehlt,Abwehr,Zaubern,Resistenz,Ausdauer};
private:

      struct st_grad{int abwehr;int abwehr_kosten;int resistenz;
                     int resistenz_kosten;int zaubern;int zaubern_kosten;
                     int gfp;int schicksalsgunst; int ap_kosten;
               st_grad()
                  :abwehr(0),abwehr_kosten(0),resistenz(0),
                   resistenz_kosten(0),zaubern(0),zaubern_kosten(0),
                   schicksalsgunst(0),ap_kosten(0) {}
               st_grad(int a,int ak,int r, int rk,int z,int zk, int g,int s,int apk)
                  :abwehr(a),abwehr_kosten(ak),resistenz(r),
                   resistenz_kosten(rk),zaubern(z),zaubern_kosten(zk),
                   gfp(g),schicksalsgunst(s),ap_kosten(apk) {}
               };
      mutable std::map<int,st_grad> map_grad;
      mutable std::map<int,int> map_Abwehr_kosten;  // Index = Erfolgsewert
      mutable std::map<int,int> map_Resistenz_kosten; 
      mutable std::map<int,int> map_Zaubern_kosten; 

      void fill_kosten_maps();
   public:
      Grad_anstieg() {};// anderer ctor war mit progressbar
      Grad_anstieg(bool t) ;
      
//      void getGrad_anstieg();

     
      int get_AP_Kosten(int grad) const;
      int get_MaxAbwehr(int grad) const;
      int get_Abwehr_Kosten(int erfolgswert) const ;
      int get_MaxResistenz(int grad) const ;
      int get_Resistenz_Kosten(int erfolgswert) const;
      int get_MaxZauber(int grad) const ;
      int get_Zauber_Kosten(int erfolgswert) const;

      int get_Grad(int gfp) const ;
      int get_Schicksalsgunst(int grad) const ;
      int getGFP_for(ewas e,const Grundwerte& Werte) const ;
      std::string getGFP_for_str(ewas e,const Grundwerte& Werte) const ;

      int getGFP(int grad) const;
};  
#endif
