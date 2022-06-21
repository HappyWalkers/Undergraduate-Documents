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

#include "role_side_back.h"
#include <rcsc/action/body_clear_ball.h>
#include "strategy.h"
#include "bhv_basic_offensive_kick.h"
#include "bhv_basic_tackle.h"
#include "role_side_back_move.h"
#include "role_offensive_half_move.h"
#include "bhv_dangerAreaTackle.h"
#include "bhv_basic_move.h"
#include <rcsc/action/body_intercept.h>
#include <rcsc/action/basic_actions.h>
#include <rcsc/action/bhv_go_to_point_look_ball.h>
#include <rcsc/action/body_go_to_point2010.h>  //add
#include <rcsc/action/bhv_scan_field.h>
#include <rcsc/action/body_go_to_point.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/body_clear_ball2009.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_ball_or_scan.h>
#include <rcsc/action/neck_turn_to_player_or_scan.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>
#include <rcsc/action/body_intercept2009.h>
#include <rcsc/formation/formation.h>
#include "role_center_back_move.h"
#include <rcsc/player/player_agent.h>
#include <rcsc/player/intercept_table.h>
#include <rcsc/player/debug_client.h>
#include <iostream>
#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/line_2d.h>
#include <rcsc/geom/ray_2d.h>
#include <rcsc/soccer_math.h>
#include <rcsc/math_util.h>
#include "neck_offensive_intercept_neck.h"

using namespace rcsc;

/*-------------------------------------------------------------------*/
/*!

 */
void
rolesidebackmove::doBasicMove(rcsc::PlayerAgent * agent,
    const rcsc::Vector2D & home_pos)
{
//  rcsc::dlog.addText(rcsc::Logger::ROLE, __FILE__": doBasicMove");

  const rcsc::WorldModel & wm = agent->world();

  //-----------------------------------------------
  // tackle
  if (Bhv_BasicTackle(0.85, 60.0).execute(agent))
  {
    return;
  }

  //--------------------------------------------------
  // intercept

  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();

  if (self_min <= 3
      || (self_min < 20
          && (self_min < mate_min || (self_min < mate_min + 3 && mate_min > 3))
          && self_min <= opp_min + 1)
      || (self_min < mate_min && opp_min >= 2 && self_min <= opp_min + 1))
  {
//    rcsc::dlog.addText(rcsc::Logger::ROLE, __FILE__": doBasicMove() intercept");
    Body_Intercept2009().execute(agent);
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
    return;
  }

  /*--------------------------------------------------------*/
  if (self_min > mate_min)
  {
    rolecenterbackmove().doMarkMove(agent, home_pos);
  }
//  if (doBlockPassLine(agent, home_pos))
//  {
//    return;
//  }

  // decide move target point
  rcsc::Vector2D target_point = getBasicMoveTarget(agent, home_pos);

  // decide dash power
  double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);
  // decide threshold
  double dist_thr = std::fabs(wm.ball().pos().x - wm.self().pos().x) * 0.1; //wm.ball().distFromSelf() * 0.1;
  if (dist_thr < 1.0)
    dist_thr = 1.0;

//  agent->debugClient().addMessage("%.0f", dash_power);
//  agent->debugClient().setTarget(target_podaint);
//  agent->debugClient().addCircle(target_point, dist_thr);

  if (!rcsc::Body_GoToPoint(target_point, dist_thr, dash_power).execute(agent))
  {
    rcsc::AngleDeg body_angle = (
        wm.ball().pos().y < wm.self().pos().y ? -90.0 : 90.0 );
    rcsc::Body_TurnToAngle(body_angle).execute(agent);
  }

  if (wm.ball().distFromSelf() < 20.0
      && (wm.existKickableOpponent() || opp_min <= 3))
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
rcsc::Vector2D
rolesidebackmove::getBasicMoveTarget(rcsc::PlayerAgent * agent,
    const rcsc::Vector2D & home_pos)
{
  const rcsc::WorldModel & wm = agent->world();

  rcsc::Vector2D target_point = home_pos;

  const int opp_min = wm.interceptTable()->opponentReachCycle();

  const rcsc::Vector2D opp_trap_pos = (
      opp_min < 100 ?
          wm.ball().inertiaPoint(opp_min) : wm.ball().inertiaPoint(20) );

  // decide wait position
  // adjust to the defence line

  if (wm.ball().pos().x < 10.0 && -36.0 < home_pos.x && home_pos.x < 10.0
      && wm.self().pos().x > home_pos.x
      && wm.ball().pos().x > wm.self().pos().x + 3.0)
  {
    // make static line
    double tmpx = home_pos.x;
    for (double x = -12.0; x > -27.0; x -= 8.0)
    {
      if (opp_trap_pos.x > x + 1.0)
      {
        tmpx = x - 3.3;
        break;
      }
    }

    target_point.x = tmpx;

//    agent->debugClient().addMessage("LineDef%.1f", target_point.x);
  }
  else
  {
//    agent->debugClient().addMessage("SB:Normal");
  }

  const bool is_left_side = agent->config().playerNumber() == 4;
  const rcsc::PlayerPtrCont::const_iterator end = wm.opponentsFromSelf().end();

  double first_x = 100.0;

  for (rcsc::PlayerPtrCont::const_iterator it = wm.opponentsFromSelf().begin();
      it != end; ++it)
      {
    if ((*it)->pos().x < first_x)
      first_x = (*it)->pos().x;
  }

  double max_y = 1.0;

  for (rcsc::PlayerPtrCont::const_iterator it = wm.opponentsFromSelf().begin();
      it != end; ++it)
      {
    if (is_left_side && (*it)->pos().y > 0.0)
      continue;
    if (!is_left_side && (*it)->pos().y < 0.0)
      continue;

    //if ( (*it)->pos().x > target_point.x + 15.0 ) continue;
    if ((*it)->pos().x > first_x + 15.0)
      continue;

    if ((*it)->pos().absY() > max_y)
    {
//      dlog.addText( Logger::ROLE,
//          __FILE__": getBasicMoveTarget. updated max y. opp=%d(%.1f %.1f)",
//          (*it)->unum(),
//          (*it)->pos().x, (*it)->pos().y );
      max_y = (*it)->pos().absY();
    }
  }

  if (max_y > 0.0 && max_y < target_point.absY())
  {
    target_point.y = (is_left_side ? -max_y + 0.5 : max_y - 0.5 );
//    dlog.addText( Logger::ROLE,
//        __FILE__": getBasicMoveTarget. shrink formation y. %.1f",
//        target_point.y );
//    agent->debugClient().addMessage( "ShrinkY" );
  }

  return target_point;
}

