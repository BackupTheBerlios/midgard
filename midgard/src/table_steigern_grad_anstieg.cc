// $Id: table_steigern_grad_anstieg.cc,v 1.12 2002/11/01 10:23:48 thoma Exp $
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
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

#include "midgard_CG.hh"
#include "table_steigern.hh"
#include <Misc/itos.h>

void table_steigern::on_grad_anstieg_clicked()
{
 radiobutton_steigern->set_active(true);
 int act_grad=hauptfenster->getWerte().Grad();
 int max_grad=hauptfenster->getCDatabase().GradAnstieg.get_Grad(hauptfenster->getWerte().GFP());

//cout << act_grad<<' '<<max_grad<<'\t'<<hauptfenster->getWerte().GFP()<<'\n';

// hauptfenster->getWerte().setGrad(hauptfenster->getCDatabase().GradAnstieg.get_Grad(hauptfenster->getWerte().GFP()));

 while(act_grad<max_grad)
  {
    hauptfenster->getWerte().setGrad(++act_grad);

    std::string info;
    hauptfenster->getChar()->get_ausdauer(act_grad,hauptfenster->getCDatabase(),info,
                           get_wie_steigern(),get_bool_steigern());
    hauptfenster->set_status(info);

    get_ab_re_za(Enums::eAbwehr);
    get_ab_re_za(Enums::eResistenz);
    get_ab_re_za(Enums::eZaubern);
    int wurf=hauptfenster->random.integer(1,100);
    get_grundwerte(wurf);
//    ++old_grad;
  }
}

void table_steigern::on_button_grad_clicked()
{   
  hauptfenster->getWerte().setGrad(hauptfenster->getCDatabase().GradAnstieg.get_Grad(hauptfenster->getWerte().GFP()));
  zeige_werte();
}
void table_steigern::on_button_grad_ausdauer_clicked()
{   
 std::string info;
 hauptfenster->getChar()->get_ausdauer(hauptfenster->getWerte().Grad(),hauptfenster->getCDatabase(),info,get_wie_steigern(),get_bool_steigern());
 hauptfenster->set_status(info,false);
 zeige_werte();
}
void table_steigern::on_button_grad_abwehr_clicked()
{   
 get_ab_re_za(Enums::eAbwehr);
}
void table_steigern::on_button_grad_zaubern_clicked()
{   
 get_ab_re_za(Enums::eZaubern);
}
void table_steigern::on_button_grad_resistenz_clicked()
{   
 get_ab_re_za(Enums::eResistenz);
}
void table_steigern::on_button_grad_basiswerte_clicked()
{   
  int wurf=hauptfenster->random.integer(1,100);
  get_grundwerte(wurf);
  zeige_werte();
}

gint table_steigern::on_button_grad_basiswerte_button_release_event(GdkEventButton *ev)
{
  if (ev->button == 1) on_button_grad_basiswerte_clicked();
  if (ev->button == 3) 
   {
     spinbutton_eigenschaften_grad_anstieg->show();
     spinbutton_eigenschaften_grad_anstieg->grab_focus();
     spinbutton_eigenschaften_grad_anstieg->select_region(0,-1);
   }
  return true;
}

void table_steigern::on_spinbutton_eigenschaften_grad_anstieg_activate()
{
  spinbutton_eigenschaften_grad_anstieg->update();
  spinbutton_eigenschaften_grad_anstieg->hide();
  int wurf=spinbutton_eigenschaften_grad_anstieg->get_value_as_int();
  get_grundwerte(wurf);
  zeige_werte();
}


void table_steigern::get_grundwerte(int wurf)
{
  std::string info;
  hauptfenster->getChar()->eigenschaften_steigern(info,hauptfenster->getCDatabase());
  hauptfenster->set_status(info);
  zeige_werte();
}

void table_steigern::get_ab_re_za(Enums::e_was_steigern was)
{
  std::string info;
  const bool bsteigern=radiobutton_steigern->get_active();
  hauptfenster->getChar()->get_ab_re_za(was,get_wie_steigern(),bsteigern,
                        hauptfenster->getCDatabase(),info,get_bool_steigern());
  hauptfenster->set_status(info);
  zeige_werte();
}
