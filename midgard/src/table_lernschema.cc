// generated 2002/5/16 18:55:17 CEST by thoma@Tiger.(none)
// using glademm V0.6.4b_cvs
//
// newer (non customized) versions of this file go to table_lernschema.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "table_lernschema.hh"
#include "midgard_CG.hh"
#include "class_SimpleTree.hh"
#include "Fertigkeiten.hh"
#include <Misc/itos.h>
#include "WaffeGrund.hh"
#include <SelectMatching.h>
#include "KiDo.hh"
#include "Sprache.hh"
#include "LernListen.hh"

void table_lernschema::init(midgard_CG *h)
{
  hauptfenster=h;
  maxkido=0;
  gwr_auswahl=ENone;
  show_gelerntes();
  zeige_werte();
  
  vbox_berufsname->hide();
  button_kido_auswahl->set_sensitive(false);
  button_angeborene_fert->set_sensitive(false);
}


void table_lernschema::on_button_waffe_trans_clicked()
{  
 if(lernpunkte.Waffen()>0)
   {
     lernpunkte.addWaffen(-1);
     lernpunkte.addUnge(+1);  
   }
 zeige_lernpunkte();
}

void table_lernschema::on_button_fach_trans_clicked()
{  
   if(lernpunkte.Fach()>0)
   {
     lernpunkte.addFach(-1);
     lernpunkte.addUnge(+1);
   }
 zeige_lernpunkte();
}

bool table_lernschema::on_spinbutton_fach_focus_out_event(GdkEventFocus *ev)
{  set_lernpunkte(); return 0;}
bool table_lernschema::on_spinbutton_allgemein_focus_out_event(GdkEventFocus *ev)
{  set_lernpunkte(); return 0;}
bool table_lernschema::on_spinbutton_waffen_focus_out_event(GdkEventFocus *ev)
{  set_lernpunkte(); return 0;}
bool table_lernschema::on_spinbutton_zaubern_focus_out_event(GdkEventFocus *ev)
{  set_lernpunkte(); return 0; }
bool table_lernschema::on_spinbutton_unge_focus_out_event(GdkEventFocus *ev)
{  set_lernpunkte(); return 0; }

bool table_lernschema::on_spinbutton_fach_focus_in_event(GdkEventFocus *ev)
{ spinbutton_fach->select_region(0,-1);   return false;}
bool table_lernschema::on_spinbutton_allgemein_focus_in_event(GdkEventFocus *ev)
{ spinbutton_allgemein->select_region(0,-1);   return false;}
bool table_lernschema::on_spinbutton_unge_focus_in_event(GdkEventFocus *ev)
{ spinbutton_unge->select_region(0,-1);   return false;}
bool table_lernschema::on_spinbutton_waffen_focus_in_event(GdkEventFocus *ev)
{ spinbutton_waffen->select_region(0,-1);   return false;}
bool table_lernschema::on_spinbutton_zaubern_focus_in_event(GdkEventFocus *ev)
{ spinbutton_zauber->select_region(0,-1);   return false;}

void table_lernschema::on_spinbutton_fach_activate()
{ set_lernpunkte(); spinbutton_allgemein->grab_focus();}
void table_lernschema::on_spinbutton_allgemein_activate()
{ set_lernpunkte(); spinbutton_unge->grab_focus();}
void table_lernschema::on_spinbutton_unge_activate()
{ set_lernpunkte(); spinbutton_waffen->grab_focus();}
void table_lernschema::on_spinbutton_waffen_activate()
{ set_lernpunkte(); spinbutton_zauber->grab_focus();}
void table_lernschema::on_spinbutton_zaubern_activate()
{ set_lernpunkte(); togglebutton_lernpunkte_edit->set_active(false);}

void table_lernschema::set_lernpunkte()
{
  spinbutton_unge->update();
  lernpunkte.setUnge(spinbutton_unge->get_value_as_int());
  spinbutton_fach->update();
  lernpunkte.setFach(spinbutton_fach->get_value_as_int());
  spinbutton_allgemein->update();
  lernpunkte.setAllgemein(spinbutton_allgemein->get_value_as_int());
  spinbutton_waffen->update();   
  lernpunkte.setWaffen(spinbutton_waffen->get_value_as_int());
  spinbutton_zauber->update();
  lernpunkte.setZauber(spinbutton_zauber->get_value_as_int());
  on_lernliste_wahl_toggled();
  zeige_werte();
}



void table_lernschema::on_lernliste_wahl_toggled()
{  
   if(button_zauber->get_active())
   {
     if (hauptfenster->getWerte().Spezialgebiet()->Spezial2()=="" && 
         hauptfenster->getChar()->Typ1()->Short()=="eBe")
      {
         hauptfenster->set_status("Erst Primär- und Sekundärelement wählen");
         return;
      }
   }
 show_lernschema();
}



void table_lernschema::on_button_waffen_clicked()
{  
  if(hauptfenster->getChar()->Typ1()->Kultwaffe() &&hauptfenster->getChar()->List_Waffen().empty())
   {
     hauptfenster->set_status(hauptfenster->getChar()->Typ1()->Name(hauptfenster->getWerte().Geschlecht())+" müssen als erstes ihre Kultwaffe wählen; fehlende Lernpunkte werden geschenkt.",false);
     togglebutton_teure_anzeigen->set_active(true);
   }
  button_lernschema_waffen->set_sensitive(true);
}



