/* gtksearchcombo - combo widget for gtk+
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

#ifndef __GTK_SEARCH_COMBO_H__
#define __GTK_SEARCH_COMBO_H__

#include <gtk/gtkhbox.h>
#include <gtk/gtkitem.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GTK_SEARCHCOMBO(obj)			GTK_CHECK_CAST (obj, gtk_searchcombo_get_type (), GtkSearchCombo)
#define GTK_SEARCH_COMBO(obj) GTK_SEARCHCOMBO(obj)
#define GTK_SEARCHCOMBO_CLASS(klass)	GTK_CHECK_CLASS_CAST (klass, gtk_searchcombo_get_type (), GtkSearchComboClass)
#define GTK_IS_SEARCHCOMBO(obj)       GTK_CHECK_TYPE (obj, gtk_searchcombo_get_type ())
#define GTK_IS_SEARCH_COMBO(obj) GTK_IS_SEARCHCOMBO(obj)

typedef struct _GtkSearchCombo		GtkSearchCombo;
typedef struct _GtkSearchComboClass	GtkSearchComboClass;

typedef enum
{
  GTK_SEARCH_FETCH,
  GTK_SEARCH_OPEN,
  GTK_SEARCH_CLOSE
} GtkSCContext;

/* you should access only the entry and list fields directly */
struct _GtkSearchCombo {
	GtkHBox hbox;
	GtkWidget *entry;
	GtkWidget *button;
	GtkWidget *popup;
	GtkWidget *popwin;
	GtkWidget *list;

	guint entry_change_id;
	guint list_change_id;
	guint idle_handler_id;

	guint ok_if_empty:1; /** not yet used */
	guint value_in_list:1;
	guint case_sensitive:1;
	guint always_fill:1;	/** whether to call search on an empty pattern */
	guint enable_tab:1;	/** whether to recognize tab for completion */
	guint autoexpand:1;	/** whether to automatically expand and activate once unique */
	guint autoexpand_on_activate:1; /** whether to expand on pressing Return */
	guint start_idle:1;	/** start search at idle time not in focus_in */
	
	/* internal state variables */
	guint backspace:1;	/** last key was backspace -> do not autocomplete */
	guint search_in_progress:1;	/** whether a search is in progress */
	guint already_started:1;	/** if not true we have to start at idle time */
	guint search_finished:1;	/** search is finished, simply display */
	guint value_selected:1;	/** a value has been selected, do not search without explicit request */
	
	guint entries_max_width;	/** for optimal popup width */
	guint entries_max_strlen;	/** speedup trick */
};

struct _GtkSearchComboClass {
	GtkHBoxClass parent_class;
	void (* search)	(GtkSearchCombo *searchcombo, gboolean *continue_, GtkSCContext new_);
	void (* activate)	(GtkSearchCombo *searchcombo);
};

guint      gtk_searchcombo_get_type              (void);
guint      gtk_search_combo_get_type              (void);

GtkWidget *gtk_searchcombo_new                   (void);
const gchar *gtk_searchcombo_get_text		(const GtkSearchCombo *searchcombo);
void	gtk_searchcombo_set_text		(GtkSearchCombo *searchcombo,
						const gchar * text);
void	gtk_searchcombo_add_item		(GtkSearchCombo *searchcombo,
						const gchar * text);
void	gtk_searchcombo_reset			(GtkSearchCombo *searchcombo);
/* empty list & entry, search again */

void	gtk_searchcombo_set_case_sensitive (GtkSearchCombo * searchcombo, gint val);
void	gtk_searchcombo_set_autoexpand (GtkSearchCombo * searchcombo, gint val);
void	gtk_searchcombo_set_always_fill (GtkSearchCombo * searchcombo, gint val);
void	gtk_searchcombo_set_enable_tab (GtkSearchCombo * searchcombo, gint val);
/* whether this searchcombo degenerates to an uneditable entry (like label) */
void	gtk_searchcombo_set_editable (GtkSearchCombo * searchcombo, gint val);
/* trigger new search e.g. after activate/set_text */
void	gtk_searchcombo_trigger_search (GtkSearchCombo * searchcombo);
/* deprecated, use gtk_widget_grab_focus */
void	gtk_searchcombo_grab_focus (GtkSearchCombo * searchcombo);
void	gtk_searchcombo_set_start_on_idle(GtkSearchCombo * searchcombo,gboolean val);
void	gtk_searchcombo_set_value_in_list (GtkSearchCombo * searchcombo, gint val, gint ok_if_empty);
gint	gtk_searchcombo_get_selected_index(const GtkSearchCombo * searchcombo);
guint	gtk_searchcombo_get_size(const GtkSearchCombo * searchcombo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GTK_SEARCH_COMBO_H__ */
