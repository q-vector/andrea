//
// geodesy.h
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

#ifndef DENISE_ANDREA_GEODESY_H
#define DENISE_ANDREA_GEODESY_H

#include <map>
#include <denise/geodesy.h>
#include <andrea/package.h>

using namespace std;
using namespace denise;

namespace andrea
{

   class Geodesy_Package : protected Package
   {

      protected:

         Integer
         lat_long_dp;

         map<Dstring, Geodesy>
         geodesy_map;

         Geodesy_Package (Andrea& andrea);

         void
         geodesy_assign (const Dstring& identifier,
                         const Dstring& str);

         void
         geodesy_print (const Dstring& identifier) const;

         void
         geodesy_distance (const Tokens& tokens) const;

         void
         geodesy_azimuth (const Tokens& tokens) const;

         void
         geodesy_destination (const Tokens& tokens) const;

         void
         geodesy_parse (const Tokens& tokens);

      public: 

         const map<Dstring, Geodesy>&
         get_geodesy_map () const;

         const Geodesy&
         get_geodesy (const Dstring& idenfifier) const;

   };

};

#endif /* DENISE_ANDREA_GEODESY_H */
