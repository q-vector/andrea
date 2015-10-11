//
// indices.cc
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
#include "indices.h"

using namespace std;
using namespace denise;
using namespace andrea;

Indices_Package::Indices_Package (Andrea& andrea)
   : Package (andrea)
{
}

Indices_Package::~Indices_Package ()
{
}

void
Indices_Package::indices_fire_parse (const Dstring& index,
                                     const Tokens& arguments) const
{

   bool si = false;
   Real curing = 100;
   Real df = 10;

   Real t = GSL_NAN;
   Real rh = GSL_NAN;
   Real kph = GSL_NAN;

   Real td = GSL_NAN;
   Real speed = GSL_NAN;

   for (auto iterator = arguments.begin ();
        iterator != arguments.end (); iterator++)
   {

      const Tokens tokens (iterator->get_lower_case (), "=");
      if (tokens.size () < 2) { continue; }

      const Dstring& option = tokens[0];
      const Dstring& value = tokens[1];
      const bool yes = (value == "y" || value == "yes" ||
                        value == "t" || value == "true");

      if (option == "si") { si = yes; }

      if (option == "curing") { curing = stof (value); }
      if (option == "df") { df = stof (value); }

      if (option == "t") { t = stof (value); }
      if (option == "rh") { rh = stof (value); }
      if (option == "kph") { kph = stof (value); }

      if (option == "td") { td = stof (value); }
      if (option == "speed") { speed = stof (value); }

   }

   if (si) { t = t - K; td = td - denise::K; }
   if (gsl_isnan (t)) { t = t - denise::K; }
   if (gsl_isnan (rh)) { rh = Moisture::get_rh (t, td) * 100; }
   if (gsl_isnan (kph)) { kph = speed * 3.6; }

   const Real fdi = (index == "gfdi") ?
      Fire::get_gfdi (t, rh, kph, curing) :
      Fire::get_ffdi (t, rh, kph, df);

   cout << fdi << endl;

}

void
Indices_Package::indices_thermo_parse (const Dstring& index,
                                       const Tokens& arguments) const
{

   bool si = false;

   Real t = GSL_NAN;
   Real td = GSL_NAN;
   Real rh = GSL_NAN;
   Real p = GSL_NAN;

   for (auto iterator = arguments.begin ();
        iterator != arguments.end (); iterator++)
   {

      const Tokens tokens (iterator->get_lower_case (), "=");
      const Dstring& option = tokens[0];
      const Dstring& value = tokens[1];
      const bool yes = (value == "y" || value == "yes" ||
                        value == "t" || value == "true");

      if (option == "si") { si = yes; }

      if (option == "t") { t = stof (value); }
      if (option == "td") { td = stof (value); }
      if (option == "rh") { rh = stof (value); }
      if (option == "p") { p = stof (value); }

   }

   if (index == "dew_point" || index == "td")
   {
      if (!si) { t += K; rh *= 0.01; }
      const Real t_d = Moisture::get_t_d (t, rh);
      cout << (si ? t_d : t_d - K) << endl;
   }
   else
   if (index == "e")
   {
      if (si) { t -= K; p *= 0.01; }
      const bool p_specified = !gsl_isnan (p);
      const Real e = p_specified ?
         Moisture::get_e_s (td) : Moisture::get_e_s (td, p);
      cout << (si ? e : e * 0.01) << endl;
   }
   if (index == "e_s")
   {
      if (si) { t -= K; p *= 0.01; }
      const bool p_specified = !gsl_isnan (p);
      const Real e_s = p_specified ?
         Moisture::get_e_s (t, p) : Moisture::get_e_s (t);
      cout << (si ? e_s : e_s * 0.01) << endl;
   }
   else
   if (index == "q")
   {
      if (si) { td -= K; } else { p *= 100; }
      const Real q = Moisture::get_q_s (td, p);
      cout << (si ? q : q * 1000) << endl;
   }
   else
   if (index == "q_s")
   {
      if (si) { t -= K; } else { p *= 100; }
      const Real q_s = Moisture::get_q_s (t, p);
      cout << (si ? q_s : q_s * 1000) << endl;
   }
   else
   if (index == "r")
   {
      if (si) { td -= K; } else { p *= 100; }
      const Real r = Moisture::get_r_s (td, p);
      cout << (si ? r : r * 1000) << endl;
   }
   else
   if (index == "r_s")
   {
      if (si) { t -= K; } else { p *= 100; }
      const Real q_s = Moisture::get_r_s (t, p);
      cout << (si ? q_s : q_s * 1000) << endl;
   }
   else
   if (index == "rh")
   {
      if (si) { t -= K; td -= K; }
      const Real rh = Moisture::get_rh (t, td);
      cout << (si ? rh : rh * 100) << endl;
   }
   else
   if (index == "theta")
   {
      if (si) { t -= K; } else { p *= 100; }
      const Real theta = Thermo_Point::t_p (t, p).get_theta ();
      cout << (si ? theta + K : theta) << endl;
   }

}

void
Indices_Package::indices_parse (const Tokens& tokens) const
{

   const Integer n = tokens.size ();

   if (tokens[0] == "fire")
   {
      const Dstring& index = tokens[1];
      indices_fire_parse (tokens[1], tokens.subtokens (2));
   }
   else
   if (tokens[0] == "thermo")
   {
      const Dstring& index = tokens[1];
      indices_thermo_parse (tokens[1], tokens.subtokens (2));
   }

}

