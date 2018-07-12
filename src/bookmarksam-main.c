/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * bookmarksam-main.c
 * Copyright (C) 2018 Rémi Cohen-Scali <remi@cohenscali.net>
 * 
 * sigmoid is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * sigmoid is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <libintl.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <gio/gio.h>
#include <gtk/gtk.h>

#include "bookmarksam-common.h"
#include "bookmarksam.h"

static Bookmarksam *g_bookmarksam;

#ifndef g_strlen
#define g_strlen(str) 	strlen((str))
#endif /* !g_strlen */

GtkWidget *
get_window_widget(Bookmarksam *bookmarksam)
{
    g_debug("get_window_widget(): ENTRY");
    static GtkWidget *window = NULL;
    if (!window)
        {
            GValue *window_value = (GValue *)g_new0(GtkWidget *, 1);
            g_value_init (window_value, GTK_TYPE_WIDGET);
            g_object_get_property(G_OBJECT(g_bookmarksam), "window", window_value);
            window = GTK_WIDGET(g_value_get_object(window_value));
        }
    window = GTK_WIDGET(g_object_ref(window));
    g_debug("get_window_widget(): RETURN(%p)", window);
    return (window);
}

GtkWidget *
get_about_dialog_widget(Bookmarksam *bookmarksam)
{
    g_debug("get_about_dialog_widget(): ENTRY");
    static GtkWidget *about_dialog = NULL;
    if (!about_dialog)
        {
            GValue *about_dialog_value = (GValue *)g_new0(GtkWidget *, 1);
            g_value_init (about_dialog_value, GTK_TYPE_WIDGET);
            g_object_get_property(G_OBJECT(g_bookmarksam), "about-dialog", about_dialog_value);
            about_dialog = GTK_WIDGET(g_value_get_object(about_dialog_value));
        }
    about_dialog = GTK_WIDGET(g_object_ref(about_dialog));
    g_debug("get_about_dialog_widget(): RETURN(%p)", about_dialog);
    return (about_dialog);
}

GSimpleAction *
get_bookmarksam_action(Bookmarksam *bookmarksam, gchar *prefix, gchar *action_name)
{
    g_debug("get_bookmarksam_action(prefix='%s', action_name='%s'): ENTRY", prefix, action_name);

    GValue *action_group_value = (GValue *)g_new0(GtkWidget *, 1);
    g_value_init (action_group_value, G_TYPE_ACTION_MAP);
	GActionGroup *action_group = NULL;
	if (!g_ascii_strncasecmp(prefix, "app", g_strlen("app")))
		{
			g_object_get_property(G_OBJECT(g_bookmarksam), "app-action-group", action_group_value);
			action_group = (GActionGroup *)g_value_get_object(action_group_value);
		}
	else if (!g_ascii_strncasecmp(prefix, "edit", g_strlen("edit")))
		{
			g_object_get_property(G_OBJECT(g_bookmarksam), "edit-action-group", action_group_value);
			action_group = (GActionGroup *)g_value_get_object(action_group_value);
		}
	else if (!g_ascii_strncasecmp(prefix, "display", g_strlen("display")))
		{
			g_object_get_property(G_OBJECT(g_bookmarksam), "display-action-group", action_group_value);
			action_group = (GActionGroup *)g_value_get_object(action_group_value);
		}
	else if (!g_ascii_strncasecmp(prefix, "help", g_strlen("help")))
		{
			g_object_get_property(G_OBJECT(g_bookmarksam), "help-action-group", action_group_value);
			action_group = (GActionGroup *)g_value_get_object(action_group_value);
		}
	else
		{
			g_error(_("unknown action prefix: '%s'"), prefix);
		}


    GAction *action = g_action_map_lookup_action(G_ACTION_MAP(action_group), action_name);

    g_debug("get_bookmarksam_action(): RETURN(%p)", action);
    return (G_SIMPLE_ACTION(action));
}

/*
 * cb_apropos_accel_activate
 */
void
cb_apropos_accel_activate(void)
{
    g_debug("cb_apropos_accel_activate(): ENTRY");
	
    g_debug("cb_apropos_accel_activate(): EXIT");
}

/*
 * cb_app_new_action_activate
 */
void
cb_app_new_action_activate(GSimpleAction *simple,
						   gpointer       user_data)
{
    g_debug("cb_app_new_action_activate(): ENTRY");

    g_debug("cb_app_new_action_activate(): EXIT");
}

/*
 * cb_app_open_action_activate
 */
void
cb_app_open_action_activate(GSimpleAction *simple,
							gpointer       user_data)
{
    g_debug("cb_app_open_action_activate(): ENTRY");
  
    g_debug("cb_app_open_action_activate(): EXIT");
}


/*
 * cb_app_save_action_activate
 */
void
cb_app_save_action_activate(GSimpleAction *simple,
							gpointer       user_data)
{
    g_debug("cb_app_save_action_activate(): ENTRY");

    g_debug("cb_app_save_action_activate(): EXIT");
}

/*
 * cb_app_saveas_action_activate
 */
void
cb_app_saveas_action_activate(GSimpleAction *simple,
							  gpointer       user_data)
{
    g_debug("cb_app_saveas_action_activate(): ENTRY");

    g_debug("cb_app_saveas_action_activate(): EXIT");
}

/*
 * cb_quit
 *
 * Callback for window destroy: this will exit the application
 */
void
cb_quit(void)
{
    g_debug("cb_quit(): ENTRY");
    g_application_quit(G_APPLICATION(g_bookmarksam));
    g_debug("cb_quit(): EXIT");
}

