#ifndef _GRADANSTIEG_HH
#  define _GRADANSTIEG_HH
#include <gtk--/progressbar.h>
#include <map>

class Grad_anstieg{

      struct st_grad{int abwehr;int abwehr_kosten;int resistenz;
                     int resistenz_kosten;int zaubern;int zaubern_kosten;
                     int gfp;
               st_grad()
                  :abwehr(0),abwehr_kosten(0),resistenz(0),
                   resistenz_kosten(0),zaubern(0),zaubern_kosten(0){}
               st_grad(int a,int ak,int r, int rk,int z,int zk, int g)
                  :abwehr(a),abwehr_kosten(ak),resistenz(r),
                   resistenz_kosten(rk),zaubern(z),zaubern_kosten(zk){}
               };
      map<int,st_grad> map_grad;

//      int grad;
      int steigern_EP_prozent;
      int grad_basiswerte; 
/*
      int grad_max_abwehr; 
      int grad_max_resistenz;
      int grad_max_zaubern;
*/
   public:
      Grad_anstieg(): steigern_EP_prozent(50), grad_basiswerte(1){}
      Grad_anstieg(Gtk::ProgressBar *progressbar) ;
//               : grad(1), steigern_EP_prozent(50), grad_basiswerte(1),
//                 grad_max_abwehr(1), grad_max_resistenz(1), grad_max_zaubern(1) {}
//      void clear() {*this=grad_anstieg();}

      int get_Steigern_EP_Prozent() const {return steigern_EP_prozent;}
      int get_Grad_Basiswerte() const {return grad_basiswerte;}

//      int get_Grad() const {return grad;}
      int get_Abwehr(int grad) ;
      int get_Abwehr_Kosten(int grad);
      int get_Resistenz(int grad)  ;
      int get_Resistenz_Kosten(int grad) ;
      int get_Zauber(int grad) ;
      int get_Zauber_Kosten(int grad);

      int get_Grad(int gfp) ;

//      void get_max_werte();
      void set_Grad_Anstieg(int p,int b) 
              { steigern_EP_prozent=p; grad_basiswerte=b; }
//      void set_Grad(int g) {grad=g;}
/*
      void set_Grad_Anstieg(int g) 
              { grad=g; get_max_werte(); }
*/
      void set_Steigern_EP_Prozent(int i) {steigern_EP_prozent=i;}
      void set_Grad_Basiswerte(int i) {grad_basiswerte=i;}
};  
#endif
