#ifndef _LERNPUNKTE_HH
#  define _LERNPUNKTE_HH



class Lernpunkte {

int fach, waffen, allgemein, unge, zauber;

public:
   Lernpunkte():fach(0),waffen(0),allgemein(0),unge(0),zauber(0){}
   Lernpunkte(int f, int w, int a,int u, int z)
      :fach(f),waffen(w),allgemein(a),unge(0),zauber(z){}

   void clear() {fach=0;waffen=0;allgemein=0;unge=0;zauber=0;}

   int Fach() const {return fach;}
   int Waffen() const {return waffen;}
   int Allgemein() const {return allgemein;}
   int Unge() const {return unge;}
   int Zauber() const { return zauber;}

   void set_Fach(int i) {fach =i;}
   void set_Waffen(int i) {waffen =i;}
   void set_Allgemein(int i) {allgemein =i;}
   void set_Unge(int i) {unge =i;}
   void set_Zauber(int i) {zauber =i;}

//   void set_d_Beruf(int i) {beruf +=i;}
//   void set_d_Fertigkeit(int i) {fertigkeit +=i;}
//   void set_d_Waffen(int i) {waffen +=i;}
//   void set_d_Zauber(int i) {zauber +=i;}
};
#endif
