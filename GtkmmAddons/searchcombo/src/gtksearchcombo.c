/* gtksearchcombo - huge data combo-like widget for gtk+
 * Copyright 1999 Christof Petig
 * based on gtkcombo: Copyright 1997 Paolo Molaro
 *                    Modified by the GTK+ Team and others 1997-1999.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <string.h>

#include <gtk/gtkarrow.h>
#include <gtk/gtklabel.h>
#include <gtk/gtklist.h>
#include <gtk/gtkentry.h>
#include <gtk/gtkeventbox.h>
#include <gtk/gtkbutton.h>
#include <gtk/gtklistitem.h>
#include <gtk/gtkscrolledwindow.h>
#include <gtk/gtkmain.h>
#include <gtk/gtksignal.h>
#include <gtk/gtkwindow.h>
#include <gdk/gdkkeysyms.h>
#include "gtksearchcombo.h"
#include <gtk/gtkframe.h>
#include <gtk/gtkwidget.h>

#if 0
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif

enum {
  SELECTED,
  SEARCH,
  /* for reference */
  LAST_SIGNAL
};

const gchar * gtk_searchcombo_string_key = "gtk-searchcombo-string-value";
static guint searchcombo_signals[LAST_SIGNAL] = { 0 };
static GtkListItem *	gtk_searchcombo_find (const GtkSearchCombo * searchcombo);

#define SEARCHCOMBO_LIST_MAX_HEIGHT	(400)
#define	EMPTY_LIST_HEIGHT	(20)
#define START_IDLE_HEIGHT	(180)
#define SEARCHCOMBO_FIRST_SEARCH (20)

static void gtk_searchcombo_class_init(GtkSearchComboClass * klass);
static void gtk_searchcombo_init(GtkSearchCombo * searchcombo);
static void gtk_searchcombo_destroy(GtkObject * searchcombo);
static gint gtk_searchcombo_entry_focus_out(GtkEntry * entry,
					    GdkEventFocus * event,
					    GtkSearchCombo * searchcombo);
static gint gtk_searchcombo_entry_focus_in(GtkEntry * entry,
					   GdkEventFocus * event,
					   GtkSearchCombo * searchcombo);
static void gtk_searchcombo_get_pos(GtkSearchCombo * searchcombo,
				    gint * x,
				    gint * y,
				    gint * height,
				    gint * width);
static void gtk_searchcombo_popup_list(GtkSearchCombo * searchcombo);
static void gtk_searchcombo_activate(GtkWidget * widget,
				     GtkSearchCombo * searchcombo);
static void gtk_searchcombo_new_selection(GtkList * list,
					  GtkSearchCombo * searchcombo);
static void gtk_searchcombo_entry_changed(GtkEntry * entry,
					  GtkSearchCombo * searchcombo);
static gint gtk_searchcombo_button_click(GtkButton * button, GtkSearchCombo * searchcombo);
static void gtk_searchcombo_stop_if_running(GtkSearchCombo * searchcombo);
static void gtk_searchcombo_clear_list(GtkSearchCombo * searchcombo);
static gint gtk_searchcombo_entry_key_press  (GtkEntry     *widget, 
                                               GdkEventKey   *event, 
                                               GtkSearchCombo      *searchcombo);
static gchar *      gtk_searchcombo_func            (GtkListItem  *li);
static gint gtk_searchcombo_capture_focus (GtkSearchCombo * searchcombo);
static gint gtk_searchcombo_complete(GtkSearchCombo *searchcombo);
static void gtk_searchcombo_activate_by_enter (GtkWidget        *widget,
		    GtkSearchCombo         *searchcombo);

static GtkHBoxClass *parent_class = NULL;

static void
gtk_searchcombo_class_init (GtkSearchComboClass * klass)
{
  GtkObjectClass *object_class;
  GtkWidgetClass *widget_class;

  object_class = (GtkObjectClass *) klass;
  widget_class = (GtkWidgetClass *) klass;

  parent_class = gtk_type_class (gtk_hbox_get_type ());
  object_class->destroy = gtk_searchcombo_destroy;
  
  searchcombo_signals[SELECTED] =
    gtk_signal_new ("activate",
		    GTK_RUN_LAST,
		    object_class->type,
		    GTK_SIGNAL_OFFSET (GtkSearchComboClass, activate),
		    gtk_marshal_NONE__NONE,
		    GTK_TYPE_NONE, 0);
  searchcombo_signals[SEARCH] =
    gtk_signal_new ("search",
		    GTK_RUN_LAST,
		    object_class->type,
		    GTK_SIGNAL_OFFSET (GtkSearchComboClass, search),
		    gtk_marshal_NONE__POINTER_INT,
		    GTK_TYPE_NONE, 
		    2,
		    GTK_TYPE_POINTER,
		    GTK_TYPE_BOOL);
  gtk_object_class_add_signals (object_class, searchcombo_signals, LAST_SIGNAL);
  
  klass->search=NULL;
  klass->activate=NULL;
}