void table_lernschema::on_tree_gelerntes_leaf_selected(cH_RowDataBase d)
{  
  if(!togglebutton_spezialwaffe->get_active() && 
     !togglebutton_gelernt_verlernen->get_active()) return;
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  MBEmlt MBE = dt->getMBE();
  if(togglebutton_spezialwaffe->get_active() && (*MBE).What()!= MidgardBasicElement::WAFFE)
      {
        hauptfenster->set_status((*MBE).What_str()+" kann nicht als Spezialwaffe verwendet werden.");
        return;         
      }
  switch((*MBE).What()) {
     case MidgardBasicElement::WAFFE :
         { 
           if(togglebutton_spezialwaffe->get_active() )
            { 
             cH_Waffe W(MBE->getMBE());
             if(W->Verteidigung())
               { hauptfenster->set_status("Eine Verteidingungswaffe kann keine Spezialwaffe werden."); return;}
             else if(W->Reichweite()=="" && (*MBE).Lernpunkte()>1 )
               { hauptfenster->set_status("Nahkampfwaffen können nur dann eine Spezialwaffe werden wenn sie max. 1 Lernpunkte gekostet haben");return;}
             else if(W->Reichweite()!="" && (*MBE).Lernpunkte()>2 )
               { hauptfenster->set_status("Fernkampfwaffen können nur dann eine Spezialwaffe werden wenn sie max. 2 Lernpunkte gekostet haben");return;}
             else
               {  
                hauptfenster->getWerte().setSpezialisierung((*MBE)->Name());
                Waffe::setSpezialWaffe(hauptfenster->getWerte().Spezialisierung(),hauptfenster->getChar()->List_Waffen());
                togglebutton_spezialwaffe->set_active(false);
                if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::SPEZIALWAFFE);
               }
            }  
           else
            {  
             hauptfenster->getChar()->List_Waffen().remove(MBE);
             if(MBE->LernArt().find("Allg")!=std::string::npos) lernpunkte.addAllgemein( MBE->Lernpunkte());
             else lernpunkte.addWaffen(MBE->Lernpunkte());
             hauptfenster->getChar()->remove_WaffenGrund();
            }
           break;
         }
     case MidgardBasicElement::WAFFEBESITZ :
         { 
           cH_Waffe W(MBE->getMBE());
           H_WaffeBesitz WB=new WaffeBesitz(W,(*MBE)->Name(),0,0,"","");
// sieht nicht sooo sinnvoll aus, etwas neu erzeugtes wegzunehmen CP
           hauptfenster->getChar()->List_Waffen_besitz().remove(WB);  
           std::string art=W->Art2();
           if(art=="E" || art=="W" || art=="V") waffebesitzlernen.add_EWaffe(1);
           else waffebesitzlernen.add_AWaffe(1);
           break;
         }
     case MidgardBasicElement::ZAUBER :
         {hauptfenster->getChar()->List_Zauber().remove(MBE);
           lernpunkte.addZauber(MBE->Lernpunkte());
           break;
         }
     case MidgardBasicElement::KIDO :
         {hauptfenster->getChar()->List_Kido().remove(MBE);
           ++maxkido;
           fill_kido_lernschema();
           break;
         }
     case MidgardBasicElement::FERTIGKEIT_ANG :
         { hauptfenster->getChar()->List_Fertigkeit_ang().remove(MBE);
           break;
         }
     case MidgardBasicElement::FERTIGKEIT :
     case MidgardBasicElement::SPRACHE :
     case MidgardBasicElement::SCHRIFT :
        {
           switch((*MBE).What()) {
             case MidgardBasicElement::FERTIGKEIT :
                 hauptfenster->getChar()->List_Fertigkeit().remove(MBE);
                 list_FertigkeitZusaetze.remove((*MBE)->Name());
                 break;
             case MidgardBasicElement::SPRACHE :
                 hauptfenster->getChar()->List_Sprache().remove(MBE);
                 break;
             case MidgardBasicElement::SCHRIFT :
                 hauptfenster->getChar()->List_Schrift().remove(MBE);
                 break;
             default: assert(!"never get here\n");
           }
           if     (MBE->LernArt().find("Fach")!=std::string::npos) lernpunkte.addFach( MBE->Lernpunkte());
           else if(MBE->LernArt().find("Allg")!=std::string::npos) lernpunkte.addAllgemein( MBE->Lernpunkte());
           else if(MBE->LernArt().find("Unge")!=std::string::npos) lernpunkte.addUnge( MBE->Lernpunkte());
           if(MBE->LernArt().find("Heimat")!=std::string::npos) 
              list_FertigkeitZusaetze.remove("Landeskunde (Heimat)");
           else if(MBE->LernArt().find("_Schreiben_Muttersprache")!=std::string::npos) 
             { list_FertigkeitZusaetze.remove("Schreiben: Muttersprache(+4)"); 
               list_FertigkeitZusaetze.remove("Schreiben: Muttersprache(+9)"); 
               list_FertigkeitZusaetze.remove("Schreiben: Muttersprache(+12)");
             }
           else if(MBE->LernArt().find("Muttersprache")!=std::string::npos) 
                  list_FertigkeitZusaetze.remove(MBE->LernArt());
           else if(MBE->LernArt().find("Gastlandsprache")!=std::string::npos) 
                  list_FertigkeitZusaetze.remove(MBE->LernArt());
           else hauptfenster->set_info("Fehler beim Lernpunkte zurückstellen");
           std::string::size_type st = (*MBE)->Name().find("KiDo-Technik");
           if(st!=std::string::npos)  --maxkido;
           break;
         }
     default : break;
   }
  if((*MBE).What()==MidgardBasicElement::WAFFEBESITZ)
    show_WaffenBesitz_lernschema();
  else 
     show_lernschema();
  show_gelerntes();
  if((*MBE).What()==MidgardBasicElement::WAFFE && togglebutton_spezialwaffe->get_active())
     hauptfenster->undosave("Spezialwaffe "+(*MBE)->Name()+" gewählt");
  else
     hauptfenster->undosave((*MBE)->What_str()+" "+(*MBE)->Name()+" verlernt");
}
 
