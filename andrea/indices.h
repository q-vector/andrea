//
// indices.h
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

#ifndef DENISE_ANDREA_INDICES_H
#define DENISE_ANDREA_INDICES_H

#include <map>
#include <denise/met.h>
#include <andrea/package.h>

using namespace std;
using namespace denise;

namespace andrea
{

   class Indices_Package : public Package
   {

      protected:

         Indices_Package (Andrea& andrea);

         ~Indices_Package ();

         void
         indices_fire_parse (const Dstring& index,
                             const Tokens& arguments) const;

         void
         indices_thermo_parse (const Dstring& index,
                               const Tokens& arguments) const;

         void
         indices_parse (const Tokens& tokens) const;

      public:

   };

};

#endif /* DENISE_ANDREA_INDICES_H */
