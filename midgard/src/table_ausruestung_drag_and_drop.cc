/*  Midgard Character Generator
 *  Copyright (C) 2001-2002 Malte Thoma
 *  Copyright (C) 2005 Christof Petig
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

#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
   typedef Gtk::SelectionData &selection_data_t;
#  define GTKMM24(x) x
#include <sigc++/bind.h>
#else
   typedef GtkSelectionData* selection_data_t;
#  define GTKMM24(x)
#endif

class MyTreeStore : public Gtk::TreeStore
{	MyTreeStore(const Gtk::TreeModelColumnRecord& cols) 
		: Gtk::TreeStore(cols) {}
	virtual bool drag_data_get_vfunc(const Gtk::TreeModel::Path& path, selection_data_t selection_data);
	virtual bool drag_data_delete_vfunc(const Gtk::TreeModel::Path& path);
	virtual bool drag_data_received_vfunc(const TreeModel::Path& dest, selection_data_t selection_data);
public:
	static Glib::RefPtr<MyTreeStore> MyTreeStore::create(const Gtk::TreeModelColumnRecord& cols)
	{  MyTreeStore *x=new MyTreeStore(cols);
 	   x->reference();
	   return Glib::RefPtr<MyTreeStore>(x);
	}
};

bool MyTreeStore::drag_data_get_vfunc(const Gtk::TreeModel::Path& path, 
					selection_data_t selection_data)
{ 
std::cerr << "drag_data_get " << path.to_string() << ' ' << selection_data GTKMM24(.gobj())->target << '\n'; 
   return Gtk::TreeStore::drag_data_get_vfunc(path,selection_data);
//   return false;
}

bool MyTreeStore::drag_data_delete_vfunc(const Gtk::TreeModel::Path& path)
{ 
std::cerr << "drag_data_delete " << path.to_string() << '\n'; 
   return false;
}

#include <gtk/gtktreednd.h>

bool MyTreeStore::drag_data_received_vfunc(const Gtk::TreeModel::Path& dest, 
					selection_data_t selection_data)
{  GtkTreeModel *model=0;
   GtkTreePath *path=0;
   if (!gtk_tree_get_row_drag_data(selection_data GTKMM24(.gobj()),&model,&path)) 
      return false;
std::cerr << "drag_data_received " << dest.to_string() << ' ' << model
<< ' ' << Gtk::TreeModel::Path(path,false).to_string() << '\n';
   if (model!=GTK_TREE_MODEL(gobj())) 
   {  std::cerr << "my model is @"<< gobj() << '\n';
//      goto out;
//    out:
      if (path) gtk_tree_path_free(path);
      return false;
   }
   // von Node suchen, löschen, nach Node suchen, einfügen
std::cerr << "gtk-tree-model-drop-append=" << get_data("gtk-tree-model-drop-append") << '\n';
   
   Gtk::TreeIter sourceit=get_iter(Gtk::TreeModel::Path(path,false)),
   	destit=get_iter(dest);
#if 0   	
   move(sourceit,destit);
#endif   
//   Gtk::TreeIter newit=insert(destit);
   if (path) gtk_tree_path_free(path);
   return true;
}

void table_ausruestung::on_preise_tree_neu_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&context,
                                     selection_data_t    selection_data,
                                     guint               info,
                                     guint32             time )
{
}

#if 1
//static  Gdk_Pixmap drag_icon;
//#include "/tmp/testdrag_and_drop.xpm"

const GtkTargetEntry table_ausruestung::target_table[4] = {
           { "STRING",     0, table_ausruestung::TARGET_STRING },
           { "text/plain", 0, table_ausruestung::TARGET_STRING },
           { "text/uri-std::list", 0, table_ausruestung::TARGET_URL },
           { "application/x-rootwin-drop", 0, table_ausruestung::TARGET_ROOTWIN}
           };
#endif

table_ausruestung::table_ausruestung(GlademmData *_data)
: table_ausruestung_glade(_data) , hauptfenster(), besitz(),
	Ausruestung_tree()
{
//  target_table=tt;
//  n_targets = sizeof(target_table) / sizeof(target_table[0]);

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

#if 0
  preise_tree_neu->drag_source_set ( static_cast < GdkModifierType > ( GDK_BUTTON1_MASK | GDK_BUTTON3_MASK ) ,
                             target_table, n_targets,
                             static_cast < GdkDragAction > ( GDK_ACTION_COPY | GDK_ACTION_MOVE ) );

//  Ausruestung_tree->signal_drag_data_received().connect(slot(this,&(table_ausruestung::drag_data_received)));

  checkbutton_ausruestung_geld->signal_drag_data_received().connect(SigC::slot(*this,&table_ausruestung::tree_drag_data_received));
  checkbutton_ausruestung_geld->drag_dest_set ( Gtk::DEST_DEFAULT_ALL,
                          target_table, n_targets - 1, /* no rootwin */
                          static_cast < GdkDragAction > ( GDK_ACTION_COPY | GDK_ACTION_MOVE) );
