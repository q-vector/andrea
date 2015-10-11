//
// andrea.h
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

#ifndef DENISE_ANDREA_ANDREA_H
#define DENISE_ANDREA_ANDREA_H

#include <map>
#include <denise/dstring.h>
#include <andrea/package.h>
#include <andrea/geodesy.h>
#include <andrea/geodetic_mesh.h>
#include <andrea/geodetic_transform.h>
#include <andrea/gshhs.h>
#include <andrea/indices.h>
#include <andrea/journey.h>
#include <andrea/sounding.h>
#include <andrea/surface.h>
#include <andrea/tc.h>
#include <andrea/track.h>

using namespace std;
using namespace denise;

namespace andrea
{

   class Entity : public Dstring
   {

      public:

         Entity (const Dstring& str);

         Real
         value () const;

   };

   class Andrea : public Assignable,
                  public Geodesy_Package,
                  public Geodetic_Mesh_Package,
                  public Geodetic_Transform_Package,
                  public Gshhs_Package,
                  public Indices_Package,
                  public Journey_Package,
                  public Sounding_Package,
                  public Surface_Package,
                  public Tc_Package,
                  public Track_Package
   {

      private:

         map<Dstring, Dstring>
         data_path_map;

         Dstring
         prompt;

         void
         data_path (const Tokens& arguments);

         void
         wind_shear (const Tokens& arguments) const;

         void
         print (const Entity& entity) const;

      public:

         Andrea (const Dstring& prompt);

         const Dstring&
         get_data_path (const Dstring& identifier) const;

         virtual void
         parse (const Tokens& tokens);

         void
         loop ();

   };

};

#endif /* DENISE_ANDREA_ANDREA_H */

