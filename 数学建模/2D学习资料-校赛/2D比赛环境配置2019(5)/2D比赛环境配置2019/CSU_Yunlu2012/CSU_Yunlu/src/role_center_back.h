// -*-c++-*-

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3, or (at your option)
 any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this code; see the file COPYING.  If not, write to
 the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifndef ROLE_CENTER_BACK_H
#define ROLE_CENTER_BACK_H

#include "soccer_role.h"

#include <rcsc/geom/vector_2d.h>

class RoleCenterBack
    : public SoccerRole {
private:

public:

    static const std::string NAME;

    RoleCenterBack()
      { }

    ~RoleCenterBack()
      { }

    virtual
    bool execute( rcsc::PlayerAgent * agent );


    static
    const
    std::string & name()
      {
          return NAME;
      }

    static
    SoccerRole::Ptr create()
      {
          SoccerRole::Ptr ptr( new RoleCenterBack() );
          return ptr;
      }

private:
    void doDefMidFieldMove(rcsc::PlayerAgent * agent);
    void doKick( rcsc::PlayerAgent * agent );
    void doMove( rcsc::PlayerAgent * agent );
    void doOffensiveMove(rcsc::PlayerAgent * agent);
    void doDefensiveMove(rcsc::PlayerAgent * agent);
    void doDribbleBlockMove(rcsc::PlayerAgent* agent);
    void doCrossAreaMove(rcsc::PlayerAgent * agent);

};

#endif
