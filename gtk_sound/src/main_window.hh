// generated 2001/8/25 19:23:23 CEST by thoma@Tiger.
// using glademm V0.6.2_cvs
//
// newer (non customized) versions of this file go to main_window.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _MAIN_WINDOW_HH
#  include "main_window_glade.hh"
#  define _MAIN_WINDOW_HH

#include <vector>
#include "class_sound.h"


class main_window : public main_window_glade
{   
       bool killbool,repeatbool;
       struct st_playlist {unsigned int pid;std::string name;
            st_playlist(unsigned int p,std::string n):pid(p),name(n) {}} ;
        
        friend class main_window_glade;
        void on_button_close_clicked();
        void get_files(const std::string& pfad);
        vector<std::string> vec_inputfiles;
        void set_tree_titles();
        void set_tree_content();
        void tree_leaf_selected(cH_RowDataBase d);
        void play(std::string titel,std::string file);
        void fill_playlist();
        void on_clist_playlist_select_row(gint row, gint column, GdkEvent *event);
        void remove_from_playlist(unsigned int pid);
        void play_auswahl(std::string kategorie,int nr);
        void on_kill_on_new_button_toggled();
        void on_button_kill_clicked();
        void on_togglebutton_repeat_toggled();
        void toggle_tree(std::string kategorie);

        soundmap sound;
        std::string pfad;
        vector<st_playlist> vec_playlist;
        gint on_eventbox_key_press_event(GdkEventKey *ev);
        gint on_tree_list_key_press_event(GdkEventKey *ev);

        static main_window *objekt;
        static void signalhandler(int signr);
   public:
      main_window(const std::string& pfad_);
};


#include <Aux/EntryValueIntString.h>

class Data_tree : public RowDataBase
{
   int iindex;
   std::string sindex;
   std::string titel,filename;
//   soundmap sound;
 public:
   Data_tree(int i,std::string s,std::string t,std::string f)
      :iindex(i),sindex(s),titel(t),filename(f){}

   enum spalten {S,I,T};
   virtual const cH_EntryValue Value(guint seqnr, gpointer gp) const
    { 
      switch (seqnr) {
         case S    : return cH_EntryValueIntString(sindex); 
         case I    : return cH_EntryValueIntString(iindex); 
         case T    : return cH_EntryValueIntString(titel);
        }
     return cH_EntryValueIntString("?");
    }
 std::string Titel() const {return titel;}
 std::string Filename() const {return filename;}
 std::string Buchstabe() const {return sindex;}
 int Zahl() const {return iindex;}
};
#endif
