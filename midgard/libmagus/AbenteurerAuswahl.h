// $Id: AbenteurerAuswahl.h,v 1.2 2003/11/24 16:21:42 christof Exp $               
/*  Midgard Character Generator
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

#ifndef ABENTEURERAUSWAHL_HH
#define ABENTEURERAUSWAHL_HH

#include "VAbenteurer.hh"

class AbenteurerAuswahl : public SigC::Object // um signale zu empfangen
{
      VAbenteurer::iterator ai;
      SigC::Signal0<void> sig_anderer;

      void divert_proxy();
public:
      VAbentModelProxy proxies;
      static VAbenteurer Chars;

      AbenteurerAuswahl();
      // these operate on the concept of a current character
      VAbenteurer::iterator actualIterator();
      VAbenteurer::const_iterator actualIterator() const;
      __deprecated const Abenteurer &getCAbenteurer() const {return actualIterator()->getAbenteurer();}
      __deprecated const Abenteurer &getAbenteurer() const {return actualIterator()->getAbenteurer();}
      __deprecated Abenteurer &getAbenteurer() {return actualIterator()->getAbenteurer();}
      void setAbenteurer(const VAbenteurer::iterator &i);
//      void set_Abenteurer(const Abenteurer& A);
      SigC::Signal0<void> &signal_anderer_abenteurer() { return sig_anderer; }

      __deprecated void modified() {actualIterator()->modified();}
      __deprecated void saved() {actualIterator()->saved();}
      __deprecated bool gespeichert() const {return actualIterator()->gespeichert();}
      __deprecated void setFilename(std::string s) {actualIterator()->setFilename(s);}
      __deprecated const std::string &getFilename() {return actualIterator()->getFilename();}
      __deprecated AbenteurerLernpunkte &getLernpunkte() { return actualIterator()->getLernpunkte(); }
      __deprecated const AbenteurerLernpunkte &getLernpunkte() const { return actualIterator()->getLernpunkte(); }
      __deprecated Wizard &getWizard() { return actualIterator()->getWizard(); }
      __deprecated void undosave(const std::string &s) { actualIterator()->undosave(s); }
      bool valid() const;
      operator bool() const { return valid(); }
   const VAbenteurer::Item *operator->() const
   {  return &*actualIterator(); }
   VAbenteurer::Item *operator->()
   {  return &*actualIterator(); }
#if 0   
   Abenteurer *operator->()
   {  return &actualIterator()->getAbenteurer(); }
#endif
};

#endif
