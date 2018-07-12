/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * bookmarksam.c
 * Copyright (C) 2018 Rémi Cohen-Scali <remi@cohenscali.net>
 * 
 * bookmarksam is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * bookmarksam is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <strings.h>
#include "bookmarksam-common.h"
#include "bookmarksam.h"

#include <glib/gi18n.h>
#include <glib-object.h>
#include <gtk/gtk.h>

/* For testing propose use the local (not installed) ui file */
#define UI_FILE_INSTALLED PACKAGE_DATA_DIR"/ui/bookmarksam.ui"
#define UI_FILE_SRC_LOCAL "src/bookmarksam.ui"
#define UI_FILE_LOCAL     "bookmarksam.ui"

#define TOP_WINDOW "window1"

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

/* ANJUTA: Macro BOOKMARKSAM_APPLICATION gets Bookmarksam - DO NOT REMOVE */
struct _BookmarksamPrivate
{
    GString *filename;
    
    /* ANJUTA: Private declaration for bookmarksam - DO NOT REMOVE */
    GtkBuilder *builder;
    GtkApplication *app;
    GtkWidget *widget;
    GtkWidget *about;

    /* ANJUTA: Widgets declaration for bookmarksam.glade - DO NOT REMOVE */
    GtkWidget *window;
    GtkMenuBar *menubar;
    GtkMenuItem *menufichier;
    GtkImageMenuItem *menufichier_new;
    GtkImageMenuItem *menufichier_open;
    GtkImageMenuItem *menufichier_save;
    GtkImageMenuItem *menufichier_saveas;
    GtkImageMenuItem *menufichier_quit;
    GtkMenuItem *menuedition;
    GtkImageMenuItem *menuedition_cut;
    GtkImageMenuItem *menuedition_copy;
    GtkImageMenuItem *menuedition_paste;
    GtkImageMenuItem *menuedition_delete;
    GtkMenuItem *menuaffichage;
    GtkMenuItem *menuaide;
    GtkImageMenuItem *menuaide_about;
    GtkToolbar *toolbar;
    GtkToolButton *toolnew;
    GtkToolButton *toolopen;
    GtkToolButton *toolsave;
    GtkToolButton *toolsaveas;
    GtkToolButton *toolquit;
    GtkToolButton *toolcut;
    GtkToolButton *toolcopy;
    GtkToolButton *toolpaste;
    GtkToolButton *tooldelete;
    GtkScrolledWindow *scrolledwindow;
    GtkViewport *viewport;
    GtkLabel *framelabel;
    GtkInfoBar *infobar;
    GtkAboutDialog *aboutdialog;

    /* Actions */
    GSimpleActionGroup *actions_app;
    GSimpleActionGroup *actions_edit;
    GSimpleActionGroup *actions_display;
    GSimpleActionGroup *actions_help;
    gboolean save_state;
    gboolean saveas_state;
    gboolean cut_state;
    gboolean copy_state;
    gboolean paste_state;
    gboolean delete_state;
};

G_DEFINE_TYPE_WITH_CODE (Bookmarksam, bookmarksam, GTK_TYPE_APPLICATION, G_ADD_PRIVATE(Bookmarksam));

