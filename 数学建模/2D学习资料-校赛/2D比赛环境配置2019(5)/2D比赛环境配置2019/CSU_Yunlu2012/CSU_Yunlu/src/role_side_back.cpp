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
#include "bhv_basic_tackle.h"
#include "role_side_back.h"
#include "strategy.h"
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
#include "role_defensive_half_move.h"
#include "role_offensive_half_move.h"
using namespace rcsc;

const std::string RoleSideBack::NAME("SideBack");

/*-------------------------------------------------------------------*/
/*!

 */
namespace
{
  rcss::RegHolder role = SoccerRole::creators().autoReg(&RoleSideBack::create,
      RoleSideBack::NAME);
}

/*-------------------------------------------------------------------*/
/*!

 */
bool
RoleSideBack::execute(PlayerAgent * agent)
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
RoleSideBack::doKick(PlayerAgent * agent)
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
RoleSideBack::doMove(rcsc::PlayerAgent * agent)
{
  Vector2D ballPos = agent->world().ball().pos();
  const WorldModel & wm = agent->world();
  Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());
  switch (Strategy::get_ball_area(agent->world().ball().pos()))
  {
  case Strategy::BA_DribbleBlock://2014-08-26
	rolesidebackmove().doDribbleBlockAreaMove(agent,home_pos);
    break;
  case Strategy::BA_CrossBlock:
    rolesidebackmove().doCrossBlockAreaMove(agent,home_pos);
    break;
  case Strategy::BA_DefMidField:
    rolesidebackmove().doDefensiveMove(agent);  //ht: 20140831 09:54
//    roledefensivehalfmove().doDefensiveMove(agent);
    break;
  case Strategy::BA_Danger:
    rolesidebackmove().doDangerAreaMove(agent,home_pos);
    break;
  default:
    Bhv_BasicMove().execute(agent);
    break;
  }
  Bhv_BasicMove().execute(agent);
}
