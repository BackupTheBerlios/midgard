


class Lernpunkte {

int beruf, fertigkeit, waffen, zauber;

public:
   Lernpunkte():beruf(0),fertigkeit(0),waffen(0),zauber(0){}
   Lernpunkte(int b, int f, int w, int z)
      :beruf(b),fertigkeit(f),waffen(w),zauber(z){}

   void clear() {beruf=0;fertigkeit=0;waffen=0;zauber=0;}

   int Beruf() const {return beruf;}
   int Fertigkeiten() const {return fertigkeit;}
   int Waffen() const {return waffen;}
   int Zauber() const { return zauber;}

   void set_Beruf(int i) {beruf =i;}
   void set_Fertigkeit(int i) {fertigkeit =i;}
   void set_Waffen(int i) {waffen =i;}
   void set_Zauber(int i) {zauber =i;}

//   void set_d_Beruf(int i) {beruf +=i;}
//   void set_d_Fertigkeit(int i) {fertigkeit +=i;}
//   void set_d_Waffen(int i) {waffen +=i;}
//   void set_d_Zauber(int i) {zauber +=i;}
};
