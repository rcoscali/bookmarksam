/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * bookmarksam.h
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

#ifndef _BOOKMARKSAM_
#define _BOOKMARKSAM_

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define BOOKMARKSAM_TYPE_APPLICATION             (bookmarksam_get_type ())
#define BOOKMARKSAM_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), BOOKMARKSAM_TYPE_APPLICATION, Bookmarksam))
#define BOOKMARKSAM_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), BOOKMARKSAM_TYPE_APPLICATION, BookmarksamClass))
#define BOOKMARKSAM_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BOOKMARKSAM_TYPE_APPLICATION))
#define BOOKMARKSAM_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), BOOKMARKSAM_TYPE_APPLICATION))
#define BOOKMARKSAM_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), BOOKMARKSAM_TYPE_APPLICATION, BookmarksamClass))

typedef struct _BookmarksamClass BookmarksamClass;
typedef struct _Bookmarksam Bookmarksam;
typedef struct _BookmarksamPrivate BookmarksamPrivate;

struct _BookmarksamClass
{
    GtkApplicationClass parent_class;
};

enum BookmarksamProperties
    {
        PROP_APPLICATION = 1,
        PROP_BUILDER,
        PROP_WINDOW,
        PROP_ABOUT,
        PROP_APP_ACTION_GROUP,
        PROP_EDIT_ACTION_GROUP,
        PROP_DISPLAY_ACTION_GROUP,
        PROP_HELP_ACTION_GROUP,
        N_PROPERTIES
    };

struct _Bookmarksam
{
    GtkApplication parent_instance;

    BookmarksamPrivate *priv;

};

GType bookmarksam_get_type (void) G_GNUC_CONST;
Bookmarksam *bookmarksam_new (void);

/* Callbacks */

G_END_DECLS

#endif /* _APPLICATION_H_ */
