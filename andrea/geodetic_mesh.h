//
// geodetic_mesh.h
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

#ifndef DENISE_ANDREA_GEODETIC_MESH_H
#define DENISE_ANDREA_GEODETIC_MESH_H

#include <map>
#include <denise/geodesy.h>
#include <andrea/package.h>

using namespace std;
using namespace denise;

namespace andrea
{

   class Geodetic_Mesh_Package : public Package
   {

      protected:

         map<Dstring, Geodetic_Mesh>
         geodetic_mesh_map;

         Geodetic_Mesh_Package (Andrea& andrea);

         void
         geodetic_mesh_assign (const Dstring& identifier,
                               const Size_2D& size_2d,
                               const Domain_2D& domain_2d);

         void
         geodetic_mesh_add (const Dstring& identifier,
                            const Tokens& arguments);

         void
         geodetic_mesh_print (const Dstring& identifier,
                              const Tokens& arguments) const;

         void
         geodetic_mesh_parse (const Tokens& tokens);

      public:

         const map<Dstring, Geodetic_Mesh>&
         get_geodetic_mesh_map () const;

         const Geodetic_Mesh&
         get_geodetic_mesh (const Dstring& identifier) const;

         void
         surface_geodetic_mesh (const Dstring& surface_identifier,
                                const Dstring& geodetic_transform_identifier,
                                const Dstring& geodetic_mesh_identifier,
                                const Tokens& arguments);

   };

};

#endif /* DENISE_ANDREA_GEODETIC_MESH_H */
