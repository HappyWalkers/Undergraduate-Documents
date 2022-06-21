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

#include "bhv_basic_move.h"

#include "strategy.h"

#include "bhv_basic_tackle.h"
#include "role_center_back_move.h"
#include <rcsc/action/basic_actions.h>
#include <rcsc/action/body_go_to_point.h>
#include <rcsc/action/body_intercept.h>
#include <rcsc/action/neck_turn_to_ball_or_scan.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>
#include <rcsc/player/intercept_table.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>

#include "neck_offensive_intercept_neck.h"

using namespace rcsc;

/*-------------------------------------------------------------------*/
/*!

 */
bool
Bhv_BasicMove::execute( PlayerAgent * agent )
{
    dlog.addText( Logger::TEAM,
                  __FILE__": Bhv_BasicMove" );

    //-----------------------------------------------
    // tackle
    if ( Bhv_BasicTackle( 0.8, 80.0 ).execute( agent ) )
    {
        #ifdef DEBUG2014
        std::cerr << agent->world().time() << __FILE__ << agent->world().self().unum() << __FILE__ << ": basic_tackle...\n";
        #endif // DEBUG2014

        return true;
    }

    const WorldModel & wm = agent->world();
    const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();
    const PlayerPtrCont & opps = wm.opponentsFromSelf();
    const PlayerObject * nearest_opp = ( opps.empty()
            ? static_cast< PlayerObject * >( 0 )
            : opps.front() );
    const double nearest_opp_dist = ( nearest_opp
                                      ? nearest_opp->distFromSelf()
                                      : 1000.0 );
    const Vector2D nearest_opp_pos = ( nearest_opp
                                       ? nearest_opp->pos()
                                       : Vector2D( -1000.0, 0.0 ) );
 const Vector2D fastest_opp_pos = ( fastest_opp
                                       ? fastest_opp->pos()
                                       : Vector2D( -1000.0, 0.0 ) );
    /*--------------------------------------------------------*/
    // chase ball
    const int self_min = wm.interceptTable()->selfReachCycle();
    const int mate_min = wm.interceptTable()->teammateReachCycle();
    const int opp_min = wm.interceptTable()->opponentReachCycle();
//add by lzh
//--------------------------------------------------------------------
   /* if (!wm.existKickableTeammate() && wm.ball().pos().x < 10.0 && wm.self().unum() == (2||3))
    {
       if (nearest_opp && fabs(wm.ball().pos().y) < 20.0)
       {
         Vector2D Pos = nearest_opp_pos;
         double dash_power = rolecenterbackmove().get_dash_power(agent, Pos);
         Body_GoToPoint(Pos,0.1,dash_power);
         return true;
       }
       else
       {
          Vector2D target_point = wm.ball().pos() + wm.ball().vel();
         // decide dash power
         //double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);

         double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
         if (dist_thr < 0.5)
         dist_thr = 0.5;
         Body_GoToPoint(target_point, dist_thr, rcsc::ServerParam::i().maxPower()*2);//add 2
         return true;
       }
    }
    if (!wm.existKickableTeammate() && wm.ball().pos().x < 10.0 && wm.self().unum() == (4||5))
    {
       if (nearest_opp && fabs(wm.ball().pos().y) > 20.0)
       {
         Vector2D Pos = nearest_opp_pos;
         double dash_power = rolecenterbackmove().get_dash_power(agent, Pos);
         Body_GoToPoint(Pos, 0.1,dash_power);
         return true;
       }
       else
       {
          Vector2D target_point = wm.ball().pos() + wm.ball().vel();
         // decide dash power
         //double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);

         double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
         if (dist_thr < 0.5)
         dist_thr = 0.5;
         Body_GoToPoint(target_point, dist_thr, rcsc::ServerParam::i().maxPower()*2);//add 2
         return true;
       }
    }*/
//--------------------------------------------------------------------------------
////*****************************add jelly 2014-7-24
//if (wm.self().unum() == 6 && wm.ball().pos().x >10.0 && wm.ball().pos().x<26 && !wm.existKickableTeammate())
//    {
//       if (nearest_opp && fabs(wm.ball().pos().y) < 20.0)
//       {
//         //std::cerr<<"wm.self().unum()==6dashpower intercepit"<<std::endl;
//         Vector2D Pos = nearest_opp_pos;
//         double dash_power = rolecenterbackmove().get_dash_power(agent, Pos);
//         Body_GoToPoint(Pos,0.1,dash_power);
//        agent->setNeckAction( new Neck_OffensiveInterceptNeck());
//        std::cerr << wm.time().cycle() << __FILE__ << ": No.6 chase nearest_opp(with maxpower)...\n";    //20140905: 我想看看这个有木有用
//        return true;
//       }
//       else
//       {
//          Vector2D target_point = wm.ball().pos() + wm.ball().vel();
//         // decide dash power
//         //double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);
//
//         double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
//         if (dist_thr < 0.5)
//         dist_thr = 0.5;
//         Body_GoToPoint(target_point, dist_thr, rcsc::ServerParam::i().maxPower()*1.5);//add1.5
//           agent->setNeckAction( new Neck_TurnToBallOrScan());
//         //agent->setNeckAction( new Neck_TurnToBall() );
//         //std::cerr<<"i(6).maxPower()*1.5gotopoint"<<std::endl;
//         std::cerr << wm.time().cycle() << __FILE__ << ": No.6 chase ball(with maxpower*1.5)...\n";
//         return true;
//
//       }
//    }
//
//if (wm.self().unum() == 11 && wm.ball().pos().x >26 && !wm.existKickableTeammate())
//    {
//       if (nearest_opp && fabs(wm.ball().pos().y) < 20.0)
//       {
//         //std::cerr<<"wm.self().unum()==11dashpower"<<std::endl;
//         Vector2D Pos = nearest_opp_pos;
//         double dash_power = rolecenterbackmove().get_dash_power(agent, Pos);
//         Body_GoToPoint(Pos,0.1,dash_power);
//
//        agent->setNeckAction( new Neck_OffensiveInterceptNeck() );
//        std::cerr << wm.time().cycle() << __FILE__ << ": No.6 chase nearest_opp(with maxpower)...\n";
//        return true;
//
//       }
//       else
//       {
//          Vector2D target_point = wm.ball().pos() + wm.ball().vel();
//         // decide dash power
//         //double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);
//
//         double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
//         if (dist_thr < 0.5)
//         dist_thr = 0.5;
//         Body_GoToPoint(target_point, dist_thr, rcsc::ServerParam::i().maxPower()*1.5);//add1.5
//          agent->setNeckAction( new Neck_TurnToBall());
//        std::cerr << wm.time().cycle() << __FILE__ << ": No.6 chase nearest_opp(with maxpower)...\n";
//         return true;
//
//         // std::cerr<<"i(11).maxPower()*1.5)"<<std::endl;
//
//       }

//**********************************

//if(fastest_opp&&(wm.ourDefenseLineX()+5 > wm.ball().pos().x))//add jelly
// {
      //   Vector2D Pos =fastest_opp_pos;
      //   double dash_power = rolecenterbackmove().get_dash_power(agent, Pos);
      //   Body_GoToPoint(Pos,0.1,dash_power);
      //   dlog.addText( Logger::TEAM,
      //                __FILE__": intercept" );
       // Body_Intercept().execute( agent );
       // agent->setNeckAction( new Neck_TurnToBall());
       // std::cerr<<"exit fastest_opp dash power"<<std::endl;


  // }
//  }

//**************************
    if ( ! wm.existKickableTeammate()
         && ( self_min <= 10
              || (wm.self().pos().absX()>20 && self_min <= mate_min + 10
                   && self_min < opp_min + 10 )
              )
         )
    {
        if(!(self_min>mate_min && mate_min<opp_min -3 )){
            dlog.addText( Logger::TEAM,
                      __FILE__": intercept" );
        Body_Intercept().execute( agent );
        agent->setNeckAction( new Neck_OffensiveInterceptNeck() );

        return true;
        }
        
    }

    const Vector2D target_point = Strategy::i().getPosition( wm.self().unum() );
    //const
    		double dash_power = Strategy::get_normal_dash_power( wm );

    //ht: 20140830 00:23
    if ( wm.self().unum() == 11 || wm.self().unum() == 10 || wm.self().unum() == 9 )
    {
        if ( wm.ball().pos().x > 40.0 )
        {
            if ( wm.ball().vel().x > 1.2
                 || (wm.ball().vel().x > 0.0 && wm.self().pos().x < wm.ball().pos().x - 5.5))
            {
                dash_power = ServerParam::i().maxPower() * 1.4;
            }
            else
            {
                dash_power = ServerParam::i().maxPower();
            }

        }
    }
    else if ( wm.ourDefenseLineX()+2 > wm.ball().pos().x
                ||Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_Danger)
    {
        dash_power = ServerParam::i().maxPower();
    }

    else if ( (wm.self().unum() == 7 || wm.self().unum() == 8 )
             && wm.ball().pos().x > 36.0 && wm.ball().vel().x > 1.4 )
    {
            dash_power = ServerParam::i().maxPower() ;
    }


//    double dist_thr = wm.ball().distFromSelf() * 0.1;
    double dist_thr = fabs( wm.ball().pos().x - wm.self().pos().x ) * 0.1;
    if ( dist_thr < 1.0 ) dist_thr = 1.0;

//    dlog.addText( Logger::TEAM,
//                  __FILE__": Bhv_BasicMove target=(%.1f %.1f) dist_thr=%.2f",
//                  target_point.x, target_point.y,
//                  dist_thr );
//
//    agent->debugClient().addMessage( "BasicMove%.0f", dash_power );
//    agent->debugClient().setTarget( target_point );
//    agent->debugClient().addCircle( target_point, dist_thr );

    if ( ! Body_GoToPoint( target_point, dist_thr, dash_power
                           ).execute( agent ) )
    {
        Body_TurnToBall().execute( agent );
    }

    if ( wm.existKickableOpponent()
         && wm.ball().distFromSelf() < 18.0 )
    {
        agent->setNeckAction( new Neck_TurnToBall() );
    }
    else
    {
        agent->setNeckAction( new Neck_TurnToBallOrScan() );
    }

    return true;
}
