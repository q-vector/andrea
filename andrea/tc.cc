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

   const Dstring& source = arguments[0];

   if (source == "jma_best_tracks")
   {

      const Dstring& name = arguments[1];
      const auto tc_track_map_id_set = jma_best_tracks.get_id_set (name);

      for (auto iterator = tc_track_map_id_set.begin ();
           iterator != tc_track_map_id_set.end (); iterator++)
      {
         const Dstring& id = *(iterator);
         const Tc_Track& tc_track = jma_best_tracks.at (*(iterator));

         const Dstring& i = identifier + id;

         tc_track_map.insert (i, tc_track);
         cout << "assigning " << id << " " << tc_track.get_name () << " to " << i << endl;
      }

   }
   else
   if (source == "hko_best_tracks")
   {

      const Dstring& name = arguments[1];
      const auto tc_track_map_id_set = hko_best_tracks.get_id_set (name);

      for (auto iterator = tc_track_map_id_set.begin ();
           iterator != tc_track_map_id_set.end (); iterator++)
      {
         const Dstring& id = *(iterator);
         const Tc_Track& tc_track = hko_best_tracks.at (*(iterator));

         const Dstring& i = identifier + id;

         tc_track_map.insert (i, tc_track);
         cout << "assigning " << id << " " << tc_track.get_name () << " to " << i << endl;
      }

   }
   else
   {
      Tc_Track tc_track ("name");
      tc_track_map.insert (identifier, tc_track);
   }
}

void
Tc_Package::tc_track_print (const Dstring& identifier) const
{
   auto iterator = tc_track_map.find (identifier);
   const bool is_present = (iterator != tc_track_map.end ());
   if (is_present)
   {
      const Tc_Track& tc_track = tc_track_map.at (identifier);
      cout << tc_track << endl;
   }
}

void
Tc_Package::tc_track_surface (const Dstring& surface_identifier,
                              const Dstring& geodetic_transform_identifier,
                              const Tokens& arguments)
{

   const Dstring& tc_track_identifier = arguments[0];

   const RefPtr<Surface>& surface = andrea.get_surface (surface_identifier);
   const RefPtr<Context> cr = andrea.get_cr (surface_identifier);
   const Size_2D& size_2d = andrea.get_size_2d (surface_identifier);
   const Point_2D centre (Real (size_2d.i) / 2, Real (size_2d.j) / 2);

   const Geodetic_Transform* geodetic_transform_ptr =
      andrea.get_geodetic_transform_ptr (geodetic_transform_identifier, centre);
   const Geodetic_Transform& geodetic_transform = *geodetic_transform_ptr;

   const Tc_Track& tc_track = get_tc_track (tc_track_identifier);
   const set<Dtime> dtime_set = tc_track.get_dtime_set ();

   const Real start_tau = tc_track.get_start_tau ();
   const Real end_tau = tc_track.get_end_tau ();
   const Integer n = Integer (round (end_tau - start_tau));
   const Tuple tau_tuple (n, start_tau, end_tau);

   cr->set_line_width (2);
   cr->set_font_size (10);

   Tuple tau_24_tuple;

   for (auto iterator = tau_tuple.begin ();
        iterator != tau_tuple.end (); iterator++)
   {

      const Real tau = *(iterator);
      const Dtime& dtime = tc_track.get_dtime (tau);
      const bool is_24 = (dtime.get_hour () % 24 == 0);
      if (is_24) { tau_24_tuple.push_back (tau); continue; }

      const Lat_Long& lat_long = tc_track.get_lat_long (dtime);
      const Real max_wind = tc_track.get_datum ("max_wind", dtime);
      const Point_2D& point = geodetic_transform.transform (lat_long);
      const Real h = Domain_1D (100, 20).normalize (max_wind) * 0.5;
      const Real s = Domain_1D (20, 100).normalize (max_wind) * 0.5 + 0.4;
      const Real b = Domain_1D (20, 100).normalize (max_wind) * 0.4 + 0.6;

      const bool is_6 = (dtime.get_hour () % 6 == 0);
      const Real radius = is_6 ? 4 : 2;

      Ring (radius).cairo (cr, point);
      Color::hsb (h, s, b, 0.5).cairo (cr);
      cr->fill_preserve ();
      Color::hsb (h, s, b, 0.8).cairo (cr);
      cr->stroke ();

   }

   for (auto iterator = tau_24_tuple.begin ();
        iterator != tau_24_tuple.end (); iterator++)
   {

      const Real tau = *(iterator);
      const Dtime& dtime = tc_track.get_dtime (tau);

      const Lat_Long& lat_long = tc_track.get_lat_long (dtime);
      const Real max_wind = tc_track.get_datum ("max_wind", dtime);
      const Point_2D& point = geodetic_transform.transform (lat_long);
      const Real radius = 8;
      const Dstring& hh = Dstring::render ("%d", dtime.get_day ());
      const Real h = Domain_1D (100, 20).normalize (max_wind) * 0.5;
      const Real s = Domain_1D (20, 100).normalize (max_wind) * 0.5 + 0.4;
      const Real b = Domain_1D (20, 100).normalize (max_wind) * 0.4 + 0.6;

      Ring (radius).cairo (cr, point);
      Color::hsb (h, s, b, 0.5).cairo (cr);
      cr->fill_preserve ();
      Color::hsb (h, s, b, 0.8).cairo (cr);
      cr->stroke ();
      Color::hsb (h, s/2, b/4).cairo (cr);
      Label (hh, point, 'c', 'c').cairo (cr);

   }

   delete geodetic_transform_ptr;

}

void
Tc_Package::tc_parse (const Tokens& tokens)
{

   const Dstring& action = tokens[0].get_lower_case ();
   const Integer n = tokens.size ();

   if (action == "assign")
   {
      const Dstring& identifier = tokens[1];
      tc_track_assign (identifier, tokens.subtokens (2));
   }
   else
   if (action == "jma_best_tracks")
   {
      const Dstring& jma_best_tracks_action = tokens[1].get_lower_case ();
      if (jma_best_tracks_action == "ingest")
      {
         const Dstring& path = tokens[2];
         jma_best_tracks.ingest (path);
      }
   }
   else
   if (action == "hko_best_tracks")
   {
      const Dstring& hko_best_tracks_action = tokens[1].get_lower_case ();
      if (hko_best_tracks_action == "ingest")
      {
         const Dstring& path = tokens[2];
         hko_best_tracks.ingest (path);
      }
   }
   else
   if (tokens[0] == "surface")
   {
      const Dstring& surface_identifier = tokens[1];
      const Dstring& geometric_transform_identifier = tokens[2];
      tc_track_surface (surface_identifier, geometric_transform_identifier,
         tokens.subtokens (3));
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