#endif                          

  Ausruestung_tree=manage(new Gtk::TreeView());
  m_refStore= MyTreeStore::create(m_columns);
  Ausruestung_tree->enable_model_drag_source();
  Ausruestung_tree->enable_model_drag_dest();
  Ausruestung_tree->set_model(m_refStore);
  Ausruestung_tree->append_column("Titel",m_columns.name);
  Ausruestung_tree->append_column("Material",m_columns.material);
  Ausruestung_tree->append_column("Anzahl",m_columns.anzahl);
  Ausruestung_tree->append_column("Gewicht",m_columns.gewicht);
  Ausruestung_tree->append_column("Sichtbar",m_columns.sichtbar);
  Ausruestung_tree->append_column("Region",m_columns.region);
  Ausruestung_tree->show(); 
  scrolledwindow_ausruestung->add(*Ausruestung_tree);
   table_gruppe->hide();
   table_artikel->hide();      
   togglebutton_artikel_neu->set_active(false);
   togglebutton_gruppe_neu->set_active(false); 
//   fill_new_preise();
   fill_all_Combos_Art_Einheit_Region();
   fill_all_Combo_Art2();
   preise_tree_neu->enable_model_drag_source();
//  sichtbarConnection=checkbutton_sichtbar->signal_toggled().connect(SigC::slot(*static_cast<class table_ausruestung*>(this), &table_ausruestung::on_checkbutton_sichtbar_toggled));
  dynamic_cast<Gtk::CellRendererText*>(Ausruestung_tree->get_column(sTitel)->get_first_cell_renderer())
      ->property_editable()=true;
  dynamic_cast<Gtk::CellRendererText*>(Ausruestung_tree->get_column(sTitel)->get_first_cell_renderer())
      ->signal_edited().connect(SigC::bind(SigC::slot(*this,&table_ausruestung::cell_edited),sTitel));
  dynamic_cast<Gtk::CellRendererText*>(Ausruestung_tree->get_column(sMaterial)->get_first_cell_renderer())
      ->property_editable()=true;
  dynamic_cast<Gtk::CellRendererText*>(Ausruestung_tree->get_column(sMaterial)->get_first_cell_renderer())
      ->signal_edited().connect(SigC::bind(SigC::slot(*this,&table_ausruestung::cell_edited),sMaterial));
  dynamic_cast<Gtk::CellRendererText*>(Ausruestung_tree->get_column(sAnzahl)->get_first_cell_renderer())
      ->property_editable()=true;
  dynamic_cast<Gtk::CellRendererText*>(Ausruestung_tree->get_column(sAnzahl)->get_first_cell_renderer())
      ->signal_edited().connect(SigC::bind(SigC::slot(*this,&table_ausruestung::cell_edited),sAnzahl));
//  Ausruestung_tree->get_column(sSichtbar)->get_first_cell_renderer()
//      ->property_sensitive()=true;
  dynamic_cast<Gtk::CellRendererToggle*>(Ausruestung_tree->get_column(sSichtbar)->get_first_cell_renderer())
      ->property_activatable()=true;
  dynamic_cast<Gtk::CellRendererToggle*>(Ausruestung_tree->get_column(sSichtbar)->get_first_cell_renderer())
      ->signal_toggled().connect(SigC::slot(*this,&table_ausruestung::cell_edited_bool));
}

#if 0
// GdkDragContext *context, 
void table_ausruestung::tree_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
                                  gint x,gint y,
                                  selection_data_t data,
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
std::cout << "OUT:"<<sdp<<" at "<<adresse<<'\n';


      void *gp = reinterpret_cast<void*>(adresse);
std::cout << "gp: "<<gp<<'t'<<'\n';
/*
      Data_NewPreis *dp=reinterpret_cast<Data_NewPreis*>(gp);

      cH_Data_NewPreis P(dp);
      P->unref();
std::cout << "Finaly we got: "<<P->Ware()->Name()<<' '<<P->Kosten()<<'\n';
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
std::cout << "Traget Drop\n";
  return false;
}
*/

void table_ausruestung::on_preise_tree_neu_drag_data_get(GdkDragContext *context,
                                     selection_data_t selection_data,
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

std::cout << "IN: "<<data<<" at "<<*adresse<<'\t'<<'\n';
   gtk_selection_data_set(selection_data GTKMM_24(->gobj()),
       selection_data GTKMM_24(->gobj())->target,8, 
       reinterpret_cast < const unsigned char * > ( data.c_str() ) ,
       data.size() );

   }catch(std::exception &e) {Ausgabe(Ausgabe::Error,e.what());}   
}

#endif
