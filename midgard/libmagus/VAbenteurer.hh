// $Id: VAbenteurer.hh,v 1.12 2003/12/15 23:17:06 christof Exp $               
/*  Midgard Character Generator
 *  Copyright (C) 2002 Malte Thoma
 *  Copyright (C) 2003 Christof Petig
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

#ifndef CLASS_VABENTEURER_HH
#define CLASS_VABENTEURER_HH

#include "Abenteurer.hh"
#include "AbenteurerLernpunkte.hh"
#include "Wizard.hh"
#include <sigc++/object.h>
#include "VAbentModelProxy.hh"

namespace AbenteurerListe
{
	struct st_undo
	{	std::string text; // Bezeichnung des UndoSchrittes
		Abenteurer abenteurer;
       		AbenteurerLernpunkte ab_lp;
       		Wizard wizard;
       			    // ... z.B. wie steigern etc ...
       		st_undo(const Abenteurer &a) : 
       			text("geladen?"), 
       			abenteurer(a)
       			{}
	};
	class Item : public SigC::Object
	{	std::vector<st_undo> undos;
		// Einfügen und löschen können den Iterator gerne ungültig machen,
		// er muss so oder so neu gesetzt werden
       		// global 
		std::vector<st_undo>::iterator current_undo;
		SigC::Signal0<void> _signal_undo_changed;
		SigC::Signal0<void> _signal_undo_list_changed;
		std::string filename;
		bool bgespeichert;
		Model<bool> werte_eingeben;

		void divert_proxy();
		void operator=(const Item &);
		void init(); // iterator setzen, connect
	public:
		typedef std::vector<st_undo>::const_iterator const_iterator;
		typedef std::vector<st_undo>::iterator iterator;
		
		const_iterator begin() const { return undos.begin(); }
		const_iterator end() const { return undos.end(); }
		const_iterator getUndo() const { return current_undo; }
		void setUndo(const_iterator it);

		VAbentModelProxy proxies; // proxy ist erforderlich um mit dem richtigen
			// Model in den Undoschritten zu arbeiten
		
		Item(const Abenteurer &A=Abenteurer(),bool g=true);
		Item(const Item &i);
		
		Abenteurer &getAbenteurer() { return current_undo->abenteurer; }
		AbenteurerLernpunkte &getLernpunkte() { return current_undo->ab_lp; }
		Wizard &getWizard() { return current_undo->wizard; }
		const Abenteurer &getAbenteurer() const { return current_undo->abenteurer; }
		const AbenteurerLernpunkte &getLernpunkte() const { return current_undo->ab_lp; }
		const Wizard &getWizard() const { return current_undo->wizard; }
		void modified() {bgespeichert=false;}
		void saved() {bgespeichert=true;}
		bool gespeichert() const {return bgespeichert;}
		void setFilename(std::string s) {filename=s;}
		const std::string &getFilename() {return filename;}
		// einen Undoschritt abschließen und benennen
		void undosave(const std::string &s);
		SigC::Signal0<void> &signal_undo_changed()
		{  return _signal_undo_changed; }
		SigC::Signal0<void> &signal_undo_list_changed()
		{  return _signal_undo_list_changed; }
		Model_ref<bool> WerteEingebenModel() { return werte_eingeben; }
	};
}

class VAbenteurer // : public SigC::Object // um signale zu empfangen
{
   public:
	typedef AbenteurerListe::Item Item;
	typedef AbenteurerListe::st_undo st_undo;
	typedef Item st_abenteurer; // old name
	typedef std::list<Item>::const_iterator const_iterator;
	typedef std::list<Item>::iterator iterator;
   private:
	std::list<Item> VA;
	SigC::Signal0<void> list_changed;

      class sort {
        public: sort() {}
        bool operator()(const Item &x,const Item &y) const
          { return x.getAbenteurer().Gw() < y.getAbenteurer().Gw() ;
          }
      };
      
      iterator push_back_silent();
      iterator erase_silent(iterator i);
   public:
   
//      VAbenteurer();
      
      const std::list<Item> &getList() const {return VA;}
      std::list<Item> &getList() {return VA;}
      void sort_gw() {VA.sort(sort());}
      iterator push_back(); // kein Argument???
      iterator load(std::istream &datei); // throw (was denn?)
      iterator load(const std::string &dateiname); // throw (was denn?)
      iterator erase(iterator i);
      bool unsaved_exist();
      bool empty() const {return VA.empty();}
      size_t size() const {return VA.size();}
      iterator end() { return VA.end(); }
      iterator begin() { return VA.begin(); }
      void delete_empty();
      SigC::Signal0<void> &signal_changed() { return list_changed; }
};

#endif
