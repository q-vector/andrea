//
// journey.cc
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
#include "journey.h"

using namespace std;
using namespace denise;
using namespace andrea;

Journey_Package::Journey_Package (Andrea& andrea)
   : Package (andrea)
{
}

void
Journey_Package::journey_assign (const Dstring& identifier,
                                 const Dstring& journey_str)
{
   journey_map[identifier] = Journey (journey_str);
}

void
Journey_Package::journey_print (const Dstring& identifier,
                                const Dstring& action,
                                const Tokens& arguments) const
{

   for (auto iterator = arguments.begin ();
        iterator != arguments.end (); iterator++)
   {
   }

   const Journey& journey = journey_map.at (identifier);

   if (action == "nodes")
   {
      for (auto j = journey.begin (); j != journey.end (); j++)
      {
         const Lat_Long lat_long (*(j));
         cout << lat_long << endl;
      }
   }
   else
   if (action == "distance")
   {
      cout << journey.get_distance () << endl;
   }
   else
   if (action == "legs")
   {
      for (auto this_j = journey.begin (); this_j != journey.end (); this_j++)
      {

         auto next_j = this_j; next_j++;
         if (next_j == journey.end ()) { break; }

         const Lat_Long this_ll (*(this_j));
         const Lat_Long next_ll (*(next_j));
         const Journey::Simple sj (this_ll, next_ll);
         const Real distance = sj.get_distance ();
         const Real azimuth_f = sj.get_azimuth_forward ();
         const Real azimuth_b = sj.get_azimuth_backward ();
         cout << this_ll << " " << next_ll << " ";
         cout << distance << " " << azimuth_f << " " << azimuth_b << endl;
      }
   }
   else
   if (action == "breakup")
   {
      const Real distance = journey.get_distance ();
      const Real approx_d = stof (arguments[0]);
      const Integer n = Integer (round (distance / approx_d)) + 1;
      const Tuple tuple (n, 0, distance);
      for (auto iterator = tuple.begin (); iterator != tuple.end (); iterator++)
      {
         const Real x = *(iterator);
         const Lat_Long& lat_long = journey.get_lat_long (x);
         cout << lat_long << endl;
      }
   }

}

void
Journey_Package::journey_parse (const Tokens& tokens)
{

   const Integer n = tokens.size ();

   if (tokens[0] == "assign")
   {
      const Dstring& identifier = tokens[1];
      const Dstring& journey_str = tokens[2];
      journey_assign (identifier, journey_str);
   }
   else
   if (tokens[0] == "print")
   {
      const Dstring& identifier = tokens[1];
      const Dstring& action = tokens[2];
      journey_print (identifier, action, tokens.subtokens (3));
   }

}

const map<Dstring, Journey>&
Journey_Package::get_journey_map () const
{
   return journey_map;
}

const Journey&
Journey_Package::get_journey (const Dstring& identifier) const
{
   Exception e ("journey not found: " + identifier);
   try { return journey_map.at (identifier); }
   catch (const std::out_of_range& oor) { throw e; }
}

void
Journey_Package::surface_journey (const Dstring& surface_identifier,
                                  const Dstring& geodetic_transform_identifier,
                                  const Dstring& journey_identifier)
{

   const RefPtr<Surface>& surface = andrea.get_surface (surface_identifier);
   const RefPtr<Context> cr = andrea.get_cr (surface_identifier);
   const Size_2D& size_2d = andrea.get_size_2d (surface_identifier);
   const Point_2D centre (Real (size_2d.i) / 2, Real (size_2d.j) / 2);

   const Geodetic_Transform* geodetic_transform_ptr =
      andrea.get_geodetic_transform_ptr (geodetic_transform_identifier, centre);
   const Geodetic_Transform& geodetic_transform = *geodetic_transform_ptr;

   const Journey& journey = andrea.get_journey (journey_identifier);

   cr->save ();
   Color::black ().cairo (cr);
   journey.cairo (cr, geodetic_transform);
   cr->restore ();

   delete geodetic_transform_ptr;

}