static void
bookmarksam_init_priv (Bookmarksam *object)
{
    object->priv->window = GTK_WIDGET(gtk_builder_get_object(object->priv->builder, "window1"));
    object->priv->window = GTK_WIDGET(g_object_ref(G_OBJECT(object->priv->window)));
    g_debug("bookmarksam_init_priv(): Window = %p", object->priv->window);
    object->priv->menubar = GTK_MENU_BAR(gtk_builder_get_object(object->priv->builder, "menubar"));
    g_debug("bookmarksam_init_priv(): Menubar = %p", object->priv->menubar);
    object->priv->menufichier = GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menufichier"));
    //g_menu_item_set_attribute (GTKobject->priv->menufichier, "action-namespace", "s", "file");
    g_debug("bookmarksam_init_priv(): Menufichier = %p", object->priv->menufichier);

    object->priv->menufichier_new = (GtkImageMenuItem *)GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuitem-filenew"));
    g_debug("bookmarksam_init_priv(): Menuitem-filenew = %p", object->priv->menufichier_new);
    object->priv->menufichier_open = (GtkImageMenuItem *)GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuitem-fileopen"));
    g_debug("bookmarksam_init_priv(): Menuitem-fileopen = %p", object->priv->menufichier_open);
    object->priv->menufichier_save = (GtkImageMenuItem *)GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuitem-filesave"));
    object->priv->save_state = FALSE;
    g_debug("bookmarksam_init_priv(): Menuitem-filesave = %p", object->priv->menufichier_save);
    object->priv->menufichier_saveas = (GtkImageMenuItem *)GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuitem-filesaveas"));
    object->priv->saveas_state = FALSE;
    g_debug("bookmarksam_init_priv(): Menuitem-filesaveas = %p", object->priv->menufichier_saveas);
    object->priv->menufichier_quit = (GtkImageMenuItem *)GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuitem-filequit"));
    g_debug("bookmarksam_init_priv(): Menuitem-filequit = %p", object->priv->menufichier_quit);

    object->priv->menuedition = GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuedition"));
    //g_menu_item_set_attribute (object->priv->menuedition, "action-namespace", "s", "edit");
    g_debug("bookmarksam_init_priv(): Menuedition = %p", object->priv->menuedition);

    object->priv->menuedition_cut = (GtkImageMenuItem *)GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuitem-editcut"));
    object->priv->cut_state = FALSE;
    g_debug("bookmarksam_init_priv(): Menuedition-filecut = %p", object->priv->menuedition_cut);
    object->priv->menuedition_copy = (GtkImageMenuItem *)GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuitem-editcopy"));
    object->priv->copy_state = FALSE;
    g_debug("bookmarksam_init_priv(): Menuedition-filecopy = %p", object->priv->menuedition_copy);
    object->priv->menuedition_paste = (GtkImageMenuItem *)GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuitem-editpaste"));
    object->priv->paste_state = FALSE;
    g_debug("bookmarksam_init_priv(): Menuedition-filepaste = %p", object->priv->menuedition_paste);
    object->priv->menuedition_delete = (GtkImageMenuItem *)GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuitem-editdelete"));
    object->priv->delete_state = FALSE;
    g_debug("bookmarksam_init_priv(): Menuedition-filedelete = %p", object->priv->menuedition_delete);

    object->priv->menuaffichage = GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuaffichage"));
    //g_menu_item_set_attribute (object->priv->menuaffichage, "action-namespace", "s", "display");
    g_debug("bookmarksam_init_priv(): Menuaffichage = %p", object->priv->menuaffichage);
    object->priv->menuaide = GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuaide"));
    //g_menu_item_set_attribute (object->priv->menuaide, "action-namespace", "s", "help");
    g_debug("bookmarksam_init_priv(): Menuaide = %p", object->priv->menuaide);

    object->priv->menuaide_about = (GtkImageMenuItem *)GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuitem-helpabout"));
    g_debug("bookmarksam_init_priv(): Menuaide-helpabout = %p", object->priv->menuaide_about);
    
    object->priv->toolbar = GTK_TOOLBAR(gtk_builder_get_object(object->priv->builder, "toolbar"));
    g_debug("bookmarksam_init_priv(): Toolbar = %p", object->priv->toolbar);

    object->priv->toolnew = GTK_TOOL_BUTTON(gtk_builder_get_object(object->priv->builder, "tool-new"));
    g_debug("bookmarksam_init_priv(): Tool-new = %p", object->priv->toolnew);
    object->priv->toolopen = GTK_TOOL_BUTTON(gtk_builder_get_object(object->priv->builder, "tool-open"));
    g_debug("bookmarksam_init_priv(): Tool-open = %p", object->priv->toolopen);
    object->priv->toolsave = GTK_TOOL_BUTTON(gtk_builder_get_object(object->priv->builder, "tool-save"));
    g_debug("bookmarksam_init_priv(): Tool-save = %p", object->priv->toolsave);
    object->priv->toolsaveas = GTK_TOOL_BUTTON(gtk_builder_get_object(object->priv->builder, "tool-saveas"));
    g_debug("bookmarksam_init_priv(): Tool-saveas = %p", object->priv->toolsaveas);
    object->priv->toolquit = GTK_TOOL_BUTTON(gtk_builder_get_object(object->priv->builder, "tool-quit"));
    g_debug("bookmarksam_init_priv(): Tool-quit = %p", object->priv->toolquit);

    object->priv->toolcut = GTK_TOOL_BUTTON(gtk_builder_get_object(object->priv->builder, "tool-cut"));
    g_debug("bookmarksam_init_priv(): Tool-cut = %p", object->priv->toolcut);
    object->priv->toolcopy = GTK_TOOL_BUTTON(gtk_builder_get_object(object->priv->builder, "tool-copy"));
    g_debug("bookmarksam_init_priv(): Tool-copy = %p", object->priv->toolcopy);
    object->priv->toolpaste = GTK_TOOL_BUTTON(gtk_builder_get_object(object->priv->builder, "tool-paste"));
    g_debug("bookmarksam_init_priv(): Tool-paste = %p", object->priv->toolpaste);
    object->priv->tooldelete = GTK_TOOL_BUTTON(gtk_builder_get_object(object->priv->builder, "tool-delete"));
    g_debug("bookmarksam_init_priv(): Tool-delete = %p", object->priv->tooldelete);
    
    object->priv->scrolledwindow = GTK_SCROLLED_WINDOW(gtk_builder_get_object(object->priv->builder, "scrolledwindow"));
    g_debug("bookmarksam_init_priv(): ScrolledWindow = %p", object->priv->scrolledwindow);
    object->priv->viewport = GTK_VIEWPORT(gtk_builder_get_object(object->priv->builder, "viewport"));
    g_debug("bookmarksam_init_priv(): Viewport = %p", object->priv->viewport);
    object->priv->framelabel = GTK_LABEL(gtk_builder_get_object(object->priv->builder, "framelabel"));
    g_debug("bookmarksam_init_priv(): Framelabel = %p", object->priv->framelabel);
    object->priv->infobar = GTK_INFO_BAR(gtk_builder_get_object(object->priv->builder, "infobar"));
    g_debug("bookmarksam_init_priv(): Infobar = %p", object->priv->infobar);
    object->priv->aboutdialog = GTK_ABOUT_DIALOG(gtk_builder_get_object(object->priv->builder, "aboutdialog"));
    object->priv->about = GTK_WIDGET(object->priv->aboutdialog);
    g_debug("bookmarksam_init_priv(): AboutDialog = %p", object->priv->aboutdialog);

    g_debug("bookmarksam_init_priv(): EXIT");
}