void table_lernschema::on_tree_lernschema_leaf_selected(cH_RowDataBase d)
{
  Abenteurer &A=hauptfenster->getAben();
  const Data_SimpleTree *dt=dynamic_cast<const Data_SimpleTree*>(&*d);
  MBEmlt MBE = dt->getMBE();
  if(MBE->Gelernt()) 
   { 
     hauptfenster->set_status("Diese Fertigkeit ist schon gelernt");
     tree_lernschema->get_selection()->unselect_all();
     return;
   }
 if(((*MBE).What()==MidgardBasicElement::FERTIGKEIT || (*MBE).What()==MidgardBasicElement::WAFFE)
   && !(*MBE)->Voraussetzung(A,false))
  {
    hauptfenster->set_status("Erst muß "+(*MBE)->Voraussetzung()+" gelernt werden");
    return;
  }
  
  switch((*MBE).What()) {
    case MidgardBasicElement::WAFFE:
      { 
        if(button_allgemeinwissen->get_active())
         { if(MBE->Lernpunkte()>lernpunkte.Allgemein() )
             { hauptfenster->set_status("Nicht genug Lernpunkte");
               tree_lernschema->get_selection()->unselect_all();
               return;
             }
           lernpunkte.addWaffen(MBE->Lernpunkte());
           lernpunkte.addAllgemein(-MBE->Lernpunkte());
         }
        int lp=MBE->Lernpunkte();
        if(A.Typ1()->Kultwaffe() &&A.List_Waffen().empty())
          {
            // Für eine Kultwaffe werden fehlende Lernpunkte geschenkt
            if( lp>lernpunkte.Waffen() ) lp=lernpunkte.Waffen();
            hauptfenster->set_status((*MBE)->Name()+" als Kultwaffe gewählt");
          }
        else if(MBE->Lernpunkte()>lernpunkte.Waffen())
          { hauptfenster->set_status("Nicht genug Lernpunkte");
            tree_lernschema->get_selection()->unselect_all();
            return;
          }
       A.List_Waffen().push_back(MBE);
       A.List_WaffenGrund().push_back(
          MBEmlt(&*cH_WaffeGrund(cH_Waffe(MBE->getMBE())->Grundkenntnis())));

       if(MBE->getMBE()->Name()=="Anderthalbh�nder" && 
          cH_Waffe(MBE->getMBE())->Min_St_Einhand(hauptfenster->getWerte()) )
             A.List_WaffenGrund().push_back(                              
                MBEmlt(&*cH_WaffeGrund("Einhandschwert")));
       else if(MBE->getMBE()->Name()=="Schlachtbeil" &&   
          cH_Waffe(MBE->getMBE())->Min_St_Einhand(hauptfenster->getWerte()) )
             A.List_WaffenGrund().push_back(              
                MBEmlt(&*cH_WaffeGrund("Einhandschlagwaffe")));

       A.List_WaffenGrund().sort(MBEmlt::sort(MBEmlt::sort::NAME));
       A.List_WaffenGrund().unique();
        lernpunkte.addWaffen(-lp);
        break; }
    case MidgardBasicElement::ZAUBER:
      { 
        if(MBE->Lernpunkte()>lernpunkte.Zauber())
          { hauptfenster->set_status("Nicht genug Lernpunkte");
            tree_lernschema->get_selection()->unselect_all();
            return;
          }
        if(!(*MBE)->ZusatzEnum(A.getVTyp())) // Das macht 'lernen_zusatz' automatisch
           A.List_Zauber().push_back(MBE); 
        else lernen_zusatz((*MBE)->ZusatzEnum(A.getVTyp()),MBE);
        lernpunkte.addZauber(- MBE->Lernpunkte());   
        break; }
    case MidgardBasicElement::FERTIGKEIT:
      { 
        if( (MBE->LernArt().find("Fach")!=std::string::npos  &&
             MBE->Lernpunkte() > lernpunkte.Fach()) ||
             (MBE->LernArt().find("Allg")!=std::string::npos &&
             MBE->Lernpunkte() > lernpunkte.Allgemein()) ||
             (MBE->LernArt().find("Unge")!=std::string::npos &&
             MBE->Lernpunkte() > lernpunkte.Unge()))
          { hauptfenster->set_status("Nicht genug Lernpunkte");      
            tree_lernschema->get_selection()->unselect_all();
            return;
          }
        if(!LernListen::SpracheSchrift(MBE->getMBE()))
          { 
            std::string::size_type st = (*MBE)->Name().find("KiDo-Technik");
            if(st!=std::string::npos) 
               { ++maxkido; list_FertigkeitZusaetze.push_back((*MBE)->Name());}
            if(!(*MBE)->ZusatzEnum(A.getVTyp()) && st==std::string::npos)// Das 'push_back' macht 'lernen_zusatz' automatisch
                 A.List_Fertigkeit().push_back(MBE); 
            if((*MBE)->Name()=="KiDo" && A.Typ1()->Short()=="Kd") maxkido+=2;
            if(maxkido>0 && MBEmlt(&*cH_Fertigkeit("KiDo"))->ist_gelernt(hauptfenster->getChar()->List_Fertigkeit()))
               zeige_werte();
         }
        else
          { // Damit Sprachen und Schriften nicht doppelt angezeigt werden
            // später: nach einhelliger Meinung sollen sie das doch 
//            list_FertigkeitZusaetze.push_back((*(*MBE))->Name());
          }
        if((*MBE)->ZusatzEnum(A.getVTyp())) 
          lernen_zusatz((*MBE)->ZusatzEnum(A.getVTyp()),MBE);

        if(MBE->LernArt().find("Fach")!=std::string::npos)
           lernpunkte.addFach(-MBE->Lernpunkte());
        else if(MBE->LernArt().find("Allg")!=std::string::npos)
           lernpunkte.addAllgemein(- MBE->Lernpunkte());
        else if(MBE->LernArt().find("Unge")!=std::string::npos)
           lernpunkte.addUnge(- MBE->Lernpunkte());     
        break; }
    default : break;
   }
  hauptfenster->undosave((*MBE)->What_str()+" "+(*MBE)->Name()+" gelernt");
  show_lernschema();
  show_gelerntes(); 
  if(frame_lernschema_zusatz->is_visible()) scrolledwindow_lernen->set_sensitive(false);
}



