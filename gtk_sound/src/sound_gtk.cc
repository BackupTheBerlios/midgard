// generated 2001/8/25 19:23:22 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to sound_gtk.cc_new

// This file is for your program, I won't touch it again!

#include <gtk--/main.h>

#include "main_window.hh"

int main(int argc, char **argv)
{   
//   if (argc!=2) {cout << "Bitte Pfad der Sounddateien angeben\n"; exit(0);}
   
   Gtk::Main m(&argc, &argv);
//manage(new class main_window(argv[1]));
  manage(new class main_window("/sound/roleplay/"));
   m.run();
   return 0;
}
