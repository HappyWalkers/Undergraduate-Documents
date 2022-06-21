// -*-c++-*-

/*!
  \file bhv_shoot2008.cpp
  \brief advanced shoot planning and behavior.
*/

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "bhv_shoot2008.h"

#include <rcsc/common/logger.h>
#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include "neck_turn_to_goalie_or_scan.h"

#include "body_smart_kick.h"

//#include <rcsc/action/obsolete/body_kick_multi_step.h>
#include <rcsc/common/server_param.h>

#include <rcsc/geom/vector_2d.h>
#include <rcsc/geom/triangle_2d.h>
#include <rcsc/geom/line_2d.h>

using namespace rcsc;

namespace rcsc {

ShootTable2008 Bhv_Shoot2008::S_shoot_table;

/*-------------------------------------------------------------------*/
/*!

*/
bool
Bhv_Shoot2008::execute_test( PlayerAgent * agent )
{
	M_shoot_check = get_best_shoot( agent , M_shoot_point );

	if( !M_shoot_check )
	{
		rcsc::dlog.addText( rcsc::Logger::ROLE,
				    "%s:%d: shoot is not suitable.",
				    __FILE__, __LINE__ );
		return false;
	}

//	if( !M_shoot_point.valid() )        //error: valid() is not the member of rcsc
//	{
//		rcsc::dlog.addText( rcsc::Logger::ROLE,
//				    "%s:%d: shoot is not suitable.",
//				    __FILE__, __LINE__ );
//		return false;
//	}


	if( M_shoot_point.absY() < 6.9 )
	{
	    std::cerr << __FILE__ << ": M_shoot_point.absY() < 6.9, shoot is not suitable.?.?.? \n";
		rcsc::dlog.addText( rcsc::Logger::ROLE,
				    "%s:%d: shoot is not suitable.",
				    __FILE__, __LINE__ );
		return false;
	}


//	#ifdef USE_SMART_KICK
		rcsc::Body_SmartKick( M_shoot_point,
				      ServerParam::i().ballSpeedMax(),
				      ServerParam::i().ballSpeedMax() * 0.96,
				      3 ).execute( agent );
//	#else
//		rcsc::Body_KickMultiStep( M_shoot_point , ServerParam::i().ballSpeedMax() ).execute( agent );
//	#endif

	agent->setNeckAction( new Neck_TurnToGoalieOrScan( -1 ) );

	rcsc::dlog.addText( rcsc::Logger::ROLE,
			    "%s:%d: shoot action.",
			    __FILE__, __LINE__ );

//	if ( one_step_speed > first_speed * 0.99 )
//    {
//        if ( Body_SmartKick( target_point,
//                             one_step_speed,
//                             one_step_speed * 0.99 - 0.0001,
//                             1 ).execute( agent ) )
//        {
//             agent->setNeckAction( new Neck_TurnToGoalieOrScan( -1 ) );
//             agent->debugClient().addMessage( "Force1Step" );
//             return true;
//        }
//    }
//
//    if ( Body_SmartKick( target_point,
//                         first_speed,
//                         first_speed * 0.99,
//                         3 ).execute( agent ) )
//    {
//        agent->setNeckAction( new Neck_TurnToGoalieOrScan( -1 ) );
//        return true;
//    }

	return false;
}



/*!

*/
bool
Bhv_Shoot2008::execute( PlayerAgent * agent )
{
    if ( ! agent->world().self().isKickable() )
    {
        std::cerr << __FILE__ << ": " << __LINE__
                  << " not ball kickable!"
                  << std::endl;
        dlog.addText( Logger::ACTION,
                      __FILE__":  not kickable" );
        return false;
    }
    else if ( agent->world().existKickableOpponent() )
    {
        std::cerr << __FILE__ << ": " << __LINE__
                  << " Do not shoot at opp!"
                  << std::endl;
        dlog.addText( Logger::ACTION,
                      __FILE__":  not kickable" );
        return false;
    }
    //yily change
   const ShootTable2008::ShotCont & shots = S_shoot_table.getShots( agent );

    ShootTable2008::ShotCont::const_iterator shot
        = std::min_element( shots.begin(),
                            shots.end(),
                            ShootTable2008::ScoreCmp() );
    //update
   if ( shots.empty()||shot == shots.end() )
    {
      dlog.addText( Logger::SHOOT,
                    __FILE__": no shoot route or no best shot" );

        const ShootTable2008::ShotCont & shots = S_shoot_table.getShots2( agent );
        ShootTable2008::ShotCont::const_iterator shot
             = std::min_element( shots.begin(),
                                 shots.end(),
                                 ShootTable2008::ScoreCmp() );
        if ( shots.empty()||shot == shots.end() )
        {
            dlog.addText( Logger::SHOOT,
                          __FILE__": no shoot route" );
            return false;
        }
    }


    // it is necessary to evaluate shoot courses

    Vector2D target_point = shot->point_;
    double first_speed = shot->speed_;

    agent->debugClient().addMessage( "Shoot" );
    agent->debugClient().setTarget( target_point );

    Vector2D one_step_vel
        = KickTable::calc_max_velocity( ( target_point - agent->world().ball().pos() ).th(),
                                        agent->world().self().kickRate(),
                                        agent->world().ball().vel() );
    double one_step_speed = one_step_vel.r();

    dlog.addText( Logger::SHOOT,
                  __FILE__": shoot to (%.2f, %.2f) speed=%f one_kick_max_speed=%f",
                  target_point.x, target_point.y,
                  first_speed,
                  one_step_speed );

    if ( one_step_speed > first_speed * 0.99 )
    {
        if ( Body_SmartKick( target_point,
                             one_step_speed,
                             one_step_speed * 0.99 - 0.0001,
                             1 ).execute( agent ) )
        {
             agent->setNeckAction( new Neck_TurnToGoalieOrScan( -1 ) );
             agent->debugClient().addMessage( "Force1Step" );
             return true;
        }
    }

    if ( Body_SmartKick( target_point,
                         first_speed,
                         first_speed * 0.99,
                         3 ).execute( agent ) )
    {
        agent->setNeckAction( new Neck_TurnToGoalieOrScan( -1 ) );
        return true;
    }

    dlog.addText( Logger::SHOOT,
                  __FILE__": failed" );
    return false;
}

}