void table_lernschema::on_herkunftsland_clicked()
{  
  cH_MidgardBasicElement Dummy=&*cH_Fertigkeit("",true);
  MBEmlt Mdummy(Dummy);
  lernen_zusatz(MidgardBasicElement::ZHerkunft,Mdummy);
}

void table_lernschema::lernpflichten_info()
{
  std::string t1=hauptfenster->getChar()->Typ1()->getLernpflichtenInfo(hauptfenster->getWerte().Herkunft());
  std::string t2=hauptfenster->getChar()->Typ2()->getLernpflichtenInfo(hauptfenster->getWerte().Herkunft());
  if(!t1.empty() || !t2.empty())
      hauptfenster->set_info(t1+"\n"+t2);
}

#include "Zufall.hh"
void table_lernschema::on_lernpunkte_wuerfeln_clicked()
{ if (hauptfenster->MOptionen->WerteEingebenModel().Value()) 
  {  togglebutton_lernpunkte_edit->set_active(true);
     return;
  }
  lernpflichten_info();
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::LERNPUNKTE);
  Zufall::Lernpunkte_wuerfeln(lernpunkte,hauptfenster->getAben(),hauptfenster->random);
  show_gelerntes();

  zeige_lernpunkte();

  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active)
     button_lernpunkte->set_sensitive(false);

  button_sensitive(true);
  on_lernliste_wahl_toggled();
}

void table_lernschema::button_sensitive(bool b)
{
  button_fachkenntnisse->set_sensitive(b);
  button_allgemeinwissen->set_sensitive(b);
  button_untyp_fertigkeiten->set_sensitive(b);
  button_waffen->set_sensitive(b);
#warning Christof: Warum stürzt das Programm ab, wenn man das 'b &&' wegnimmt?
  if(b && hauptfenster->getChar()->is_mage())
      button_zauber->set_sensitive(b);
  button_beruf->set_sensitive(b);
  button_lernschema_geld->set_sensitive(b);
  button_lernschema_waffen->set_sensitive(b);
  button_ruestung->set_sensitive(b);
  button_ausruestung->set_sensitive(b);
}



void table_lernschema::on_togglebutton_lernpunkte_edit_toggled()
{  
  edit_lernpunkte(togglebutton_lernpunkte_edit->get_active());
}

void table_lernschema::edit_lernpunkte(bool b)
{
 spinbutton_fach->set_sensitive(b);
 spinbutton_allgemein->set_sensitive(b);
 spinbutton_unge->set_sensitive(b);
 spinbutton_waffen->set_sensitive(b);
 spinbutton_zauber->set_sensitive(b);
 if(b) table_berufsprozent->show();
 else  table_berufsprozent->hide();
}


