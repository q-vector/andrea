//
// tc.h
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

#ifndef DENISE_ANDREA_TC_H
#define DENISE_ANDREA_TC_H

#include <map>
#include <denise/geodesy.h>
#include <denise/tc.h>
#include <andrea/package.h>

using namespace std;
using namespace denise;

namespace andrea
{

   class Tc_Package : protected Package
   {

      protected:

         Jma_Best_Tracks
         jma_best_tracks;

         Tc_Track_Map
         tc_track_map;

         Tc_Package (Andrea& andrea);

         void
         tc_track_assign (const Dstring& identifier,
                          const Tokens& arguments);

         void
         tc_track_print (const Dstring& identifier) const;

         void
         tc_parse (const Tokens& tokens);

      public: 

         const Tc_Track_Map&
         get_tc_track_map () const;

         const Tc_Track&
         get_tc_track (const Dstring& identifier) const;

         void
         surface_tc_track (const Dstring& surface_identifier,
                           const Dstring& geodetic_transform_identifier,
                           const Dstring& tc_track_identifier);

   };

};

#endif /* DENISE_ANDREA_TC_H */