static void
gtk_searchcombo_destroy (GtkObject * searchcombo)
{
  gtk_searchcombo_stop_if_running(GTK_SEARCHCOMBO (searchcombo));
  gtk_widget_destroy (GTK_SEARCHCOMBO (searchcombo)->popwin);
  gtk_widget_unref (GTK_SEARCHCOMBO (searchcombo)->popwin);

  if (GTK_OBJECT_CLASS (parent_class)->destroy)
    (*GTK_OBJECT_CLASS (parent_class)->destroy) (searchcombo);
}

/** determine position and size (verbatim copy from gtkcombo.c) */
static void
gtk_searchcombo_get_pos (GtkSearchCombo * searchcombo, gint * x, gint * y, gint * height, gint * width)
{
  GtkBin *popwin;
  GtkWidget *widget;
  GtkScrolledWindow *popup;
  
  gint real_height;
  GtkRequisition list_requisition;
  gboolean show_hscroll = FALSE;
  gboolean show_vscroll = FALSE;
  gint avail_height;
  gint min_height;
  gint alloc_width;
  gint work_height;
  gint old_height;
  gint old_width;
  
  widget = GTK_WIDGET(searchcombo);
  popup  = GTK_SCROLLED_WINDOW (searchcombo->popup);
  popwin = GTK_BIN (searchcombo->popwin);
  
  gdk_window_get_origin (searchcombo->entry->window, x, y);
  real_height = MIN (searchcombo->entry->requisition.height, 
		     searchcombo->entry->allocation.height);
  *y += real_height;
  avail_height = gdk_screen_height () - *y;
  
  gtk_widget_size_request (searchcombo->list, &list_requisition);
  min_height = MIN (list_requisition.height, 
		    popup->vscrollbar->requisition.height);
  if (!GTK_LIST (searchcombo->list)->children)
  {  list_requisition.height += EMPTY_LIST_HEIGHT;
     if (searchcombo->start_idle) list_requisition.height += START_IDLE_HEIGHT;
  }
  
  alloc_width = (widget->allocation.width -
		 2 * popwin->child->style->klass->xthickness -
		 2 * GTK_CONTAINER (popwin->child)->border_width -
		 2 * GTK_CONTAINER (searchcombo->popup)->border_width -
		 2 * GTK_CONTAINER (GTK_BIN (popup)->child)->border_width - 
		 2 * GTK_BIN (popup)->child->style->klass->xthickness);
  
  work_height = (2 * popwin->child->style->klass->ythickness +
		 2 * GTK_CONTAINER (popwin->child)->border_width +
		 2 * GTK_CONTAINER (searchcombo->popup)->border_width +
		 2 * GTK_CONTAINER (GTK_BIN (popup)->child)->border_width +
		 2 * GTK_BIN (popup)->child->style->klass->xthickness);
  
  do 
    {
      old_width = alloc_width;
      old_height = work_height;
      
      if (!show_hscroll &&
	  alloc_width < list_requisition.width)
	{
	  work_height += popup->hscrollbar->requisition.height +
	    GTK_SCROLLED_WINDOW_CLASS 
	    (GTK_OBJECT (searchcombo->popup)->klass)->scrollbar_spacing;
	  show_hscroll = TRUE;
	}
      if (!show_vscroll && 
	  work_height + list_requisition.height > avail_height)
	{
	  if (work_height + min_height > avail_height && 
	      *y - real_height > avail_height)
	    {
	      *y -= (work_height + list_requisition.height + real_height);
	      break;
	    }
	  alloc_width -= 
	    popup->vscrollbar->requisition.width +
	    GTK_SCROLLED_WINDOW_CLASS 
	    (GTK_OBJECT (searchcombo->popup)->klass)->scrollbar_spacing;
	  show_vscroll = TRUE;
	}
    } while (old_width != alloc_width || old_height != work_height);
  
  if (searchcombo->entries_max_width > alloc_width) 
     *width=searchcombo->entries_max_width+(alloc_width-widget->allocation.width);
  else 
     *width = widget->allocation.width;

  if (show_vscroll)
    *height = avail_height;
  else
    *height = work_height + list_requisition.height;
  
  if (*x < 0)
    *x = 0;
}

/** position and popup the list */
static void
gtk_searchcombo_popup_list (GtkSearchCombo * searchcombo)
{
  gint height, width, x, y;

  gtk_searchcombo_get_pos (searchcombo, &x, &y, &height, &width);
  DEBUG(printf("new position %dx%d%+d%+d\n",width,height,x,y));
  gtk_widget_set_uposition (searchcombo->popwin, x, y);
  gtk_widget_set_usize (searchcombo->popwin, width, height);
  gtk_widget_realize (searchcombo->popwin);
  gdk_window_resize (searchcombo->popwin->window, width, height);
  gtk_widget_show (searchcombo->popwin);
}

