// $Id: table_steigern_grad_anstieg.cc,v 1.25 2003/12/09 16:58:26 christof Exp $
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
#include <libmagus/Random.hh>
#include <libmagus/Datenbank.hh>

void table_steigern::on_grad_anstieg_clicked()
{
 flashing_gradanstieg->setTime(0);
 flashing_eigenschaft->setTime(0);
 radiobutton_steigern->set_active(true);
 int act_grad=hauptfenster->getAben().Grad();
 int max_grad=Datenbank.GradAnstieg.get_Grad(hauptfenster->getAben().GFP());

//cout << act_grad<<' '<<max_grad<<'\t'<<hauptfenster->getAben().GFP()<<'\n';

// hauptfenster->getAben().setGrad(Datenbank.GradAnstieg.get_Grad(hauptfenster->getAben().GFP()));

 while(act_grad<max_grad)
  {
    hauptfenster->getAben().setGrad(++act_grad);

    std::string info;
    hauptfenster->getAben().get_ausdauer(act_grad,
                           get_wie_steigern(),get_bool_steigern());
//    hauptfenster->set_status(info);

    get_ab_re_za(Enums::eAbwehr);
    get_ab_re_za(Enums::eResistenz);
    get_ab_re_za(Enums::eZaubern);
    int wurf=Random::W100();
    get_grundwerte(wurf);
  }
}

void table_steigern::on_button_grad_clicked()
{   
  flashing_gradanstieg->setTime(0);
  hauptfenster->getAben().setGrad(Datenbank.GradAnstieg.get_Grad(hauptfenster->getAben().GFP()));
  zeige_werte();
}
void table_steigern::on_button_grad_ausdauer_clicked()
{   
 std::string info;
 hauptfenster->getAben().get_ausdauer(hauptfenster->getAben().Grad(),get_wie_steigern(),get_bool_steigern());
// hauptfenster->set_status(info,false);
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
  flashing_eigenschaft->setTime(0);
  int wurf=Random::integer(1,100);
  get_grundwerte(wurf);
  zeige_werte();
}

void table_steigern::on_button_grad_basiswerte()
{
  if (hauptfenster->getChar().proxies.werte_eingeben.Value()) 
   {
     spinbutton_eigenschaften_grad_anstieg->show();
     spinbutton_eigenschaften_grad_anstieg->grab_focus();
     spinbutton_eigenschaften_grad_anstieg->select_region(0,-1);
   }
   else on_button_grad_basiswerte_clicked();
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
  hauptfenster->getAben().eigenschaften_steigern(wurf);
  zeige_werte();
}

void table_steigern::get_ab_re_za(Enums::e_was_steigern was)
{
  std::string info;
  const bool bsteigern=radiobutton_steigern->get_active();
  hauptfenster->getAben().get_ab_re_za(was,get_wie_steigern(),bsteigern,
                        get_bool_steigern());
  zeige_werte();
}
