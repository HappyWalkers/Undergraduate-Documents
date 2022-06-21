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
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "role_defensive_half.h"
#include "role_defensive_half_move.h"
#include "role_center_forward.h"
#include "bhv_basic_tackle.h"
#include "role_side_back.h"
#include "strategy.h"
#include "bhv_dangerAreaTackle.h"
#include <rcsc/geom.h>
#include <rcsc/geom/ray_2d.h>
#include "bhv_chain_action.h"
#include "bhv_basic_offensive_kick.h"
#include "bhv_basic_move.h"
#include <rcsc/action/body_intercept.h>
#include <rcsc/action/body_intercept2009.h>
#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>
#include <rcsc/formation/formation_static.h>
#include <rcsc/formation/formation_dt.h>
#include <rcsc/common/logger.h>
#include <rcsc/player/intercept_table.h>
#include <rcsc/common/server_param.h>
#include <role_side_back_move.h>
#include <rcsc/action/basic_actions.h>
#include <rcsc/action/bhv_go_to_point_look_ball.h>
#include <rcsc/action/bhv_scan_field.h>
#include <rcsc/action/body_go_to_point.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_ball_or_scan.h>
#include <rcsc/action/neck_turn_to_player_or_scan.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>
#include <iostream>
using namespace std;
using namespace rcsc;

const std::string RoleDefensiveHalf::NAME("DefensiveHalf");

/*-------------------------------------------------------------------*/
/*!

 */
namespace
{
  rcss::RegHolder role = SoccerRole::creators().autoReg(
      &RoleDefensiveHalf::create, RoleDefensiveHalf::NAME);
}

/*-------------------------------------------------------------------*/
/*!

 */
bool
RoleDefensiveHalf::execute(PlayerAgent * agent)
{
  bool kickable = agent->world().self().isKickable();
  if (agent->world().existKickableTeammate()
      && agent->world().teammatesFromBall().front()->distFromBall()
          < agent->world().ball().distFromSelf())
  {
    kickable = false;
  }

  if (kickable)
  {
    doKick(agent);
  }
  else
  {
    doMove(agent);
  }

  return true;
}

/*-------------------------------------------------------------------*/
/*!

 */
void
RoleDefensiveHalf::doKick(PlayerAgent * agent)
{
	if ( Bhv_ChainAction().execute( agent ) )
	    {
	        dlog.addText( Logger::TEAM,
	                      __FILE__": (execute) do chain action" );
	        agent->debugClient().addMessage( "ChainAction" );
	        return;
	    }
	 Bhv_BasicOffensiveKick().execute( agent );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
RoleDefensiveHalf::doMove(PlayerAgent * agent)
{
  Vector2D ballPos = agent->world().ball().pos();
  const WorldModel & wm = agent->world();
  Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());

  if (!home_pos.isValid())
    home_pos.assign(0.0, 0.0);
//  cout<<"DEFENSIVEHALF!!!!!!!"<<endl;
  switch (Strategy::get_ball_area(ballPos))
  {
  case Strategy::BA_CrossBlock:
    roledefensivehalfmove().doCrossBlockMove(agent);
    break;
  case Strategy::BA_Danger:
    //need to change
    roledefensivehalfmove().doDangerAreaMove(agent);//doCrossBlockMove(agent);
    break;
  case Strategy::BA_DribbleBlock:
    roledefensivehalfmove().doDribbleBlockMove(agent);
    break;
  case Strategy::BA_DefMidField:
//      cout<<"BA_DefMidField"<<endl;
    roledefensivehalfmove().doDefensiveMove(agent);
    break;
  case Strategy::BA_DribbleAttack:
    Bhv_BasicMove().execute(agent);
    break;
  case Strategy::BA_OffMidField:
    roledefensivehalfmove().doOffensiveMove(agent);
    break;
  case Strategy::BA_Cross:
    roledefensivehalfmove().doCrossAreaMove(agent);
    break;
  case Strategy::BA_ShootChance:
    roledefensivehalfmove().doShootChanceMove(agent);   //new: 20140929 07:49
//    Bhv_BasicMove().execute(agent);
    break;
  default:
    //cout << "default" << endl;
    Bhv_BasicMove().execute(agent);
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
    break;
  }

}
