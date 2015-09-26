//
// track.h
// 
// Copyright (C) 2005-2015 Simon E. Ching
// 
// This file is part of the denise suite.
//
// libdenise is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libdenise is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libdenise.  If not, see <http://www.gnu.org/licenses/>.

#ifndef DENISE_ANDREA_TRACK_H
#define DENISE_ANDREA_TRACK_H

#include <map>
#include <denise/geodesy.h>
#include <andrea/package.h>

using namespace std;
using namespace denise;

namespace andrea
{

   class Track_Package : protected Package
   {

      protected:

         Track::Map
         track_map;

         Track_Package (Andrea& andrea);

         void
         track_ingest (const Dstring& file_path);

         void
         track_print (const Dstring& identifier,
                      const Tokens& arguments) const;

         void
         track_surface (const Dstring& surface_identifier,
                        const Dstring& geodetic_transform_identifier,
                        const Dstring& track_identifier,
                        const Tokens& arguments);

         void
         track_parse (const Tokens& tokens);

      public: 

         const Track::Map&
         get_track_map () const;

         const Track&
         get_track (const Dstring& identifier) const;

   };

};

#endif /* DENISE_ANDREA_TRACK_H */
