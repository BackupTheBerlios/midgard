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

#include "table_ausruestung.hh"
#include "midgard_CG.hh"
#include "Data_NewPreis.hh"
#include <Misc/mystring.h>

//static  Gdk_Pixmap drag_icon;
//#include "/tmp/testdrag_and_drop.xpm"

const GtkTargetEntry table_ausruestung::target_table[4] = {
           { "STRING",     0, table_ausruestung::TARGET_STRING },
           { "text/plain", 0, table_ausruestung::TARGET_STRING },
           { "text/uri-std::list", 0, table_ausruestung::TARGET_URL },
           { "application/x-rootwin-drop", 0, table_ausruestung::TARGET_ROOTWIN}
           };

table_ausruestung::table_ausruestung(GlademmData *_data)
: table_ausruestung_glade(_data) , hauptfenster(0), besitz(0)
{
//  target_table=tt;
  n_targets = sizeof(target_table) / sizeof(target_table[0]);

/*
  Gdk_Color transparent;
  Gdk_Colormap cmap ( get_colormap () );
  Gdk_Bitmap drag_mask;


  drag_icon.create_colormap_from_xpm_d ( NULL, // drawable
                                           cmap, // colormap
                                           drag_mask, // mask
                                           transparent,  // transparent color
                                           drag_icon_xpm); // data
*/

// Ausruestung_tree->signal_drag_drop().connect(slot(this,&(table_ausruestung::target_drag_drop)));

  preise_tree_neu->drag_source_set ( static_cast < GdkModifierType > ( GDK_BUTTON1_MASK | GDK_BUTTON3_MASK ) ,
                             target_table, n_targets,
                             static_cast < GdkDragAction > ( GDK_ACTION_COPY | GDK_ACTION_MOVE ) );

//  Ausruestung_tree->signal_drag_data_received().connect(slot(this,&(table_ausruestung::drag_data_received)));

  checkbutton_ausruestung_geld->signal_drag_data_received().connect(SigC::slot(*this,&table_ausruestung::tree_drag_data_received));
  checkbutton_ausruestung_geld->drag_dest_set ( Gtk::DEST_DEFAULT_ALL,
                          target_table, n_targets - 1, /* no rootwin */
                          static_cast < GdkDragAction > ( GDK_ACTION_COPY | GDK_ACTION_MOVE) );

}

void table_ausruestung::tree_drag_data_received(GdkDragContext *context, 
                                  gint x,gint y,
                                  GtkSelectionData   *data,
                                  guint info,guint32 time)
{
  Gdk_DragContext gdc ( context );
  if ( ( data -> length >= 0 ) && ( data -> format == 8 ) )
    {
      std::cout << "Received \""
           << (gchar *)data->data
           << "\" in label"
           << " x="<<x<<" y="<<y
           << endl;

      std::string sdp = (gchar *)data->data;
      int adresse = atoi(sdp.c_str());
cout << "OUT:"<<sdp<<" at "<<adresse<<'\n';


      void *gp = reinterpret_cast<void*>(adresse);
cout << "gp: "<<gp<<'t'<<'\n';
/*
      Data_NewPreis *dp=reinterpret_cast<Data_NewPreis*>(gp);

      cH_Data_NewPreis P(dp);
      P->unref();
cout << "Finaly we got: "<<P->Ware()->Name()<<' '<<P->Kosten()<<'\n';
*/
      Gtk::Widget::drag_finish ( gdc, true, false, time );
      return;
    }
  Gtk::Widget::drag_finish ( gdc , false, false, time );
}



/*
gboolean table_ausruestung::target_drag_drop(GdkDragContext *context,
                                  gint x,gint y, guint time )
{
cout << "Traget Drop\n";
  return false;
}
*/

void table_ausruestung::on_preise_tree_neu_drag_data_get(GdkDragContext *context,     
                                     GtkSelectionData   *selection_data,       
                                     guint               info,
                                     guint32             time )
{
   try{
    cH_Data_NewPreis dt(preise_tree_neu->getSelectedRowDataBase_as<cH_Data_NewPreis>());

/*
   std::string data= dt->Ware()->Name()+"@"+dtos(dt->Kosten())+"@";
   for(std::map<table_ausruestung::e_spalten,PreiseNewMod::st_preismod>::const_iterator i=M.begin();i!=M.end();++i)
      data += i->second.spezifikation+", ";
   ManuProC::remove_last_from(data,", ");
*/
   int *adresse=reinterpret_cast<int*>(dt->ref());
   std::string data=itos(*adresse);

cout << "IN: "<<data<<" at "<<*adresse<<'\t'<<'\n';
   gtk_selection_data_set(selection_data,selection_data->target,8, 
       reinterpret_cast < const unsigned char * > ( data.c_str() ) ,
       data.size() );

   }catch(std::exception &e) {std::cerr << e.what()<<'\n';}   
}

