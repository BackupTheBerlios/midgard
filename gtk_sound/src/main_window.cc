// generated 2001/8/25 19:23:23 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to main_window.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "main_window.hh"
#include <gtk--/main.h>

#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <Gtk_OStream.h>
#include <Aux/itos.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

main_window *main_window::objekt;

main_window::main_window(const std::string& pfad_)
: pfad(pfad_)
{
 repeatbool=false;
 killbool=false;
 scrolledwindow_auswahl->hide();
 on_kill_on_new_button_toggled();
 get_files(pfad);
 sound.Set(vec_inputfiles);
 set_tree_titles();
 set_tree_content();
 objekt=this;
 signal(SIGCHLD,&signalhandler);
}

gint main_window::on_eventbox_key_press_event(GdkEventKey *ev)
{   
// if (ev->keyval==GDK_F1) {on_button_refresh_clicked();return 0;}
 if (ev->keyval==GDK_F2) {kill_on_new_button->set_active(!killbool); on_kill_on_new_button_toggled();return 0;}
 if (ev->keyval==GDK_F3) {on_button_kill_clicked();return 0;}
 if (ev->keyval==GDK_F4) {togglebutton_repeat->set_active(!repeatbool); on_togglebutton_repeat_toggled();return 0;}

 static int pressnr=1;
 static std::string kategorie;
// char c=(char)ev->keyval;
 std::string s;
 s+=(char)ev->keyval;;

//cout << pressnr<<"\t"<<kategorie<<"\t"<<s<<"\n";
 if(pressnr==1)  
  {
   kategorie = soundmap::Kategorie(s);
   if (kategorie=="?") return 0;
//cout << "kategorie ="<<kategorie<<"\n";
   toggle_tree(kategorie);
   pressnr=2;
   return 0;
  }          
 if(pressnr==2)  
  {
//cout << "Nr = "<<s<<"\t"<<atoi(s.c_str())<<"\n";      
     toggle_tree(kategorie);
     play_auswahl(kategorie,atoi(s.c_str())); 
     pressnr=1;
     return 0;
  }          
 abort();
}

void main_window::toggle_tree(std::string kategorie)
{
 for (SimpleTree::iterator i=tree_list->begin();i!=tree_list->end();++i)
  { std::vector <std::string> col = (*i).get_columns();      
    for(std::vector <std::string>::const_iterator c=col.begin();c!=col.end();++c)
       if ((*c)==kategorie) (*i).toggle_expansion();
  }
}

void main_window::play_auswahl(std::string kategorie,int nr)
{
   for(soundmap::const_iterator i=sound.begin();i!=sound.end();++i)
      if (sound.Zahl(i)==nr && sound.Kategorie(i)==kategorie)
       {
//cout << sound.Titel(i)<<"\n";
         play(sound.Titel(i),sound.Filename(i));
         return;
       }
}


gint main_window::on_tree_list_key_press_event(GdkEventKey *ev)
{
   return on_eventbox_key_press_event(ev);
}
 

void main_window::set_tree_content()
{
 std::vector<cH_RowDataBase> datavec;

//cout << "Size="<<sound.size()<<"\n";
 for(soundmap::const_iterator i=sound.begin();i!=sound.end();++i)
 {
   datavec.push_back(new Data_tree(sound.Zahl(i),sound.Kategorie(i),sound.Titel(i),sound.Filename(i)));
 }
 tree_list->setDataVec(datavec);
}

void main_window::tree_leaf_selected(cH_RowDataBase d)
{  const Data_tree *dt=dynamic_cast<const Data_tree*>(&*d);

  play(dt->Titel(),dt->Filename());
}

void main_window::on_button_kill_clicked()
{   
  for (vector<st_playlist>::iterator i=vec_playlist.begin();i!=vec_playlist.end();++i)
   {
cout << "kill "<<(*i).pid<<"\n";
     kill((*i).pid,9);
   }
  vec_playlist.clear();
//  system("killall mpg123");
  clist_playlist->clear();
}   


void main_window::play(std::string titel,std::string file)
{
  if(killbool) on_button_kill_clicked();

  std::string com = "mpg123 ";
  if(repeatbool) { com += " -Z ";  titel += " (Repeat)";}
  com+= " -sq -b10240 "+pfad+file+" | asdcat";

 int childpid;
 if (!(childpid=fork()))
  {setpgrp();
// cout << com.c_str()<<' '<<getpid() <<"\n";
   execl("/bin/sh",  "sh","-c",com.c_str(),NULL);
   perror("/bin/sh");
   _exit(errno);
  }

 vec_playlist.push_back(st_playlist(childpid,titel));
//cout << "childpid = "<<childpid<<"\t"<<titel<<"\n";;
 fill_playlist();

}


void main_window::signalhandler(int signr)
{
  if ( signr== SIGCHLD )
   { int result;
    int pid = wait(&result);
//cout << "remove  "<<pid<<"\t"<<result<<'\n';
     objekt->remove_from_playlist(pid);
   }
 signal(SIGCHLD,&signalhandler);
}


void main_window::fill_playlist()
{
 clist_playlist->clear();
 Gtk::OStream os(clist_playlist);
 for (vector<st_playlist>::iterator i=vec_playlist.begin();i!=vec_playlist.end();++i)
  {
   os << (*i).name<<"\n";
   os.flush(&*i);
  }
}

void main_window::on_clist_playlist_select_row(gint row, gint column, GdkEvent *event)
{
  st_playlist *sp = (st_playlist*)clist_playlist->row(row).get_data();
cout << sp->pid <<"\t"<<sp->name<<"\n";
  kill(sp->pid,9);
  for (vector<st_playlist>::iterator i=vec_playlist.begin();i!=vec_playlist.end();++i)
    if(sp->pid==(*i).pid) { vec_playlist.erase(i);break;}
  fill_playlist();
}

void main_window::remove_from_playlist(unsigned int pid)
{
  for (vector<st_playlist>::iterator i=vec_playlist.begin();i!=vec_playlist.end();++i)
     if(pid==(*i).pid) { vec_playlist.erase(i);break;}
  fill_playlist();
}


void main_window::on_kill_on_new_button_toggled()
{
 killbool=kill_on_new_button->get_active();
}

void main_window::on_togglebutton_repeat_toggled()
{
 repeatbool=togglebutton_repeat->get_active();
}



void main_window::set_tree_titles()
{
 vector<std::string> vt;
 vt.push_back("Kategorie");
 vt.push_back("Nr.");
 vt.push_back("Titel");
 tree_list->setTitles(vt);
}


void main_window::get_files(const std::string& pfad)
{
 std::string com = "ls -1 "+pfad+"*_*.mp3";
 FILE *fein = popen(com.c_str(),"r");
 if(fein==NULL) {cout<<"Verzeichnis konnte nicht geöffnet werden\n";exit(0);}  
 vector<std::string> vec_files;
 int maxlaenge=1000;
 char dname[maxlaenge];
 while (fgets(dname,maxlaenge,fein)!=NULL) 
  {
   std::string dateiname_((string)dname,pfad.size(),std::string::npos);
   std::string dateiname (dateiname_,0,dateiname_.size()-1); // Abschließendes '\n' entfernen
   vec_inputfiles.push_back(dateiname);
  }
 pclose(fein);
}

void main_window::on_button_close_clicked()
{   
   on_button_kill_clicked();
   Gtk::Main::instance()->quit(); 
}