static void
bookmarksam_save_activate(GSimpleAction *simple,
                          GVariant *param,
                          gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);

    param = param;
    g_debug("bookmarksam_save_activate(): ENTRY");
    priv->save_state = ! priv->save_state;
    GVariant *save_state = g_variant_parse(NULL, priv->save_state ? "false" : "true", NULL, NULL, NULL);
    GAction *save_action = g_action_map_lookup_action(G_ACTION_MAP(priv->actions_app), "save");
    g_simple_action_set_state(G_SIMPLE_ACTION(save_action), save_state);
    g_debug("bookmarksam_save_activate(): EXIT");
}

static void
bookmarksam_on_save_state_changed(GSimpleAction *action,
								  GVariant *value,
                                  gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);
    
    g_debug("bookmarksam_on_save_state_changed(): ENTRY: state = %s", priv->save_state ? "TRUE" : "FALSE");
    gtk_widget_set_sensitive(GTK_WIDGET(priv->menufichier_save), priv->save_state);
    gtk_widget_set_sensitive(GTK_WIDGET(priv->toolsave), priv->save_state);
    g_debug("bookmarksam_on_save_state_changed(): EXIT");
}

static void
bookmarksam_saveas_activate(GSimpleAction *simple,
                            GVariant *param,
                            gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);

    param = param;
    g_debug("bookmarksam_saveas_activate(): ENTRY");
    priv->saveas_state = ! priv->saveas_state;
    GVariant *saveas_state = g_variant_parse(NULL, priv->saveas_state ? "false" : "true", NULL, NULL, NULL);
    GAction *saveas_action = g_action_map_lookup_action(G_ACTION_MAP(priv->actions_app), "saveas");
    g_simple_action_set_state(G_SIMPLE_ACTION(saveas_action), saveas_state);
    g_debug("bookmarksam_saveas_activate(): EXIT");
}

