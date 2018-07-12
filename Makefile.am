# -*- Mode: Makefile.am; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
#
# Makefile.am
#
# Copyright (C) 2018 Rémi Cohen-Scali <remi@cohenscali.net>
# 
# sigmoid is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# sigmoid is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.

## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src po help tests

MOSTLYCLEANFILES = *~ \#* .\#* m4/*~ Makefile */Makefile
DISTCLEANFILES = configure config.log config.status Debug Makefile.in src/Makefile.in autom4te.cache

clean-local: clean-local-check

.PHONY: clean-local-check

clean-local-check: maintainer-clean mostlyclean
	-rm -rf .anjuta autom4te.cache sigmoid.anjuta
	-rm -rf .anjuta_sym_db.db Debug

