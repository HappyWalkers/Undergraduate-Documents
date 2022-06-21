// -*-c++-*-

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2, or (at your option)
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

#include "role_center_back.h"
#include "role_center_back_move.h"
#include "neck_offensive_intercept_neck.h"
#include "strategy.h"
#include "bhv_dangerAreaTackle.h"
#include "bhv_basic_tackle.h"
#include "role_offensive_half_move.h"
#include <iostream>
#include "bhv_basic_move.h"
#include <rcsc/action/basic_actions.h>
#include <rcsc/action/body_clear_ball.h>
#include <rcsc/action/bhv_go_to_point_look_ball.h>
#include <rcsc/action/body_go_to_point.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/geom/vector_2d.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_ball_and_player.h>
#include <rcsc/action/neck_turn_to_ball_or_scan.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>
#include <rcsc/action/body_intercept2009.h>
#include <rcsc/formation/formation.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/intercept_table.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/geom/size_2d.h>
#include <rcsc/geom/rect_2d.h>
#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
using namespace std;
using namespace rcsc;

/*-------------------------------------------------------------------*/
/*!

 */
void
rolecenterbackmove::doBasicMove(PlayerAgent * agent,
    const rcsc::Vector2D & home_pos)
{
  const WorldModel & wm = agent->world();
//  Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());

//-----------------------------------------------
// tackle
  if (Bhv_BasicTackle(0.87, 70.0).execute(agent))
  {
    return;
  }

  //--------------------------------------------------
  // check intercept chance
  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();

  if (!wm.existKickableTeammate() && mate_min > 0)
  {
    int intercept_state = 0;
    if (self_min <= 1 && opp_min >= 1)
    {
      intercept_state = 1;
    }
    else if (self_min <= 2 && opp_min >= 3)
    {
      intercept_state = 2;
    }
    else if (self_min <= 3 && opp_min >= 4)
    {
      intercept_state = 3;
    }
    else if (self_min < 20 && self_min < mate_min
        && (self_min <= opp_min - 1 && opp_min >= 2))
    {
      intercept_state = 4;
    }
    else if (opp_min >= 2 && self_min <= opp_min + 1 && self_min <= mate_min)
    {
      intercept_state = 5;
    }

    Vector2D selfInterceptPoint = wm.ball().inertiaPoint(self_min);
    if (self_min < 30 && wm.self().pos().x < -20.0
        && selfInterceptPoint.x < wm.self().pos().x + 1.0)
    {
//      dlog.addText(Logger::ROLE,
//          __FILE__": doBasicMove reset intercept state %d", intercept_state);
      intercept_state = 0;

      if (self_min <= opp_min + 1 && opp_min >= 2 && self_min <= mate_min)
      {
        intercept_state = 9;
      }
      else if (self_min <= opp_min - 3 && self_min <= mate_min)
      {
        intercept_state = 10;
      }
      else if (self_min <= opp_min - 3 && self_min <= mate_min)
      {
        intercept_state = 12;
      }
      else if (self_min <= 1)
      {
        intercept_state = 13;
      }
    }

    if (intercept_state != 0)
    {
      // chase ball
      dlog.addText(Logger::ROLE, __FILE__": doBasicMove intercept. state=%d",
          intercept_state);
      agent->debugClient().addMessage("CBBasicMove:Intercept%d",
          intercept_state);
      Body_Intercept2009().execute(agent);
      const PlayerObject * opp = (
          wm.opponentsFromBall().empty() ?
              NULL : wm.opponentsFromBall().front() );
      if (opp && opp->distFromBall() < 2.0)
      {
        agent->setNeckAction(new Neck_TurnToBall());
      }
      else
      {
        agent->setNeckAction(new Neck_TurnToBallOrScan());
      }
      return;
    }
  }

  /*--------------------------------------------------------*/

  double dist_thr = 0.5;
  Vector2D target_point = getBasicMoveTarget(agent, home_pos, &dist_thr);

  // decide dash power
  double dash_power = this->get_dash_power(agent, target_point);

  //double dist_thr = wm.ball().pos().dist( target_point ) * 0.1;
  //if ( dist_thr < 0.5 ) dist_thr = 0.5;

  dlog.addText(Logger::ROLE, __FILE__": doBasicMove go to home. power=%.1f",
      dash_power);
  agent->debugClient().addMessage("CB:basic %.0f", dash_power);
  agent->debugClient().setTarget(target_point);
  agent->debugClient().addCircle(target_point, dist_thr);

  if (wm.ball().pos().x < -35.0)
  {
    if (wm.self().stamina() > ServerParam::i().staminaMax() * 0.6
        && wm.self().pos().x < target_point.x - 4.0
        && wm.self().pos().dist(target_point) > dist_thr)
    {
      Bhv_GoToPointLookBall(target_point, dist_thr, dash_power).execute(agent);
      return;
    }
  }

  doGoToPoint(agent, target_point, dist_thr, dash_power, 15.0); // dir_thr

  if (opp_min <= 3 || wm.ball().distFromSelf() < 10.0)
  {
    agent->setNeckAction(new Neck_TurnToBall());
  }
  else
  {
    agent->setNeckAction(new Neck_TurnToBallOrScan());
  }
}

/*-------------------------------------------------------------------*/
/*!

 */