/*-------------------------------------------------------------------*/

/*!
	\return best shoot point.
*/
bool
Bhv_Shoot2008::get_best_shoot( PlayerAgent * agent , Vector2D& point_ )
{

	const WorldModel & wm = agent->world();
	Vector2D posAgent = wm.self().pos();

	if( posAgent.dist( Vector2D( 52.5 , 0.0 ) )  > 18.0 && posAgent.absY() < 10.0 &&
	    agent->world().gameMode().isPenaltyKickMode() )
	{
		rcsc::dlog.addText( rcsc::Logger::ROLE,
				    "%s:%d: this place is far to goal."
				    ,__FILE__, __LINE__ );
		point_ = rcsc::Vector2D::INVALIDATED;
		return false;
	}
	else if( posAgent.dist( Vector2D( 52.5 , 0.0 ) )  > 16.0 &&
	         agent->world().gameMode().isPenaltyKickMode() )
	{
		rcsc::dlog.addText( rcsc::Logger::ROLE,
				    "%s:%d: this place is far to goal."
				    ,__FILE__, __LINE__ );
		point_ = rcsc::Vector2D::INVALIDATED;
		return false;
	}

	const PlayerObject * opp_goalie = wm.getOpponentGoalie();

	if( opp_goalie && posAgent.x > 50.0 && opp_goalie->pos().x > 50.0 )
	{
		rcsc::dlog.addText( rcsc::Logger::ROLE,
				    "%s:%d: this place is far to goal."
				    ,__FILE__, __LINE__ );
		point_ = rcsc::Vector2D::INVALIDATED;
		return false;
	}

	Triangle2D triangle_goal_[4] = { Triangle2D( posAgent , Vector2D( 52.5 , 7.0 ) , Vector2D( 52.5 , 3.5 ) ),
	                                 Triangle2D( posAgent , Vector2D( 52.5 , 3.5 ) , Vector2D( 52.5 , 0.0 ) ),
	                                 Triangle2D( posAgent , Vector2D( 52.5 , 0.0 ) , Vector2D( 52.5 ,-3.5 ) ),
	                                 Triangle2D( posAgent , Vector2D( 52.5 ,-3.5 ) , Vector2D( 52.5 ,-7.0 ) ) };

	int  i = 0;//counter
	bool bShoot = false;
	int max_p = 0;
	Vector2D * shoot_point = new Vector2D [4];

	for( i = 0 ; i < 4 ; i ++ )
	{
		shoot_point[i] = ( triangle_goal_[i].b() + triangle_goal_[i].c() ) / 2.0 ;
	}

	int * point = new int [4];
	point[0] = 0 , point[1] = 0 , point[2] = 0 , point[3] = 0;

	for( i = 0 ; i < 4 ; i ++ )
	{
		if( !opp_goalie )
		{
			bShoot = true;
			break;
		}
		else if( !triangle_goal_[i].contains( opp_goalie->pos() ) )
		{
			bShoot = true;
			break;
		}
		else
		{
			bShoot = false;
			continue;
		}
	}


	if( !opp_goalie )
	{
		rcsc::dlog.addText( rcsc::Logger::ROLE,
				    "%s:%d: shoot refused."
				    ,__FILE__, __LINE__ );
		point_ = rcsc::Vector2D( 52.5 , 0.0 );
		delete [] shoot_point;
		delete [] point;
		return true;
	}

	Vector2D opp_goalie_pos = opp_goalie->pos();

	Vector2D * intersection = new Vector2D[4];

	for( i = 0 ; i < 4 ; i ++ )
	{
		Line2D opp_goalie_line ( opp_goalie_pos , opp_goalie_pos + Vector2D( 0.0 , 1.0 ) );
		Line2D shoot_point_line( posAgent , shoot_point[i] );
		intersection[i] = Line2D::intersection( opp_goalie_line , shoot_point_line );
	}

	for( i = 0 ; i < 4 ; i ++ )
	{
		if( opp_goalie )
		{
			int time_to_score_goal  = int( posAgent.dist ( intersection[i] ) /
						rcsc::ServerParam::i().ballSpeedMax() );
			int time_to_goalie_move = int( ( opp_goalie_pos.dist( intersection[i] ) - 1.0 )/
						rcsc::ServerParam::i().defaultPlayerSpeedMax() );

			if( time_to_score_goal < time_to_goalie_move + 2 )
			{
				bShoot = true;
				break;
			}
			else
			{
				bShoot = false;
			}
		}
		else
		{
			bShoot = true;
			break;
		}
	}

	if( !bShoot )
	{
		rcsc::dlog.addText( rcsc::Logger::ROLE,
				    "%s:%d: shoot refused."
				    ,__FILE__, __LINE__ );
		point_ = rcsc::Vector2D::INVALIDATED;
		delete [] shoot_point;
		delete [] point;
		delete [] intersection;
		return false;
	}

	//
	// far_side_checker
	//
	int M_side = 0;
	if( posAgent.y > 0 )
		M_side = 3;

	if( !wm.existOpponentIn(triangle_goal_[M_side] , 10 , true ) )
		point[M_side] += 50;

	if( !triangle_goal_[M_side].contains( opp_goalie->pos() ) )
		point[M_side] += 50;

	//
	// predict catch the ball or not
	//
	for( i = 0 ; i < 4 ; i ++ )
	{
		if( opp_goalie )
		{
			int time_to_score_goal  = int( posAgent.dist ( intersection[i] ) /
						rcsc::ServerParam::i().ballSpeedMax() );
			int time_to_goalie_move = int( ( opp_goalie_pos.dist( intersection[i] )  - 1.0 )/
						rcsc::ServerParam::i().defaultPlayerSpeedMax() );

			if( time_to_score_goal < time_to_goalie_move + 2 )
			{
				point[i] += 100;
			}
		}
	}

	//
	// far_side_opp_goalie
	//

	int G_side = 0;
	if( posAgent.y > 0 )
		G_side = 3;

	if( !wm.existOpponentIn(triangle_goal_[M_side] , 10 , true ) )
		point[M_side] += 50;

	if( !triangle_goal_[G_side].contains( opp_goalie->pos() ) )
		point[G_side] += 50;

	//
	// far_side_near_opp_pos
	//

	const PlayerObject * opp_nearest = wm.getOpponentNearestToSelf( 10 );

	if( !opp_nearest )
	{
		for( i = 0 ; i < 4 ; i ++ )
		{
			if( shoot_point[i].dist( posAgent ) > 10 )
			{
				point[i] += 30;
			}
			else if( shoot_point[i].dist( posAgent ) > 7 )
			{
				point[i] += 20;
			}
			else if( shoot_point[i].dist( posAgent ) > 4 )
			{
				point[i] += 10;
			}
		}
	}
	else
	{
		Vector2D opp_nearest_pos = opp_nearest->pos();
		for( i = 0 ; i < 4 ; i ++ )
		{
			if( !wm.existOpponentIn( triangle_goal_[i] , 10 , false ) )
			{
 				if ( shoot_point[i].dist( opp_nearest_pos ) > 10 )
				{
					point[i] += 40;
				}
				else if( shoot_point[i].dist( opp_nearest_pos ) > 7 )
				{
					point[i] += 25;
				}
				else if( shoot_point[i].dist( opp_nearest_pos ) > 4 )
				{
					point[i] += 12;
				}
			}
			else
				continue;
		}
	}

	//
	// pointing and returning
	//


	for( i = 0 ; i < 4 ; i ++ )
		if( point[i] > point[max_p] )
			max_p = i;

	rcsc::dlog.addText( rcsc::Logger::ROLE,
			    "%s:%d: return shoot point.",
			    __FILE__, __LINE__ );
	point_ = shoot_point[max_p];
	delete [] shoot_point;
	delete [] point;
	delete [] intersection;
	return true;
}