/*-------------------------------------------------------------------*/
/*!

 */
bool
rolesidebackmove::doBlockPassLine(rcsc::PlayerAgent * agent,
    const rcsc::Vector2D & home_pos)
{
 // cout << "blockPassLine" << endl;
  const rcsc::WorldModel & wm = agent->world();

//  if (wm.ball().pos().x < 12.0)
//  {
//    return false;
//  }

//  if (wm.ball().pos().x < home_pos.x + 15.0)
//  {
//    return false;
//  }

  rcsc::Vector2D target_point = home_pos;

  const rcsc::PlayerObject * nearest_attacker =
      static_cast<const rcsc::PlayerObject *>(0);
  double min_dist2 = 100000.0;

  const rcsc::PlayerObject * outside_attacker =
      static_cast<const rcsc::PlayerObject *>(0);

  const bool is_left_side = agent->world().self().unum() == 4;

//  rcsc::dlog.addText(rcsc::Logger::ROLE,
//      __FILE__": doBlockPassLine() side = %s", is_left_side ? "left" : "right");

  const rcsc::PlayerPtrCont::const_iterator end = wm.opponentsFromSelf().end();
  for (rcsc::PlayerPtrCont::const_iterator it = wm.opponentsFromSelf().begin();
      it != end; ++it)
      {
    bool same_side = false;
    if (is_left_side && (*it)->pos().y < 0.0)
      same_side = true;
    if (!is_left_side && (*it)->pos().y > 0.0)
      same_side = true;

//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doBlockPassLine. check player %d (%.1f %.1f)", (*it)->unum(),
//        (*it)->pos().x, (*it)->pos().y);

    if (same_side && (*it)->pos().x < wm.ourDefenseLineX() + 20.0
        && (*it)->pos().absY() > home_pos.absY() - 5.0)
    {
      outside_attacker = *it;
//      rcsc::dlog.addText(rcsc::Logger::ROLE,
//          __FILE__": doBlockPassLine. found outside attacker %d (%.1f %.1f)",
//          outside_attacker->unum(), outside_attacker->pos().x,
//          outside_attacker->pos().y);
    }

    if ((*it)->pos().x > wm.ourDefenseLineX() + 10.0)
    {
      if ((*it)->pos().x > home_pos.x)
        continue;
    }
    if ((*it)->pos().x > home_pos.x + 10.0)
      continue;
    if ((*it)->pos().x < home_pos.x - 20.0)
      continue;
    if (std::fabs((*it)->pos().y - home_pos.y) > 20.0)
      continue;

    double d2 = (*it)->pos().dist(home_pos);
    if (d2 < min_dist2)
    {
      min_dist2 = d2;
      nearest_attacker = *it;
    }
  }

  bool block_pass = false;

  if (nearest_attacker)
  {
    block_pass = true;
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doBlockPassLine. exist nearest attacker %d (%.1f %.1f)",
//        nearest_attacker->unum(), nearest_attacker->pos().x,
//        nearest_attacker->pos().y);
  }

  if (outside_attacker && nearest_attacker != outside_attacker)
  {
    block_pass = false;
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doBlockPassLine. exist outside attacker %d (%.1f %.1f)",
//        outside_attacker->unum(), outside_attacker->pos().x,
//        outside_attacker->pos().y);
    return false;
  }

  if (!block_pass)
  {
    return false;
  }

  if (nearest_attacker->isGhost() && wm.ball().distFromSelf() > 30.0)
  {
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doBlockPassLine. ghost opponent. scan field");
//    agent->debugClient().addMessage("ScanOpp");
    rcsc::Bhv_ScanField().execute(agent);
    return true;
  }

  if (home_pos.x - nearest_attacker->pos().x > 5.0)
  {
#if 0
    rcsc::Line2D block_line( nearest_attacker->pos(), wm.ball().pos() );
    target_point.x = nearest_attacker->pos().x + 5.0;
    target_point.y = block_line.getY( target_point.x );
    target_point.y += ( home_pos.y - nearest_attacker->pos().y ) * 0.5;
#else
    target_point = nearest_attacker->pos()
        + (wm.ball().pos() - nearest_attacker->pos()).setLengthVector(1.0);
#endif
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doBlockPassLine.  block pass line front");
//    agent->debugClient().addMessage("BlockPassFront");
  }
  else if (wm.ball().pos().x - nearest_attacker->pos().x > 15.0)
  {
    target_point = nearest_attacker->pos()
        + (wm.ball().pos() - nearest_attacker->pos()).setLengthVector(1.0);
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doBlockPassLine.  block pass line");
//    agent->debugClient().addMessage("BlockPass");
  }
  else
  {
    const rcsc::Vector2D goal_pos(-50.0, 0.0);

    target_point = nearest_attacker->pos()
        + (goal_pos - nearest_attacker->pos()).setLengthVector(1.0);
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doBlockPassLine.  block through pass");
//    agent->debugClient().addMessage("BlockThrough");
  }

  double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);
  double dist_thr = nearest_attacker->distFromSelf() * 0.1;
  if (dist_thr < 1.0)
    dist_thr = 1.0;

