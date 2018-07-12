# -*- Mode: Makefile.am; indent-tabs-mode: nil; c-basic-offset: 4; tab-width: 4 -*-  */
#
# Makefile.am
#
# Copyright (C) 2018 Rémi Cohen-Scali <remi@cohenscali.net>
# 
# bookmarksam is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# bookmarksam is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.

## Process this file with automake to produce Makefile.in

uidir = $(pkgdatadir)/ui
ui_DATA = bookmarksam.ui

# Preprocessor flags
AM_CPPFLAGS = \
        -DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
        -DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
        -DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
        $(BOOKMARKSAM_CFLAGS)

# Addding debug flags
if DEBUG
AM_CFLAGS =\
         -Wall -g -O0
else
AM_CFLAGS =\
         -Wall -O3
endif

include_HEADERS = 
nodist_include_HEADERS = bookmarksam-common.h

noinst_LTLIBRARIES = libcommon.la

libcommon_la_SOURCES = bookmarksam-common.c

bin_PROGRAMS = bookmarksam

variantparse_SOURCES = \
        variantparse.c

variantparse_LDFLAGS = \
        -Wl,--export-dynamic

variantparse_LDADD = $(VARIANTPARSE_LIBS)

bookmarksam_SOURCES = \
        bookmarksam-main.c \
        bookmarksam.h \
        bookmarksam.c       


bookmarksam_LDFLAGS = \
        -Wl,--export-dynamic

bookmarksam_LDADD = $(BOOKMARKSAM_LIBS)




EXTRA_DIST = $(ui_DATA)

MOSTLYCLEANFILES = *~ \#* .\#*
#DISTCLEANFILES = 

# Remove ui directory on uninstall
uninstall-local: uninstall-local-check
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

.PHONY: unistall-local-check

unistall-local-check:
	rm -rf .deps .\#* \#*

MOSTLYCLEANFILES = *~ \#* .\#* m4/*~ Makefile */Makefile
DISTCLEANFILES = configure Debug Makefile.in src/Makefile.in 

clean-local: clean-local-check

.PHONY: clean-local-check

clean-local-check:
	-rm -rf .anjuta autom4te.cache sigmoid.anjuta
	-rm -rf .anjuta_sym_db.db Debug