void table_lernschema::on_button_lernschema_geld()
{  
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::GELD);
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active)
     button_lernschema_geld->set_sensitive(false);
  if (hauptfenster->MOptionen->WerteEingebenModel().Value())
  {  gwr_auswahl=EGeld1;
     set_gwr_eingabe();
  }
  else
  {  hauptfenster->getWerte().setGeld(0,0,0);
     geld_wuerfeln() ;
  }
}

void table_lernschema::geld_wuerfeln()
{
     VGeldwurf.clear();
     for(int i=0;i<3;++i) VGeldwurf.push_back(hauptfenster->random.integer(1,6));
     lernschema_geld_wuerfeln(VGeldwurf);
}

void table_lernschema::set_gwr_eingabe()
{
  switch (gwr_auswahl) {
    case ENone : assert(!"never get here"); break;
    case EWaffen : label_gwr->set_text("%-Wurf für\nWaffen"); break;
    case ERuestung: label_gwr->set_text("%-Wurf für\nRüstung"); break;
    case EGeld1 :  label_gwr->set_text("1. W6-Wurf für\nGeld"); break;
    case EGeld2 :  label_gwr->set_text("2. W6-Wurf für\nGeld"); break;
    case EGeld3 :  label_gwr->set_text("3. W6-Wurf für\nGeld"); break;
   }
  if(gwr_auswahl==EWaffen || gwr_auswahl==ERuestung)
    spinbutton_waffen_lernschema->get_adjustment()->set_upper(100);
  else 
    spinbutton_waffen_lernschema->get_adjustment()->set_upper(6);

  table_waffen_lernschema_eingabe->show();
  spinbutton_waffen_lernschema->select_region(0,-1);
  spinbutton_waffen_lernschema->grab_focus();
}


void table_lernschema::lernschema_geld_wuerfeln(const std::vector<int>& VGeldwurf)
{
 assert(VGeldwurf.size()==3);
 int igold=0;  
 igold=VGeldwurf[0]+VGeldwurf[1]+VGeldwurf[2];
 if      (hauptfenster->getChar()->Typ1()->Geld() == 1) igold-=3;
 else if (hauptfenster->getChar()->Typ1()->Geld() == 2) igold+=0;
 else if (hauptfenster->getChar()->Typ1()->Geld() == 3) igold+=6;
 else if (hauptfenster->getChar()->Typ1()->Geld() == 4) igold+=3;

 if(hauptfenster->getWerte().Stand()=="Adel" ) igold*=2;  
 if(hauptfenster->getWerte().Stand()=="Unfrei" ) igold/=2;
 if(VGeldwurf[0]==VGeldwurf[1] && VGeldwurf[1]==VGeldwurf[2]) igold += 100;

 std::string strinfo ="Beim Auswürfeln von Geld wurden "
   +itos(VGeldwurf[0])+"  "+itos(VGeldwurf[1])+"  "+itos(VGeldwurf[2])+" gewürfelt ==> "
   +itos(igold)+" Gold";
 hauptfenster->set_status(strinfo);   
 hauptfenster->getWerte().addGold(igold);  
 zeige_werte();
}


void table_lernschema::on_button_ruestung()
{  
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::RUESTUNG);
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active)
     button_ruestung->set_sensitive(false);
   if (!hauptfenster->MOptionen->WerteEingebenModel().Value())
   {  
     int wurf = hauptfenster->random.integer(1,100);
     on_button_ruestung_clicked(wurf);
   }
   else 
   { //manage (new Window_ruestung(hauptfenster->getWerte(),hauptfenster,hauptfenster->getDatabase()));
     gwr_auswahl=ERuestung;
     set_gwr_eingabe();  
   }
}

void table_lernschema::on_button_ruestung_clicked(int wurf)
{
  std::string rue;
  if (hauptfenster->getChar()->Typ1()->Ruestung() == 1)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "TR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "TR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "LR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "LR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "LR" ;
      if (96 <= wurf && wurf  <= 100) rue = "LR" ;
   }
  if (hauptfenster->getChar()->Typ1()->Ruestung()== 2)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "TR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "LR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "LR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "KR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "KR" ;
      if (96 <= wurf && wurf  <= 100) rue = "KR" ;
   }
  if (hauptfenster->getChar()->Typ1()->Ruestung()== 3)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "TR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "LR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "KR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "KR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "KR" ;
      if (96 <= wurf && wurf  <= 100) rue = "PR" ;
   }
  if (hauptfenster->getChar()->Typ1()->Ruestung()== 4)
   {
      if ( 1 <= wurf && wurf  <= 10 ) rue = "OR" ;
      if (11 <= wurf && wurf  <= 20 ) rue = "OR" ;
      if (21 <= wurf && wurf  <= 30 ) rue = "OR" ;
      if (31 <= wurf && wurf  <= 60 ) rue = "TR" ;
      if (61 <= wurf && wurf  <= 80 ) rue = "TR" ;
      if (81 <= wurf && wurf  <= 95 ) rue = "LR" ;
      if (96 <= wurf && wurf  <= 100) rue = "LR" ;
   }
  if(hauptfenster->getChar()->Typ1()->Short()=="Fi") rue="KR";
  hauptfenster->getWerte().setRuestung1(rue);
  hauptfenster->set_status("Beim Auswürfeln der Rüstung wurde eine "+itos(wurf)+" gewürfelt "
             "==> " + hauptfenster->getWerte().Ruestung()->Long());
  zeige_werte();
}