//  agent->debugClient().addMessage("%.0f", dash_power);
//  agent->debugClient().setTarget(target_point);
//  agent->debugClient().addCircle(target_point, dist_thr);

  if (!rcsc::Body_GoToPoint(target_point, dist_thr, dash_power).execute(agent))
  {
    rcsc::AngleDeg body_angle = (
        wm.ball().pos().y < wm.self().pos().y ? -90.0 : 90.0 );
    rcsc::Body_TurnToAngle(body_angle).execute(agent);
  }

  if (wm.ball().distFromSelf() < 20.0)
  {
    agent->setNeckAction(new rcsc::Neck_TurnToBall());
  }
  else if (nearest_attacker->posCount() >= 5)
  {
    agent->setNeckAction(
        new rcsc::Neck_TurnToPlayerOrScan(nearest_attacker, 5));
  }
  else
  {
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
  }

  return true;
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolesidebackmove::doCrossBlockAreaMove(rcsc::PlayerAgent * agent,
    const rcsc::Vector2D & home_pos)
{
  const rcsc::WorldModel & wm = agent->world();
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
//  if (wm.ball().pos().x < wm.self().pos().x
//      && agent->world().ball().pos().y * home_pos.y > 0.0
//      && fabs(wm.ball().pos().x - wm.self().pos().x) > 3
//      && fabs(wm.ball().pos().y) > 10)
//  {
//    Vector2D Pos = wm.ball().pos() + wm.ball().vel() * 2.5;
//    Body_GoToPoint(Pos, 0.1, rcsc::ServerParam::i().maxPower());
//  }


  //-----------------------------------------------
  // tackle
  if (Bhv_DangerAreaTackle(0.9).execute(agent))
  {
    return;
  }

//  const rcsc::WorldModel & wm = agent->world();

  //--------------------------------------------------
  // intercept
  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();

  if ( wm.interceptTable()->isSelfFastestPlayer()
       && Body_Intercept2009().execute( agent ) )
  {
      //这里木有return！！
      #ifdef DEBUG2014
      std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_Intercept2009(testing...)\n";
      #endif // DEBUG2014

  }

#if 1
    //  20140927
  if (fastest_opp)
  {
     Vector2D target_point = fastest_opp->pos() + wm.ball().pos() ;
     double dash_power = rcsc::ServerParam::i().maxPower();
     rolecenterbackmove().doGoToPoint(agent, target_point, 0.1,dash_power, 15.0);
     #ifdef DEBUG2014
     std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doGoToPoint.\n";
     #endif // DEBUG2014
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
           #ifdef DEBUG2014
           std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_GoToPoint.\n";
           #endif // DEBUG2014

            return;
       }

    }
#endif  //1

#if 1
    if ( wm.ball().pos().x < wm.self().pos().x -5.0 )       //ht:20140830 02:58
    {
        if ( agent->world().ball().pos().y * home_pos.y > 0.0       //same side
                && wm.ball().pos().absY() > 10 )
        {
            //when opp begin fast attack, 4/5 go back!
            Vector2D adjust(0.0, 0.0);
            if ( wm.ball().vel().y * wm.self().pos().y < 0.0 )  //ht:20140830 01:56
            {
                adjust = wm.ball().vel() + wm.ball().vel();
            }
            else
            {
//                adjust.y = wm.ball().vel().y;
                adjust.x = 2.0 * wm.ball().vel().x;
            }
            Vector2D Pos = wm.ball().pos() + adjust; //wm.ball().vel() * 2.5;     //vel*2 at 20140814 testing....
    //        std::cerr << __FILE__ << wm.time().cycle() << "is there any use??? \n";
            Body_GoToPoint(Pos, 0.1, rcsc::ServerParam::i().maxPower() * 1.5 );
            agent->setNeckAction( new Neck_TurnToBallOrScan());
        }


    }
    else  if (wm.ball().pos().x < wm.self().pos().x -3.0
        && agent->world().ball().pos().y * home_pos.y > 0.0 //same side
        && wm.ball().pos().absY() > 10)    //modified by ht at 20140814
    {
        //when opp begin fast attack, 4/5 go back!
        Vector2D adjust(0.0, 0.0);
        if ( wm.ball().vel().y * wm.self().pos().y < 0.0 )  //ht:20140830 01:56 //need to change!!跑动不连贯
        {
            adjust = wm.ball().vel() + wm.ball().vel();
        }
        else
        {
            adjust.y = wm.ball().vel().y;
            adjust.x = 2.0 * wm.ball().vel().x;
        }
        Vector2D Pos = wm.ball().pos() + adjust; //wm.ball().vel() * 2.5;     //vel*2 at 20140814 testing....
//        std::cerr << __FILE__ << wm.time().cycle() << "is there any use??? \n";
        Body_GoToPoint(Pos, 0.1, rcsc::ServerParam::i().maxPower());
        agent->setNeckAction( new Neck_TurnToBallOrScan());
    }
#endif //1

  if (wm.self().unum() == 5 && wm.ball().pos().y < -1.0)
  {
    if (nearest_opp_dist < 3.0)
    {
        rolecenterbackmove().doMarkMove(agent, home_pos);
//        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doMarkMove(1)\n";
    }
    else
    {
     Body_GoToPoint(nearest_opp_pos, 0.5, rcsc::ServerParam::i().maxPower());
    }
  }
  if (wm.self().unum() == 4 && wm.ball().pos().y > 1.0)
  {
    if (nearest_opp_dist < 3.0)
    {
        rolecenterbackmove().doMarkMove(agent, home_pos);
//        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doMarkMove(2)\n";
    }
    else
    {
     Body_GoToPoint(nearest_opp_pos, 0.5, rcsc::ServerParam::i().maxPower());
    }
  }

  if (self_min < mate_min && self_min < opp_min
      || self_min <= 2 && wm.ball().pos().absY() < 20.0)
  {
    //Body_Intercept2009().execute(agent);
    Body_GoToPoint2010(wm.ball().pos(),0.1,ServerParam::i().maxDashPower());
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
    return;
  }
  if (wm.ball().pos().absY() > 20.0 && self_min < mate_min && (self_min < opp_min + 1.0 || self_min <= 3.0))
  {
//    std::cerr<<"Body_Intercept"<<std::endl;
    Body_Intercept2009().execute(agent);
    //Body_GoToPoint2010(wm.ball().pos(),0.1,ServerParam::i().maxDashPower());
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
    return;
  }
  if (wm.ball().pos().absY() > 24.0 && self_min < mate_min && !wm.existKickableTeammate())
  {
    double dash_power = rcsc::ServerParam::i().maxPower();
    Vector2D Pos = wm.ball().pos() + wm.ball().vel();
    double dist_thr = wm.ball().pos().dist(Pos) * 0.1;
    if (dist_thr < 0.5)
      dist_thr = 0.5;
    Body_GoToPoint(Pos, dist_thr,dash_power);
    return ;
  }

  //-----------------------------------------
  // set move point

  rcsc::Vector2D center(-41.5, 0.0);

  int min_cyc = std::min(mate_min, opp_min);

  rcsc::Vector2D ball_future = rcsc::inertia_n_step_point(wm.ball().pos(),
      wm.ball().vel(), min_cyc, rcsc::ServerParam::i().ballDecay());

  if (ball_future.y * home_pos.y < 0.0)
  {
    rolecenterbackmove().doMarkMove(agent, home_pos);
//    std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doMarkMove(3)\n";
    return;
  }

  if (ball_future.x < -45.0)
  {
    center.x = ball_future.x + 0.5;
    center.x = std::max(-48.0, center.x);
  }

  rcsc::Line2D block_line(ball_future, center);
  rcsc::Vector2D block_point = home_pos;