static void
bookmarksam_on_saveas_state_changed(GSimpleAction *action,
									GVariant *value,
                                    gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);
    
    g_debug("bookmarksam_on_saveas_state_changed(): ENTRY: state = %s", priv->saveas_state ? "TRUE" : "FALSE");
    gtk_widget_set_sensitive(GTK_WIDGET(priv->menufichier_saveas), priv->saveas_state);
    gtk_widget_set_sensitive(GTK_WIDGET(priv->toolsaveas), priv->saveas_state);
    g_debug("bookmarksam_on_saveas_state_changed(): EXIT");
}

static void
bookmarksam_cut_activate(GSimpleAction *simple,
                         GVariant *param,
                         gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);

    param = param;
    g_debug("bookmarksam_cut_activate(): ENTRY");
    priv->cut_state = ! priv->cut_state;
    GVariant *cut_state = g_variant_parse(NULL, priv->cut_state ? "false" : "true", NULL, NULL, NULL);
    GAction *cut_action = g_action_map_lookup_action(G_ACTION_MAP(priv->actions_edit), "cut");
    g_simple_action_set_state(G_SIMPLE_ACTION(cut_action), cut_state);
    g_debug("bookmarksam_cut_activate(): EXIT");
}

static void
bookmarksam_on_cut_state_changed(GSimpleAction *action,
								 GVariant *value,
                                 gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);
    
    g_debug("bookmarksam_on_cut_state_changed(): ENTRY: state = %s", priv->cut_state ? "TRUE" : "FALSE");
    gtk_widget_set_sensitive(GTK_WIDGET(priv->menuedition_cut), priv->cut_state);
    gtk_widget_set_sensitive(GTK_WIDGET(priv->toolcut), priv->cut_state);
    g_debug("bookmarksam_on_cut_state_changed(): EXIT");
}

static void
bookmarksam_copy_activate(GSimpleAction *simple,
                          GVariant *param,
                          gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);

    param = param;
    g_debug("bookmarksam_copy_activate(): ENTRY");
    priv->copy_state = ! priv->copy_state;
    GVariant *copy_state = g_variant_parse(NULL, priv->copy_state ? "false" : "true", NULL, NULL, NULL);
    GAction *copy_action = g_action_map_lookup_action(G_ACTION_MAP(priv->actions_edit), "copy");
    g_simple_action_set_state(G_SIMPLE_ACTION(copy_action), copy_state);
    g_debug("bookmarksam_copy_activate(): EXIT");
}