/*
 * cb_app_quit_action_activate
 */
void
cb_app_quit_action_activate(GSimpleAction *simple,
							gpointer       user_data)
{
    g_debug("cb_app_quit_action_activate(): ENTRY");
    GtkWidget *window = get_window_widget(g_bookmarksam);
	
    gtk_widget_hide(window);
    gtk_widget_destroy(window);
    g_object_unref(window);
	
    g_debug("cb_app_quit_action_activate(): EXIT");
}

/*
 * cb_edit_cut_action_activate
 */
void
cb_edit_cut_action_activate(GSimpleAction *simple,
							gpointer       user_data)
{
    g_debug("cb_edit_cut_action_activate(): ENTRY");

    g_debug("cb_edit_cut_action_activate(): EXIT");
}

/*
 * cb_edit_copy_action_activate
 */
void
cb_edit_copy_action_activate(GSimpleAction *simple,
							 gpointer       user_data)
{
    g_debug("cb_edit_copy_action_activate(): ENTRY");

    g_debug("cb_edit_copy_action_activate(): EXIT");
}

/*
 * cb_edit_paste_action_activate
 */
void
cb_edit_paste_action_activate(GSimpleAction *simple,
                         gpointer       user_data)
{
    g_debug("cb_edit_paste_action_activate(): ENTRY");

    g_debug("cb_edit_paste_action_activate(): EXIT");
}

/*
 * cb_edit_delete_action_activate
 */
void
cb_edit_delete_action_activate(GSimpleAction *simple,
							   gpointer       user_data)
{
    g_debug("cb_edit_delete_action_activate(): ENTRY");

    g_debug("cb_edit_delete_action_activate(): EXIT");
}

/*
 * cb_help_about_action_activate
 */
void
cb_help_about_action_activate(GSimpleAction *simple,
							  gpointer       user_data)
{
    g_debug("cb_help_about_action_activate(): ENTRY");
	GtkWidget *window = get_window_widget(g_bookmarksam);
	GtkWidget *about = get_about_dialog_widget(g_bookmarksam);

	gtk_show_about_dialog(GTK_WINDOW(window),
						  "program-name", "Sigmoid",
						  "title", _("About Bookmarksam"),
						  NULL);

	g_object_unref(about);

    g_debug("cb_help_about_action_activate(): EXIT");
}

void
bookmarksam_setup_cb(Bookmarksam *bookmarksam)
{
	g_debug("bookmarksam_setup_cb(): ENTRY");

	g_signal_connect_data(get_bookmarksam_action(bookmarksam, "app", "new"),
						  "activate",
						  G_CALLBACK(cb_app_new_action_activate),
						  (gpointer)bookmarksam,
						  NULL,
						  0);
	
	g_signal_connect_data(get_bookmarksam_action(bookmarksam, "app", "open"),
						  "activate",
						  G_CALLBACK(cb_app_new_action_activate),
						  (gpointer)bookmarksam,
						  NULL,
						  0);

	g_signal_connect_data(get_bookmarksam_action(bookmarksam, "app", "save"),
						  "activate",
						  G_CALLBACK(cb_app_open_action_activate),
						  (gpointer)bookmarksam,
						  NULL,
						  0);

	g_signal_connect_data(get_bookmarksam_action(bookmarksam, "app", "saveas"),
						  "activate",
						  G_CALLBACK(cb_app_saveas_action_activate), 
						  (gpointer)bookmarksam,
						  NULL,
						  0);

	g_signal_connect_data(get_bookmarksam_action(bookmarksam, "app", "quit"),
						  "activate",
						  G_CALLBACK(cb_app_quit_action_activate),
						  (gpointer)bookmarksam,
						  NULL,
						  0);

	g_signal_connect_data(get_bookmarksam_action(bookmarksam, "edit", "cut"),
						  "activate",
						  G_CALLBACK(cb_edit_cut_action_activate),
						  (gpointer)bookmarksam,
						  NULL,
						  0);

	g_signal_connect_data(get_bookmarksam_action(bookmarksam, "edit", "copy"),
						  "activate",
						  G_CALLBACK(cb_edit_copy_action_activate),
						  (gpointer)bookmarksam,
						  NULL,
						  0);

	g_signal_connect_data(get_bookmarksam_action(bookmarksam, "edit", "paste"),
						  "activate",
						  G_CALLBACK(cb_edit_paste_action_activate),
						  (gpointer)bookmarksam,
						  NULL,
						  0);

	g_signal_connect_data(get_bookmarksam_action(bookmarksam, "edit", "delete"),
						  "activate",
						  G_CALLBACK(cb_edit_delete_action_activate),
						  (gpointer)bookmarksam,
						  NULL,
						  0);

	g_signal_connect_data(get_bookmarksam_action(bookmarksam, "help", "about"),
						  "activate",
						  G_CALLBACK(cb_help_about_action_activate),
						  (gpointer)bookmarksam,
						  NULL,
						  0);

    g_debug("bookmarksam_setup_cb(): EXIT");
}

/*
 * main
 *
 * Main entry point for application
 *
 * @param[in] argc  number of arguments
 * @param[in] argv  table of arguments pointers
 *
 * @return exit code as an int
 */
int
main(int argc, char **argv)
{
    int ret = 0;
    g_debug("main(): ENTRY");
    gtk_init(&argc, &argv);
    g_bookmarksam = bookmarksam_new();
	bookmarksam_setup_cb(g_bookmarksam);
    ret = g_application_run(G_APPLICATION(g_bookmarksam), argc, argv);
    g_debug("main(): EXIT = %d", ret);
    exit(ret);
}
