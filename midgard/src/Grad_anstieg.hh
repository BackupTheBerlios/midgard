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
#include <gtk--/progressbar.h>
#include <map>
#include <Grundwerte.hh>

class Grad_anstieg{
public:
      enum ewas{Grad,Abwehr,Zaubern,Resistenz,Ausdauer};
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
      map<int,st_grad> map_grad;

      int steigern_EP_prozent;
      int grad_basiswerte; 


   public:
      Grad_anstieg(): steigern_EP_prozent(50), grad_basiswerte(1){}
      Grad_anstieg(Gtk::ProgressBar *progressbar) ;
//      void clear() {*this=Grad_anstieg();}

      int get_Steigern_EP_Prozent() const {return steigern_EP_prozent;}
      int get_Grad_Basiswerte() const {return grad_basiswerte;}

      int get_AP_Kosten(int grad);
      int get_Abwehr(int grad) ;
      int get_Abwehr_Kosten(int grad);
      int get_Resistenz(int grad)  ;
      int get_Resistenz_Kosten(int grad) ;
      int get_Zauber(int grad) ;
      int get_Zauber_Kosten(int grad);

      int get_Grad(int gfp) ;
      int get_Schicksalsgunst(int grad) ;
      int getGFP_for(ewas e,const Grundwerte& Werte);
      std::string getGFP_for_str(ewas e,const Grundwerte& Werte);
      int getGFP_forGrad(int g);


      void set_Grad_Anstieg(int p,int b) 
              { steigern_EP_prozent=p; grad_basiswerte=b; }
      void set_Steigern_EP_Prozent(int i) {steigern_EP_prozent=i;}
      void set_Grad_Basiswerte(int i) {grad_basiswerte=i;}
};  
#endif