static void
bookmarksam_on_copy_state_changed(GSimpleAction *action,
								  GVariant *value,
                                  gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);
    
    g_debug("bookmarksam_on_copy_state_changed(): ENTRY: state = %s", priv->copy_state ? "TRUE" : "FALSE");
    gtk_widget_set_sensitive(GTK_WIDGET(priv->menuedition_copy), priv->copy_state);
    gtk_widget_set_sensitive(GTK_WIDGET(priv->toolcopy), priv->copy_state);
    g_debug("bookmarksam_on_copy_state_changed(): EXIT");
}

static void
bookmarksam_paste_activate(GSimpleAction *simple,
                           GVariant *param,
                           gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);

    param = param;
    g_debug("bookmarksam_paste_activate(): ENTRY");
    priv->paste_state = ! priv->paste_state;
    GVariant *paste_state = g_variant_parse(NULL, priv->paste_state ? "false" : "true", NULL, NULL, NULL);
    GAction *paste_action = g_action_map_lookup_action(G_ACTION_MAP(priv->actions_edit), "paste");
    g_simple_action_set_state(G_SIMPLE_ACTION(paste_action), paste_state);
    g_debug("bookmarksam_paste_activate(): EXIT");
}

static void
bookmarksam_on_paste_state_changed(GSimpleAction *action,
								   GVariant *value,
                                   gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);
    
    g_debug("bookmarksam_on_paste_state_changed(): ENTRY: state = %s", priv->paste_state ? "TRUE" : "FALSE");
    gtk_widget_set_sensitive(GTK_WIDGET(priv->menuedition_paste), priv->paste_state);
    gtk_widget_set_sensitive(GTK_WIDGET(priv->toolpaste), priv->paste_state);
    g_debug("bookmarksam_on_paste_state_changed(): EXIT");
}

static void
bookmarksam_delete_activate(GSimpleAction *simple,
                            GVariant *param,
                            gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);

    param = param;
    g_debug("bookmarksam_delete_activate(): ENTRY");
    priv->delete_state = ! priv->delete_state;
    GVariant *delete_state = g_variant_parse(NULL, priv->delete_state ? "false" : "true", NULL, NULL, NULL);
    GAction *delete_action = g_action_map_lookup_action(G_ACTION_MAP(priv->actions_edit), "delete");
    g_simple_action_set_state(G_SIMPLE_ACTION(delete_action), delete_state);
    g_debug("bookmarksam_delete_activate(): EXIT");
}

static void
bookmarksam_on_delete_state_changed(GSimpleAction *action,
									GVariant *value,
                                    gpointer userdata)
{
    Bookmarksam *app = BOOKMARKSAM_APPLICATION(userdata);
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (app, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);
    
    g_debug("bookmarksam_on_delete_state_changed(): ENTRY: state = %s", priv->delete_state ? "TRUE" : "FALSE");
    gtk_widget_set_sensitive(GTK_WIDGET(priv->menuedition_delete), priv->delete_state);
    gtk_widget_set_sensitive(GTK_WIDGET(priv->tooldelete), priv->delete_state);
    g_debug("bookmarksam_on_delete_state_changed(): EXIT");
}