void table_lernschema::on_button_ausruestung()
{  
  ausruestung_setzen();
}

void table_lernschema::ausruestung_setzen()
{
  if(hauptfenster->wizard) hauptfenster->wizard->next_step(Wizard::AUSRUESTUNG);
  if(!hauptfenster->getOptionen()->OptionenCheck(Midgard_Optionen::NSC_only).active)
     button_ausruestung->set_sensitive(false);
  
  hauptfenster->getAben().setStandardAusruestung();
//  AusruestungBaum &Rucksack=hauptfenster->getAben().getBesitz();
//  setFertigkeitenAusruestung(Rucksack);
  setFertigkeitenAusruestung();
}


void table_lernschema::on_togglebutton_teure_anzeigen_toggled()
{  
 on_lernliste_wahl_toggled();
}

void table_lernschema::on_togglebutton_gelernte_anzeigen_toggled()
{  
 on_lernliste_wahl_toggled();
}

void table_lernschema::on_togglebutton_einschraenkungen_zusatz_anzeigen_toggled()
{  
//  if(checkbutton_einschraenkungen_zusatz->get_active() &&
//     frame_lernschema_zusatz->is_visible())
//    {
      show_datavec_zusatz();
//      lernen_zusatz(was_mem,*MBE_mem);
//    }
}

void table_lernschema::zeige_werte()
{
  zeige_lernpunkte();
  label_ruestung_lernschema->set_text(hauptfenster->getWerte().Ruestung()->Long()); 
  label_herkunft_lernschema->set_text(hauptfenster->getWerte().Herkunft()->Name());
  fertig_typ->set_text(hauptfenster->getChar()->STyp());

  // Spezialwaffe anzeigen?
 if (hauptfenster->getChar()->Typ1()->Spezialwaffe() || 
      hauptfenster->getChar()->Typ2()->Spezialwaffe())
    togglebutton_spezialwaffe->show(); 
 else 
   { togglebutton_spezialwaffe->set_active(false);
     togglebutton_spezialwaffe->hide(); }


 // Magie anzeigen?
 if (hauptfenster->getChar()->is_mage())
   { if ( hauptfenster->getChar()->Typ1()->Spezialgebiet() || 
          hauptfenster->getChar()->Typ2()->Spezialgebiet() ) 
     show_magier_spezialgebiet(true);
     else show_magier_spezialgebiet(false);
     if(hauptfenster->getWerte().Spezialgebiet()->Name()!="")
       combo_magier_spezialgebiet->get_entry()->set_text(hauptfenster->getWerte().Spezialgebiet()->Name());
     button_zauber->set_sensitive(true);   
   }
 else
   { 
     show_magier_spezialgebiet(false);   
     button_zauber->set_sensitive(false);
   }
 // KiDo anzeigen?
 if(MBEmlt(&*cH_Fertigkeit("KiDo"))->ist_gelernt(hauptfenster->getChar()->List_Fertigkeit()))
   { 
     KiDo_Stile kd;
     combo_kido_stil->set_popdown_strings(kd.getVStile());
     frame_KiDo_lernschema->show();
   }  
 else 
   { 
     frame_KiDo_lernschema->hide();
   }
 // KiDo Stil setzen
 combo_kido_stil->get_entry()->set_text(hauptfenster->getWerte().Spezialisierung());
}

void table_lernschema::zeige_lernpunkte()
{
 spinbutton_fach->set_value(lernpunkte.Fach());
 spinbutton_allgemein->set_value(lernpunkte.Allgemein());
 spinbutton_unge->set_value(lernpunkte.Unge());
 spinbutton_waffen->set_value(lernpunkte.Waffen());
 spinbutton_zauber->set_value(lernpunkte.Zauber());
}

void table_lernschema::show_gelerntes()
{
  zeige_lernpunkte();
  
  std::list<MBEmlt> FL;
  std::list<std::list<MBEmlt> > LL;
  LL.push_back(hauptfenster->getChar()->List_Fertigkeit_ang());
  LL.push_back(hauptfenster->getChar()->List_Fertigkeit());
  LL.push_back(hauptfenster->getChar()->List_Waffen());
  LL.push_back(hauptfenster->getChar()->List_Zauber());
  LL.push_back(hauptfenster->getChar()->List_Zauberwerk());
  LL.push_back(hauptfenster->getChar()->List_Kido());
  LL.push_back(hauptfenster->getChar()->List_WaffenGrund());
  LL.push_back(hauptfenster->getChar()->List_Sprache());
  LL.push_back(hauptfenster->getChar()->List_Schrift());
  LL.push_back(hauptfenster->getChar()->List_Beruf());  
  LL.push_back(hauptfenster->getWerte().Sinne());
  {
  std::list<MBEmlt> temp;
  for(std::list<H_WaffeBesitz>::iterator i=hauptfenster->getChar()->List_Waffen_besitz().begin();i!=hauptfenster->getChar()->List_Waffen_besitz().end();++i)
      temp.push_back(H_MidgardBasicElement_mutable(&**i));
  LL.push_back(temp);
  }
  for(std::list<std::list<MBEmlt> >::const_iterator i=LL.begin();i!=LL.end();++i)
    for (std::list<MBEmlt>::const_iterator j=i->begin();j!=i->end();++j)
      FL.push_back(*j);
  MidgardBasicElement::show_list_in_tree(FL,tree_gelerntes,hauptfenster);

  tree_gelerntes->Expand_recursively();
  scrolledwindow_lernen->set_sensitive(true);
}
 