/** emit 'activate' */
static void        
gtk_searchcombo_activate (GtkWidget        *widget,
		    GtkSearchCombo         *searchcombo)
{  g_return_if_fail (widget != NULL);
   g_return_if_fail (GTK_IS_ENTRY (widget));
   g_return_if_fail (searchcombo != NULL);
   g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
   
   gtk_widget_hide (searchcombo->popwin);
   gtk_searchcombo_stop_if_running(searchcombo);
   gtk_signal_emit (GTK_OBJECT (searchcombo), searchcombo_signals[SELECTED]);
}

static GtkListItem *
gtk_searchcombo_find (const GtkSearchCombo * searchcombo)
{
  gchar *text;
  gchar *ltext;
  GList *clist;
  int (*string_compare) (const char *, const char *);

  if (searchcombo->case_sensitive)
    string_compare = strcmp;
  else
    string_compare = g_strcasecmp;

  text = gtk_entry_get_text (GTK_ENTRY (searchcombo->entry));
DEBUG(printf("Compare string %s\n",text));
  clist = GTK_LIST (searchcombo->list)->children;

  while (clist && clist->data)
    {
      ltext = gtk_searchcombo_func (GTK_LIST_ITEM (clist->data));
      DEBUG(printf("compared with %s\n",ltext));
      if (!ltext)
        continue;
      if (!(*string_compare) (ltext, text))
        return (GtkListItem *) clist->data;
      clist = clist->next;
    }
  return NULL;
}

static void        
gtk_searchcombo_activate_by_enter (GtkWidget        *widget,
		    GtkSearchCombo         *searchcombo)
{  g_return_if_fail (widget != NULL);
   g_return_if_fail (GTK_IS_ENTRY (widget));
   g_return_if_fail (searchcombo != NULL);
   g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
   
   // do not autocomplete if we accept any value
   if (searchcombo->value_in_list && searchcombo->autoexpand_on_activate)
   	gtk_searchcombo_complete(searchcombo);
   if (!searchcombo->ok_if_empty && !GTK_ENTRY(searchcombo->entry)->text_length)
	return;
   if (searchcombo->value_in_list && !gtk_searchcombo_find(searchcombo))
   {	DEBUG(printf("!in list\n"));
   	return;
   }
   gtk_searchcombo_activate(widget,searchcombo);
   searchcombo->value_selected=TRUE;
DEBUG(printf("SCB: abe, value_selected=%d\n",searchcombo->value_selected));
}