/* Create a new window loading a file */
static void
bookmarksam_startup (GApplication *app)
{
    GError* error = NULL;
    BookmarksamPrivate *priv = BOOKMARKSAM_APPLICATION(app)->priv;

    g_debug("bookmarksam_new_window(): builder = %p, ENTRY", priv->builder);

    /* Load UI from file */
    priv->builder = gtk_builder_new();
    
#define TRY_LOAD_UI_FILE(ui_file)                                   \
    if (gtk_builder_add_from_file (priv->builder, ui_file, &error)) \
        break;
    
    do
        {
            TRY_LOAD_UI_FILE(UI_FILE_LOCAL);
            g_error ("Couldn't load builder file: %s", error->message);
            TRY_LOAD_UI_FILE(UI_FILE_SRC_LOCAL);
            g_error ("Couldn't load builder file: %s", error->message);
            TRY_LOAD_UI_FILE(UI_FILE_INSTALLED);
            
            g_critical ("Couldn't load builder file: %s", error->message);
            g_error_free (error);
        }
    while (0);
#undef TRY_LOAD_UI_FILE

    /* Set app property */
    g_debug("bookmarksam_new_window(): app = %p", app);
    priv->app = GTK_APPLICATION(app);

    /* load all widgets */
    bookmarksam_init_priv(BOOKMARKSAM_APPLICATION(app));
    priv->widget = GTK_WIDGET(priv->window);
    
    /* Auto-connect signal handlers */
    gtk_builder_connect_signals (priv->builder, app);

    /* ANJUTA: Widgets initialization for bookmarksam.ui - DO NOT REMOVE */

    gtk_window_set_application (GTK_WINDOW (priv->window), GTK_APPLICATION (app));

    GSimpleActionGroup *app_action_group = g_simple_action_group_new();
    GSimpleActionGroup *edit_action_group = g_simple_action_group_new();
    GSimpleActionGroup *display_action_group = g_simple_action_group_new();
    GSimpleActionGroup *help_action_group = g_simple_action_group_new();

	priv->actions_app = app_action_group;
	priv->actions_edit = edit_action_group;
	priv->actions_display = display_action_group;
	priv->actions_help = help_action_group;

    gtk_widget_insert_action_group(GTK_WIDGET(priv->window), "app", G_ACTION_GROUP(priv->actions_app));
    gtk_widget_insert_action_group(GTK_WIDGET(priv->window), "edit", G_ACTION_GROUP(priv->actions_edit));
    gtk_widget_insert_action_group(GTK_WIDGET(priv->window), "display", G_ACTION_GROUP(priv->actions_display));
    gtk_widget_insert_action_group(GTK_WIDGET(priv->window), "help", G_ACTION_GROUP(priv->actions_help));
    
    const GActionEntry app_entries[] = {
        { "new",             NULL, NULL, NULL, NULL},
        { "open",            NULL, NULL, NULL, NULL},
        { "save",            bookmarksam_save_activate, NULL, "true", bookmarksam_on_save_state_changed        },
        { "saveas",          bookmarksam_saveas_activate, NULL, "true", bookmarksam_on_saveas_state_changed    },
        { "quit",            NULL, NULL, NULL, NULL }
    };
    const GActionEntry edit_entries[] = {
        { "cut",            bookmarksam_cut_activate,    NULL,    "true", bookmarksam_on_cut_state_changed     },
        { "copy",           bookmarksam_copy_activate,   NULL,    "true", bookmarksam_on_copy_state_changed    },
        { "paste",          bookmarksam_paste_activate,  NULL,    "true", bookmarksam_on_paste_state_changed   },
        { "delete",         bookmarksam_delete_activate,  NULL,    "true", bookmarksam_on_delete_state_changed }
    };
    const GActionEntry help_entries[] = {
        { "about",          NULL,  NULL,   NULL, NULL }
    };
    g_action_map_add_action_entries(G_ACTION_MAP(app_action_group), app_entries,  G_N_ELEMENTS (app_entries), app);
    g_action_map_add_action_entries(G_ACTION_MAP(edit_action_group), edit_entries,  G_N_ELEMENTS (edit_entries), app);
    g_action_map_add_action_entries(G_ACTION_MAP(help_action_group), help_entries,  G_N_ELEMENTS (help_entries), app);

    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->menufichier_new), "app.new");
    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->menufichier_open), "app.open");
    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->menufichier_save), "app.save");
    gtk_widget_set_sensitive(GTK_WIDGET(priv->menufichier_save), FALSE);
    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->menufichier_saveas), "app.saveas");
    gtk_widget_set_sensitive(GTK_WIDGET(priv->menufichier_saveas), FALSE);
    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->menufichier_quit), "app.quit");

    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->menuaide_about), "help.about");

    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->toolnew), "app.new");
    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->toolopen), "app.open");
    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->toolsave), "app.save");
    gtk_widget_set_sensitive(GTK_WIDGET(priv->toolsave), FALSE);
    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->toolsaveas), "app.saveas");
    gtk_widget_set_sensitive(GTK_WIDGET(priv->toolsaveas), FALSE);
    gtk_actionable_set_action_name(GTK_ACTIONABLE(priv->toolquit), "app.quit");

    g_debug("bookmarksam_new_window(): EXIT");
}


