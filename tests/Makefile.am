
GTEST_DIR = $(top_builddir)/googletest/googletest
GTEST_INCLUDE_DIR = $(GTEST_DIR)/include

SUBDIRS = ../googletest/googletest

bin_PROGRAMS = bookmarksam_tests

# Modifies compiler and linker flags for pthreads compatibility.
if HAVE_PTHREADS
  AM_CXXFLAGS = @PTHREAD_CFLAGS@ -DGTEST_HAS_PTHREAD=1
  AM_LIBS = @PTHREAD_LIBS@
else
  AM_CXXFLAGS = -DGTEST_HAS_PTHREAD=0
endif

bookmarksam_tests_SOURCES = \
	bookmarksam_tests_main.cc \
	dummy_test.cc
bookmarksam_tests_CXXFLAGS = -I$(GTEST_INCLUDE_DIR) $(AM_CXXFLAGS)
bookmarksam_tests_LDADD = ../googletest/googletest/make/gtest_main.a $(AM_LIBS)
#bookmarksam_tests_DEPENDENCIES = lib/libgtest.la

all-recusive:
	make -C $(SUBDIRS)/make all

.PHONY: all-recusive