static void
gtk_searchcombo_init (GtkSearchCombo * searchcombo)
{
  GtkWidget *arrow;
  GtkWidget *frame;

  searchcombo->case_sensitive = FALSE;
  searchcombo->ok_if_empty = TRUE;
  searchcombo->value_in_list = TRUE;
  searchcombo->search_in_progress = FALSE;
  searchcombo->always_fill = FALSE;
  searchcombo->enable_tab = FALSE;
  searchcombo->autoexpand = FALSE;
  searchcombo->backspace = FALSE;
  searchcombo->search_finished = FALSE;
  searchcombo->value_selected = FALSE;
DEBUG(printf("SCB: value_selected=%d\n",searchcombo->value_selected));
  searchcombo->idle_handler_id=-1;
  searchcombo->autoexpand_on_activate = TRUE;
  searchcombo->start_idle=TRUE;
  searchcombo->already_started=FALSE;
  
  searchcombo->entries_max_width=FALSE;
  searchcombo->entries_max_strlen=FALSE;
  
  searchcombo->entry = gtk_entry_new ();
  searchcombo->button = gtk_button_new ();
  GTK_WIDGET_UNSET_FLAGS (GTK_WIDGET(searchcombo->button), GTK_CAN_FOCUS);
  arrow = gtk_arrow_new (GTK_ARROW_DOWN, GTK_SHADOW_OUT);
  gtk_widget_show (arrow);
  gtk_container_add (GTK_CONTAINER (searchcombo->button), arrow);
  gtk_box_pack_start (GTK_BOX (searchcombo), searchcombo->entry, TRUE, TRUE, 0);
  gtk_box_pack_end (GTK_BOX (searchcombo), searchcombo->button, FALSE, FALSE, 0);
  GTK_WIDGET_UNSET_FLAGS (searchcombo->button, GTK_CAN_FOCUS);
  gtk_widget_show (searchcombo->entry);
  gtk_widget_show (searchcombo->button);
  searchcombo->entry_change_id = gtk_signal_connect (GTK_OBJECT (searchcombo->entry), "changed",
			      (GtkSignalFunc) gtk_searchcombo_entry_changed, searchcombo);
  gtk_signal_connect (GTK_OBJECT (searchcombo->entry), "key_press_event",
		      (GtkSignalFunc) gtk_searchcombo_entry_key_press, searchcombo);
  gtk_signal_connect_after (GTK_OBJECT (searchcombo->entry), "focus_out_event",
			    (GtkSignalFunc) gtk_searchcombo_entry_focus_out, searchcombo);
  gtk_signal_connect_after (GTK_OBJECT (searchcombo->entry), "focus_in_event",
			    (GtkSignalFunc) gtk_searchcombo_entry_focus_in, searchcombo);
  /* searchcombo->activate_id = */
  gtk_signal_connect (GTK_OBJECT (searchcombo->entry), "activate",
		      (GtkSignalFunc) gtk_searchcombo_activate_by_enter, searchcombo);
  gtk_signal_connect(GTK_OBJECT(searchcombo->button), "clicked",
     (GtkSignalFunc)gtk_searchcombo_button_click, searchcombo);

  searchcombo->popwin = gtk_window_new (GTK_WINDOW_POPUP);
  gtk_widget_ref (searchcombo->popwin);
  gtk_window_set_policy (GTK_WINDOW (searchcombo->popwin), 1, 1, 0);

  frame = gtk_frame_new (NULL);
  gtk_container_add (GTK_CONTAINER (searchcombo->popwin), frame);
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_OUT);
  gtk_widget_show (frame);

  searchcombo->popup = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (searchcombo->popup),
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  GTK_WIDGET_UNSET_FLAGS (GTK_SCROLLED_WINDOW (searchcombo->popup)->hscrollbar, GTK_CAN_FOCUS);
  GTK_WIDGET_UNSET_FLAGS (GTK_SCROLLED_WINDOW (searchcombo->popup)->vscrollbar, GTK_CAN_FOCUS);
  gtk_container_add (GTK_CONTAINER (frame), searchcombo->popup);
  gtk_widget_show (searchcombo->popup);

  searchcombo->list = gtk_list_new ();

  gtk_list_set_selection_mode(GTK_LIST(searchcombo->list), GTK_SELECTION_SINGLE);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (searchcombo->popup), searchcombo->list);
  gtk_container_set_focus_vadjustment (GTK_CONTAINER (searchcombo->list),
				       gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (searchcombo->popup)));
  gtk_container_set_focus_hadjustment (GTK_CONTAINER (searchcombo->list),
				       gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (searchcombo->popup)));
  gtk_widget_show (searchcombo->list);

  searchcombo->list_change_id = gtk_signal_connect (GTK_OBJECT (searchcombo->list), "selection_changed",
			     (GtkSignalFunc) gtk_searchcombo_new_selection, searchcombo);
  gtk_signal_connect(GTK_OBJECT(searchcombo), "grab_focus",
    		GTK_SIGNAL_FUNC (gtk_searchcombo_capture_focus),NULL);
}

guint
gtk_searchcombo_get_type (void)
{
  static guint searchcombo_type = 0;

  if (!searchcombo_type)
    {
      static const GtkTypeInfo searchcombo_info =
      {
	"GtkSearchCombo",
	sizeof (GtkSearchCombo),
	sizeof (GtkSearchComboClass),
	(GtkClassInitFunc) gtk_searchcombo_class_init,
	(GtkObjectInitFunc) gtk_searchcombo_init,
	/* reserved_1 */ NULL,
	/* reserved_2 */ NULL,
        (GtkClassInitFunc) NULL,
      };
      searchcombo_type = gtk_type_unique (gtk_hbox_get_type (), &searchcombo_info);
    }
  return searchcombo_type;
}

guint
gtk_search_combo_get_type (void) // needed for gtkmm (default naming scheme)
{  return gtk_searchcombo_get_type();
}

GtkWidget *
gtk_searchcombo_new (void)
{
  return GTK_WIDGET (gtk_type_new (gtk_searchcombo_get_type ()));
}

/** simply hide the window */
static gint
gtk_searchcombo_entry_focus_out (GtkEntry      *entry, 
                                               GdkEventFocus *event, 
                                               GtkSearchCombo      *searchcombo)
{  g_return_val_if_fail (searchcombo != NULL, FALSE);
   g_return_val_if_fail (GTK_IS_SEARCHCOMBO (searchcombo), FALSE);
   DEBUG(printf("gtk_searchcombo_entry_focus_out\n"));
   gtk_widget_hide (searchcombo->popwin);
   /* there should be a better way!!! */
   gtk_searchcombo_stop_if_running(searchcombo);
   return FALSE;
}