void table_lernschema::show_lernschema()
{
  Abenteurer &A=hauptfenster->getAben();
  if(button_kido_auswahl->get_active()) return;
  clean_lernschema_trees();
  tree_lernschema = manage(new MidgardBasicTree(MidgardBasicTree::LERNSCHEMA));
  tree_lernschema->signal_leaf_selected().connect(SigC::slot(*static_cast<class table_lernschema*>(this), &table_lernschema::on_tree_lernschema_leaf_selected));
  
  MidgardBasicElement::MBEE what;
  std::string fert;
  if(button_waffen->get_active())
    {  what=MidgardBasicElement::WAFFE;
       label_lernschma_titel->set_text("Waffen");
    }
  else if(button_zauber->get_active())
    {  what=MidgardBasicElement::ZAUBER;
       label_lernschma_titel->set_text("Zauber");
    }
  else
    {  what=MidgardBasicElement::FERTIGKEIT;
       if(button_fachkenntnisse->get_active())
         {  fert="Fach";
            label_lernschma_titel->set_text("Fachkenntnisse");
         }
        else if(button_untyp_fertigkeiten->get_active())
         {  fert="Unge";
            label_lernschma_titel->set_text("Ungewöhnliche Fertigkeiten");
         }
        else
         {  fert="Allg";
            label_lernschma_titel->set_text("Allgemeinwissen ("+
                  A.getWerte().Stadt_Land_str()+")");
         }
   }

  std::list<MBEmlt> newlist;
  std::list<MBEmlt> LW;
  LernListen LL(hauptfenster->getDatabase());
  if(fert=="Unge" || fert=="Allg") 
   {
    std::list<MBEmlt> L; 
    if     (fert=="Unge") L=LL.getMBEm(A,LernListen::lUnge,0,0,"Unge");
    else if(fert=="Allg") L=LL.getMBEm(A,LernListen::lAllg,0,0,"Allg");  
    for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
     {
       int lp=(*i)->Lernpunkte();
       if(fert=="Allg")
        {
          if(!togglebutton_teure_anzeigen->get_active() && lp>lernpunkte.Allgemein())
               continue;
        }
       if(fert=="Unge")
       if(!togglebutton_teure_anzeigen->get_active() && lp>lernpunkte.Unge())
            continue;
       if(lp == 99  ) continue;

       if(!(*(*i))->Voraussetzung(A)) continue;
       if ((*(*i))->ist_gelernt(list_FertigkeitZusaetze)) (*i)->setGelernt(true);
       else {(*i)->setGelernt(false);(*i)->setZusatz(MidgardBasicElement::st_zusatz(""));}
       if((*(*i))->Name()=="Landeskunde (Heimat)" && (*(*i))->ist_gelernt(list_FertigkeitZusaetze)) (*i)->setGelernt(true);
       if ((*i)->ist_gelernt(A.List_Fertigkeit())) (*i)->setGelernt(true); 
       if ((*i)->ist_gelernt(A.List_Waffen())) (*i)->setGelernt(true); 
       if((*i)->Gelernt()&&!togglebutton_gelernte_anzeigen->get_active()) continue;
       newlist.push_back(*i);
     }
   }
  if(fert=="Fach") // Freiwillige Speziesfertigkeiten
   {
     std::list<MBEmlt> LW=A.getWerte().Spezies()->getFreiwilligeFertigkeiten(A.getWerte());
     for(std::list<MBEmlt>::iterator i=LW.begin();i!=LW.end();++i)
      {
       (*i)->setLernArt("Fach");
       bool gelernt=false;
       bool zuteuer=false;
       if ((*i)->ist_gelernt(A.List_Fertigkeit())) gelernt=true;
       if ((*(*i))->ist_gelernt(list_FertigkeitZusaetze)) gelernt=true;
       if((*i)->Lernpunkte() > lernpunkte.Fach() ) zuteuer=true;
       if(zuteuer && !togglebutton_teure_anzeigen->get_active()) continue;
       if(gelernt && !togglebutton_gelernte_anzeigen->get_active()) continue;
       if(gelernt) (*i)->setGelernt(true); 
       newlist.push_back(*i);
     }
   }
  if(fert!="Unge" && fert!="Allg" )
    {
    std::list<MBEmlt> L; 
    if(what==MidgardBasicElement::WAFFE) L=LL.getMBEm(A,LernListen::lWaff,0,0,"Waff");
    else if(what==MidgardBasicElement::ZAUBER)L=LL.getMBEm(A,LernListen::lZaub,0,0,"Zaub");
    else if(what==MidgardBasicElement::FERTIGKEIT)L=LL.getMBEm(A,LernListen::lFach,0,0,"Fach");
    for(std::list<MBEmlt>::const_iterator i=L.begin();i!=L.end();++i)
     {
       bool gelernt=false;
       if((*i)->Lernpunkte() == 99  ) continue;
       if(what==MidgardBasicElement::WAFFE) 
        {
          if ((*i)->ist_gelernt(A.List_Waffen())) gelernt=true;
          if (!(*(*i))->Voraussetzung(A)) continue ;
          if(A.Typ1()->Kultwaffe() &&A.List_Waffen().empty())
            hauptfenster->set_status(A.Typ1()->Name(A.getWerte().Geschlecht())+" müssen als erstes ihre Kultwaffe wählen; fehlende Lernpunkte werden geschenkt.");
        }
       else if(what==MidgardBasicElement::ZAUBER)
        {
          if ((*i)->ist_gelernt(A.List_Zauber()) )  gelernt=true;
        }
       else if(what==MidgardBasicElement::FERTIGKEIT)
        {
          if ((*i)->ist_gelernt(newlist)) continue ; // Speziesfertigkeiten
          if (!(*(*i))->Voraussetzung(A)) continue ;
          if ((*i)->ist_gelernt(hauptfenster->getChar()->List_Fertigkeit())) gelernt=true;
          if ((*(*i))->ist_gelernt(list_FertigkeitZusaetze)) gelernt=true;
         (*i)->setLernArt("Fach");
        }

       bool zuteuer=false;
       if(what==MidgardBasicElement::WAFFE)
         { if((*i)->Lernpunkte() > lernpunkte.Waffen() ) zuteuer=true;}
       else if(what==MidgardBasicElement::ZAUBER)
         { if((*i)->Lernpunkte() > lernpunkte.Zauber() ) zuteuer=true; }
       else if(what==MidgardBasicElement::FERTIGKEIT)
         { if((*i)->Lernpunkte() > lernpunkte.Fach() ) zuteuer=true; }

       if(zuteuer && !togglebutton_teure_anzeigen->get_active()) continue;
       if(gelernt && !togglebutton_gelernte_anzeigen->get_active()) continue;
       if(gelernt) (*i)->setGelernt(true); 

       newlist.push_back(*i);
      }
     }   
  MidgardBasicElement::show_list_in_tree(newlist,tree_lernschema,hauptfenster);
  tree_lernschema->show();
  scrolledwindow_lernen->add(*tree_lernschema);

  setTitels_for_Lernschema(what,fert);
  tree_lernschema->Expand_recursively();

  scrolledwindow_lernen->show();
}
 
