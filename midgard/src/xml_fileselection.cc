// generated 2001/5/24 12:36:04 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to xml-fileselection.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "xml_fileselection.hh"
#include "midgard_CG.hh"

void xml_fileselection::on_ok_button1_clicked()
{   
cout << get_filename()<<"\n";
 hauptfenster->xml_import(this->get_filename());
 destroy();
}

void xml_fileselection::on_cancel_button1_clicked()
{   
  destroy();
}

xml_fileselection::xml_fileselection(midgard_CG* h)
{
 hauptfenster=h;
}
