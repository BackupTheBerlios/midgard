// generated 2001/2/2 12:23:26 CET by thoma@ig23.
// using glademm V0.5_11c
//
// newer (non customized) versions of this file go to midgard.cc_glade

// This file is for your program, I won't touch it again!

#include <gtk--/main.h>

#include "midgard_CG.hh"
#include "Window_werte_editieren.hh"
#include "Window_lernpunkte_editieren.hh"
#include <Aux/dbconnect.h>

int main(int argc, char **argv)
{   
   Gtk::Main m(&argc, &argv);
   try {
      Petig::Connection conn;
      conn.setDbase("midgard");
      Petig::dbconnect(conn);

      midgard_CG *midgard_cg = manage(new midgard_CG());

      m.run();
      Petig::dbdisconnect();
   } catch (SQLerror &e)
   {  cerr << e << '\n';
      return 1;
   }
   return 0;
}
