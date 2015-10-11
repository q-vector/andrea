//
// track.cc
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
#include "track.h"

using namespace std;
using namespace denise;
using namespace andrea;

Track_Package::Track_Package (Andrea& andrea)
   : Package (andrea)
{
}

void
Track_Package::track_ingest (const Dstring& file_path)
{
   igzstream file (file_path);
   track_map.ingest (file);
   file.close ();
}

void
Track_Package::track_print (const Dstring& identifier,
                            const Tokens& arguments) const
{

   const Track& track = track_map.at (identifier);
   const set<Dtime>& dtime_set = track.get_dtime_set ();

   for (auto iterator = dtime_set.begin ();
        iterator != dtime_set.end (); iterator++)
   {

      const Dtime& dtime = *(iterator);
      const Dstring& time_str = dtime.get_string ("%Y%m%d%H%M%S");
      const Lat_Long& ll = track.get_lat_long (dtime);
      const Motion& motion = track.get_motion (dtime);
      const Real direction = motion.get_direction ();
      const Real speed = motion.get_speed ();

      cout << time_str << " " << ll << " " << direction << " "
           << speed << " ";
      for (auto iterator_e = track.begin ();
           iterator_e != track.end (); iterator_e++)
      {
         const Dstring& e = iterator_e->first;
         if (e == "latitude" || e == "longitude") { continue; }
         const Real datum = track.get_datum (e, dtime);
         cout << e << ":" << datum << " ";
      }

      cout << endl;

   }

}

void
Track_Package::track_surface (const Dstring& surface_identifier,
                              const Dstring& geodetic_transform_identifier,
                              const Dstring& track_identifier,
                              const Tokens& arguments)
{

   Symbol symbol;
   Color color = Color::black ();
   Real interval = 3600;
   Real line_width = 0.5;
   bool fill = false;
   Dstring encode = "";

   for (auto iterator = arguments.begin ();
        iterator != arguments.end (); iterator++)
   {

      const Tokens tokens (iterator->get_lower_case (), "=");
      if (tokens.size () < 2) { continue; }

      const Dstring& option = tokens[0];
      const Dstring& value = tokens[1];
      const bool yes = (value == "y" || value == "yes" ||
                        value == "t" || value == "true");

      if (option == "color") { color = Color (value); }
      if (option == "interval") { interval = stof (value); }
      if (option == "symbol") { symbol = Symbol::instance (value); }
      if (option == "line_width") { line_width = stof (value); }
      if (option == "fill") { fill = yes; }
      if (option == "encode") { encode = value; }
   }

   const bool no_symbol = (((const Polygon&)symbol).size () == 0);

   const RefPtr<Surface>& surface = andrea.get_surface (surface_identifier);
   const RefPtr<Context> cr = andrea.get_cr (surface_identifier);
   const Size_2D& size_2d = andrea.get_size_2d (surface_identifier);
   const Point_2D centre (Real (size_2d.i) / 2, Real (size_2d.j) / 2);

   const Geodetic_Transform* geodetic_transform_ptr =
      andrea.get_geodetic_transform_ptr (geodetic_transform_identifier, centre);
   const Geodetic_Transform& geodetic_transform = *geodetic_transform_ptr;

   const Track& track = get_track (track_identifier);
   const set<Dtime> dtime_set = track.get_dtime_set ();

   const Real start_tau = track.get_start_tau ();
   const Real end_tau = track.get_end_tau ();
   const Integer n = Integer (round ((end_tau - start_tau) * 3600 / interval)) + 1;
   const Tuple tau_tuple (n, start_tau, end_tau);

   cr->set_font_size (10);
   cr->set_line_width (line_width);
   color.cairo (cr);

   for (auto iterator = tau_tuple.begin ();
        iterator != tau_tuple.end (); iterator++)
   {

      const Real tau = *(iterator);
      const Dtime& dtime = track.get_dtime (tau);

      const Lat_Long& lat_long = track.get_lat_long (dtime);
      const Motion& motion = track.get_motion (dtime);
      //const Real z = track.get_datum ("z", dtime);

      const Point_2D& point = geodetic_transform.transform (lat_long);

      if (no_symbol)
      {
         Dstring str (track_identifier);
         if (encode != "")
         {
                 if (encode == "dd")   { str = dtime.get_string ("%d");   }
            else if (encode == "ddhh") { str = dtime.get_string ("%d%H"); }
            else if (encode == "hh")   { str = dtime.get_string ("%H");   }
            else if (encode == "hhmm") { str = dtime.get_string ("%H%M"); }
            else
            {
               str = Dstring::render ("%.0f", track.get_datum (encode, dtime));
            }
         }
         Label (str, point, 'c', 'c').cairo (cr);
      }
      else { symbol.cairo (cr, point); }

      if (fill) { cr-> fill (); } else { cr->stroke (); }

   }

   delete geodetic_transform_ptr;

}

void
Track_Package::track_parse (const Tokens& tokens)
{

   const Dstring& action = tokens[0].get_lower_case ();
   const Integer n = tokens.size ();

   if (tokens[0] == "ingest")
   {
      const Dstring& file_path = tokens[1];
      track_ingest (file_path);
   }
   else
   if (tokens[0] == "surface")
   {
      const Dstring& surface_identifier = tokens[1];
      const Dstring& geometric_transform_identifier = tokens[2];
      const Dstring& track_identifier = tokens[3];
      track_surface (surface_identifier, geometric_transform_identifier,
         track_identifier, tokens.subtokens (4));
   }
   else
   if (tokens[0] == "print")
   {
      const Dstring& identifier = tokens[1];
      track_print (identifier, tokens.subtokens (2));
   }

}

const Track::Map&
Track_Package::get_track_map () const
{
   return track_map;
}

const Track&
Track_Package::get_track (const Dstring& identifier) const
{
   Exception e ("track not found: " + identifier);
   try { return track_map.at (identifier); }
   catch (const std::out_of_range& oor) { throw e; }
}