/** call select */
static gint
gtk_searchcombo_fill_idle (GtkSearchCombo * searchcombo)
{     gboolean continue_=FALSE;
      
      GDK_THREADS_ENTER ();
      g_return_val_if_fail (searchcombo != NULL, FALSE);
      g_return_val_if_fail (GTK_IS_SEARCHCOMBO (searchcombo), FALSE);
      g_assert(searchcombo->search_in_progress && !searchcombo->search_finished);
      
      DEBUG(printf("fill idle: already_started=%d\n",searchcombo->already_started));
      gtk_signal_emit (GTK_OBJECT (searchcombo), searchcombo_signals[SEARCH],
   		&continue_, 
   		searchcombo->already_started?GTK_SEARCH_FETCH:GTK_SEARCH_OPEN);
      searchcombo->already_started=TRUE;
      if (!continue_)
      {  DEBUG(puts("fill idle: stopped"));
         searchcombo->search_in_progress=FALSE;
         searchcombo->search_finished=TRUE;
         searchcombo->idle_handler_id=-1;
         gtk_signal_emit (GTK_OBJECT (searchcombo), searchcombo_signals[SEARCH],
   		NULL, GTK_SEARCH_CLOSE);
         if (searchcombo->autoexpand && !searchcombo->backspace)
         {  GtkListItem *li=NULL;
            GtkLabel *label=NULL;
            gint children_present=g_list_length(
      			gtk_container_children(GTK_CONTAINER(searchcombo->list)));
      	    if (children_present==1) 
            {  li=(GtkListItem*)(gtk_container_children(
            			GTK_CONTAINER(searchcombo->list))->data);
               g_assert(GTK_IS_LIST_ITEM(li));
               label=(GtkLabel*)(gtk_container_children(GTK_CONTAINER(li))->data);
               g_assert(label != NULL);
               g_assert(GTK_IS_LABEL(label));
               gtk_signal_handler_block (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
               gtk_entry_set_text(GTK_ENTRY (searchcombo->entry), label->label);
               gtk_signal_handler_unblock (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
               gtk_searchcombo_activate(searchcombo->entry, searchcombo);
            }
         }
      }
      GDK_THREADS_LEAVE ();
      return continue_;
}

/** clear the list, query some, queue idle function, display the popwin */
static void
gtk_searchcombo_fill_list(GtkSearchCombo      *searchcombo)
{  gboolean continue_=FALSE;
   gint children_present=-1;
   g_return_if_fail (searchcombo != NULL);
   g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
   
   gtk_searchcombo_clear_list(searchcombo);
   g_return_if_fail (!searchcombo->search_in_progress);
   searchcombo->search_in_progress=TRUE;
   searchcombo->already_started=FALSE;
   searchcombo->value_selected=FALSE;
DEBUG(printf("SCB: fl, value_selected=%d\n",searchcombo->value_selected));
   
   if (!searchcombo->start_idle)
   {  while (children_present<SEARCHCOMBO_FIRST_SEARCH)
      {  continue_=FALSE;
         gtk_signal_emit (GTK_OBJECT (searchcombo), searchcombo_signals[SEARCH],
      		&continue_,
      		searchcombo->already_started?GTK_SEARCH_FETCH:GTK_SEARCH_OPEN);
         searchcombo->already_started=TRUE;
         if (!continue_) break;
         /* I know this is inefficient ... but easy to implement */
         children_present=g_list_length(
      		gtk_container_children(GTK_CONTAINER(searchcombo->list)));
      }
   }
   else continue_=TRUE;
   if (continue_)
   {  searchcombo->idle_handler_id=gtk_idle_add ((GtkFunction) gtk_searchcombo_fill_idle, searchcombo);
   }  
   else
   {  searchcombo->search_in_progress=FALSE;
      searchcombo->search_finished=TRUE;
      searchcombo->idle_handler_id=-1;
      gtk_signal_emit (GTK_OBJECT (searchcombo), searchcombo_signals[SEARCH],
   		NULL, GTK_SEARCH_CLOSE);
      if (searchcombo->autoexpand && !searchcombo->backspace
      	  && children_present==1)
      {  GtkListItem *li=NULL;
         GtkLabel *label=NULL;
         li=(GtkListItem*)(gtk_container_children(
         			GTK_CONTAINER(searchcombo->list))->data);
         g_assert(GTK_IS_LIST_ITEM(li));
         label=(GtkLabel*)(gtk_container_children(GTK_CONTAINER(li))->data);
         g_assert(label != NULL);
         g_assert(GTK_IS_LABEL(label));
         gtk_signal_handler_block (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
         gtk_entry_set_text(GTK_ENTRY (searchcombo->entry), label->label);
         gtk_signal_handler_unblock (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
         gtk_searchcombo_activate(searchcombo->entry, searchcombo);
         return; /* do not pop up */
      }
   }
   gtk_searchcombo_popup_list(searchcombo);
}

/** (re)display the list (if applicable) */
static gint
gtk_searchcombo_entry_focus_in (GtkEntry      *entry, 
                                               GdkEventFocus *event, 
                                               GtkSearchCombo      *searchcombo)
{  g_return_val_if_fail (searchcombo != NULL, FALSE);
   g_return_val_if_fail (GTK_IS_SEARCHCOMBO (searchcombo), FALSE);
   DEBUG(printf("gtk_searchcombo_entry_focus_in\n"));
   
   // do not pop up if value selected and no change happened
   if (searchcombo->value_selected) return FALSE;
   if (searchcombo->search_in_progress || searchcombo->search_finished)
      gtk_searchcombo_popup_list(searchcombo); 
   else if (GTK_ENTRY(searchcombo->entry)->text_length 
   	        || searchcombo->always_fill)
      gtk_searchcombo_fill_list(searchcombo);
   return FALSE;
}

/** restart filling the list */
static void
gtk_searchcombo_entry_changed     (GtkEntry      *entry, 
                                               GtkSearchCombo      *searchcombo)
{  g_return_if_fail (searchcombo != NULL);
   g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
   DEBUG(printf("gtk_searchcombo_entry_changed\n"));
   gtk_searchcombo_fill_list(searchcombo);
}

/** hide or show the popwindow */
static gint 
gtk_searchcombo_button_click(GtkButton *button, GtkSearchCombo *searchcombo)
{  g_return_val_if_fail (searchcombo != NULL, FALSE);
   g_return_val_if_fail (GTK_IS_SEARCHCOMBO (searchcombo), FALSE);
   DEBUG(printf("gtk_searchcombo_button_click\n"));
   if (GTK_WIDGET_VISIBLE(searchcombo->popwin))
   {  gtk_widget_hide(searchcombo->popwin);
      /* is this correct ? CP 2001-9-27, it's new */
      gtk_searchcombo_stop_if_running(searchcombo);
   }
   else 
   {  if (!searchcombo->search_in_progress && !searchcombo->search_finished)
         gtk_searchcombo_fill_list(searchcombo);
      else 
         gtk_searchcombo_popup_list(searchcombo);
      searchcombo->value_selected=FALSE;
      gtk_widget_grab_focus (searchcombo->entry);
   }
   return FALSE;
}

/** emit 'activate' on selection */
static void
gtk_searchcombo_new_selection (GtkList       *list, 
                                               GtkSearchCombo      *searchcombo)
{  GtkListItem *li=NULL;
   GtkLabel *label=NULL;
   g_return_if_fail (searchcombo != NULL);
   g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
   DEBUG(printf("gtk_searchcombo_new_selection\n"));
   if (!GTK_LIST(searchcombo->list)->selection) return;
   li=(GtkListItem*)(GTK_LIST(searchcombo->list)->selection->data);
   g_assert(GTK_IS_LIST_ITEM(li));
   label=(GtkLabel*)(gtk_container_children(GTK_CONTAINER(li))->data);
   g_assert(label != NULL);
   g_assert(GTK_IS_LABEL(label));
   // done in activate but perhaps a good idea to do it earlier
   gtk_searchcombo_stop_if_running(searchcombo); 
   gtk_signal_handler_block (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
   gtk_entry_set_text(GTK_ENTRY (searchcombo->entry), label->label);
   gtk_signal_handler_unblock (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
   gtk_list_unselect_all (list);
   gtk_searchcombo_activate(searchcombo->entry, searchcombo);
}

static void gtk_searchcombo_clear_list(GtkSearchCombo      *searchcombo)
{  g_return_if_fail (searchcombo != NULL);
   g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
   gtk_searchcombo_stop_if_running(searchcombo);
   gtk_list_clear_items(GTK_LIST(searchcombo->list), 0, -1);
   gtk_widget_hide (searchcombo->popwin);
   searchcombo->search_finished=FALSE;
   searchcombo->value_selected=FALSE;
DEBUG(printf("SCB: cl, value_selected=%d\n",searchcombo->value_selected));
}

/** sets text, hides window, clears list, new search at next focus */
void	gtk_searchcombo_set_text		(GtkSearchCombo      *searchcombo,
						const gchar *text)
{  // block change signal
   g_return_if_fail (searchcombo != NULL);
   g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
   gtk_signal_handler_block (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
   gtk_entry_set_text(GTK_ENTRY (searchcombo->entry), text);
   gtk_signal_handler_unblock (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
   // delete list
   gtk_searchcombo_clear_list(searchcombo);
   searchcombo->value_selected=TRUE;
DEBUG(printf("SCB: st, value_selected=%d\n",searchcombo->value_selected));
}

const gchar *	gtk_searchcombo_get_text		(const GtkSearchCombo      *searchcombo)
{  g_return_val_if_fail (searchcombo != NULL, NULL);
   g_return_val_if_fail (GTK_IS_SEARCHCOMBO (searchcombo), NULL);
   return gtk_entry_get_text(GTK_ENTRY (searchcombo->entry));
}

void gtk_searchcombo_add_item(GtkSearchCombo      *searchcombo, const gchar *text)
{  GtkWidget *li;
   g_return_if_fail (searchcombo != NULL);
   g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
   g_return_if_fail (text != NULL);
   
   li = gtk_list_item_new_with_label (text);
   gtk_widget_show (li);
   gtk_container_add (GTK_CONTAINER (searchcombo->list), li);
   /* this assumes that strlen is _much_ faster than gtk_widget_size_request */
   /* and of course this is not exakt */
   if (strlen(text)>searchcombo->entries_max_strlen)
   {  GtkRequisition list_requisition;
      gtk_widget_size_request (searchcombo->list, &list_requisition);
      if (list_requisition.width > searchcombo->entries_max_width)
      {  searchcombo->entries_max_width=list_requisition.width;
/*         printf("%d %s\n",searchcombo->entries_max_width,text); */
      }
      searchcombo->entries_max_strlen=strlen(text);
   }
}

static void
gtk_searchcombo_stop_if_running	(GtkSearchCombo *searchcombo)
{  
   g_return_if_fail (searchcombo != NULL);
   g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
   if (!searchcombo->search_in_progress) return;
   g_assert(searchcombo->idle_handler_id!=-1);
   if (searchcombo->idle_handler_id!=-1)
   {  gtk_idle_remove(searchcombo->idle_handler_id);
      searchcombo->search_in_progress=FALSE;
      gtk_signal_emit (GTK_OBJECT (searchcombo), searchcombo_signals[SEARCH],
   		NULL, GTK_SEARCH_CLOSE);
   }
}

void	
gtk_searchcombo_reset	(GtkSearchCombo *searchcombo)
{
   g_return_if_fail (searchcombo != NULL);
   g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
   gtk_searchcombo_stop_if_running(searchcombo);
   gtk_searchcombo_set_text(searchcombo, "");
   gtk_searchcombo_clear_list(searchcombo);
   searchcombo->value_selected=FALSE;
DEBUG(printf("SCB: r, value_selected=%d\n",searchcombo->value_selected));
}

static gint gtk_searchcombo_complete(GtkSearchCombo *searchcombo)
{   GCompletion * cmpl;
    gchar* prefix;
    gchar* nprefix = NULL;
    gint pos;

    if ( !GTK_LIST (searchcombo->list)->children ) return FALSE;
    
    // looks like completion does not work on empty strings
    // complete if there's only one choice
    if (!GTK_ENTRY(searchcombo->entry)->text_length
    	&& searchcombo->always_fill
    	&& !(GTK_LIST (searchcombo->list)->children -> next))
    {  GList *clist = GTK_LIST (searchcombo->list)->children;
       if (clist && clist->data)
       {  gtk_signal_handler_block (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
          gtk_entry_set_text(GTK_ENTRY (searchcombo->entry), gtk_searchcombo_func (GTK_LIST_ITEM (clist->data)));
          gtk_signal_handler_unblock (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
          return TRUE;
       }
    }
    
    cmpl = g_completion_new ((GCompletionFunc)gtk_searchcombo_func);
    g_completion_add_items (cmpl, GTK_LIST (searchcombo->list)->children);

//    pos = GTK_EDITABLE (searchcombo->entry)->current_pos;
    pos = GTK_ENTRY(searchcombo->entry)->text_length;
    prefix = gtk_editable_get_chars (GTK_EDITABLE (searchcombo->entry), 0, pos);

    g_completion_complete(cmpl, prefix, &nprefix);

    if (nprefix && strlen (nprefix) > strlen (prefix)) 
      { // sollte kein Neulesen erfordern ...
        gtk_signal_handler_block (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
    	gtk_editable_insert_text (GTK_EDITABLE (searchcombo->entry), nprefix + pos, 
				 strlen (nprefix) - strlen (prefix), &pos);
        gtk_signal_handler_unblock (GTK_OBJECT (searchcombo->entry), searchcombo->entry_change_id);
    	GTK_EDITABLE (searchcombo->entry)->current_pos = pos;
    }

    if (nprefix)
      g_free (nprefix);
    g_free (prefix);
    g_completion_free (cmpl);
    return TRUE;
}

static int
gtk_searchcombo_entry_key_press (GtkEntry * entry, GdkEventKey * event, GtkSearchCombo * searchcombo)
{
  searchcombo->backspace= (event->keyval == GDK_BackSpace);
  /* completion */
  if ((searchcombo->enable_tab || (event->state & GDK_MOD1_MASK)) && (event->keyval == GDK_Tab) ) 
  { 
    if ( !GTK_LIST (searchcombo->list)->children ) return FALSE;
    gtk_signal_emit_stop_by_name (GTK_OBJECT (entry), "key_press_event");
    return gtk_searchcombo_complete(searchcombo);
  }

  return FALSE;
}

static gchar *
gtk_searchcombo_func (GtkListItem * li)
{
  GtkWidget *label;
  gchar *ltext = NULL;

  ltext = (gchar *) gtk_object_get_data (GTK_OBJECT (li), gtk_searchcombo_string_key);
  if (!ltext)
    {
      label = GTK_BIN (li)->child;
      if (!label || !GTK_IS_LABEL (label))
	return NULL;
      gtk_label_get (GTK_LABEL (label), &ltext);
    }
  return ltext;
}

void
gtk_searchcombo_set_case_sensitive (GtkSearchCombo * searchcombo, gint val)
{
  g_return_if_fail (searchcombo != NULL);
  g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));

  searchcombo->case_sensitive = val;
}

void
gtk_searchcombo_set_autoexpand (GtkSearchCombo * searchcombo, gint val)
{
  g_return_if_fail (searchcombo != NULL);
  g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));

  searchcombo->autoexpand = val;
}

void
gtk_searchcombo_set_always_fill (GtkSearchCombo * searchcombo, gint val)
{
  g_return_if_fail (searchcombo != NULL);
  g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));

  searchcombo->always_fill = val;
}

void
gtk_searchcombo_set_enable_tab (GtkSearchCombo * searchcombo, gint val)
{
  g_return_if_fail (searchcombo != NULL);
  g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));

  searchcombo->enable_tab = val;
}

void
gtk_searchcombo_set_start_on_idle (GtkSearchCombo * searchcombo, gboolean val)
{
  g_return_if_fail (searchcombo != NULL);
  g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));

  searchcombo->start_idle = val;
}

// deprecated, use gtk_widget_grab_focus instead
void    gtk_searchcombo_grab_focus (GtkSearchCombo * searchcombo)
{  
  g_return_if_fail (searchcombo != NULL);
  g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
  gtk_widget_grab_focus(searchcombo->entry);
}

void	gtk_searchcombo_set_editable (GtkSearchCombo * searchcombo, gint val)
{
  // I assert here that we don't have focus ...
  g_return_if_fail (searchcombo != NULL);
  g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
  if (val)
  {  gtk_widget_show(searchcombo->button);
  }
  else
  {  gtk_widget_hide(searchcombo->button);
  }
  gtk_editable_set_editable( GTK_EDITABLE(searchcombo->entry), val);
  // perhaps GTK_CAN_FOCUS
  if (val) GTK_WIDGET_SET_FLAGS(GTK_WIDGET(searchcombo->entry),GTK_SENSITIVE);
  else GTK_WIDGET_UNSET_FLAGS(GTK_WIDGET(searchcombo->entry),GTK_SENSITIVE);
}

void	gtk_searchcombo_trigger_search (GtkSearchCombo * searchcombo)
{  
  g_return_if_fail (searchcombo != NULL);
  g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));
  gtk_searchcombo_fill_list(searchcombo);
}