#if 1
  block_point.y = ball_future.absY() - 6.0;
  block_point.y = std::max(block_point.y, 15.0);
#elif 0
  block_point.y = ball_future.absY() - 7.0;
  block_point.y = std::max( block_point.y, 18.0 );
  block_point.y = std::min( block_point.y, home_pos.absY() );
  block_point.y = std::min( ball_future.absY() - 2.0, block_point.y );
#elif 0
  block_point.y = ball_future.absY() - 5.0;
  block_point.y = std::max( block_point.y, 20.0 );
  block_point.y = std::min( ball_future.absY() - 2.0, block_point.y );
#else
  block_point.y = ball_future.absY() - 10.0;
  block_point.y = std::max( block_point.y, 15.0 );
#endif
  if (ball_future.y < 0.0)
    block_point.y *= -1.0;

  block_point.x = block_line.getX(block_point.y);

#if 1
  if (block_point.x < wm.self().pos().x - 3.0)
  {
    rcsc::Ray2D blockLine2(wm.self().pos(), wm.self().body());
    rcsc::Vector2D intersect = blockLine2.intersection(block_line);
    if (intersect.isValid() && 15 < intersect.absY()
        && intersect.absY() < ball_future.absY())
    {
      block_point = intersect;
    }
  }
#endif

  //------------------------------------------
  // set dash power
  double dash_power = rcsc::ServerParam::i().maxPower();
  if (wm.self().pos().x < block_point.x + 5.0)
  {
    dash_power -= wm.ball().distFromSelf() * 2.0;
    dash_power = std::max(20.0, dash_power);
  }

  double dist_thr = wm.ball().distFromSelf() * 0.07;
  if (dist_thr < 0.8)
    dist_thr = 0.8;

  if((wm.ourDefenseLineX()+2 > wm.ball().pos().x ||
         		Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_Danger)
         		&& !wm.existKickableTeammate())                                                         //add
          dash_power = ServerParam::i().maxPower();

  if (!rcsc::Body_GoToPoint(block_point, dist_thr, dash_power).execute(agent))
  {
    rcsc::AngleDeg body_angle = (
        wm.ball().angleFromSelf().abs() < 80.0 ? 0.0 : 180.0 );
    rcsc::Body_TurnToAngle(body_angle).execute(agent);
  }

  agent->setNeckAction(new rcsc::Neck_TurnToBall());
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolesidebackmove::doDangerAreaMove(rcsc::PlayerAgent * agent,
    const rcsc::Vector2D & home_pos)
{
//  rcsc::dlog.addText(rcsc::Logger::ROLE, __FILE__": doDangerAreaMove()");

  //-----------------------------------------------
  // tackle
  if (Bhv_DangerAreaTackle().execute(agent))
  {
    return;
  }

  const rcsc::WorldModel & wm = agent->world();

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

  const bool ball_is_same_side = (wm.ball().pos().y * home_pos.y > 0.0 );

  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();



#if 1
    //ht: 20140903 21:00 testing...

    if ( !ball_is_same_side )
    {
        if ( wm.ball().vel().x < -1.0 )
        {
            bool ball_will_be_in_my_goal = false;
            const Line2D ball_line( wm.ball().pos(), wm.ball().vel().th() );
            int endline_y = ball_line.getY( -51.5 );

            if ( endline_y < 7.0 )
            {
                ball_will_be_in_my_goal = true;
            }

            if ( ball_will_be_in_my_goal )
            {
                Vector2D target_point = wm.self().pos();
                target_point.x = -51.5;
                target_point.y = endline_y ;  //testing...

                if ( Body_GoToPoint( target_point,
                                    0.1,    //
                                    ServerParam::i().maxDashPower() * 1.5
                                    ).execute( agent ) )
                {
                    agent->setNeckAction( new Neck_TurnToBall() );
                    #ifdef DEBUG2014
                    std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Danger Situation Move\n\n";
                    #endif // DEBUG2014

                    return;
                }

            }
        }
        else if ( roleoffensivehalfmove().markCloseOpp( agent ) )
        {
//            rolecenterbackmove().doMarkMove( agent, home_pos );
            #ifdef DEBUG2014
            std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doMarkMove\n";
            #endif // DEBUG2014

            return;
        }

    }


#endif // 1

  //--------------------------------------------------
  // intercept
  if (!wm.existKickableOpponent()
       && !wm.existKickableTeammate()
       && self_min <= mate_min
       && self_min <= opp_min)
  {
    rcsc::Line2D ball_line(wm.ball().pos(), wm.ball().vel().th());
    double goal_line_y = ball_line.getY( rcsc::ServerParam::i().pitchHalfLength() );

    if (std::fabs(goal_line_y) < rcsc::ServerParam::i().goalHalfWidth() + 1.5)
    {
      if (Body_Intercept2009().execute(agent))
      {
        agent->setNeckAction(new rcsc::Neck_TurnToBall());
        return;
      }
    }
  }

//  //--------------------------------------------------
//  // intercept
//
//  if (ball_is_same_side && !wm.existKickableTeammate() && self_min <= 3
//      && self_min <= opp_min)
//  {
//    rcsc::Body_ClearBall().execute(agent);
//    return;
////    rcsc::dlog.addText(rcsc::Logger::ROLE,
////        __FILE__": doDangerAreaMove() ball is same side. try get");
////    if (Body_Intercept2009().execute(agent))
////    {
////      agent->debugClient().addMessage("DangerGetBall(1)");
////      agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
////      return;
////    }
//  }

  //--------------------------------------------------
  // attack ball


  const rcsc::PlayerObject * fastest_opp =
      wm.interceptTable()->fastestOpponent();
  Vector2D ballPos = wm.ball().pos();
  double disToFastestOpp = wm.self().pos().dist(fastest_opp->pos());
  if (opp_min <= 1 && fastest_opp && wm.self().pos().x < wm.ball().pos().x + 3.0
      && wm.self().pos().absY() < wm.ball().pos().absY()
      && wm.ball().distFromSelf() < 3.0)
  {
    rcsc::Vector2D attack_pos = ballPos + wm.ball().vel();
//
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doDangerAreaMove() exist dangerous opp. attack.");
//    agent->debugClient().addMessage("DangetAttack");
//    agent->debugClient().setTarget(attack_pos);
  //  cout << "attack opp" << endl;
    if (!rcsc::Body_GoToPoint(attack_pos, 0.1,
        rcsc::ServerParam::i().maxPower()).execute(agent))
    {
      rcsc::Body_TurnToPoint(attack_pos).execute(agent);
    }
    agent->setNeckAction(new rcsc::Neck_TurnToBall());
    return;
  }


  //--------------------------------------------------
  const double nearest_opp_dist = wm.getDistOpponentNearestToSelf(10);
  if (disToFastestOpp > nearest_opp_dist + 1 && self_min > mate_min + 1)
  {
    rolecenterbackmove().doMarkMove(agent, home_pos);
//    std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doMarkMove(1)\n";
    return;
  }
  if (nearest_opp_dist > 5.0 && self_min < opp_min)
  {
    Body_Intercept2009().execute(agent);
//    agent->debugClient().addMessage("DangerGetBall(2)");
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
    return;
  }

  //--------------------------------------------------
  if (ball_is_same_side && wm.ball().pos().x < -44.0
      && wm.ball().pos().absY() < 18.0 && !wm.existKickableTeammate())
  {
    rcsc::Body_ClearBall2009().execute(agent);
//    rcsc::dlog.addText(
//        rcsc::Logger::ROLE,
//        __FILE__": doDangerAreaMove() ball is same side. and very danger. try intercept");
//    if (Body_Intercept2009().execute(agent))
//    {
//      agent->debugClient().addMessage("DangerGetBall(3)");
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
//      return;
//    }
  }

  //--------------------------------------------------
  bool pole_block = true;
  if (opp_min <= 10)
  {
    rcsc::Vector2D opp_trap_pos = wm.ball().inertiaPoint(opp_min);
    if (opp_trap_pos.x > -40.0)
    {
//      rcsc::dlog.addText(rcsc::Logger::ROLE,
//          __FILE__": doDangerAreaMove() no pole block");
      pole_block = false;
    }
  }

  //--------------------------------------------------
  if (!pole_block
      || (ball_is_same_side
          && wm.ball().pos().absY() > rcsc::ServerParam::i().goalHalfWidth()))
  {
    double dash_power = wm.self().getSafetyDashPower(
        rcsc::ServerParam::i().maxPower());
    // I am behind of ball
    if (wm.self().pos().x < wm.ball().pos().x)
    {
      dash_power *= std::min(1.0, 7.0 / wm.ball().distFromSelf());
      dash_power = std::max(30.0, dash_power);
    }
    double dist_thr = wm.ball().distFromSelf() * 0.07;
    if (dist_thr < 0.5)
      dist_thr = 0.5;

//    agent->debugClient().addMessage("DangerGoHome%.0f", dash_power);
//    agent->debugClient().setTarget(home_pos);
//    agent->debugClient().addCircle(home_pos, dist_thr);
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doDangerAreaMove. go to home");

    if (!rcsc::Body_GoToPoint(home_pos, dist_thr, dash_power).execute(agent))
    {
      rcsc::Body_TurnToBall().execute(agent);
    }
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
    return;
  }

  //--------------------------------------------------
  // block opposite side goal
  rcsc::Vector2D goal_post(-rcsc::ServerParam::i().pitchHalfLength(),
      rcsc::ServerParam::i().goalHalfWidth() - 0.8);
  if (home_pos.y < 0.0)
  {
    goal_post.y *= -1.0;
  }

  rcsc::Line2D block_line(wm.ball().pos(), goal_post);
  rcsc::Vector2D block_point(-48.0, 0.0);
//  rcsc::dlog.addText(rcsc::Logger::ROLE,
//      __FILE__": doDangerAreaMove. block goal post. original_y = %.1f",
//      block_line.getY(block_point.x));
  block_point.y = rcsc::min_max(home_pos.y - 1.0,
      block_line.getY(block_point.x), home_pos.y + 1.0);

//  rcsc::dlog.addText(rcsc::Logger::ROLE,
//      __FILE__": doDangerAreaMove. block goal");
//  agent->debugClient().addMessage("DangerBlockPole");
//  agent->debugClient().setTarget(block_point);
//  agent->debugClient().addCircle(block_point, 1.0);

  double dash_power = wm.self().getSafetyDashPower(
      rcsc::ServerParam::i().maxPower());
#if 1
  if (wm.self().pos().x < 47.0
      && wm.self().stamina() > rcsc::ServerParam::i().staminaMax() * 0.7)
  {
    if (wm.self().pos().dist(block_point) > 0.8)
    {
//      rcsc::dlog.addText(rcsc::Logger::ROLE,
//          __FILE__": doDangerAreaMove block goal with back move");
      rcsc::Bhv_GoToPointLookBall(block_point, 1.0, dash_power).execute(agent);
    }
    else
    {
//      rcsc::dlog.addText(rcsc::Logger::ROLE,
//          __FILE__": doDangerAreaMove. already block goal(1)");
      rcsc::Vector2D face_point(wm.self().pos().x, 0.0);
      rcsc::Body_TurnToPoint(face_point).execute(agent);
      agent->setNeckAction(new rcsc::Neck_TurnToBall());
    }
    return;
  }
#endif
  if (!rcsc::Body_GoToPoint(block_point, 1.0, dash_power, 100, // cycle
      false, // no back mode
      true, // save recovery
      15.0 // dir thr
      ).execute(agent))
  {
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doDangerAreaMove. already block goal(2)");
    rcsc::Vector2D face_point(wm.self().pos().x, 0.0);
    if (wm.self().pos().y * wm.ball().pos().y < 0.0)
    {
      face_point.assign(-52.5, 0.0);
    }

    rcsc::Body_TurnToPoint(face_point).execute(agent);
  }
  agent->setNeckAction(new rcsc::Neck_TurnToBall());
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolesidebackmove::doDribbleBlockAreaMove(rcsc::PlayerAgent * agent,
    const rcsc::Vector2D & home_pos)
{
  const rcsc::WorldModel & wm = agent->world();
  const int self_min = wm.interceptTable()->selfReachCycle();
  const int mate_min = wm.interceptTable()->teammateReachCycle();
  const int opp_min = wm.interceptTable()->opponentReachCycle();
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
  const double fastest_opp_dist = ( fastest_opp
                                      ? fastest_opp->distFromSelf()
                                      : 1000.0 );
  const Vector2D fastest_opp_pos = ( fastest_opp
                                       ? fastest_opp->pos()
                                       : Vector2D( -1000.0, 0.0 ) );


/*if (wm.ball().pos().x < wm.self().pos().x
      && agent->world().ball().pos().y * home_pos.y > 0.0
      && fabs(wm.ball().pos().x - wm.self().pos().x) > 5)
  {
    Vector2D Pos = wm.ball().pos() + wm.ball().vel();
   Body_GoToPoint(Pos, 0.5, rcsc::ServerParam::i().maxPower());
   return;

  }

   // same side
  if (agent->world().ball().pos().y * home_pos.y > 0.0)
  {
    doBlockSideAttacker(agent, home_pos);
  }*/


  // same side
  if (agent->world().ball().pos().y * home_pos.y > 0.0)
  {
      // tackle
      if (Bhv_BasicTackle(0.9, 60.0).execute(agent))
      {
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
        Body_Intercept().execute( agent );
        agent->setNeckAction( new Neck_OffensiveInterceptNeck() );

        return;
      }

      Vector2D target_point = Strategy::i().getPosition( wm.self().unum() );
      double dash_power = Strategy::get_normal_dash_power( wm );
      double dist_thr = wm.ball().distFromSelf() * 0.1;
      if ( dist_thr < 0.5 ) dist_thr = 0.5;

      if(!wm.existKickableTeammate() && wm.ball().pos().x > -4.0 && self_min > mate_min)
      {
         target_point = nearest_opp_pos;
         target_point.x = target_point.x - 1.0;
         dash_power = rolecenterbackmove().get_dash_power(agent, target_point);
         dist_thr = 0.1;
      }
      if(!wm.existKickableTeammate() && self_min < mate_min)
      {
         dash_power = rcsc::ServerParam::i().maxPower();
         target_point = wm.ball().pos() + wm.ball().vel();
         if(wm.ball().pos().x < wm.self().pos().x)
         dash_power = rcsc::ServerParam::i().maxPower()*1.1;
         if(fastest_opp && fastest_opp_pos.x < wm.self().pos().x)
         dash_power = rcsc::ServerParam::i().maxPower()*1.2;
      }
      if(!wm.existKickableTeammate() && self_min < mate_min && wm.ball().pos().x - 1.0 > wm.self().pos().x)
      {
        dash_power = rcsc::ServerParam::i().maxPower()*1.1;
        target_point = wm.ball().pos() + wm.ball().vel();
      }

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

      return;
  }
  else
  {
    doBasicMove(agent, home_pos);
  }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolesidebackmove::doDefensiveMove(rcsc::PlayerAgent * agent)
{
  //ht: 20140831 09:53
  //from: roledefensivehalfmove::doDefensiveMove(rcsc::PlayerAgent * agent)

  const WorldModel & wm = agent->world();
  Vector2D ballPos = wm.ball().pos();
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
  const Vector2D fastest_opp_pos = ( fastest_opp
                                       ? fastest_opp->pos()
                                       : Vector2D( -1000.0, 0.0 ) );

  rcsc::dlog.addText(rcsc::Logger::ROLE, __FILE__": doDefensiveMove");

#if 0
    //ht:20140830 02:58 from BA_CrossBlock and wait to modifiy

    if ( wm.ball().pos().x < wm.self().pos().x -5.0 )
    {
        if ( agent->world().ball().pos().y * home_pos.y > 0.0       //same side
                && wm.ball().pos().absY() > 10 )    //
        {
            //when opp begin fast attack, 4/5 go back!
            Vector2D adjust(0.0, 0.0);
            if ( wm.ball().vel().y * wm.self().pos().y < 0.0 )  //ht:20140830 01:56
            {
                adjust = wm.ball().vel() + wm.ball().vel();
            }
            else
            {
//                adjust.y = wm.ball().vel().y;
                adjust.x = 2.0 * wm.ball().vel().x;
            }
            Vector2D Pos = wm.ball().pos() + adjust; //wm.ball().vel() * 2.5;     //vel*2 at 20140814 testing....
//    //        std::cerr << __FILE__ << wm.time().cycle() << "is there any use??? \n";
            Body_GoToPoint(Pos, 0.1, rcsc::ServerParam::i().maxPower() * 1.3 );
            agent->setNeckAction( new Neck_TurnToBallOrScan());
        }


    }
    else  if (wm.ball().pos().x < wm.self().pos().x -3.0
        && agent->world().ball().pos().y * home_pos.y > 0.0 //same side
        && wm.ball().pos().absY() > 10)    //modified by ht at 20140814
    {
        //when opp begin fast attack, 4/5 go back!
        Vector2D adjust(0.0, 0.0);
        if ( wm.ball().vel().y * wm.self().pos().y < 0.0 )  //ht:20140830 01:56 //need to change!!跑动不连贯
        {
            adjust = wm.ball().vel() + wm.ball().vel();
        }
        else
        {
            adjust.y = wm.ball().vel().y;
            adjust.x = 2.0 * wm.ball().vel().x;
        }
        Vector2D Pos = wm.ball().pos() + adjust; //wm.ball().vel() * 2.5;     //vel*2 at 20140814 testing....
//        std::cerr << __FILE__ << wm.time().cycle() << "is there any use??? \n";
        Body_GoToPoint(Pos, 0.1, rcsc::ServerParam::i().maxPower());
        agent->setNeckAction( new Neck_TurnToBallOrScan());
    }
#endif //1

  //////////////////////////////////////////////////////
  // tackle
  if (Bhv_BasicTackle(0.8, 90.0).execute(agent))
  {
//    //      cout<<"BA_DefMidField-tackle"<<endl;
    return;
  }

  //----------------------------------------------
  // intercept
  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();

#if 1
    //  20140927
  if (fastest_opp)
  {
     Vector2D target_point = fastest_opp->pos() + wm.ball().pos() ;
     double dash_power = rcsc::ServerParam::i().maxPower();
     rolecenterbackmove().doGoToPoint(agent, target_point, 0.1,dash_power, 15.0);
     #ifdef DEBUG2014
     std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doGoToPoint(2).\n";
     #endif

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
           #ifdef DEBUG2014
           std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_GoToPoint.\n";
           #endif

            return;
       }

    }
#endif  //1

  const rcsc::Vector2D self_reach_point = wm.ball().inertiaPoint(self_min);
  const rcsc::Vector2D opp_reach_point = wm.ball().inertiaPoint(opp_min);

  if (!wm.existKickableTeammate())
  {

     if (nearest_opp)
     {
       Body_GoToPoint(nearest_opp_pos, 0.1, rcsc::ServerParam::i().maxPower());
       dlog.addText( Logger::TEAM,
                      __FILE__": intercept" );
        Body_Intercept().execute( agent );
        agent->setNeckAction( new Neck_TurnToBall());

     }
     if (fastest_opp)
     {
       Vector2D Pos = fastest_opp->pos() + fastest_opp->vel();
       Body_GoToPoint(Pos, 0.1, rcsc::ServerParam::i().maxPower());
       dlog.addText( Logger::TEAM,
                      __FILE__": intercept" );
        Body_Intercept().execute( agent );
        agent->setNeckAction( new Neck_TurnToBall());

     }
     else
     {
       Vector2D Pos = wm.ball().pos() + wm.ball().vel();
       double dist_thr = wm.ball().pos().dist(Pos) * 0.1;
       if (dist_thr < 0.5)
       dist_thr = 0.5;
       Body_GoToPoint(Pos, dist_thr, rcsc::ServerParam::i().maxPower());
     }
  }

  if (!wm.existKickableTeammate()
#if 1
      && self_reach_point.dist(home_pos) < 13.0
#endif
      && (self_min < mate_min
          || self_min <= 3 && wm.ball().pos().dist2(home_pos) < 10.0 * 10.0
          || self_min <= 5 && wm.ball().pos().dist2(home_pos) < 8.0 * 8.0))
  {
    if (opp_min < mate_min - 1
        && wm.self().pos().x < wm.theirOffenseLineX())
    {
//      //      cout<<"BA_DefMidField-blockdribble"<<endl;
      rolecenterbackmove().Bhv_BlockDribble(agent);
      agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
//      //      cout<<"BA_DefMidField-blockdribble"<<endl;
      return;
    }
//    //      cout<<"BA_DefMidField-intercept"<<endl;
    Body_Intercept2009().execute(agent);
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
  else if (wm.self().stamina() > rcsc::ServerParam::i().staminaMax() * 0.8)
  {
    dash_power *= 0.8;
  }
  else
  {
    dash_power = wm.self().playerType().staminaIncMax();
    dash_power *= wm.self().recovery();
    dash_power *= 0.9;
  }

  // save recovery
  dash_power = wm.self().getSafetyDashPower(dash_power);
  if((wm.ourDefenseLineX()+2 > wm.ball().pos().x ||
         		Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_Danger)
         		&& !wm.existKickableTeammate())                                                         //add
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
rolesidebackmove::doDefMidAreaMove(rcsc::PlayerAgent * agent,
    const rcsc::Vector2D & home_pos)
{
  if (agent->world().ball().pos().x < agent->world().self().pos().x + 15.0
      && agent->world().ball().pos().y * home_pos.y > 0.0 // same side
  && agent->world().ball().pos().absY() > 7.0
      && agent->world().self().stamina()
          > rcsc::ServerParam::i().staminaMax() * 0.6)
  {
    doBlockSideAttacker(agent, home_pos);
  }
  else
  {
    doBasicMove(agent, home_pos);
  }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
rolesidebackmove::doBlockSideAttacker(rcsc::PlayerAgent * agent,
    const rcsc::Vector2D & home_pos)
{
//  rcsc::dlog.addText(rcsc::Logger::ROLE, __FILE__": doBlockSideAttacker()");

  const rcsc::WorldModel & wm = agent->world();

  //-----------------------------------------------
  // tackle
  if (Bhv_BasicTackle(0.9, 60.0).execute(agent))
  {
    return;
  }

  //--------------------------------------------------
  // intercept

  int self_min = wm.interceptTable()->selfReachCycle();
  int mate_min = wm.interceptTable()->teammateReachCycle();
  int opp_min = wm.interceptTable()->opponentReachCycle();

  if (self_min < opp_min && self_min < mate_min)
  {
//    agent->debugClient().addMessage("BlockGetBall(1)");
    Body_Intercept2009().execute(agent);
    agent->setNeckAction(new rcsc::Neck_TurnToBall());
    return;
  }

  rcsc::Vector2D ball_get_pos = wm.ball().inertiaPoint(self_min);
  rcsc::Vector2D opp_reach_pos = wm.ball().inertiaPoint(opp_min);

  if (((self_min <= 4 && opp_min >= 4))
//      || self_min <= 2)
      && wm.self().pos().x < ball_get_pos.x
      && wm.self().pos().x < wm.ball().pos().x - 0.2
      && (std::fabs(wm.ball().pos().y - wm.self().pos().y) < 1.5
          || wm.ball().pos().absY() < wm.self().pos().absY()))
  {
//    agent->debugClient().addMessage("BlockGetBall(2)");
    Body_Intercept2009().execute(agent);
    agent->setNeckAction(new rcsc::Neck_TurnToBall());
    return;
  }

#if 0
  if ( opp_min < mate_min - 1
      && opp_min < self_min - 1 )
  {
    if ( opp_reach_pos.absY() > 20.0
        && opp_reach_pos.x < home_pos.x + 5.0
        && ( std::fabs( opp_reach_pos.y - home_pos.y ) < 10.0
            || ( opp_reach_pos.y * home_pos.y > 0.0
                && opp_reach_pos.absY() > home_pos.absY() )
        )
    )
    {
      agent->debugClient().addMessage( "DribBlock" );
      if ( Bhv_BlockDribble().execute( agent ) )
      {
        return;
      }
    }
  }
#endif

  if (wm.self().pos().x < wm.ball().pos().x - 5.0
      || (home_pos.x < wm.ball().pos().x - 5.0 && wm.self().pos().x < home_pos.x))
  {
//    agent->debugClient().addMessage("BlockToBasic");
    doBasicMove(agent, home_pos);
    return;
  }

  //--------------------------------------------------
  // block move
#if 1
  if (opp_min < mate_min - 1
      && opp_reach_pos.absY() > 20.0
      && opp_reach_pos.y * home_pos.y > 0.0
      && wm.self().pos().x < wm.theirOffenseLineX())
  {
    if (Bhv_BlockDribble(agent))
    {
      return;
    }
  }
#endif

  if (wm.ball().pos().dist(wm.self().pos()) > 10)
  {
    rolecenterbackmove().doMarkMove(agent, home_pos);
    return;
  }

  rcsc::Vector2D block_point = home_pos;

  if (wm.ball().pos().x < wm.self().pos().x)
  {
//    agent->debugClient().addMessage("SideBlockStatic");

    block_point.x = -42.0;
    block_point.y = wm.self().pos().y;
    if (wm.ball().pos().absY() < wm.self().pos().absY() - 0.5)
    {
//      agent->debugClient().addMessage("Correct");
      block_point.y = 10.0;
      if (home_pos.y < 0.0)
        block_point.y *= -1.0;
    }
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": doBlockSideAttacker() static move");
  }
  else
  {
    if (wm.ball().pos().x > -30.0 && wm.self().pos().x > home_pos.x
        && wm.ball().pos().x > wm.self().pos().x + 3.0)
    {
      // make static line
      // 0, -10, -20, ...
      //double tmpx = std::floor( wm.ball().pos().x * 0.1 ) * 10.0 - 3.5; //3.0;
      double tmpx;
      if (wm.ball().pos().x > -10.0)
        tmpx = -13.5;
      else if (wm.ball().pos().x > -16.0)
        tmpx = -19.5;
      else if (wm.ball().pos().x > -24.0)
        tmpx = -27.5;
      else if (wm.ball().pos().x > -30.0)
        tmpx = -33.5;
      else
        tmpx = home_pos.x;

      if (tmpx > 0.0)
        tmpx = 0.0;
      if (tmpx > home_pos.x + 5.0)
        tmpx = home_pos.x + 5.0;

      if (wm.ourDefenseLineX() < tmpx - 1.0)
      {
        tmpx = wm.ourDefenseLineX() + 1.0;
      }

      block_point.x = tmpx;
    }
  }

  //-----------------------------------------
  // set dash power
  double dash_power = rcsc::ServerParam::i().maxPower();
  if (wm.self().pos().x < wm.ball().pos().x - 8.0)
  {
    dash_power = wm.self().playerType().staminaIncMax() * 0.8;
  }
  else if (wm.self().pos().x < wm.ball().pos().x
      && wm.self().pos().absY() < wm.ball().pos().absY() - 1.0
      && wm.self().stamina() < rcsc::ServerParam::i().staminaMax() * 0.65)
  {
    dash_power = rcsc::ServerParam::i().maxPower() * 0.7;
  }

//  agent->debugClient().addMessage("BlockSideAttack%.0f", dash_power);

  double dist_thr = wm.ball().distFromSelf() * 0.1;
  if (dist_thr < 0.8)
    dist_thr = 0.8;

  agent->debugClient().setTarget(block_point);
  agent->debugClient().addCircle(block_point, dist_thr);

  if (!rcsc::Body_GoToPoint(block_point, dist_thr, dash_power).execute(agent))
  {
    rcsc::Vector2D face_point(-48.0, 0.0);
    rcsc::Body_TurnToPoint(face_point).execute(agent);
  }

  agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
}

bool
rolesidebackmove::Bhv_BlockDribble(PlayerAgent * agent)
{
  const WorldModel & wm = agent->world();

  // tackle
  if (Bhv_BasicTackle(0.8, 90.0).execute(agent))
  {
    dlog.addText(Logger::TEAM, __FILE__": execute(). tackle");
    return true;
  }

  const int opp_min = wm.interceptTable()->opponentReachCycle();
  const PlayerObject * opp = wm.interceptTable()->fastestOpponent();

  if (!opp)
  {
    dlog.addText(Logger::TEAM, __FILE__": execute(). no fastest opponent");
    return false;
  }

#if 0
    //ht:20140830 02:58 from BA_CrossBlock and wait to modifiy
    const WorldModel & wm = agent->world();
    if ( wm.ball().pos().x < wm.self().pos().x -5.0 )
    {
        if ( agent->world().ball().pos().y * home_pos.y > 0.0       //same side
                && wm.ball().pos().absY() > 10 )    //
        {
            //when opp begin fast attack, 4/5 go back!
            Vector2D adjust(0.0, 0.0);
            if ( wm.ball().vel().y * wm.self().pos().y < 0.0 )  //ht:20140830 01:56
            {
                adjust = wm.ball().vel() + wm.ball().vel();
            }
            else
            {
//                adjust.y = wm.ball().vel().y;
                adjust.x = 2.0 * wm.ball().vel().x;
            }
            Vector2D Pos = wm.ball().pos() + adjust; //wm.ball().vel() * 2.5;     //vel*2 at 20140814 testing....
    //        std::cerr << __FILE__ << wm.time().cycle() << "is there any use??? \n";
            Body_GoToPoint(Pos, 0.1, rcsc::ServerParam::i().maxPower() * 1.3 );
            agent->setNeckAction( new Neck_TurnToBallOrScan());
        }


    }
    else  if (wm.ball().pos().x < wm.self().pos().x -3.0
        && agent->world().ball().pos().y * home_pos.y > 0.0 //same side
        && wm.ball().pos().absY() > 10)    //modified by ht at 20140814
    {
        //when opp begin fast attack, 4/5 go back!
        Vector2D adjust(0.0, 0.0);
        if ( wm.ball().vel().y * wm.self().pos().y < 0.0 )  //ht:20140830 01:56 //need to change!!跑动不连贯
        {
            adjust = wm.ball().vel() + wm.ball().vel();
        }
        else
        {
            adjust.y = wm.ball().vel().y;
            adjust.x = 2.0 * wm.ball().vel().x;
        }
        Vector2D Pos = wm.ball().pos() + adjust; //wm.ball().vel() * 2.5;     //vel*2 at 20140814 testing....
//        std::cerr << __FILE__ << wm.time().cycle() << "is there any use??? \n";
        Body_GoToPoint(Pos, 0.1, rcsc::ServerParam::i().maxPower());
        agent->setNeckAction( new Neck_TurnToBallOrScan());
    }
#endif //1

  const Vector2D opp_target(-44.0, 0.0);
  const PlayerType & self_type = wm.self().playerType();
  const double control_area = self_type.kickableArea() - 0.3;
  const double max_moment = ServerParam::i().maxMoment(); // * ( 1.0 - ServerParam::i().playerRand() );

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
        dash_angle += angle_diff;
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

  if (!target_point.isValid())
  {
    return false;
  }
//
//  dlog.addText(Logger::TEAM,
//      __FILE__": execute(). viertual interceitp. pos=(%.1f %.1f) total_step=%d",
//      target_point.x, target_point.y, total_step);

  //0.5 -> 0.1
  if (!Body_GoToPoint(target_point, 0.1, ServerParam::i().maxPower()).execute(agent))
  {
    return false;
  }
  agent->debugClient().setTarget(target_point);
  agent->debugClient().addMessage("BlockDribVirtualIntercept");
  agent->setNeckAction(new rcsc::Neck_TurnToBall());
  return true;
}
