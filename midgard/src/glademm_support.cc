// generated 2001/4/23 11:23:23 CEST by thoma@ig23.
// using glademm V0.5_11f_cvs
//
// some glademm convenience functions
//
// DO NOT EDIT THIS FILE !

#include "config.h"
#include "glademm_support.hh"

static map<const __STD::string,Gtk::Widget *> glademm_widgets;

Gtk::Widget * glademm_get_Widget(const __STD::string &name)
{   
   
   map<const __STD::string,Gtk::Widget *>::iterator i=glademm_widgets.find(name);
   if (i==glademm_widgets.end()) return 0;
   return (*i).second;
}

void glademm_set_Widget(const __STD::string &name, Gtk::Widget *val)
{   glademm_widgets[name]=val;
}
