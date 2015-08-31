AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)
lib_LTLIBRARIES = libandrea.la

pkginclude_HEADERS = andrea.h package.h geodesy.h geodetic_mesh.h \
   geodetic_transform.h gshhs.h journey.h sounding.h surface.h tc.h

libandrea_la_LDFLAGS = -release $(VERSION)
libandrea_la_SOURCES = andrea.cc package.cc geodesy.cc geodetic_mesh.cc \
   geodetic_transform.cc gshhs.cc journey.cc sounding.cc surface.cc tc.cc

