/* $Id: tclist.cc,v 1.8 2002/01/21 17:17:54 christof Exp $ */
/*  Gtk--addons: a collection of gtk-- addons
    Copyright (C) 1998  Adolf Petig GmbH. & Co. KG
    Developed by Christof Petig <christof.petig@wtal.de>
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "TCList.h"
//#include "TCList.h"
#include <gtk--/window.h>
#include <gtk--/main.h>
#include <iostream.h>

class testwindow : public Gtk::Window
{
        TCList *liste;
        /*   Gtk::ScrolledWindow listwin; */
    public:
        testwindow()
        {
            const gchar *title[]={ "customer","article","color","count"};
            const int title_size=sizeof(title)/sizeof(title[0]);
            liste = new TCList(title_size,title);
            add(*liste);

            for (int i=0;i<title_size;i++)
            {
                liste->set_column_width(i,40);
            }
            liste->show();
            liste->freeze();
            {  // the long one
                std::vector <std::string> v;
                v.push_back("0"); v.push_back(""); v.push_back(""); v.push_back("20");
                TCListRow &r1=*(liste->push_back(v)); v.erase(v.begin(),v.end());
                r1.expand();
                r1.set_expanding_column(1);
                r1.set_user_data((gpointer)0x700323);

                const gchar *a00[]={ "","1","","12",0};
                TCListRow &r3=*(r1.push_back(a00,2));
                r3.set_user_data((gpointer)0x690807);
                const gchar *a20[]={ "","","2","2",0 };
                r3.push_back(a20);
                const gchar *a21[]={ "","","3","6",0 };
                r3.push_back(a21);
                const gchar *a22[]={ "","","4","4",0 };
                r3.push_back(a22);

                const gchar *a01[]={ "","2","","8",0 };
                TCListRow &r4=*(r1.push_back(a01,2,true));
                r4.set_user_data((gpointer)0x951229);
                const gchar *a10[]={ "","","2","3",0 };
                r4.push_back(a10);
                const gchar *a11[]={ "","","4","5",0 };
                r4.push_back(a11);

                const gchar *a30[]={ "1","6","7","30",0 };
                liste->push_back(a30);

                const gchar *a40[]={ "2","8","+","10",0 };
                TCListRow &r2=*(liste->push_back(a40,2,true));
                r2.set_user_data((gpointer)0x990411);
                const gchar *a41[]={ "","","3","7",0 };
                r2.push_back(a41);
                const gchar *a42[]={ "","","4","3",0 };
                r2.push_back(a42);
                
                const gchar *am1[]={ "Aller","Anfang","ist","schwer",0 };
                liste->insert(liste->begin(),am1);
                
                const gchar *am2[]={ "Diese","Node","_hatte_","ein Kind",0 };
                TCListRow *rm2=liste->insert(liste->begin(),am2);

                const gchar *am3[]={ "Diese","Node","wird","erscheinen",0 };
                rm2->push_back(am3);
                
                rm2->reparent_children(*liste);
            }
            liste->thaw();
            
//            liste->detach_from_clist();
//            liste->attach_to_clist();

            for (TCList::const_iterator i=liste->begin();i!=liste->end();i++)
                std::cout << *i;
            liste->delete_user.connect(SigC::slot(this,&testwindow::delete_user_imp));
        }
        ~testwindow()
        {
            std::cout << "~testwindow\n";
//            liste->erase(liste->begin(),liste->end());
//            delete liste;
        }
        void delete_user_imp(gpointer x)
        {
            std::cout << x << "\t";
        }
        gint delete_event_impl(GdkEventAny *)
        {
            std::cout << "~delete_event_impl\n";
//            liste->erase(liste->begin(),liste->end());
//            delete liste;
            std::cout << "\n";
            Gtk::Main::instance()->quit();
            return 0;
        }
};


int main( int argc, char **argv )
{
    Gtk::Main m(argc, argv );
    testwindow w;

    w.set_usize( 220,200 );
    w.show();

    m.run();
    return 0;
}