static gint gtk_searchcombo_capture_focus (GtkSearchCombo * searchcombo)
{
  g_return_val_if_fail (searchcombo != NULL,FALSE);
  g_return_val_if_fail (GTK_IS_SEARCHCOMBO (searchcombo),FALSE);
  gtk_widget_grab_focus(GTK_WIDGET(searchcombo->entry));
  return TRUE;
}

void gtk_searchcombo_set_value_in_list (GtkSearchCombo * searchcombo, gint val, gint ok_if_empty)
{
  g_return_if_fail (searchcombo != NULL);
  g_return_if_fail (GTK_IS_SEARCHCOMBO (searchcombo));

  searchcombo->value_in_list = val;
  searchcombo->ok_if_empty = ok_if_empty;
}

gint	gtk_searchcombo_get_selected_index(const GtkSearchCombo * searchcombo)
{
  g_return_val_if_fail (searchcombo != NULL,-1);
  g_return_val_if_fail (GTK_IS_SEARCHCOMBO (searchcombo),-1);
  
  if (!GTK_LIST(searchcombo->list)->selection) 
  {  GtkListItem *li=gtk_searchcombo_find(searchcombo);
     if (!li) return -1;
     return g_list_index(GTK_LIST(searchcombo->list)->children, li);
  }
  return g_list_index(GTK_LIST(searchcombo->list)->children, GTK_LIST(searchcombo->list)->selection->data);
}

guint gtk_searchcombo_get_size(const GtkSearchCombo * searchcombo)
{
  g_return_val_if_fail (searchcombo != NULL,0);
  g_return_val_if_fail (GTK_IS_SEARCHCOMBO (searchcombo),0);
  
  return g_list_length(GTK_LIST(searchcombo->list)->children); 
}
