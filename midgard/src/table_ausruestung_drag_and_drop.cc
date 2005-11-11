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
#include <Misc/TraceNV.h>

#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
   typedef Gtk::SelectionData &selection_data_t;
   typedef const Gtk::SelectionData &const_selection_data_t;
#  define GTKMM24(x) x
#include <sigc++/bind.h>
#else
   typedef GtkSelectionData* selection_data_t;
   typedef GtkSelectionData* const_selection_data_t;
#  define GTKMM24(x)
#endif

static const UniqueValue::value_t trace_channel=ManuProC::Tracer::channels.get();
static ManuProC::Tracer::Environment trace_channel_e("DEBUG_DND",trace_channel);

class table_ausruestung::MyTreeStore : public Gtk::TreeStore
{	MyTreeStore(const Gtk::TreeModelColumnRecord& cols, table_ausruestung *cont) 
		: Gtk::TreeStore(cols), container(cont) {}
//	virtual bool drag_data_get_vfunc(const Gtk::TreeModel::Path& path, selection_data_t selection_data);
	virtual bool drag_data_delete_vfunc(const Gtk::TreeModel::Path& path);
	virtual bool drag_data_received_vfunc(const TreeModel::Path& dest, const_selection_data_t selection_data);
	table_ausruestung *container;
public:
	static Glib::RefPtr<MyTreeStore> MyTreeStore::create(const Gtk::TreeModelColumnRecord& cols, table_ausruestung *cont)
	{  MyTreeStore *x=new MyTreeStore(cols,cont);
 	   x->reference();
	   return Glib::RefPtr<MyTreeStore>(x);
	}
};

#if 0 // is not called, don't know why ...
bool table_ausruestung::MyTreeStore::drag_data_get_vfunc(const Gtk::TreeModel::Path& path, 
					selection_data_t selection_data)
{ 
std::cerr << "drag_data_get " << path.to_string() << ' ' << selection_data GTKMM24(.gobj())->target << '\n'; 
   return Gtk::TreeStore::drag_data_get_vfunc(path,selection_data);
//   return false;
}
#endif

bool table_ausruestung::MyTreeStore::drag_data_delete_vfunc(const Gtk::TreeModel::Path& path)
{ 
  ManuProC::Trace _t(trace_channel,__FUNCTION__,path.to_string());  
  bool is_end;
  AusruestungBaum::iterator iter=container->get_Iter(path,is_end);
  assert(!is_end);
  Gtk::TreePath parentpath=path;
  if (parentpath.up())
  { container->get_Var(parentpath).erase(iter);
  }
  else std::cerr << "up() failed\n";
  return Gtk::TreeStore::drag_data_delete_vfunc(path);
}

#include <gtk/gtktreednd.h>

bool table_ausruestung::MyTreeStore::drag_data_received_vfunc(const Gtk::TreeModel::Path& dest, 
					const_selection_data_t selection_data)
{  ManuProC::Trace _t(trace_channel,__FUNCTION__,dest.to_string());  
   Glib::RefPtr<TreeModel> model;
   Gtk::TreePath path;
   if (!Gtk::TreePath::get_from_selection_data(selection_data,model,path))
   { ManuProC::Trace(trace_channel,"=","false");  
     return false;
   }
   if (model->gobj()!=static_cast<Gtk::TreeModel*>(this)->gobj())
   {  std::cerr << "my model is @"<< gobj() << '\n';
std::cerr << "drag_data_received " << dest.to_string() << ' ' << model->gobj()
<< ' ' << path.to_string() << '\n';
      return false;
   }
   
   bool is_end;
   AusruestungBaum::iterator destiter=container->get_Iter(dest,is_end);
   AusruestungBaum &source=container->get_Var(path);
   Gtk::TreePath parentpath=dest;
   if (parentpath.up())
   { container->get_Var(parentpath).insert(destiter,source);
   }
   else std::cerr << "up() failed\n";
   return Gtk::TreeStore::drag_data_received_vfunc(dest,selection_data);
}

#if 0
void table_ausruestung::on_preise_tree_neu_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&context,
                                     selection_data_t    selection_data,
                                     guint               info,
                                     guint32             time )
{
}

//static  Gdk_Pixmap drag_icon;
//#include "/tmp/testdrag_and_drop.xpm"

const GtkTargetEntry table_ausruestung::target_table[4] = {
           { "STRING",     0, table_ausruestung::TARGET_STRING },
           { "text/plain", 0, table_ausruestung::TARGET_STRING },
           { "text/uri-std::list", 0, table_ausruestung::TARGET_URL },
           { "application/x-rootwin-drop", 0, table_ausruestung::TARGET_ROOTWIN}
           };
#endif

static void drag_data_display(const Glib::RefPtr<Gdk::DragContext>& context,
                                  gint x,gint y,
                                  const_selection_data_t data,
                                  guint info,guint32 time)
{ std::cout << "drag data received: " << x << "," << y << " " << info << ' ';
  std::cout << context->get_action() << ' ' << '\n';
}

static bool drag_drop_display(const Glib::RefPtr<Gdk::DragContext>& context,
                                  gint x,gint y,guint32 time)
{ std::cout << "drop: " << x << "," << y << " " << time << '\n';
  return false; // ?
}

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

  

  checkbutton_ausruestung_geld->signal_drag_data_received().connect(SigC::slot(*this,&table_ausruestung::tree_drag_data_received));
  checkbutton_ausruestung_geld->drag_dest_set ( Gtk::DEST_DEFAULT_ALL,
                          target_table, n_targets - 1, /* no rootwin */
                          static_cast < GdkDragAction > ( GDK_ACTION_COPY | GDK_ACTION_MOVE) );
#endif                          

  Ausruestung_tree=manage(new Gtk::TreeView());
//  Ausruestung_tree->signal_drag_data_received().connect(SigC::slot(&drag_data_display),false);
//  Ausruestung_tree->signal_drag_drop().connect(SigC::slot(&drag_drop_display),false);
  m_refStore= MyTreeStore::create(m_columns,this);
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
//   preise_tree_neu->enable_model_drag_source();
#warning nur zum Test
//   preise_tree_neu->enable_model_drag_dest();
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
  preise_tree_neu->signal_clicked().connect(SigC::slot(*this,&table_ausruestung::neu_clicked));
}

void table_ausruestung::neu_clicked(const cH_RowDataBase& row,int col,bool& handled)
{ // hauptfenster->getAben().getBesitz().push_back(row.cast_dynamic<Data_NewPreis>()->Ware());
#warning Ware von unten nach oben übernehmen
// siehe on_preise_tree_neu_leaf_selected
}

#if 0
// GdkDragContext *context, 
void table_ausruestung::tree_drag_data_received(
                                  const Glib::RefPtr<Gdk::DragContext>& context,
                                  gint x,gint y,
                                  const_selection_data_t data,
                                  guint info,guint32 time)
{
#if 0
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
#endif
}
#endif


/*
gboolean table_ausruestung::target_drag_drop(GdkDragContext *context,
                                  gint x,gint y, guint time )
{
std::cout << "Traget Drop\n";
  return false;
}
*/

#if 0
void table_ausruestung::on_preise_tree_neu_drag_data_get(
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
                                     Gtk::SelectionData   &selection_data,
#else // gtkmm 2.2
				     GtkSelectionData *selection_data,
#endif
                                     GdkDragContext *context,
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