Vector2D
rolecenterbackmove::getBasicMoveTarget(PlayerAgent * agent,
    const Vector2D & home_pos, double * dist_thr)
{
  const WorldModel & wm = agent->world();
//  const bool is_left_side = formation().isSideType(
//      agent->config().playerNumber());
//  const bool is_right_side = formation().isSynmetryType(
//      agent->config().playerNumber());

  Vector2D target_point = home_pos;

  *dist_thr = wm.ball().pos().dist(target_point) * 0.1;
  if (*dist_thr < 0.5)
    *dist_thr = 0.5;

  // get mark target player

  if (wm.ball().pos().x > home_pos.x + 15.0)
  {
    const PlayerPtrCont::const_iterator end = wm.opponentsFromSelf().end();

    double first_x = 100.0;

    for (PlayerPtrCont::const_iterator it = wm.opponentsFromSelf().begin();
        it != end; ++it)
        {
      if ((*it)->pos().x < first_x)
        first_x = (*it)->pos().x;
    }

    const PlayerObject * nearest_attacker = static_cast<const PlayerObject *>(0);
    double min_dist2 = 100000.0;

    for (PlayerPtrCont::const_iterator it = wm.opponentsFromSelf().begin();
        it != end; ++it)
        {
      if ((*it)->pos().x > wm.ourDefenseLineX() + 10.0)
        continue;
      if ((*it)->pos().x > home_pos.x + 10.0)
        continue;
      if ((*it)->pos().x < home_pos.x - 10.0)
        continue;
      if (std::fabs((*it)->pos().y - home_pos.y) > 10.0)
        continue;
#if 0
      if (is_left_side && (*it)->pos().y < home_pos.y - 2.0)
      continue;
      if (is_right_side && (*it)->pos().y > home_pos.y + 2.0)
      continue;

#endif

      double d2 = (*it)->pos().dist2(home_pos);
      if (d2 < min_dist2)
      {
        min_dist2 = d2;
        nearest_attacker = *it;
      }
      break;
    }

    if (nearest_attacker)
    {
      //const Vector2D goal_pos( -50.0, 0.0 );

      target_point.x = nearest_attacker->pos().x - 2.0;
      if (target_point.x > home_pos.x)
      {
        target_point.x = home_pos.x;
      }

      target_point.y = nearest_attacker->pos().y
          + (nearest_attacker->pos().y > home_pos.y ? -1.0 : 1.0);

      *dist_thr = std::min(1.0, wm.ball().pos().dist(target_point) * 0.1);

//      dlog.addText(Logger::ROLE, __FILE__":d getBasicMoveTarget."
//      "  block opponent front. dist_thr=%.2f", *dist_thr);
//      agent->debugClient().addMessage("BlockOpp");
    }
  }

  return target_point;
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolecenterbackmove::doCrossBlockAreaMove(PlayerAgent * agent,
    const Vector2D & home_pos)
{
//-----------------------------------------------
  // tackle
  //ht:20140830 01:35
  if (Bhv_DangerAreaTackle(0.9).execute(agent))
  {
    return;
  }

  const WorldModel & wm = agent->world();
  const ServerParam &SP = ServerParam::i();
  const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();
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
  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();



#if 1
//ht: ht:20140830 01:36

//    const rcsc::Rect2D our_penalty_plus(Vector2D( -SP.pitchHalfLength(),
//                                                    -SP.penaltyAreaHalfWidth() + 1.0 ),
//                                    rcsc::Size2D( SP.penaltyAreaLength() - 1.0,
//                                                  SP.penaltyAreaWidth() - 2.0 ) );

    const rcsc::Rect2D our_penalty_plus(Vector2D( -SP.pitchHalfLength(),
                                                    -SP.penaltyAreaHalfWidth() + 5.0 ),
                                    rcsc::Size2D( SP.penaltyAreaLength() + 5.0,
                                                  SP.penaltyAreaWidth() - 2.0 ) );

    if ( ( wm.existKickableOpponent() || ! wm.interceptTable()->isOurTeamBallPossessor() )   //our_penalty.contains( wm.ball().inertiaPoint(opp_min) )
            && wm.existOpponentIn(our_penalty_plus, 1, NULL) )   //快进禁区也要防！！！！！！！！！！！！！！！！！！
    {
//        doMarkMove( agent, home_pos );
//        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doMarkMove(1).\n";
//        return;
        if ( roleoffensivehalfmove().markCloseOpp(agent) ) //testing... 20141001
        {
            #ifdef DEBUG2014
            std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": markCloseOpp(1).\n";
            #endif

            return;
        }

    }


#endif // 1


//  org for off_half
//  if (wm.self().unum() == 8 && wm.ball().pos().y > 1.0)
//  {
//     if (wm.ball().distFromSelf() > 12.0 && wm.ball().pos().y > 24.0)
//     doMarkMove(agent, home_pos);
//     if (wm.ball().distFromSelf() < 4.0 && wm.ball().pos().y < 18.0 && self_min < opp_min + 2.0)
//     Body_ClearBall().execute( agent );
//
//     Vector2D target_point = wm.ball().pos() + wm.ball().vel();
//    // decide dash power
//    double dash_power = get_dash_power(agent, target_point);
//
//    double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
//    if (dist_thr < 0.5)
//      dist_thr = 0.5;
//
//    doGoToPoint(agent, target_point, dist_thr, dash_power, 15.0); // dir_thr
//  }
//  if (wm.self().unum() == 7 && wm.ball().pos().y < -1.0)
//  {
//     if (wm.ball().distFromSelf() > 12.0 && wm.ball().pos().y < -24.0)
//     doMarkMove(agent, home_pos);
//     if (wm.ball().distFromSelf() < 4.0 && wm.ball().pos().y > -18.0 && self_min < opp_min + 2.0)
//     Body_ClearBall().execute( agent );
//
//     Vector2D target_point = wm.ball().pos() + wm.ball().vel();
//    // decide dash power
//    double dash_power = get_dash_power(agent, target_point);
//
//    double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
//    if (dist_thr < 0.5)
//      dist_thr = 0.5;
//
//    doGoToPoint(agent, target_point, dist_thr, dash_power, 15.0); // dir_thr
//  }

//  if (nearest_opp)
//  {
//     Vector2D target_point ;
//     double dash_power = get_dash_power(agent, target_point);
//     target_point.x = (nearest_opp_pos.x + -52.0 )/2;
//     target_point.y = nearest_opp_pos.y/2;
//     doGoToPoint(agent, target_point, 0.1,dash_power, 15.0);
//     std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doGoToPoint(1).\n";
//     //############这里不要随便跑动！！看看doGoToPoint可能不太好################## ht:20140907
//  }
  if (fastest_opp)
  {
     Vector2D target_point = fastest_opp->pos() + wm.ball().pos() ;
     double dash_power = rcsc::ServerParam::i().maxPower();
     doGoToPoint(agent, target_point, 0.1,dash_power, 15.0);
//     std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doGoToPoint(2).\n";
     return;
  }
#if 1
    //
    if ( wm.ball().vel().r() > 2.0  // !wm.existKickableOpponent()
         && !wm.existKickableTeammate()
         && self_min <= opp_min
         && self_min < mate_min    // < ?
         /*&& Body_Intercept2009().execute( agent ) */)
    {
       if ( Body_GoToPoint2010( wm.ball().pos() + wm.ball().vel(),
                                 0.1,
                                 ServerParam::i().maxDashPower()).execute( agent )*1.5) //power*1.5
       {
           agent->setNeckAction( new rcsc::Neck_TurnToBallOrScan() );
//            std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_GoToPoint.\n";
            return;
       }

    }
#endif  //1

    doMarkMove( agent, home_pos );
    #ifdef DEBUG2014
    std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doMarkMove(2).\n";
    #endif // DEBUG2014

    return;

//  //20140905
//  if ( markCloseOpp(agent) )
//    {
////        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": markCloseOpp(2).\n";
//        return;
//    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolecenterbackmove::doStopperMove(PlayerAgent * agent,
    const Vector2D & home_pos)
{

  const WorldModel & wm = agent->world();
  const int opp_min = wm.interceptTable()->opponentReachCycle();
  const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();

  if (wm.self().pos().x > 35.0 && wm.ball().pos().absY() < 12.0
      && wm.ball().pos().x < wm.self().pos().x + 1.0
//      && wm.ball().pos().x > -42.0
      && (wm.ball().vel().x < -0.7 || wm.existKickableOpponent() || opp_min <= 1))
  {
    Vector2D target_point(-48.0, 0.0);
    if (wm.ball().pos().x > -38.0)
      target_point.x = -38.0;

    double dash_power = get_dash_power(agent, target_point);
    double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
    if (dist_thr < 0.5)
      dist_thr = 0.5;

//    dlog.addText(Logger::ROLE,
//        __FILE__": doStopperMove block center. (%.1f %.1f) thr=%.1f power=%.1f",
//        target_point.x, target_point.y, dist_thr, dash_power);
//    agent->debugClient().addMessage("StopperBlockCenter");
//    agent->debugClient().setTarget(target_point);
//    agent->debugClient().addCircle(target_point, dist_thr);

    doGoToPoint(agent, target_point, dist_thr, dash_power, 15.0); // dir_thr

    if (opp_min <= 3 || wm.ball().distFromSelf() < 10.0)
    {
      if (fastest_opp && opp_min <= 1)
      {
        agent->setNeckAction(new Neck_TurnToBallAndPlayer(fastest_opp));
      }
      else
      {
        agent->setNeckAction(new Neck_TurnToBall());
      }
    }
    else
    {
      agent->setNeckAction(new Neck_TurnToBallOrScan());
    }
    return;
  }

  if (agent->world().ball().pos().x > home_pos.x + 1.0)
  {
    agent->debugClient().addMessage("StopperMove(1)");
    doBasicMove(agent, home_pos);
    return;
  }

  if (agent->world().ball().pos().absY()
      > ServerParam::i().goalHalfWidth() + 2.0)
  {
    agent->debugClient().addMessage("StopperMove(2)");
    doMarkMove(agent, home_pos);
  }

  ////////////////////////////////////////////////////////
  // search mark target opponent
  if (doDangerGetBall(agent, home_pos))
  {
    return;
  }

//  agent->debugClient().addMessage("StopperMove(4)");
//  dlog.addText(Logger::ROLE, __FILE__": doStopperMove no gettable point");
  Bhv_BasicMove().execute(agent);
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolecenterbackmove::doDangerAreaMove(PlayerAgent * agent,
    const Vector2D & home_pos)
{
  const WorldModel & wm = agent->world();


  //-----------------------------------------------
  // tackle
  if (Bhv_DangerAreaTackle().execute(agent))
  {
//      std::cerr << agent->world().time().cycle() << __FILE__ << ": Bhv_DangerAreaTackle >>> No." << agent->world().self().unum() << std::endl;
    return;
  }


#if 1   //ht: 20140831 20:59
  if ( wm.self().isKickable()
       && (wm.self().pos().x > wm.ball().pos().x || wm.ball().pos().x < -50.0) )
  {
        //（每个球员）可以再加一个禁区罚球（x<-47）时，可以tackle就直接tackle?
        Body_ClearBall().execute(agent);
        agent->setNeckAction(new Neck_ScanField());
//        std::cerr << agent->world().time().cycle() << __FILE__ << ": Clear(testing...) >>> No." << agent->world().self().unum() << std::endl;
  }

#endif // 1

  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();
  const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();
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
  const Vector2D fastest_opp_pos = ( fastest_opp
                                       ? nearest_opp->pos()
                                       : Vector2D( -1000.0, 0.0 ) );
  Vector2D opp_trap_pos = wm.ball().inertiaPoint(opp_min);


#if 1   //ht:20140831 20:13

  //--------------------------------------------------
  // intercept
  if (!wm.existKickableOpponent()
      && !wm.existKickableTeammate()
      && wm.ball().vel().x < 0.5
      && self_min < mate_min
      && self_min < 3 )
  {
    rcsc::Line2D ball_line(wm.ball().pos(), wm.ball().vel().th());
    double goal_line_x = ball_line.getX( wm.self().pos().y );
    if ( goal_line_x < wm.self().pos().x + 1.0
         && goal_line_x > 52.5 ) //37?
    {
      if (Body_Intercept2009().execute(agent))  // or gotopoint?
      {
//        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": (BA_Danger) Body_Intercept (1) >>>testing(or just go to point)... \n";
        agent->setNeckAction(new rcsc::Neck_TurnToBall());
        return;
      }
    }
  }

#endif // 1


  if (nearest_opp
      && wm.self().pos().x <= wm.ball().pos().x
      && fabs(wm.ball().pos().y) < 12.0
      && markCloseOpp(agent))
  {
//      std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": markCloseOpp (1) ... \n";
      return;
//     Vector2D target_point ;
//     double dash_power = get_dash_power(agent, target_point);
//     target_point.x = (nearest_opp_pos.x + -52.0 )/2;
//     target_point.y = (nearest_opp_pos.y + 0)/2;
//     Body_GoToPoint(target_point, 0.1, dash_power);
  }

  //chase fastest opp
//  if (fastest_opp && fastest_opp_pos.absY() < 13.0)     //fastest_opp_pos.absY() < 13.0  20140831 20:21
//  {
//      Vector2D target_pos;
//      target_pos.y = fastest_opp_pos.y + fastest_opp->vel().y;
//      target_pos.x = fastest_opp_pos.x + fastest_opp->vel().x * 2.0;
//      if ( fastest_opp->vel().r() > 0.38 )
//      {
//          power = ServerParam::i().maxDashPower() * 1.4;
//      }
//      else
//      {
//          power = ServerParam::i().maxDashPower());
//      }
//
//      if ( Body_GoToPoint(target_pos, 0.1, power) )
//      {
//          agent->setNeckAction( new Neck_OffensiveInterceptNeck() );
//          return;
//      }
//
////     std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": chase fastest opp...\n";
//  }

  if (opp_trap_pos.absY() >= ServerParam::i().goalHalfWidth()
      || mate_min < self_min - 2)
  {
    markCloseOpp(agent);
//    std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": markCloseOpp (2) ... \n";
    return;
  }

  if ( ! wm.existKickableTeammate()
       && ( self_min <= 3
            || ( self_min <= mate_min
                 && self_min < opp_min + 3 )
            )
       )
  {
      dlog.addText( Logger::TEAM,
                    __FILE__": intercept" );
      Body_Intercept2009().execute( agent );
      agent->setNeckAction( new Neck_OffensiveInterceptNeck() );
//      std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_Intercept(2) ... \n";

      return;
  }

#if 1
  if (opp_min < mate_min && opp_min < self_min + 3
      && wm.ball().pos().x < wm.self().pos().x + 1.0
      && (wm.ball().vel().x < -0.7 || wm.existKickableOpponent() || opp_min <= 1))
  {
//    Vector2D target_point(-47.0, 0.0);
//    double y_sign = (opp_trap_pos.y > 0.0 ? 1.0 : -1.0 );
//    if (opp_trap_pos.absY() > 5.0)
//      target_point.y = y_sign * 5.0;
//    if (opp_trap_pos.absY() > 3.0)
//      target_point.y = y_sign * 3.0;
//    if (home_pos.y * target_point.y < 0.0)
//      target_point.y = 0.0;
    Vector2D target_point = wm.ball().pos() + wm.ball().vel();
    // decide dash power
    //double dash_power = get_dash_power(agent, target_point);

    //double dist_thr = wm.ball().distFromSelf() * 0.1;
    double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
    if (dist_thr < 0.5)
      dist_thr = 0.5;


    doGoToPoint(agent, target_point, dist_thr, ServerParam::i().maxDashPower(), 15.0); // dir_thr
    if (fastest_opp && opp_min <= 1)
    {
      agent->setNeckAction(new Neck_TurnToBallAndPlayer(fastest_opp));
    }
    else
    {
      agent->setNeckAction(new Neck_TurnToBall());
    }
//    std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doGoToPoint ... \n";

    return;
  }

  ////////////////////////////////////////////////////////
  // search mark target opponent
  if ( self_min < mate_min
       && doDangerGetBall(agent, home_pos) )
  {
      return;
//      std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doDangerGetBall... \n";
  }

  else if (markCloseOpp(agent)) //domarkmove->markcloseopp  20140905
  {

//    std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": markCloseOpp (3) ... \n";
//    dlog.addText(Logger::ROLE, __FILE__": doDangerMove. done doDangetGetBall");
    return;
  }
//  dlog.addText(Logger::ROLE, __FILE__": no gettable point in danger mvve");

  Bhv_BasicMove().execute(agent);
#endif
}

/*-------------------------------------------------------------------*/
/*!

 */

void
rolecenterbackmove::doMarkMove(PlayerAgent * agent, const Vector2D & home_pos)
{
  //-----------------------------------------------
  // tackle
  if (Bhv_DangerAreaTackle().execute(agent))
  {
    return;
  }

  ////////////////////////////////////////////////////////

  const WorldModel & wm = agent->world();

  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();
  const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();

  if (!wm.existKickableTeammate())
  {
    if ((self_min <= 1 && opp_min >= 1) || (self_min <= 2 && mate_min >= 2)
        || (self_min <= 3 && mate_min >= 3) || (self_min <= 4 && mate_min >= 5)
        || (self_min < opp_min + 3 && self_min < mate_min))
    {
//      dlog.addText(Logger::ROLE, __FILE__": doMarkMove intercept.");
//      agent->debugClient().addMessage("CBMark.Intercept");
      Body_Intercept2009().execute(agent);
      if (fastest_opp && opp_min <= 1)
      {
        agent->setNeckAction(new Neck_TurnToBallAndPlayer(fastest_opp));
      }
      else
      {
        agent->setNeckAction(new Neck_TurnToBallOrScan());
      }
      return;
    }
  }
#if 0
  if ( opp_min < self_min
      && wm.self().pos().x > -40.0 )
  {
    Vector2D opp_trap_pos = wm.ball().inertiaPoint( opp_min );

    if ( opp_trap_pos.absY() < 20.0
        && opp_trap_pos.x < wm.self().pos().x + 2.0 )
    {
      Vector2D move_pos( -47.0, 5.0 );
      if ( home_pos.y < 0.0 ) move_pos.y *= -1.0;

      double dist_thr = 1.0;

      agent->debugClient().addMessage( "CBMark.FastBack" );
      agent->debugClient().setTarget( move_pos );
      agent->debugClient().addCircle( move_pos, dist_thr );

      doGoToPoint( agent,
          move_pos, dist_thr,
          ServerParam::i().maxPower(),
          15.0 ); // dir_thr

      if ( fastest_opp && opp_min <= 1 )
      {
        agent->setNeckAction( new Neck_TurnToBallAndPlayer( fastest_opp ) );
      }
      else if ( opp_min <= 3 )
      {
        agent->setNeckAction( new Neck_TurnToBall() );
      }
      else
      {
        agent->setNeckAction( new Neck_TurnToBallOrScan() );
      }

      return;
    }
  }
#endif

  ////////////////////////////////////////////////////////

  if (doDangerGetBall(agent, home_pos))
  {
    return;
  }

  ////////////////////////////////////////////////////////
  // search mark target opponent

  const PlayerObject * mark_target = wm.getOpponentNearestTo(home_pos, 1, NULL);

  ////////////////////////////////////////////////////////
  // check candidate opponent
  if (!mark_target
      || mark_target->posCount() > 10	//B_add
      || mark_target->pos().x > -36.0 || mark_target->distFromSelf() > 10.0
      || mark_target->distFromBall()
          < ServerParam::i().defaultKickableArea() + 0.5
//      || mark_target->pos().dist(home_pos) > 3.0
      )
  {
    // not found
    doBasicMove(agent, home_pos);
    return;
  }

  ////////////////////////////////////////////////////////
  // check teammate closer than self
  {
    if(roleoffensivehalfmove().markCloseOpp(agent))
      return;
    double marker_dist = 100.0;
    const PlayerObject * marker = wm.getTeammateNearestTo(mark_target->pos(),
        30, &marker_dist);
    if (marker && marker_dist < mark_target->distFromSelf())
    {
      if (Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_Danger)
      {
        Vector2D target, Goal;
        Goal.x = -52;
        Goal.y = 7;
        if (wm.ball().pos().y > 0)
          Goal.y = -7;
        Line2D lineShoot(marker->pos(), Goal);
        target.x = home_pos.x;
        target.y = lineShoot.getY(target.x);
        Body_GoToPoint2010(target, 0.1, ServerParam::i().maxDashPower());
        return;
      }
      if (Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_CrossBlock)
      {
        Vector2D target;
        Line2D lineBlock(mark_target->pos(), wm.ball().pos());
        target.x = home_pos.x;
        target.y = lineBlock.getY(target.x);
        Body_GoToPoint2010(target, 0.1, ServerParam::i().maxDashPower());
        return;
      }
      Bhv_BasicMove().execute(agent);
      	 return;
    }
  }

  ////////////////////////////////////////////////////////
  // set target point
  Vector2D block_point = mark_target->pos();
  //block_point += mark_target->vel() / 0.6;
  block_point += mark_target->vel();
  Line2D blockline(block_point, wm.ball().pos());
  block_point.x -= 0.7;
  block_point.y = blockline.getY(block_point.x);
  // block_point.y += (mark_target->pos().y > wm.ball().pos().y ? -0.6 : 0.6 );

//  if (block_point.x > wm.ball().pos().x + 5.0)
//  {
//    // not found
//    agent->debugClient().addMessage("MarkToBasic");
//    dlog.addText(Logger::ROLE,
//        __FILE__": doMarkMove. (mark_point.x - ball.x) X diff is big");
//    doBasicMove(agent, home_pos);
//    return;
//  }

  double dash_power = ServerParam::i().maxPower();
  double x_diff = block_point.x - wm.self().pos().x;

  if (x_diff > 20.0)
  {
    //dash_power *= 0.5;
    dash_power = wm.self().playerType().staminaIncMax() * wm.self().recovery();
  }
  else if (x_diff > 10.0)
  {
    dash_power *= 0.7;
  }
  else if (wm.ball().pos().dist(block_point) > 20.0)
  {
    dash_power *= 0.6;
  }

  double dist_thr = wm.ball().distFromSelf() * 0.05;
//  if (dist_thr < 0.5)
//    dist_thr = 0.5;

  if (wm.self().pos().x < block_point.x
      && wm.self().pos().dist(block_point) < dist_thr)
  {
    AngleDeg body_angle = (
        wm.ball().pos().x < wm.self().pos().x - 5.0 ? 0.0 : 180.0 );

    Body_TurnToAngle(body_angle).execute(agent);
    if (wm.existKickableOpponent() || wm.ball().distFromSelf() > 15.0)
    {
      if (fastest_opp && opp_min <= 1)
      {
        agent->setNeckAction(new Neck_TurnToBallAndPlayer(fastest_opp));
      }
      else
      {
        agent->setNeckAction(new Neck_TurnToBall());
      }
    }
    else
    {
      agent->setNeckAction(new Neck_TurnToBallOrScan());
    }
    return;
  }

  if (wm.self().pos().dist(block_point) > 3.0)
  {
//    agent->debugClient().addMessage("MarkForwardDash");
//    agent->debugClient().setTarget(block_point);
//    agent->debugClient().addCircle(block_point, dist_thr);

//    dlog.addText(Logger::ROLE, __FILE__": doMarkMove. forward move");

    doGoToPoint(agent, block_point, dist_thr, dash_power, 15.0);

    if (wm.existKickableOpponent() || wm.ball().distFromSelf() > 15.0)
    {
      if (fastest_opp && opp_min <= 1)
      {
        agent->setNeckAction(new Neck_TurnToBallAndPlayer(fastest_opp));
      }
      else
      {
        agent->setNeckAction(new Neck_TurnToBall());
      }
    }
    else
    {
      agent->setNeckAction(new Neck_TurnToBallOrScan());
    }
    return;
  }

//  dlog.addText(Logger::ROLE, __FILE__": doMarkMove. ball looking move");

  Bhv_GoToPointLookBall(block_point, dist_thr, dash_power).execute(agent);

  const PlayerObject * ball_owner = wm.getOpponentNearestToBall(5);

  if (!ball_owner
      || ball_owner->distFromBall() > 1.2 + wm.ball().distFromSelf() * 0.05)
  {
    if (mark_target && mark_target->unum() < 0)
    {
      AngleDeg angle_diff = agent->effector().queuedNextAngleFromBody(
          mark_target->pos() + mark_target->vel());
      if (angle_diff.abs() < 100.0)
      {
        dlog.addText(Logger::ROLE,
            __FILE__": doMarkMove. check unknown mark target");
        agent->setNeckAction(
            new Neck_TurnToPoint(mark_target->pos() + mark_target->vel()));
        return;
      }
    }
//    dlog.addText(Logger::ROLE, __FILE__": doMarkMove. look ball or field scan");
    agent->setNeckAction(new Neck_TurnToBallOrScan());
  }
}

/*-------------------------------------------------------------------*/
/*!

 */
bool
rolecenterbackmove::doDangerGetBall(PlayerAgent * agent,
    const Vector2D & home_pos)
{
  //////////////////////////////////////////////////////////////////
  // tackle
  if (Bhv_DangerAreaTackle().execute(agent))
  {
    dlog.addText(Logger::ROLE, __FILE__": doDangetGetBall done tackle");
    return true;
  }

  const WorldModel & wm = agent->world();

  //--------------------------------------------------
  if (wm.existKickableTeammate() || wm.ball().pos().x > -36.0
      || wm.ball().pos().dist(home_pos) > 5.0 || wm.ball().pos().absY() > 9.0)
  {
    dlog.addText(Logger::ROLE,
        __FILE__": doDangetGetBall. no danger situation");
    return false;
  }

  const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();

  if (wm.existKickableOpponent())
  {
    Vector2D opp_pos = wm.opponentsFromBall().front()->pos();

    if (wm.self().pos().x < opp_pos.x
        && std::fabs(wm.self().pos().y - opp_pos.y) < 0.8)
    {
      dlog.addText(Logger::ROLE,
          __FILE__": doDangetGetBall attack to ball owner");

      Vector2D opp_vel = wm.opponentsFromBall().front()->vel();
      opp_pos.x -= 0.2;
      if (opp_vel.x < -0.1)
      {
        opp_pos.x -= 0.5;
      }
      if (opp_pos.x > wm.self().pos().x
          && fabs(opp_pos.y - wm.self().pos().y) > 0.8)
      {
        opp_pos.x = wm.self().pos().x;
      }

      agent->debugClient().addMessage("DangerAttackOpp");
      agent->debugClient().setTarget(opp_pos);
      agent->debugClient().addCircle(opp_pos, 0.1);

      dlog.addText(Logger::ROLE, __FILE__": doDangetGetBall (%.2f %.2f)",
          opp_pos.x, opp_pos.y);
      Body_GoToPoint(opp_pos, 0.1, ServerParam::i().maxPower()).execute(agent);
      if (fastest_opp)
      {
        agent->setNeckAction(new Neck_TurnToBallAndPlayer(fastest_opp));
      }
      else
      {
        agent->setNeckAction(new Neck_TurnToBall());
      }
      return true;
    }
  }
  else
  {
    int self_min = wm.interceptTable()->selfReachCycle();
    Vector2D selfInterceptPoint = wm.ball().inertiaPoint(self_min);
    if (self_min <= 2 && selfInterceptPoint.dist(home_pos) < 10.0)
    {
      dlog.addText(Logger::ROLE,
          __FILE__": doDangetGetBall. intercept. reach cycle = %d", self_min);
      agent->debugClient().addMessage("DangerGetBall");

      Body_Intercept2009().execute(agent);
      agent->setNeckAction(new Neck_TurnToBallOrScan());
      return true;
    }
  }

  return false;
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolecenterbackmove::doGoToPoint(PlayerAgent * agent,
    const Vector2D & target_point, const double & dist_thr,
    const double & dash_power, const double & dir_thr)
{

  if (Body_GoToPoint(target_point, dist_thr, dash_power, 100, // cycle
      false, // no back
      true, // stamina save
      15.0 //25.0 // dir_thr
      ).execute(agent))
  {
    return;
  }

  const WorldModel & wm = agent->world();

  AngleDeg body_angle;
  if (wm.ball().pos().x < -30.0)
  {
    body_angle = wm.ball().angleFromSelf() + 90.0;
    if (wm.ball().pos().x < -45.0)
    {
      if (body_angle.degree() < 0.0)
      {
        body_angle += 180.0;
      }
    }
    else if (body_angle.degree() > 0.0)
    {
      body_angle += 180.0;
    }
  }
  else // if ( std::fabs( wm.self().pos().y - wm.ball().pos().y ) > 4.0 )
  {
    //body_angle = wm.ball().angleFromSelf() + ( 90.0 + 20.0 );
    body_angle = wm.ball().angleFromSelf() + 90.0;
    if (wm.ball().pos().x > wm.self().pos().x + 15.0)
    {
      if (body_angle.abs() > 90.0)
      {
        body_angle += 180.0;
      }
    }
    else
    {
      if (body_angle.abs() < 90.0)
      {
        body_angle += 180.0;
      }
    }
  }
  /*
   else
   {
   body_angle = ( wm.ball().pos().y < wm.self().pos().y
   ? -90.0
   : 90.0 );
   }
   */

  Body_TurnToAngle(body_angle).execute(agent);

}

double
rolecenterbackmove::get_dash_power(const rcsc::PlayerAgent * agent,
    const rcsc::Vector2D & home_pos)
{
  static bool S_recover_mode = false;

  const rcsc::WorldModel & wm = agent->world();

  if (wm.self().stamina() < rcsc::ServerParam::i().staminaMax() * 0.5)
  {
    S_recover_mode = true;
  }
  else if (wm.self().stamina() > rcsc::ServerParam::i().staminaMax() * 0.85)
  {
    S_recover_mode = false;
  }

  const double ball_xdiff
  //= wm.ball().pos().x - home_pos.x;
  = wm.ball().pos().x - wm.self().pos().x;

  const rcsc::PlayerType & mytype = wm.self().playerType();
  const double my_inc = mytype.staminaIncMax() * wm.self().recovery();

  double dash_power;

  if((wm.ourDefenseLineX()+2 > wm.ball().pos().x ||
        		Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_Danger)
        		&& !wm.existKickableTeammate())                                                         //add
                	  return ServerParam::i().maxPower();
  if((Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_ShootChance
        		||Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_Cross)
        && wm.self().unum() == 11 && wm.existKickableTeammate()
        )
        		 return ServerParam::i().maxPower();


  if (S_recover_mode)
  {
    if (wm.ourDefenseLineX() > wm.self().pos().x)
    {
      rcsc::dlog.addText(rcsc::Logger::TEAM,
          __FILE__": get_dash_power. correct DF line & recover");
      dash_power = my_inc;
    }
    else if (ball_xdiff < 5.0)
    {
      dash_power = rcsc::ServerParam::i().maxPower();
    }
    else if (ball_xdiff < 10.0)
    {
      dash_power = rcsc::ServerParam::i().maxPower();
      dash_power *= 0.7;
      //dash_power
      //    = mytype.getDashPowerToKeepSpeed( 0.7, wm.self().effort() );
    }
    else if (ball_xdiff < 20.0)
    {
      dash_power = std::max(0.0, my_inc - 10.0);
    }
    else // >= 20.0
    {
      dash_power = std::max(0.0, my_inc - 20.0);
    }

    rcsc::dlog.addText(rcsc::Logger::TEAM,
        __FILE__": get_dash_power. recover mode dash_power= %.1f", dash_power);

    return dash_power;
  }

  // normal case

#if 1
  // added 2006/06/11 03:34
  if (wm.ball().pos().x > 0.0 && wm.self().pos().x < home_pos.x)
  {
    double power_for_max_speed = mytype.getDashPowerToKeepMaxSpeed(
        wm.self().effort());
    double defense_dash_dist = wm.self().pos().dist(rcsc::Vector2D(-48.0, 0.0));
    int cycles_to_reach = mytype.cyclesToReachDistance(defense_dash_dist);
    int available_dash_cycles = mytype.getMaxDashCyclesSavingRecovery(
        power_for_max_speed, wm.self().stamina(), wm.self().recovery());
    if (available_dash_cycles < cycles_to_reach)
    {
      rcsc::dlog.addText(rcsc::Logger::TEAM,
          __FILE__": get_dash_power. keep stamina for defense back dash,"
          " power_for_max=%.1f"
          " dash_dist=%.1f, reach_cycle=%d, dashable_cycle=%d",
          power_for_max_speed, defense_dash_dist, cycles_to_reach,
          available_dash_cycles);
      dash_power = std::max(0.0, my_inc - 20.0);
      return dash_power;
    }
  }
#endif

  if (wm.self().pos().x < -30.0 && wm.ourDefenseLineX() > wm.self().pos().x)
  {
    rcsc::dlog.addText(rcsc::Logger::TEAM,
        __FILE__": get_dash_power. correct dash power for the defense line");
    dash_power = rcsc::ServerParam::i().maxPower();
  }
  else if (home_pos.x < wm.self().pos().x)
  {
    rcsc::dlog.addText(
        rcsc::Logger::TEAM,
        __FILE__": get_dash_power. max power to go to the behind home position");
    dash_power = rcsc::ServerParam::i().maxPower();
  }
  else if (ball_xdiff > 20.0)
  {
    rcsc::dlog.addText(rcsc::Logger::TEAM,
        __FILE__": get_dash_power. correct dash power to save stamina(1)");
    dash_power = my_inc;
  }
  else if (ball_xdiff > 10.0)
  {
    rcsc::dlog.addText(rcsc::Logger::TEAM,
        __FILE__": get_dash_power. correct dash power to save stamina(2)");
    dash_power = rcsc::ServerParam::i().maxPower();
    dash_power *= 0.6;
    //dash_power = mytype.getDashPowerToKeepSpeed( 0.6, wm.self().effort() );
  }
  else if (ball_xdiff > 5.0)
  {
    rcsc::dlog.addText(rcsc::Logger::TEAM,
        __FILE__": get_dash_power. correct dash power to save stamina(3)");
    dash_power = rcsc::ServerParam::i().maxPower();
    dash_power *= 0.85;
    //dash_power = mytype.getDashPowerToKeepSpeed( 0.85, wm.self().effort() );
  }
  else
  {
    rcsc::dlog.addText(rcsc::Logger::TEAM,
        __FILE__": get_dash_power. max power");
    dash_power = rcsc::ServerParam::i().maxPower();
  }

  rcsc::dlog.addText(rcsc::Logger::TEAM,
      __FILE__": get_dash_power. nomal mode dash_power=%.1f", dash_power);

  return dash_power;
}

bool
rolecenterbackmove::Bhv_BlockDribble(PlayerAgent * agent)
{

  const WorldModel & wm = agent->world();

  // tackle
  if (Bhv_BasicTackle(0.8, 90.0).execute(agent))
  {
//    cout<<"BA_DefMidField-blockdribble-basictackle"<<endl;
    dlog.addText(Logger::TEAM, __FILE__": execute(). tackle");
    return true;
  }

  const int opp_min = wm.interceptTable()->opponentReachCycle();
  const PlayerObject * opp = wm.interceptTable()->fastestOpponent();

  if (!opp)
  {
//    cout<<"BA_DefMidField-blockdribble-oppfalse"<<endl;
    dlog.addText(Logger::TEAM, __FILE__": execute(). no fastest opponent");
    return false;
  }

  const Vector2D opp_target(-44.0, 0.0);
  const PlayerType & self_type = wm.self().playerType();
  const double control_area = self_type.kickableArea() - 0.3;
  const double max_moment = ServerParam::i().maxMoment() * ( 1.0 - ServerParam::i().playerRand() );

  const double first_my_speed = wm.self().vel().r();
  const Vector2D first_ball_pos = wm.ball().inertiaPoint(opp_min);
  const Vector2D first_ball_vel = (opp_target - first_ball_pos).setLengthVector(
      opp->playerTypePtr()->realSpeedMax());

  Vector2D target_point = Vector2D::INVALIDATED;
  int total_step = -1;

  for (int cycle = 1; cycle <= 20; ++cycle)
  {
    int n_turn = 0;
    int n_dash = 0;
    AngleDeg dash_angle = wm.self().body();

    Vector2D ball_pos = inertia_n_step_point(first_ball_pos, first_ball_vel,
        cycle, ServerParam::i().ballDecay());
    Vector2D my_pos = wm.self().inertiaPoint(cycle + opp_min);
    Vector2D target_rel = ball_pos - my_pos;
    double target_dist = target_rel.r();
    AngleDeg target_angle = target_rel.th();

    double stamina = wm.self().stamina();
    double effort = wm.self().effort();
    double recovery = wm.self().recovery();

    // turn
    double angle_diff = (target_angle - wm.self().body()).abs();
    double turn_margin = 180.0;
    if (control_area < target_dist)
    {
      turn_margin = AngleDeg::asin_deg(control_area / target_dist);
    }
    turn_margin = std::max(turn_margin, 15.0);
    double my_speed = first_my_speed;
    while (angle_diff > turn_margin)
    {
      double max_turn = self_type.effectiveTurn(max_moment, my_speed);
      angle_diff -= max_turn;
      my_speed *= self_type.playerDecay();
      ++n_turn;
    }

    if (n_turn > cycle + opp_min)
    {
      continue;
    }

    if (n_turn > 0)
    {
      angle_diff = std::max(0.0, angle_diff);
      dash_angle = target_angle;
      if ((target_angle - wm.self().body()).degree() > 0.0)
      {
        dash_angle += angle_diff;
      }
      else
      {
        dash_angle -= angle_diff;                                                          //change + to -
      }
    }
    // dash
    n_dash = self_type.cyclesToReachDistance(target_dist);

    if (stamina < ServerParam::i().recoverDecThrValue() + 300.0)
    {
      continue;
    }

    if (n_turn + n_dash <= cycle + opp_min)
    {
      target_point = ball_pos;
      total_step = n_turn + n_dash;
      break;
    }
  }
//  cout<<"BA_DefMidField-blockdribble-target_valid??"<<endl;
  if (!target_point.isValid())
  {
//    cout<<"BA_DefMidField-blockdribble-target_!!!valid"<<endl;
    return false;
  }
//  cout<<"BA_DefMidField-blockdribble-gotopoint"<<endl;
  if (!Body_GoToPoint(target_point, 0.5, ServerParam::i().maxPower()).execute(
      agent))
  {
//    cout<<"BA_DefMidField-blockdribble-gotopoint-failed"<<endl;
    return false;
  }
//  cout<<"BA_DefMidField-blockdribble-gotopoint-success"<<endl;
//  agent->debugClient().setTarget(target_point);
//  agent->debugClient().addMessage("BlockDribVirtualIntercept");
  agent->setNeckAction(new rcsc::Neck_TurnToBall());
  return true;

}
//////////////////////////////////////////////////////
// yily adds the following codes;
void
rolecenterbackmove::doOffensiveMove(rcsc::PlayerAgent * agent)
{
  Vector2D ballPos = agent->world().ball().pos();
  const WorldModel & wm = agent->world();
  Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());

  static bool s_recover_mode = false;

  //-----------------------------------------------
  // tackle
  if (Bhv_BasicTackle(0.8, 80.0).execute(agent))
  {
    return;
  }

  /*--------------------------------------------------------*/
  // chase ball
  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();

  if (!wm.existKickableTeammate()
      && (self_min <= 3 || (self_min < mate_min + 3 && self_min <= opp_min + 1)))
  {
    rcsc::dlog.addText(rcsc::Logger::TEAM,
        __FILE__": doOffensiveMove() intercept");
    Body_Intercept2009().execute(agent);

    if (self_min == 4 && opp_min >= 2)
    {
      agent->setViewAction(new rcsc::View_Wide());
    }
    else if (self_min == 3 && opp_min >= 2)
    {
      agent->setViewAction(new rcsc::View_Normal());
    }

    if (wm.ball().distFromSelf() < rcsc::ServerParam::i().visibleDistance())
    {
      agent->setNeckAction(new rcsc::Neck_TurnToLowConfTeammate());
      ;
    }
    else
    {
      agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
    }
    return;
  }

  if (wm.self().stamina() < rcsc::ServerParam::i().staminaMax() * 0.5)
  {
    s_recover_mode = true;
  }
  else if (wm.self().stamina() > rcsc::ServerParam::i().staminaMax() * 0.7)
  {
    s_recover_mode = false;
  }

  double dash_power = 100.0;
  const double my_inc = wm.self().playerType().staminaIncMax()
      * wm.self().recovery();

  if (wm.ourDefenseLineX() > wm.self().pos().x
      && wm.ball().pos().x < wm.ourDefenseLineX() + 20.0)
  {
    dash_power = rcsc::ServerParam::i().maxPower();
  }
  else if (s_recover_mode)
  {
    dash_power = my_inc - 25.0; // preffered recover value
    if (dash_power < 0.0)
      dash_power = 0.0;
  }
  else if (wm.existKickableTeammate() && wm.ball().distFromSelf() < 20.0)
  {
    dash_power = std::min(my_inc * 1.1, rcsc::ServerParam::i().maxPower());
  }
  // in offside area
  else if (wm.self().pos().x > wm.offsideLineX())
  {
    dash_power = rcsc::ServerParam::i().maxPower();
  }
  else if (home_pos.x < wm.self().pos().x
      && wm.self().stamina() > rcsc::ServerParam::i().staminaMax() * 0.7)
  {
    dash_power = rcsc::ServerParam::i().maxPower();
  }
  // normal
  else
  {
    dash_power = std::min(my_inc * 1.7, rcsc::ServerParam::i().maxPower());
  }

  double dist_thr = wm.ball().distFromSelf() * 0.1;
  if (dist_thr < 1.5)
    dist_thr = 1.5;

  agent->debugClient().addMessage("OffMove%.0f", dash_power);
  agent->debugClient().setTarget(home_pos);
  agent->debugClient().addCircle(home_pos, dist_thr);

  if (!rcsc::Body_GoToPoint(home_pos, dist_thr, dash_power).execute(agent))
  {
    rcsc::Vector2D my_next = wm.self().pos() + wm.self().vel();
    rcsc::Vector2D ball_next = (
        wm.existKickableOpponent() ?
            wm.ball().pos() : wm.ball().pos() + wm.ball().vel() );
    rcsc::AngleDeg body_angle = (ball_next - my_next).th() + 90.0;
    if (body_angle.abs() < 90.0)
      body_angle -= 180.0;

    rcsc::Body_TurnToAngle(body_angle).execute(agent);
  }

  if (wm.existKickableOpponent() && wm.ball().distFromSelf() < 18.0)
  {
    agent->setNeckAction(new rcsc::Neck_TurnToBall());
  }
  else
  {
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
  }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolecenterbackmove::doDefensiveMove(rcsc::PlayerAgent * agent)
{
//  //      cout<<"BA_DefMidField-begin"<<endl;
  Vector2D ballPos = agent->world().ball().pos();
  const WorldModel & wm = agent->world();
  const ServerParam & SP = ServerParam::i();
  Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());
  const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();
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

  rcsc::dlog.addText(rcsc::Logger::ROLE, __FILE__": doDefensiveMove");


#if 1
    //chase ball/opp

    if ( wm.ball().pos().x < wm.self().pos().x -5.0 )       //ht:20140830 02:58
    {
        if ( wm.ball().pos().y * home_pos.y < 0.0       //same side
                && wm.ball().pos().absY() < 12.0 )
        {
            //when opp begin fast attack, 4/5 go back!
            Vector2D adjust(0.0, 0.0);
//            if ( wm.ball().vel().y * wm.self().pos().y < 0.0 )  //ht:20140830 01:56
//            {
//                adjust = wm.ball().vel() + wm.ball().vel();
//            }
//            else
            {
//                adjust.y = wm.ball().vel().y;
                adjust.x = 2.0 * wm.ball().vel().x;
            }
            Vector2D Pos = wm.ball().pos() + adjust; //wm.ball().vel() * 2.5;     //vel*2 at 20140814 testing....
    //        std::cerr << __FILE__ << wm.time().cycle() << "is there any use??? \n";
            Body_GoToPoint(Pos, 0.1, rcsc::ServerParam::i().maxPower() * 1.5 );
            agent->setNeckAction( new Neck_TurnToBallOrScan());
//            std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": chase opp/ball(1)\n";

            return;
        }


    }
    else  if (wm.ball().pos().x < wm.self().pos().x -3.0
        && agent->world().ball().pos().y * home_pos.y > 0.0   //same side
        && wm.ball().pos().absY() < 12.0 )    //modified by ht at 20140905
    {
        //when opp begin fast attack, 4/5 go back!
        Vector2D adjust(0.0, 0.0);
//        if ( wm.ball().vel().y * wm.self().pos().y < 0.0 )  //ht:20140830 01:56 //need to change!!跑动不连贯
//        {
//            adjust = wm.ball().vel() + wm.ball().vel();
//        }
//        else
//        {
            adjust.x = wm.ball().vel().x;   //2.0 * wm.ball().vel().x;
//        }
        Vector2D Pos = wm.ball().pos() + adjust; //wm.ball().vel() * 2.5;     //vel*2 at 20140814 testing....
//        std::cerr << __FILE__ << wm.time().cycle() << "is there any use??? \n";
        Body_GoToPoint(Pos, 0.1, rcsc::ServerParam::i().maxPower());
        agent->setNeckAction( new Neck_TurnToBallOrScan());
//        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": chase opp/ball(2)\n";

        return;
    }
#endif //1

  //////////////////////////////////////////////////////
  // tackle
  if (Bhv_BasicTackle(0.8, 80.0).execute(agent))
  {
    return;
  }

  //----------------------------------------------
  // intercept
  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();

#if 0
    //  20140927
  if (fastest_opp)
  {
     Vector2D target_point = fastest_opp->pos() + wm.ball().pos() ;
     double dash_power = rcsc::ServerParam::i().maxPower();
     rolecenterbackmove().doGoToPoint(agent, target_point, 0.1,dash_power, 15.0);
     std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doGoToPoint(2).\n";
     return;
  }

    if ( wm.ball().vel().r() > 2.0  // !wm.existKickableOpponent()
         && !wm.existKickableTeammate()
         && self_min <= opp_min
         && self_min < mate_min    // < ?
         /*&& Body_Intercept2009().execute( agent ) */)
    {
       if ( Body_GoToPoint2010( wm.ball().pos() + wm.ball().vel(),
                                 0.1,
                                 ServerParam::i().maxDashPower()).execute( agent )*1.5) //power*1.5
       {
           agent->setNeckAction( new rcsc::Neck_TurnToBallOrScan() );
            std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_GoToPoint.\n";
            return;
       }

    }
#endif  //1

  const rcsc::Vector2D self_reach_point = wm.ball().inertiaPoint(self_min);
  const rcsc::Vector2D opp_reach_point = wm.ball().inertiaPoint(opp_min);

  if (wm.ball().pos().x < -20.0 && nearest_opp && nearest_opp_pos.x < wm.self().pos().x - 1.5 &&
      !wm.existKickableTeammate() && self_min > mate_min)
  {
    Vector2D Pos = nearest_opp_pos + wm.ball().vel() * 2.0; //wm.ball().vel() -> wm.ball().vel() * 2.0
    double dash_power = get_dash_power(agent, Pos);
    Body_GoToPoint(Pos, 0.1, dash_power);
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
//    std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": chase opp/ball(3)\n";
    return ;
  }
  if (wm.self().pos().x > wm.ball().pos().x + 1.0 && !wm.existKickableTeammate() && fastest_opp)
  {
    double dash_power = rcsc::ServerParam::i().maxPower();
    Vector2D Pos = wm.ball().pos() + wm.ball().vel();
    Body_GoToPoint(Pos, 0.1, dash_power);
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
//    std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": chase opp/ball(4)\n";
    return ;
  }

  if (!wm.existKickableTeammate()
#if 1
      && self_reach_point.dist(home_pos) < 13.0
#endif
      && (self_min < mate_min
          || self_min <= 3 && wm.ball().pos().dist2(home_pos) < 10.0 * 10.0
          || self_min <= 5 && wm.ball().pos().dist2(home_pos) < 8.0 * 8.0))
  {
    if ( opp_min < mate_min - 1
         && wm.self().pos().x < wm.theirOffenseLineX() )
    {
//      //      cout<<"BA_DefMidField-blockdribble"<<endl;
      rolecenterbackmove().Bhv_BlockDribble(agent);
      agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
//      std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Bhv_BlockDribble\n";
//      //      cout<<"BA_DefMidField-blockdribble"<<endl;
      return;
    }
//    //      cout<<"BA_DefMidField-intercept"<<endl;
    //20140830 01:07  need to change
    if ( !wm.existKickableTeammate()
        && self_min <= mate_min && self_min <= 3.0
        && self_min <= opp_min
        && Body_Intercept2009().execute(agent) )
    {
        agent->setNeckAction( new Neck_OffensiveInterceptNeck() );
//        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_Intercept\n";
        return;
    }

//    //      cout<<"BA_DefMidField-intercept"<<endl;
    if (self_min == 4 && opp_min >= 2)
    {
      agent->setViewAction(new rcsc::View_Wide());
    }
    else if (self_min == 3 && opp_min >= 2)
    {
      agent->setViewAction(new rcsc::View_Normal());
    }

    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
    return;
  }

//  if (!wm.existKickableTeammate()
//      && (self_min < opp_min + 2.0 || self_min <= 3.0 )
//      && Body_Intercept2009().execute(agent))
//  {
//      agent->setNeckAction( new Neck_OffensiveInterceptNeck() );
//    return;
//  }

#if 1
//ht: ht:20140830 01:36

//    const rcsc::Rect2D our_penalty_plus(Vector2D( -SP.pitchHalfLength(),
//                                                    -SP.penaltyAreaHalfWidth() + 1.0 ),
//                                    rcsc::Size2D( SP.penaltyAreaLength() - 1.0,
//                                                  SP.penaltyAreaWidth() - 2.0 ) );

    const rcsc::Rect2D our_penalty_plus(Vector2D( -SP.pitchHalfLength(),
                                                    -SP.penaltyAreaHalfWidth() + 5.0 ),
                                    rcsc::Size2D( SP.penaltyAreaLength() + 5.0,
                                                  SP.penaltyAreaWidth() - 2.0 ) );

    if ( ( wm.existKickableOpponent() || ! wm.interceptTable()->isOurTeamBallPossessor() )   //our_penalty.contains( wm.ball().inertiaPoint(opp_min) )
            && wm.existOpponentIn(our_penalty_plus, 1, NULL) )   //快进禁区也要防！！！！！！！！！！！！！！！！！！
    {
//        if ( doMarkMove( agent, home_pos ) )
        doMarkMove( agent, home_pos );
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doMarkMove(1).\n";
        #endif

        return;
//        {
//            std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doMarkMove(1).\n";
//            return;
//        }

    }

    if ( markCloseOpp(agent) )
    {
        return;
    }


#endif // 1

  //////////////////////////////////////////////////////

  rcsc::Vector2D ball_future = rcsc::inertia_n_step_point(wm.ball().pos(),
      wm.ball().vel(), mate_min, rcsc::ServerParam::i().ballDecay());

  const double future_x_diff = ball_future.x - wm.self().pos().x;

  double dash_power = rcsc::ServerParam::i().maxPower();

  if (wm.existKickableTeammate() && wm.ball().distFromSelf())
  {
    dash_power *= 0.5;
  }
  else if (future_x_diff < 0.0) // ball is behind
  {
    dash_power *= 0.9;
  }
  else if (wm.self().stamina() < rcsc::ServerParam::i().staminaMax() * 0.8)
  {
    dash_power *=  wm.self().stamina() / rcsc::ServerParam::i().staminaMax();
  }
  else
  {
    dash_power = wm.self().playerType().staminaIncMax();
    //dash_power *= wm.self().recovery();
    //dash_power *= 0.9;
  }

  // save recovery
  //dash_power = wm.self().getSafetyDashPower(dash_power);

  if((wm.ourDefenseLineX()+2 > wm.ball().pos().x || wm.ball().pos().x < wm.self().pos().x + 1.5 ||
   	   Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_Danger)
    		&& !wm.existKickableTeammate())
            	 dash_power = ServerParam::i().maxPower();

  rcsc::dlog.addText(rcsc::Logger::ROLE,
      __FILE__": doDefensiveMove() go to home. dash_power=%.1f", dash_power);

  double dist_thr = wm.ball().distFromSelf() * 0.1;
  if (dist_thr < 0.5)
    dist_thr = 0.5;

  agent->debugClient().addMessage("DMFDefMove");
  agent->debugClient().setTarget(home_pos);
  agent->debugClient().addCircle(home_pos, dist_thr);
//  //      cout<<"BA_DefMidField-gotopoint"<<endl;
  if (!rcsc::Body_GoToPoint(home_pos, dist_thr, dash_power).execute(agent))
  {
//    //      cout<<"!!!!!!!BA_DefMidField-gotopoint"<<endl;
    rcsc::AngleDeg body_angle = 0.0;
    if (wm.ball().angleFromSelf().abs() > 80.0)
    {
      body_angle = (wm.ball().pos().y > wm.self().pos().y ? 90.0 : -90.0 );
    }
//    //      cout<<"BA_DefMidField-turnto"<<endl;
    rcsc::Body_TurnToAngle(body_angle).execute(agent);
//    //      cout<<"BA_DefMidField-turnto-end"<<endl;
  }
  agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolecenterbackmove::doDribbleBlockMove(rcsc::PlayerAgent* agent)
{
  Vector2D ballPos = agent->world().ball().pos();
  const WorldModel & wm = agent->world();
  const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();
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
  const Vector2D fastest_opp_pos = ( fastest_opp
                                       ? fastest_opp->pos()
                                       : Vector2D( -1000.0, 0.0 ) );
  Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());
  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();
  bool meFastest = false;
  if ( self_min < mate_min
       && ( self_min < opp_min
            || ( self_min == opp_min        //20141001
                 && wm.ball().vel().y * wm.self().pos().y < 0 ) ) )
  {
      meFastest = true;
  }

  rcsc::dlog.addText(rcsc::Logger::ROLE, __FILE__": doDribbleBlockMove()");

  ///////////////////////////////////////////////////
  // tackle
  if (Bhv_BasicTackle(0.8, 80.0).execute(agent))
  {
    return;
  }

  ///////////////////////////////////////////////////
  if (meFastest)
  {
    rcsc::dlog.addText(rcsc::Logger::ROLE,
        __FILE__": doDribbleBlockMove() I am fastest. intercept");
    Body_Intercept2009().execute(agent);
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
    return;
  }

  if (fastest_opp && fastest_opp_pos.x < wm.self().pos().x - 1.0)
  {
    double dash_power = ServerParam::i().maxPower();
    Vector2D Pos =fastest_opp->pos() + fastest_opp->vel();
    double dist_thr = wm.ball().pos().dist(fastest_opp_pos) * 0.1;
    if (dist_thr < 0.5)
      dist_thr = 0.5;
     Body_GoToPoint(Pos, dist_thr,dash_power);
  }
  if (wm.ball().pos().x > -15.0 && !wm.existKickableTeammate() && nearest_opp)
  {
     // decide dash power
    double dash_power = get_dash_power(agent, nearest_opp_pos);

    double dist_thr = wm.ball().pos().dist(nearest_opp_pos) * 0.1;
    if (dist_thr < 0.5)
      dist_thr = 0.5;
     Body_GoToPoint(nearest_opp_pos, dist_thr,dash_power);
  }
  if (wm.ball().pos().x < -15.0 && !wm.existKickableTeammate())
  {
      double dash_power = ServerParam::i().maxPower();
      Vector2D Pos = wm.ball().pos() + wm.ball().vel();
      double dist_thr = wm.ball().pos().dist(Pos) * 0.1;
      if (dist_thr < 0.5)
      dist_thr = 0.5;
      Body_GoToPoint(Pos,dist_thr, dash_power);
  }
  ///////////////////////////////////////////////////
  double dash_power;

  if (wm.self().pos().x + 5.0 < wm.ball().pos().x)
  {
    if (wm.self().stamina() < rcsc::ServerParam::i().staminaMax() * 0.7)
    {
      dash_power = rcsc::ServerParam::i().maxPower() * 0.7
          * (wm.self().stamina() / rcsc::ServerParam::i().staminaMax());
      rcsc::dlog.addText(rcsc::Logger::ROLE,
          __FILE__": doDribbleBlockMove() dash_power=%.1f", dash_power);
    }
    else
    {
      dash_power = rcsc::ServerParam::i().maxPower() * 0.75
          - std::min(30.0, wm.ball().distFromSelf());
      rcsc::dlog.addText(rcsc::Logger::ROLE,
          __FILE__": doDribbleBlockMove() dash_power=%.1f", dash_power);
    }
  }
  else
  {
    dash_power = rcsc::ServerParam::i().maxPower() + 10.0
        - wm.ball().distFromSelf();
    dash_power = rcsc::min_max(0.0, dash_power,
        rcsc::ServerParam::i().maxPower());
    rcsc::dlog.addText(rcsc::Logger::ROLE,
        __FILE__": doDribbleBlockMove() dash_power=%.1f", dash_power);
  }

  if (wm.existKickableTeammate())
  {
    dash_power = std::min(rcsc::ServerParam::i().maxPower() * 0.5, dash_power);
  }

  if((wm.ourDefenseLineX()+2 > wm.ball().pos().x
      		  ||Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_CrossBlock)
              		&& !wm.existKickableTeammate())                                                         //add
                      	  dash_power = ServerParam::i().maxPower();

  dash_power = wm.self().getSafetyDashPower(dash_power);

  double dist_thr = wm.ball().distFromSelf() * 0.1;
  if (dist_thr < 0.5)
    dist_thr = 0.5;

  agent->debugClient().addMessage("DribBlockMove");
  agent->debugClient().setTarget(home_pos);
  agent->debugClient().addCircle(home_pos, dist_thr);

  if (!rcsc::Body_GoToPoint(home_pos, dist_thr, dash_power).execute(agent))
  {
    // face to front or side
    rcsc::AngleDeg body_angle = 0.0;
    if (wm.ball().angleFromSelf().abs() > 90.0)
    {
      body_angle = (wm.ball().pos().y > wm.self().pos().y ? 90.0 : -90.0 );
    }
    rcsc::Body_TurnToAngle(body_angle).execute(agent);
  }
  agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolecenterbackmove::doCrossAreaMove(rcsc::PlayerAgent * agent)
{
  Bhv_BasicMove().execute(agent);
}

void
rolecenterbackmove::doDefMidMove( PlayerAgent * agent,
                              const Vector2D & home_pos )
{
    agent->debugClient().addMessage( "DefMidMove" );

    dlog.addText( Logger::ROLE,
                  __FILE__": doDefMidMove" );

    const WorldModel & wm = agent->world();

    //-----------------------------------------------
    // tackle
    if ( Bhv_BasicTackle( 0.85, 50.0 ).execute( agent ) )
    {
        return;
    }

    //--------------------------------------------------
    // check intercept chance
    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();

#if 1
    {
        const rcsc::Vector2D self_reach_point = wm.ball().inertiaPoint( self_min );
        const rcsc::Vector2D opp_reach_point = wm.ball().inertiaPoint( opp_min );

        if ( self_min <= mate_min + 2
             && opp_reach_point.dist( home_pos ) < 5.0
             && opp_reach_point.x < home_pos.x + 5.0 )
        {
            rcsc::dlog.addText( rcsc::Logger::ROLE,
                                __FILE__": doDefMidMove. try BlockDribble"
                                " home=(%.1f %.1f)",
                                " opp_reach_pos=(%.1f %.1f)",
                                home_pos.x, home_pos.y,
                                opp_reach_point.x, opp_reach_point.y );
            if ( Bhv_BlockDribble(agent)  )
            {

                agent->debugClient().addMessage( "DefMidBlockDrib" );
                return;
            }
        }
    }
#endif

    const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();

    bool chase_ball = false;

    //if ( self_min == 1 && opp_min >= 1 ) chase_ball = true;
    if ( self_min == 1 ) chase_ball = true;
    if ( self_min == 2 && opp_min >= 1 ) chase_ball = true;
    if ( self_min >= 3 && opp_min >= self_min - 1 ) chase_ball = true;
    if ( mate_min <= self_min - 2 ) chase_ball = false;
    if ( wm.existKickableTeammate() || mate_min == 0 ) chase_ball = false;

    if ( chase_ball )
    {
        // chase ball
        dlog.addText( Logger::ROLE,
                      __FILE__": doDefMidMove intercept." );
        agent->debugClient().addMessage( "CB:DefMid:Intercept" );

        Body_Intercept2009().execute( agent );

        if ( fastest_opp && opp_min <= 1 )
        {
            agent->setNeckAction( new Neck_TurnToBallAndPlayer( fastest_opp ) );
        }
        else
        {
            agent->setNeckAction( new Neck_TurnToBallOrScan() );
        }
        return;
    }

    const Vector2D opp_trap_pos = ( opp_min < 100
                                    ? wm.ball().inertiaPoint( opp_min )
                                    : wm.ball().inertiaPoint( 20 ) );

    /*--------------------------------------------------------*/
    // ball is in very safety area (very front & our ball)
    // go to home position

    if ( opp_trap_pos.x > home_pos.x + 4.0
         && opp_trap_pos.x > wm.self().pos().x + 5.0
         && ( mate_min <= opp_min - 2 || self_min <= opp_min - 4 ) )
    {
        dlog.addText( Logger::ROLE,
                      __FILE__": doDefMidMove. opp trap pos is front. cycle=%d (%.1f %.1f)",
                      opp_min, opp_trap_pos.x, opp_trap_pos.y );
        agent->debugClient().addMessage( "CB:safety" );
        Bhv_BasicMove().execute( agent );
        return;
    }

    Vector2D target_point = getDefMidMoveTarget( agent, home_pos );

    // decide dash power
    double dash_power
        = get_dash_power( agent, target_point );

    //double dist_thr = wm.ball().distFromSelf() * 0.1;
    //if ( dist_thr < 0.5 ) dist_thr = 0.5;
    double dist_thr = wm.ball().pos().dist( target_point ) * 0.1;
    if ( dist_thr < 0.5 ) dist_thr = 0.5;

    dlog.addText( Logger::ROLE,
                  __FILE__": doDefMidMove go to home. power=%.1f",
                  dash_power );
    agent->debugClient().addMessage( "CB:DefMid%.0f", dash_power );
    agent->debugClient().setTarget( target_point );
    agent->debugClient().addCircle( target_point, dist_thr );

    if ( wm.ball().pos().x < -35.0 )
    {
        if ( wm.self().stamina() > ServerParam::i().staminaMax() * 0.6
             && wm.self().pos().x < target_point.x - 4.0
             && wm.self().pos().dist( target_point ) > dist_thr )
        {
            Bhv_GoToPointLookBall( target_point,
                                   dist_thr,
                                   dash_power
                                   ).execute( agent );
            return;
        }
    }

    doGoToPoint( agent, target_point, dist_thr, dash_power,
                 15.0 ); // dir_thr

    const PlayerObject * ball_nearest_opp = wm.getOpponentNearestToBall( 5 );

    if ( ball_nearest_opp && ball_nearest_opp->distFromBall() < 2.0 )
    {
        agent->setNeckAction( new Neck_TurnToBallAndPlayer( ball_nearest_opp ) );
    }
    if ( opp_min <= 3
         || wm.ball().distFromSelf() < 10.0 )
    {
        if ( fastest_opp && opp_min <= 1 )
        {
            agent->setNeckAction( new Neck_TurnToBallAndPlayer( fastest_opp ) );
        }
        else
        {
            agent->setNeckAction( new Neck_TurnToBall() );
        }
    }
    else
    {
        agent->setNeckAction( new Neck_TurnToBallOrScan() );
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
Vector2D
rolecenterbackmove::getDefMidMoveTarget( PlayerAgent * agent,
                                     const Vector2D & home_pos )
{
    const WorldModel & wm = agent->world();

    Vector2D target_point = home_pos;

    int opp_min = wm.interceptTable()->opponentReachCycle();
    const Vector2D opp_trap_pos = ( opp_min < 100
                                    ? wm.ball().inertiaPoint( opp_min )
                                    : wm.ball().inertiaPoint( 20 ) );

    /*--------------------------------------------------------*/
    // decide wait position
    // adjust to the defence line
    if ( -30.0 < home_pos.x
         && home_pos.x < -10.0
         && wm.self().pos().x > home_pos.x
         && wm.ball().pos().x > wm.self().pos().x )
    {
        // make static line
        double tmpx = home_pos.x;
        for ( double x = -12.0; x > -27.0; x -= 8.0 )
        {
            if ( opp_trap_pos.x > x + 1.0 )
            {
                tmpx = x - 3.3;
                dlog.addText( Logger::ROLE,
                              __FILE__": getDefMidMoveTarget found static defense line x=%.1f",
                              tmpx );
                break;
            }
        }

//         if ( std::fabs( wm.self().pos().y - opp_trap_pos.y ) > 5.0 )
//         {
//             tmpx -= 3.0;
//         }
        target_point.x = tmpx;

        agent->debugClient().addMessage( "LineDef%.1f", target_point.x );
    }


    if ( wm.ball().pos().absY() < 7.0
         && wm.ball().pos().x < wm.self().pos().x + 1.0
         && wm.ball().pos().x > -42.0
         && ( wm.ball().vel().x < -0.7
              || wm.existKickableOpponent()
              || opp_min <= 1 )
         )
    {
        dlog.addText( Logger::ROLE,
                      __FILE__": getDefMidMoveTarget. correct target point to block center" );
        agent->debugClient().addMessage( "BlockCenter" );
        target_point.assign( -47.0, 0.0 );
        if ( wm.ball().pos().x > -38.0 ) target_point.x = -41.0;
//         double y_sign = ( opp_trap_pos.y > 0.0 ? 1.0 : -1.0 );
//         if ( opp_trap_pos.absY() > 5.0 ) target_point.y = y_sign * 5.0;
//         if ( opp_trap_pos.absY() > 3.0 ) target_point.y = y_sign * 3.0;
//         if ( home_pos.y * target_point.y < 0.0 ) target_point.y = 0.0;
    }

    return target_point;
}

/*-------------------------------------------------------------------*/
/*!
from roleoffensivehalfmove::markCloseOpp(rcsc::PlayerAgent * agent)
ht: changed at 20140904 12:00
*/
bool
rolecenterbackmove::markCloseOpp(rcsc::PlayerAgent * agent)
{
  //-----------------------------------------------
  //tackle
  //
//  if ( agent->world().ball().pos().x < 32.0
//      && Bhv_DangerAreaTackle().execute(agent) )
//  {
//      //20140918 22:38 testing...
//      return true;
//  }
//  else if (Bhv_BasicTackle(0.9, 60.0).execute(agent) )
//  {
//    return true;
//  }

  const rcsc::WorldModel & wm = agent->world();
  const Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());
  //-----------------------------------------------
  // intercept
  //
  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();
  const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();
  double dist_opp_to_home = 222.0;
  const PlayerObject * opp = wm.getOpponentNearestTo(home_pos, 1, &dist_opp_to_home);

//  bool iamfastest = false;
//  if (self_min < mate_min && self_min < opp_min)
//  {
//      iamfastest = true;
//  }
//
//  if ((!wm.existKickableTeammate() && self_min < 3) //4->3
//      || iamfastest )
//  {
//    rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": intercept");
//    if ( Body_Intercept2009().execute(agent) )
//    {
//        agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
//        return true;
//    }
//
//  }

  if ( self_min < mate_min
       && opp
//       && self_min <= opp_min       // == or <= ?
       && opp->unum() == fastest_opp->unum() )
//       && Body_Intercept2009().execute(agent) )
  {
      if ( self_min + 2 <= opp_min
           && Body_Intercept2009().execute(agent) )
      {
          agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
#ifdef DEBUG2014
            std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": (markcloseopp)Body_Intercept2009\n";
#endif // DEBUG2014

          return true;
      }
      else if ( self_min <= opp_min )
      {
#ifdef DEBUG2014
            std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": 要不要去截球？\n";
#endif // DEBUG2014

      }
  }





//  {
//    const double dist_opp_to_ball = (opp ? opp->distFromBall() : 100.0 );
//
//    if ( wm.interceptTable()->isOurTeamBallPossessor() )  //org: wm.existKickableTeammate() 20140919 13:49 testing...
////        && dist_opp_to_ball > 2.5)   //
//    {
//      // not found
//      return Bhv_BasicMove().execute(agent);
//    }
//  }

  ////////////////////////////////////////////////////////

  //check mark mode
  bool mark_mode = false;

  rcsc::Vector2D nearest_opp_pos(rcsc::Vector2D::INVALIDATED);
  if (opp)
  {
    nearest_opp_pos = opp->pos();
  }
  else
  {
     return Bhv_BasicMove().execute(agent);
  }

  // found candidate opponent

  if (nearest_opp_pos.isValid()
      && (dist_opp_to_home < 7.0 )
      && nearest_opp_pos.x + 2.0 > home_pos.x
      && nearest_opp_pos.x + 0.7 > wm.ourDefenseLineX() )
  {
      mark_mode = true;
  }
//  else
//  {
//    rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": mark target not found");
//    // not found
//    return Bhv_BasicMove().execute(agent);
//  }

  ////////////////////////////////////////////////////////
  // check teammate closer than self
//  {
//    bool opp_is_not_danger = (nearest_opp_pos.x > -32.0     // need to change?
//                            || nearest_opp_pos.absY() > 20.0 ); //17->20

    const PlayerPtrCont::const_iterator opps_end = wm.teammatesFromSelf().end();
    for (PlayerPtrCont::const_iterator it = wm.teammatesFromSelf().begin(); it != opps_end; ++it)
    {
      if ( mark_mode
           && nearest_opp_pos.dist2((*it)->pos()) > wm.self().pos().dist2((*it)->pos()) )
      {
        continue;
      }

//      Vector2D mate_home_pos  = Strategy::i().getPosition( (*it)->unum() );

//      double dist_opp_to_mate_home_pos = nearest_opp_pos.dist( mate_home_pos );
      double dist_opp_to_it = nearest_opp_pos.dist( (*it)->pos() );

      if ( dist_opp_to_it <= dist_opp_to_home
           && (*it)->unum() <= 5 )
      {
          mark_mode = false;
      }
      else if ( nearest_opp_pos.x > -32.0
                && nearest_opp_pos.dist( (*it)->pos() ) < 1.7 )
      {
          mark_mode = false;
      }

    }

    // basic_move
    if ( !mark_mode )
    {
        return Bhv_BasicMove().execute(agent);
    }
//  }

  ////////////////////////////////////////////////////////
  //decide block point
//  rcsc::AngleDeg block_angle = (wm.ball().pos() - nearest_opp_pos).th();
  Vector2D base_point(-52.5, 0.0);

  const double dist_x = wm.ball().pos().x - nearest_opp_pos.x;
  const double dist_y = wm.ball().pos().y - nearest_opp_pos.y;

  if ( dist_x < 5.0
       && std::fabs( dist_y ) > 6.0
       && std::fabs( dist_y ) > std::fabs( dist_x ) * 2.0
       || wm.interceptTable()->isOurTeamBallPossessor() )
  {
      base_point = wm.ball().pos();      //20141002 17:02 testing...
  }
  AngleDeg block_angle = ( base_point - nearest_opp_pos + opp->vel() ).th();    //20140919 12:08 testing...

  Vector2D block_point = nearest_opp_pos + Vector2D::polar2vector( 0.35, block_angle ); //0.35?
  block_point += opp->vel();
  block_point.x -= 0.1;

  if ( block_point.x < wm.self().pos().x
       && wm.self().pos().x < nearest_opp_pos.x )
  {
      //avoid back testing...
      block_point.x = wm.self().pos().x;
  }

  ////////////////////////////////////////////////////////
//  if (block_point.x < wm.self().pos().x - 1.5)
//  {
//    block_point.y = wm.self().pos().y;
//  }

  //decide dashpower
  double dash_power = rcsc::ServerParam::i().maxPower() * 0.9;
  double x_diff = block_point.x - wm.self().pos().x;

  if (x_diff > 20.0)
  {
    dash_power *= 0.5;
  }
  else if (x_diff > 10.0)
  {
    dash_power *= 0.5;
  }
  else
  {
    dash_power *= 0.7;
  }

#if 1
  //20140927  testing...
  if ( fastest_opp )
  {
     double dash_power = rcsc::ServerParam::i().maxPower() * 1.5;
//     std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": mark(with 1.5*power.\n";
  }

#endif // 1

//  rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": mark to (%.1f, %.1f)",
//      block_point.x, block_point.y);

  double dist_thr = wm.ball().pos().dist( wm.self().pos() ) * 0.1;
  if ( dist_thr < 0.5 )
  {
      dist_thr = 0.5; //0.5 or 1.0?
  }

  agent->debugClient().addMessage("marking");
  agent->debugClient().setTarget(block_point);
  agent->debugClient().addCircle(block_point, dist_thr);

  if (!rcsc::Body_GoToPoint(block_point, dist_thr, dash_power).execute(agent))
  {
    if ( ! Body_TurnToBall().execute(agent) )
    {
        #ifdef DEBUG2014
        std::cerr << "#######是不是因为这个原因？？#########\n\n";
        #endif // DEBUG2014

        return Bhv_BasicMove().execute( agent );
    }
  }
  agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
  #ifdef DEBUG2014
  std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum()
            << ": markto " << block_point.x << ',' << block_point.y << std::endl;
  #endif // DEBUG2014

  return true;
}