void table_lernschema::setTitels_for_Lernschema(const MidgardBasicElement::MBEE& what,const std::string& fert)
{
 std::vector<std::string> vs;
 vs.push_back("LP");
 switch (what) {
   case MidgardBasicElement::WAFFE:
     {
       vs.push_back("Grundkenntnnis"); // PFLICHTg
       vs.push_back("Waffe");
       vs.push_back("Wert"); 
       vs.push_back(""); // EIGENSCHAFTg
       vs.push_back("Voraussetzung");   
       vs.push_back("Schwierigkeit");   
       break;
     }
   case MidgardBasicElement::FERTIGKEIT:
     {
       vs.push_back("Pflicht");
       vs.push_back("Fertigkeit");
       vs.push_back("Wert");  
       vs.push_back("L.E.");  
       vs.push_back("Voraussetzung");
       vs.push_back("Kosten");       
       break;
     }
   case MidgardBasicElement::ZAUBER:
     {
       vs.push_back("");
       vs.push_back("Zauber");
       vs.push_back("AP"); // WERTg
       vs.push_back("");
       vs.push_back("");
       vs.push_back("Kosten");
       break;
     }
   default: break;
   }
 vs.push_back("Art");
 vs.push_back("Gelernt");
 tree_lernschema->setTitles(vs);

 switch (what) {
   case MidgardBasicElement::WAFFE:
     {
       tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,true);
       tree_lernschema->set_column_visibility(Data_SimpleTree::EIGENSCHAFTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::VORAUSSETZUNGg,true);
       tree_lernschema->set_column_visibility(Data_SimpleTree::KOSTENg,true);
       break;
     }
   case MidgardBasicElement::FERTIGKEIT:
     {
       if(fert=="Fach") tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,true);
       else tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::EIGENSCHAFTg,true);
       tree_lernschema->set_column_visibility(Data_SimpleTree::VORAUSSETZUNGg,true);
       tree_lernschema->set_column_visibility(Data_SimpleTree::KOSTENg,true);
       break;
     }
   case MidgardBasicElement::ZAUBER:
     {
       tree_lernschema->set_column_visibility(Data_SimpleTree::PFLICHTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::EIGENSCHAFTg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::VORAUSSETZUNGg,false);
       tree_lernschema->set_column_visibility(Data_SimpleTree::KOSTENg,true);
       break;
     }
    default : break;
   }
}

void table_lernschema::clean_lernschema_trees()
{
  scrolledwindow_lernen->remove();
  tree_lernschema=0;
  Beruf_tree=0;
  tree_angeb_fert=0;
  tree_kido_lernschema=0;
  tree_waffen_lernschema=0;
}

