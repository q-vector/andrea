AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)
lib_LTLIBRARIES = libandrea.la

pkginclude_HEADERS = andrea.h package.h geodesy.h geodetic_mesh.h \
   geodetic_transform.h gshhs.h indices.h journey.h sounding.h \
   surface.h tc.h track.h

libandrea_la_LDFLAGS = -release $(VERSION)
libandrea_la_SOURCES = andrea.cc package.cc geodesy.cc geodetic_mesh.cc \
   geodetic_transform.cc gshhs.cc indices.cc journey.cc sounding.cc \
   surface.cc tc.cc track.cc

