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
#ifndef ROLE_SIDE_BACK_MOVE_H
#define ROLE_SIDE_BACK_MOVE_H

#include <rcsc/geom/vector_2d.h>
#include <rcsc/player/soccer_action.h>

class rolesidebackmove : public rcsc::SoccerBehavior
{
  /*private:
   const rcsc::Vector2D M_home_pos;
   const bool M_turn_at;
   const bool M_turn_neck;*/
public:
  rolesidebackmove()
  {
  }
  void
 doBasicMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  void
  doDribbleBlockAreaMove(rcsc::PlayerAgent * agent,const rcsc::Vector2D & home_pos);

  void
  doDefensiveMove(rcsc::PlayerAgent * agent);

  bool
  Bhv_BlockDribble(rcsc::PlayerAgent * agent);
  void
  doDefMidAreaMove(rcsc::PlayerAgent * agent,const rcsc::Vector2D & home_pos);
  void
  doDangerAreaMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);
  void
  Bhv_GetBall(rcsc::PlayerAgent * agent);
  rcsc::Vector2D
  getBasicMoveTarget(rcsc::PlayerAgent * agent,
      const rcsc::Vector2D & home_pos);
  bool
  doBlockPassLine(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);
  void
  doCrossBlockAreaMove(rcsc::PlayerAgent * agent,
      const rcsc::Vector2D & home_pos);
  void
  doBlockSideAttacker(rcsc::PlayerAgent * agent,
      const rcsc::Vector2D & home_pos);
  bool
  execute(rcsc::PlayerAgent * agent)
  {
    return false;
  }
};

#endif
