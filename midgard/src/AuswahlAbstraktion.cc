// $Id: AuswahlAbstraktion.cc,v 1.2 2004/12/22 08:10:31 christof Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2004 Christof Petig
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

#include <AuswahlAbstraktion.h>
#include <MagusDialog.hh>
#include <libmagus/Magus_Optionen.hh>

AuswahlAbstraktion::AuswahlAbstraktion(Gtk::Window *mainwin, Gtk::Bin &no_dialog_container,const SigC::Slot1<void,> &cb)
  : container(&no_dialog_container), dialog(), label(),
    is_dialog(!Programmoptionen.OberCheck(Magus_Optionen::AvoidDialogues).active)
{ if (is_dialog)
  { dialog=new MagusDialog(mainwin);
    dialog->set_style(MagusDialog::b_Close);
    container=dialog->get_vbox();
  }
  else
  { no_dialog_container.remove();
    container=Gtk::manage(new Gtk::VBox(false,1));
    Gtk::Button *canc=Gtk::manage(new Gtk::Button(Gtk::Stock::CANCEL));
    label= Gtk::manage(new Gtk::Label());
    container->pack_start(*label,Gtk::PackOptions());
    container->pack_end(*canc,Gtk::PackOptions());
    canc->show();
    no_dialog_container.add(container);
    container->show();
    // do not show label (yet)
  }
}

void AuswahlAbstraktion::add_sensitivity(Gtk::Widget &w)
{ if (w.is_sensitive())
  { w.set_sensitive(false);
    sensitivity.push_back(&w);
  }
}

void AuswahlAbstraktion::on_cancel()
{ signal_response()(Gtk::RESPONSE_CLOSE);
}

void AuswahlAbstraktion::set_title(const Glib::ustring &t)
{ if (dialog && is_dialog) dialog->set_title(t);
  if (!is_dialog && label) { label->set_text(t); label->show(); }
}

namespace { struct RunInfo
{ AuswahlAbstraktion *aa;
  gint response_id; 
  GMainLoop *loop;  

  RunInfo(AuswahlAbstraktion *_aa)
  : aa(_aa), response_id(Gtk::RESPONSE_NONE), loop()
  { loop = g_main_loop_new (NULL, FALSE);
  }
  void shutdown();
  void shutdown2(int response)
  { response_id=response; shutdown(); }
  int run()
  { GDK_THREADS_LEAVE ();
    g_main_loop_run (loop);
    GDK_THREADS_ENTER ();
    return response_id;
  }
  ~RunInfo()
  { g_main_loop_unref (loop);
  }
}; }

void RunInfo::shutdown()
{
  if (g_main_loop_is_running (loop))
    g_main_loop_quit (loop);
}
 
int AuswahlAbstraktion::run()
{ if (is_dialog)
  { signal_response().connect(SigC::slot(*dialog,&Gtk::Dialog::response));
    return dialog->run();
  }
  else
  { RunInfo ri;
    // connect to shutdown
    signal_response().connect(SigC::slot(ri,&RunInfo::shutdown2));
    return ri.run();
  }
}

std::string AuswahlAbstraktion::choose(Gtk::Window *mainwin, Gtk::Bin &no_dialog_container,const std::vector<std::string> &list)
{ //???
  // ein Optionmenu erzeugen und warten was passiert
}
