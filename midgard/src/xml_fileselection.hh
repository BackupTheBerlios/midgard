// generated 2001/5/24 12:36:04 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to xml-fileselection.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _XML_FILESELECTION_HH
#  include "xml_fileselection_glade.hh"
#  define _XML_FILESELECTION_HH
#include "glademm_support.hh"

class midgard_CG;

class xml_fileselection : public xml_fileselection_glade
{   
        midgard_CG* hauptfenster;        
        string was;
        friend class xml_fileselection_glade;
        void on_ok_button1_clicked();
        void on_cancel_button1_clicked();
   public:
      xml_fileselection(midgard_CG* h,string _was);
};
#endif
