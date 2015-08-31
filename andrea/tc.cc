//
// tc.cc
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

#include "andrea.h"
#include "tc.h"

using namespace std;
using namespace denise;
using namespace andrea;

Tc_Package::Tc_Package (Andrea& andrea)
   : Package (andrea)
{
}

void
Tc_Package::tc_track_assign (const Dstring& identifier,
                             const Tokens& arguments)
{

   Tc_Track tc_track ("name");

/*
   for (auto iterator = arguments.begin ();
        iterator != arguments.end (); iterator++)
   {
      const Lat_Long lat_long (*(iterator));
      journey.push_back (lat_long);
   }
*/

   tc_track_map.insert (identifier, tc_track);

}

void
Tc_Package::tc_track_print (const Dstring& identifier) const
{
   auto iterator = tc_track_map.find (identifier);
   const bool is_present = (iterator != tc_track_map.end ());
   if (is_present)
   {
      cout << "tc_track " << identifier << " is present" << endl;
   }
}

void
Tc_Package::tc_parse (const Tokens& tokens)
{

   const Integer n = tokens.size ();

   if (tokens[0] == "assign")
   {
      const Dstring& identifier = tokens[1];
      tc_track_assign (identifier, tokens.subtokens (2));
   }
   else
   if (tokens[0] == "print")
   {
      const Dstring& identifier = tokens[1];
      tc_track_print (identifier);
   }

}

const Tc_Track_Map&
Tc_Package::get_tc_track_map () const
{
   return tc_track_map;
}

const Tc_Track&
Tc_Package::get_tc_track (const Dstring& identifier) const
{
   Exception e ("tc_track not found: " + identifier);
   try { return tc_track_map.at (identifier); }
   catch (const std::out_of_range& oor) { throw e; }
}

void
Tc_Package::surface_tc_track (const Dstring& surface_identifier,
                              const Dstring& geodetic_transform_identifier,
                              const Dstring& tc_track_identifier)
{

   const RefPtr<Surface>& surface = andrea.get_surface (surface_identifier);
   const RefPtr<Context> cr = andrea.get_cr (surface_identifier);
   const Size_2D& size_2d = andrea.get_size_2d (surface_identifier);
   const Point_2D centre (Real (size_2d.i) / 2, Real (size_2d.j) / 2);

   const Geodetic_Transform* geodetic_transform_ptr =
      andrea.get_geodetic_transform_ptr (geodetic_transform_identifier, centre);
   const Geodetic_Transform& geodetic_transform = *geodetic_transform_ptr;

   const Tc_Track& tc_track = andrea.get_tc_track (tc_track_identifier);

/*
   cr->save ();
   Color::black ().cairo (cr);
   tc_track.cairo (cr, geodetic_transform);
   cr->restore ();
*/

   delete geodetic_transform_ptr;

}