/* GApplication implementation */
static void
bookmarksam_activate (GApplication *application)
{
    g_debug("bookmarksam_activate(): ENTRY");

    bookmarksam_startup (application);
    //bookmarksam_new();

    gtk_widget_show_all (GTK_WIDGET (BOOKMARKSAM_APPLICATION(application)->priv->window));
    gtk_window_present (GTK_WINDOW (BOOKMARKSAM_APPLICATION(application)->priv->window));
    
    g_debug("bookmarksam_activate(): EXIT");
}

static void
bookmarksam_open (GApplication  *application,
                  GFile        **files,
                  gint           n_files,
                  const gchar   *hint)
{
    gint i;
    
    g_debug("bookmarksam_open(): ENTRY");
    for (i = 0; i < n_files; i++)
        {
            bookmarksam_startup (application);
            //bookmarksam_open(files[i]);
        }
    g_debug("bookmarksam_open(): EXIT");
}

static void
bookmarksam_set_property (GObject      *object,
                          guint         property_id,
                          const GValue *value,
                          GParamSpec   *pspec)
{
    //Bookmarksam *self = BOOKMARKSAM_APPLICATION (object);

    g_debug("bookmarksam_set_property(): ENTRY");
    switch (property_id)
        {
        default:
            /* We don't have any other property... */
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
        }
    g_debug("bookmarksam_set_property(): EXIT");
}

static void
bookmarksam_get_property (GObject    *object,
                          guint       property_id,
                          GValue     *value,
                          GParamSpec *pspec)
{
    Bookmarksam *self = BOOKMARKSAM_APPLICATION (object);

    g_debug("bookmarksam_get_property(): ENTRY");
    switch (property_id)
        {
        case PROP_APPLICATION:
            g_value_set_object (value, self->priv->app);
            break;
            
        case PROP_BUILDER:
            g_value_set_object (value, self->priv->builder);
            break;
            
        case PROP_WINDOW:
            g_value_set_object (value, self->priv->widget);
            break;
            
        case PROP_ABOUT:
            g_value_set_object (value, self->priv->about);
            break;
            
        case PROP_APP_ACTION_GROUP:
            g_value_set_object (value, self->priv->actions_app);
            break;
            
        case PROP_EDIT_ACTION_GROUP:
            g_value_set_object (value, self->priv->actions_edit);
            break;
            
        case PROP_DISPLAY_ACTION_GROUP:
            g_value_set_object (value, self->priv->actions_display);
            break;
            
        case PROP_HELP_ACTION_GROUP:
            g_value_set_object (value, self->priv->actions_help);
            break;
            
        default:
            /* We don't have any other property... */
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
        }
    g_debug("bookmarksam_get_property(): EXIT");
}

static void
bookmarksam_init (Bookmarksam *object)
{
    g_debug("bookmarksam_init(): ENTRY");
    object->priv = G_TYPE_INSTANCE_GET_PRIVATE (object, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);
    bzero(object->priv, sizeof(struct _BookmarksamPrivate));
    g_debug("bookmarksam_init(): EXIT");
}

static void
bookmarksam_finalize (GObject *object)
{
    g_debug("bookmarksam_finalize(): ENTRY");
    BookmarksamPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (object, BOOKMARKSAM_TYPE_APPLICATION, BookmarksamPrivate);
    g_object_unref(priv->builder);
    g_object_unref(priv->actions_app);
    g_object_unref(priv->actions_edit);
    g_object_unref(priv->actions_display);
    g_object_unref(priv->actions_help);
    G_OBJECT_CLASS (bookmarksam_parent_class)->finalize (object);
    g_debug("bookmarksam_finalize(): EXIT");
}

