// $Id: AuswahlAbstraktion.h,v 1.2 2004/12/22 08:10:31 christof Exp $
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

#ifndef CD2CA1FE_FF8D_472C_A56C_2205B7D5B16B
#  define CD2CA1FE_FF8D_472C_A56C_2205B7D5B16B

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>

class MagusDialog;

class AuswahlAbstraktion
{ Gtk::VBox *container;
  MagusDialog *dialog;
  Gtk::Label *label;
  SigC::Slot1<void,> callback;
  bool is_dialog;
  std::vector<Gtk::Widget *> sensitivity;
  SigC::Signal1<void,int> _response_sig;
  void on_cancel();
public:
  AuswahlAbstraktion(Gtk::Window *mainwin, Gtk::Bin &no_dialog_container,const SigC::Slot1<void,> &cb);
//  ~AuswahlAbstraktion() ?
  void add_sensitivity(Gtk::Widget &w);
  void set_title(const Glib::ustring &t);
  void run(); // kein Rückgabewert?
  
  SigC::Signal1<void,int> &signal_response()
  { return _response_sig; }
  void response(int response_id)
  { signal_response()(response_id);
  }
  
//  static std::string choose(Gtk::Window *mainwin, Gtk::Bin &no_dialog_container,const std::vector<std::string> &list)
  // member da so add_sensitivity genutzt werden kann ...
  std::string choose(const std::vector<std::string> &list);
};

#endif
