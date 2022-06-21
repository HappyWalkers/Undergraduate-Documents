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
#ifndef ROLE_OFFENSIVE_HALS_MOVE_H
#define ROLE_OFFENSIVE_HALS_MOVE_H

#include <rcsc/geom/vector_2d.h>
#include <rcsc/player/soccer_action.h>

class roleoffensivehalfmove : public rcsc::SoccerBehavior
{
  /*private:
   const rcsc::Vector2D M_home_pos;
   const bool M_turn_at;
   const bool M_turn_neck;*/
public:
  roleoffensivehalfmove()
  {
  }

  void
  doOffensiveMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  void
  doDefMidMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  void
  doShootAreaMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);
  void
  doGoToCrossPoint( rcsc::PlayerAgent * agent,
                                       const rcsc::Vector2D & home_pos );
  bool
  doCheckCrossPoint( rcsc::PlayerAgent * agent );
  double
  getShootAreaMoveDashPower( rcsc::PlayerAgent * agent,
                                        const rcsc::Vector2D & target_point );
  rcsc::Vector2D
  getShootAreaMoveTarget( rcsc::PlayerAgent * agent,
                                           const rcsc::Vector2D & home_pos );
  //20140904 need to change
  void
  doDangerAreaMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  //20140904 need to change
  void
  doCrossBlockAreaMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  bool
  Bhv_Press(rcsc::PlayerAgent * agent);
  bool
  markCloseOpp(rcsc::PlayerAgent * agent);
  bool
  execute(rcsc::PlayerAgent * agent)
  {
    return false;
  }
};

#endif
