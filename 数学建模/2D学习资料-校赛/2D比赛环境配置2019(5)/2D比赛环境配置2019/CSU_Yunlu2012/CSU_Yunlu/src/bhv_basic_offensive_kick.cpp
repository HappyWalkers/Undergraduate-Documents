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

#include "bhv_basic_offensive_kick.h"

#include <rcsc/action/body_advance_ball.h>
#include <rcsc/action/body_dribble.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/body_pass.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>
#include <rcsc/geom/rect_2d.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>
#include <rcsc/player/world_model.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/sector_2d.h>

using namespace rcsc;

/*-------------------------------------------------------------------*/
/*!

 */
bool
Bhv_BasicOffensiveKick::execute( PlayerAgent * agent )
{
    dlog.addText( Logger::TEAM,
                  __FILE__": Bhv_BasicOffensiveKick" );

    const WorldModel & wm = agent->world();

    const PlayerPtrCont & opps = wm.opponentsFromSelf();
    const PlayerObject * nearest_opp
        = ( opps.empty()
            ? static_cast< PlayerObject * >( 0 )
            : opps.front() );
    const double nearest_opp_dist = ( nearest_opp
                                      ? nearest_opp->distFromSelf()
                                      : 1000.0 );
    const Vector2D nearest_opp_pos = ( nearest_opp
                                       ? nearest_opp->pos()
                                       : Vector2D( -1000.0, 0.0 ) );

    Vector2D pass_point;

    if( wm.self().pos().x>32) return false;
    if ( Body_Pass::get_best_pass( wm, &pass_point, NULL, NULL ) )
    {
        if ( (wm.self().pos().x < 0.0 &&
        	pass_point.x > wm.self().pos().x -5.0)
        		||(wm.self().pos().x >= 0.0 &&
        	        	pass_point.x > wm.self().pos().x -14.0))
        {
            bool safety = true;
            const PlayerPtrCont::const_iterator opps_end = opps.end();
            for ( PlayerPtrCont::const_iterator it = opps.begin();
                  it != opps_end;
                  ++it )
            {
                if ( (*it)->pos().dist( pass_point ) < 3.0 )
	        {
                    safety = false;
                }//?????????????????????????????????????????????????
            }


            if ( nearest_opp_dist < 3.0&&safety)
              {
                  if ( Body_Pass().execute( agent ) )
                  {
                      dlog.addText( Logger::TEAM,
                                    __FILE__": (execute) do best pass" );
                      agent->debugClient().addMessage( "OffKickPass(2)" );
                      agent->setNeckAction( new Neck_TurnToLowConfTeammate() );

                      return true;
                  }
              }
            return false;


        }
        return false;



    }



    // opp is far from me

    return false;

}

//yily changes it 2013-6-2

bool
Bhv_BasicOffensiveKick::execute_side_cross( PlayerAgent * agent )
{
    dlog.addText( Logger::TEAM,
                  __FILE__": Bhv_BasicOffensiveKick" );

    const WorldModel & wm = agent->world();

    const PlayerPtrCont & opps = wm.opponentsFromSelf();
    const PlayerObject * nearest_opp
        = ( opps.empty()
            ? static_cast< PlayerObject * >( 0 )
            : opps.front() );
    const double nearest_opp_dist = ( nearest_opp
                                      ? nearest_opp->distFromSelf()
                                      : 1000.0 );
    const Vector2D nearest_opp_pos = ( nearest_opp
                                       ? nearest_opp->pos()
                                       : Vector2D( -1000.0, 0.0 ) );

    Vector2D pass_point;

    if( wm.self().pos().x>32 && fabs(wm.self().pos().y)<17) return false;
    if ( Body_Pass::get_best_pass( wm, &pass_point, NULL, NULL ) )
    {
        if ( (wm.self().pos().x < 0.0 &&
        	pass_point.x > wm.self().pos().x -5.0)
        		||(wm.self().pos().x >= 0.0 &&
        	        	pass_point.x > wm.self().pos().x -15.0))
        {
            bool safety = true;
            const PlayerPtrCont::const_iterator opps_end = opps.end();
            for ( PlayerPtrCont::const_iterator it = opps.begin();
                  it != opps_end;
                  ++it )
            {
                if ( (*it)->pos().dist( pass_point ) < 4.0 )
	        {
                    safety = false;
                }//?????????????????????????????????????????????????
            }


            if ( safety)
              {
                  if ( Body_Pass().execute( agent ) )
                  {
                      dlog.addText( Logger::TEAM,
                                    __FILE__": (execute) do best pass" );
                      agent->debugClient().addMessage( "OffKickPass(2)" );
                      agent->setNeckAction( new Neck_TurnToLowConfTeammate() );

                      return true;
                  }
              }
            return false;


        }
        return false;



    }



    // opp is far from me

    return false;

}

