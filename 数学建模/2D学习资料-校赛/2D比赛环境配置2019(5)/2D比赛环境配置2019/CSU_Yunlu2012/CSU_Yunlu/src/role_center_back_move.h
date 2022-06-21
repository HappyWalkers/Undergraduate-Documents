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
#ifndef ROLE_CENTER_BACK_MOVE_H
#define ROLE_CENTER_BACK_MOVE_H

#include <rcsc/geom/vector_2d.h>
#include <rcsc/player/soccer_action.h>

class rolecenterbackmove : public rcsc::SoccerBehavior
{
  /*private:
   const rcsc::Vector2D M_home_pos;
   const bool M_turn_at;
   const bool M_turn_neck;*/
public:
  rolecenterbackmove()
  {
  }
  double
  get_dash_power(const rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  void
  doBasicMove(rcsc::PlayerAgent * agent,
              const rcsc::Vector2D & home_pos);

  rcsc::Vector2D
  getBasicMoveTarget(rcsc::PlayerAgent * agent,
                     const rcsc::Vector2D &
                     home_pos, double * dist_thr);

  // unique action for each area

  void
  doCrossBlockAreaMove(rcsc::PlayerAgent * agent,
      const rcsc::Vector2D & home_pos);

  void
  doStopperMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  void
  doDangerAreaMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  void
  doDefMidMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  rcsc::Vector2D
  getDefMidMoveTarget(rcsc::PlayerAgent * agent,
      const rcsc::Vector2D & home_pos);

  // support action

  void
  doMarkMove(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  bool
  markCloseOpp(rcsc::PlayerAgent * agent);

  bool
  doDangerGetBall(rcsc::PlayerAgent * agent, const rcsc::Vector2D & home_pos);

  void
  doGoToPoint(rcsc::PlayerAgent * agent, const rcsc::Vector2D & target_point,
      const double & dist_thr, const double & dash_power,
      const double & dir_thr);
  bool
  Bhv_BlockDribble(rcsc::PlayerAgent * agent);
  bool execute(rcsc::PlayerAgent * agent) {return false;}
//yily adds this
  void doOffensiveMove(rcsc::PlayerAgent * agent);
  void doDefensiveMove(rcsc::PlayerAgent * agent);
  void doDribbleBlockMove(rcsc::PlayerAgent* agent);
  void doCrossAreaMove(rcsc::PlayerAgent * agent);
};

#endif
