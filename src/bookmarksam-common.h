/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * bookmarksam-common.h
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
#ifndef BOOKMARKSAM_COMMON_H
#define BOOKMARKSAM_COMMON_H

#include <glib.h>
#include <glib/gi18n.h>
#include <gio/gio.h>

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

void cb_app_new_action_activate(GSimpleAction *, gpointer);
void cb_app_open_action_activate(GSimpleAction *, gpointer);
void cb_app_save_action_activate(GSimpleAction *, gpointer);
void cb_app_saveas_action_activate(GSimpleAction *, gpointer);
void cb_app_quit_action_activate(GSimpleAction *, gpointer);
void cb_edit_cut_action_activate(GSimpleAction *, gpointer);
void cb_edit_copy_action_activate(GSimpleAction *, gpointer);
void cb_edit_paste_action_activate(GSimpleAction *, gpointer);
void cb_edit_delete_action_activate(GSimpleAction *, gpointer);
void cb_help_about_action_activate(GSimpleAction *, gpointer);

#endif /* BOOKMARKSAM_COMMON_H */