static void
bookmarksam_class_init (BookmarksamClass *klass)
{
    g_debug("bookmarksam_class_init(): ENTRY");
    //G_APPLICATION_CLASS (klass)->startup = bookmarksam_startup;
    G_APPLICATION_CLASS (klass)->activate = bookmarksam_activate;
    G_APPLICATION_CLASS (klass)->open = bookmarksam_open;

    G_OBJECT_CLASS (klass)->set_property = bookmarksam_set_property;
    G_OBJECT_CLASS (klass)->get_property = bookmarksam_get_property;
    G_OBJECT_CLASS (klass)->finalize = bookmarksam_finalize;

    obj_properties[PROP_APPLICATION] =
        g_param_spec_object ("app",
                             "Application",
                             _("The Bookmarksam GTK application object."),
                             GTK_TYPE_APPLICATION  /* type of object */,
                             G_PARAM_READABLE);

    obj_properties[PROP_BUILDER] =
        g_param_spec_object ("builder",
                             "Builder",
                             _("Name of the builder to load and display UI file."),
                             GTK_TYPE_BUILDER  /* type of object */,
                             G_PARAM_READABLE);
    
    obj_properties[PROP_WINDOW] =
        g_param_spec_object ("window",
                             "Window",
                             _("GTK window of the Bookmarksam application."),
                             GTK_TYPE_WIDGET  /* type of object */,
                             G_PARAM_READABLE);
    
    obj_properties[PROP_ABOUT] =
        g_param_spec_object ("about-dialog",
                             "AboutDialog",
                             _("GTK window of the Bookmarksam application about dialog."),
                             GTK_TYPE_WIDGET  /* type of object */,
                             G_PARAM_READABLE);
    
    obj_properties[PROP_APP_ACTION_GROUP] =
        g_param_spec_object ("app-action-group",
                             "AppActionGroup",
                             _("APP Action group for the Bookmarksam application."),
                             G_TYPE_ACTION_MAP  /* type of object */,
                             G_PARAM_READABLE);
    
    obj_properties[PROP_EDIT_ACTION_GROUP] =
        g_param_spec_object ("edit-action-group",
                             "EditActionGroup",
                             _("EDIT Action group for the Bookmarksam application."),
                             G_TYPE_ACTION_MAP  /* type of object */,
                             G_PARAM_READABLE);
    
    obj_properties[PROP_DISPLAY_ACTION_GROUP] =
        g_param_spec_object ("display-action-group",
                             "DisplayActionGroup",
                             _("DISPLAY Action group for the Bookmarksam application."),
                             G_TYPE_ACTION_MAP  /* type of object */,
                             G_PARAM_READABLE);
    
    obj_properties[PROP_HELP_ACTION_GROUP] =
        g_param_spec_object ("help-action-group",
                             "HelpActionGroup",
                             _("HELP Action group for the Bookmarksam application."),
                             G_TYPE_ACTION_MAP  /* type of object */,
                             G_PARAM_READABLE);
    
    g_object_class_install_properties (G_OBJECT_CLASS (klass),
                                       N_PROPERTIES,
                                       obj_properties);
    
    g_debug("bookmarksam_class_init(): EXIT");
}

Bookmarksam *
bookmarksam_new (void)
{
    Bookmarksam *ret = BOOKMARKSAM_APPLICATION(NULL);
    g_debug("bookmarksam_new(): ENTRY");
    ret = g_object_new (bookmarksam_get_type (),
                        "application-id", "org.gnome.bookmarksam",
                        "flags", G_APPLICATION_HANDLES_OPEN,
                        NULL);
    g_debug("bookmarksam_new() = %p: EXIT", ret);
    return ret;
}
