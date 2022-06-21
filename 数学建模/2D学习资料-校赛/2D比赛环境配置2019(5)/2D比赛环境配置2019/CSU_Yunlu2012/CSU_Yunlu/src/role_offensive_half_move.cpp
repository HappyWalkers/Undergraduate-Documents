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

#include "strategy.h"
#include "bhv_attackers_move.h"
#include "bhv_basic_offensive_kick.h"
#include "bhv_dangerAreaTackle.h"
#include "role_center_back_move.h"
#include "role_offensive_half_move.h"
#include "bhv_basic_tackle.h"
#include "strategy.h"
#include "bhv_basic_move.h"
//#include "neck_turn_to_receiver.h"

#include <rcsc/action/basic_actions.h>
#include <rcsc/action/body_go_to_point.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/body_clear_ball.h>
#include <rcsc/action/neck_turn_to_ball_or_scan.h>
#include <rcsc/action/neck_turn_to_ball_and_player.h>
#include <rcsc/action/neck_turn_to_goalie_or_scan.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>
#include <rcsc/action/neck_scan_field.h>
#include "neck_offensive_intercept_neck.h"
#include <rcsc/action/body_intercept2009.h>

#include <rcsc/formation/formation.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/intercept_table.h>
#include <rcsc/player/debug_client.h>
#include <rcsc/player/player_config.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/ray_2d.h>
#include <rcsc/soccer_math.h>
using namespace rcsc;
/*-------------------------------------------------------------------*/
/*!

 */
void
roleoffensivehalfmove::doOffensiveMove(rcsc::PlayerAgent * agent,
                                       const rcsc::Vector2D & home_pos)
{
    rcsc::dlog.addText(rcsc::Logger::ROLE, __FILE__": doOffensiveMove");

    if (home_pos.x > 30.0 && home_pos.absY() < 7.0)
    {
        if (Bhv_AttackersMove(home_pos, false).execute(agent))
            return;
    }

    //----------------------------------------------
    // tackle
    if (Bhv_BasicTackle(0.8, 90.0).execute(agent))
    {
        return;
    }

    const rcsc::WorldModel & wm = agent->world();
    //----------------------------------------------
    // intercept
    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();

    //------------------------------------------------------
    const rcsc::PlayerObject * fastest_opp =
        wm.interceptTable()->fastestOpponent();

    if (fastest_opp && opp_min < self_min - 2 && opp_min < mate_min
            && wm.ball().pos().dist(home_pos) < 10.0)
    {
        rcsc::Vector2D attack_point = (
                                          opp_min >= 3 ?
                                          wm.ball().inertiaPoint(opp_min) :
                                          fastest_opp->pos() + fastest_opp->vel() );

        if (std::fabs(attack_point.y - wm.self().pos().y) > 1.0)
        {
            rcsc::Line2D opp_move_line(fastest_opp->pos(),
                                       fastest_opp->pos() + rcsc::Vector2D(-3.0, 0.0));
            rcsc::Ray2D my_move_line(wm.self().pos(), wm.self().body());
            rcsc::Vector2D intersection = my_move_line.intersection(opp_move_line);
            if (intersection.isValid() && attack_point.x - 6.0 < intersection.x
                    && intersection.x < attack_point.x - 1.0)
            {
                attack_point.x = intersection.x;
            }
            else
            {
                attack_point.x -= 4.0;
                if (std::fabs(fastest_opp->pos().y - wm.self().pos().y) > 10.0)
                {
                    attack_point.x -= 2.0;
                }
            }
        }

        if (attack_point.x < home_pos.x + 5.0)
        {
            double dash_power = rcsc::ServerParam::i().maxPower();
            if (wm.self().stamina() < rcsc::ServerParam::i().staminaMax() * 0.5)
            {
                dash_power *= wm.self().stamina() / rcsc::ServerParam::i().staminaMax();
            }
            agent->debugClient().addMessage("OffAttackBall");
            agent->debugClient().setTarget(attack_point);
            agent->debugClient().addCircle(attack_point, 0.5);

            if (rcsc::Body_GoToPoint(attack_point, 0.5, dash_power).execute(agent))
            {
                agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
                return;
            }
        }
    }

    if (self_min < mate_min)
    {
        if ((opp_min <= 3 && opp_min <= self_min - 1) || opp_min <= self_min - 4)
        {
            agent->debugClient().addMessage("OffPress1");
            roleoffensivehalfmove().Bhv_Press(agent);
            return;
        }
        agent->debugClient().addMessage("OffGetBall(1)");
        Body_Intercept2009().execute(agent);
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

    bool iamfastest = false;
    if (self_min < mate_min && self_min < opp_min)
        iamfastest = true;
#if 1
    if (iamfastest && wm.ball().pos().dist(home_pos) < 10.0)
    {
        agent->debugClient().addMessage("OffPress");
        if (roleoffensivehalfmove().Bhv_Press(agent))
            return;
    }
#endif


//  agent->debugClient().addMessage("OffMove");
    Bhv_BasicMove().execute(agent);
}

/*-------------------------------------------------------------------*/
/*!

 */
void
roleoffensivehalfmove::doDefMidMove(rcsc::PlayerAgent * agent,
                                    const rcsc::Vector2D & home_pos)
{
    rcsc::dlog.addText(rcsc::Logger::ROLE, __FILE__": doDefensiveMove");

    agent->debugClient().addMessage("DefMidMove");

    //----------------------------------------------
    // tackle
    if (Bhv_BasicTackle(0.8, 90.0).execute(agent))
    {
        return;
    }

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

    // intercept
    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();

    if (self_min < 16)
    {
        rcsc::Vector2D get_pos = rcsc::inertia_n_step_point(wm.ball().pos(),
                                 wm.ball().vel(), self_min, rcsc::ServerParam::i().ballDecay());
        bool enough_stamina = true;
        double estimated_consume =
            wm.self().playerType().getOneStepStaminaComsumption() * self_min;
        if (wm.self().stamina() - estimated_consume
                < rcsc::ServerParam::i().recoverDecThrValue())
        {
            enough_stamina = false;
        }

        if (enough_stamina && opp_min < 3
                && (home_pos.dist(get_pos) < 10.0
                    || (home_pos.absY() < get_pos.absY() && home_pos.y * get_pos.y > 0.0) // same side
                    || get_pos.x < home_pos.x))
        {
            agent->debugClient().addMessage("DefGetBall");
            rcsc::Body_Intercept2009().execute(agent);

            if (self_min == 4 && opp_min >= 2)
            {
                agent->setViewAction(new rcsc::View_Wide());
            }
            else if (self_min == 3 && opp_min >= 2)
            {
                agent->setViewAction(new rcsc::View_Normal());
            }

            agent->setNeckAction(new rcsc::Neck_TurnToBall());
            return;
        }
    }

    if (self_min < 15 && self_min < mate_min + 2 && !wm.existKickableTeammate())
    {
        agent->debugClient().addMessage("DefGetBall(2)");
        Body_Intercept2009().execute(agent);
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
    if (wm.ball().pos().x > -15.0 && !wm.existKickableTeammate())
    {
        Vector2D Pos = wm.ball().pos() + wm.ball().vel();
        double dist_thr = wm.ball().pos().dist(Pos) * 0.1;
        if (dist_thr < 0.5)
            dist_thr = 0.5;
        Body_GoToPoint(Pos,dist_thr, rcsc::ServerParam::i().maxPower());
    }
    if ( nearest_opp && !wm.existKickableTeammate())
    {
        // decide dash power
        double dash_power = rolecenterbackmove().get_dash_power(agent,nearest_opp_pos );

        double dist_thr = wm.ball().pos().dist(nearest_opp_pos) * 0.1;
        if (dist_thr < 0.5)
            dist_thr = 0.5;
        Body_GoToPoint(nearest_opp_pos, dist_thr, rcsc::ServerParam::i().maxPower());
    }

//  rcsc::Vector2D target_point = home_pos;
//     if ( wm.existKickableTeammate()
//          || ( mate_min < 2 && opp_min > 2 )
//          )
//     {
//         target_point.x += 10.0;
//     }
// #if 1
//     else if ( home_pos.y * wm.ball().pos().y > 0.0 ) // same side
//     {
//         target_point.x = wm.ball().pos().x + 1.0;
//     }
// #endif
    Bhv_BasicMove().execute(agent);
}

/*-------------------------------------------------------------------*/
/*!

 */
bool
roleoffensivehalfmove::Bhv_Press(PlayerAgent * agent)
{
    static bool S_recover_mode = false;

    const rcsc::WorldModel & wm = agent->world();
    Vector2D homePos = Strategy::i().getPosition(wm.self().unum());
    if (wm.opponentsFromBall().empty())
    {
        return Bhv_BasicMove().execute(agent);
    }

    ///////////////////////////////////
    // tackle
    if (Bhv_BasicTackle(0.85, 90.0).execute(agent))
    {
        return true;
    }

    ///////////////////////////////////

    int self_min = wm.interceptTable()->selfReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();

    if (!wm.existKickableTeammate() && !wm.existKickableOpponent()
            && (self_min < opp_min + 3 || self_min < 4))
    {
        rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": get ball");
        agent->debugClient().addMessage("Press:get");
        Body_Intercept2009().execute(agent);
        if (wm.existKickableOpponent())
        {
            agent->setNeckAction(new rcsc::Neck_TurnToBall());
        }
        else
        {
            agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
        }
        return true;
    }

    ///////////////////////////////////
    // set target point

    const rcsc::PlayerObject * opponent = wm.opponentsFromBall().front();

    if (opponent->distFromSelf() > 10.0
            && std::fabs(opponent->pos().y - homePos.y) > 10.0)
    {
        markCloseOpp(agent);
        return true;
    }

    rcsc::Vector2D target_point = opponent->pos();

    ////////////////////////////////////////////////////////
    // check teammate closer than self
    const double x_thr = wm.ourDefenseLineX() + 5.0;
    double my_dist2 = wm.self().pos().dist2(target_point);

    const rcsc::PlayerPtrCont::const_iterator mates_end =
        wm.teammatesFromSelf().end();
    for (rcsc::PlayerPtrCont::const_iterator it = wm.teammatesFromSelf().begin();
            it != mates_end; ++it)
    {
        if ((*it)->pos().x < x_thr)
        {
            continue;
        }
        double d2 = (*it)->pos().dist2(target_point);
        if (d2 < my_dist2 || d2 < 3.0 * 3.0)
        {
            rcsc::dlog.addText(rcsc::Logger::TEAM,
                               __FILE__": exist other pressor(%.1f, %.1f)", (*it)->pos().x,
                               (*it)->pos().y);
            Bhv_BasicMove().execute(agent);
            return true;
        }
    }

    if (std::fabs(target_point.y - wm.self().pos().y) > 1.0)
    {
        rcsc::Line2D opp_move_line(opponent->pos(),
                                   opponent->pos() + rcsc::Vector2D(-3.0, 0.0));
        rcsc::Ray2D my_move_ray(wm.self().pos(), wm.self().body());
        rcsc::Vector2D intersection = my_move_ray.intersection(opp_move_line);
        if (intersection.isValid() && intersection.x < target_point.x
                && wm.self().pos().dist(intersection)
                < target_point.dist(intersection) * 1.1)
        {
            target_point.x = intersection.x;
            rcsc::dlog.addText(rcsc::Logger::ROLE,
                               __FILE__": press. attack opponent. keep body direction");
        }
        else
        {
            target_point.x -= 5.0;
            if (target_point.x > wm.self().pos().x
                    && wm.self().pos().x > homePos.x - 2.0)
            {
                target_point.x = wm.self().pos().x;
            }
            rcsc::dlog.addText(rcsc::Logger::ROLE,
                               __FILE__": press. attack opponent. back ");
        }
    }

    ///////////////////////////////////
    // set dash power
    if (wm.self().stamina() < rcsc::ServerParam::i().staminaMax() * 0.48)
    {
        S_recover_mode = true;
    }
    if (wm.self().stamina() > rcsc::ServerParam::i().staminaMax() * 0.75)
    {
        S_recover_mode = false;
    }

    double dash_power;
    if (S_recover_mode)
    {
        dash_power = wm.self().playerType().staminaIncMax();
        dash_power *= wm.self().recovery();
        dash_power *= 0.8;
    }
#if 0
    else if ( wm.ball().pos().x < wm.self().pos().x - 1.0 )
    {
        dash_power = rcsc::ServerParam::i().maxPower() * 0.9;
    }
    else if ( wm.ball().distFromSelf() > 10.0 )
    {
        dash_power = rcsc::ServerParam::i().maxPower() * 0.7;
    }
    else if ( wm.ball().distFromSelf() > 2.0 )
    {
        dash_power = rcsc::ServerParam::i().maxPower() * 0.75;
    }
#endif
    else
    {
        dash_power = rcsc::ServerParam::i().maxPower();
    }

    rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": go to (%.1f, %.1f)",
                       target_point.x, target_point.y);

    double dist_thr = wm.ball().distFromSelf() * 0.1;
    if (dist_thr < 0.5)
        dist_thr = 0.5;

    agent->debugClient().addMessage("press%.0f", dash_power);
    agent->debugClient().setTarget(target_point);
    agent->debugClient().addCircle(target_point, dist_thr);

    if (!rcsc::Body_GoToPoint(target_point, dist_thr, dash_power).execute(agent))
    {
        rcsc::Body_TurnToPoint(target_point).execute(agent);
    }

    if (wm.existKickableOpponent())
    {
        agent->setNeckAction(new rcsc::Neck_TurnToBall());
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
bool
roleoffensivehalfmove::markCloseOpp(rcsc::PlayerAgent * agent)
{
    //-----------------------------------------------
    // tackle
    if (Bhv_BasicTackle(0.85, 60.0).execute(agent))
    {
        return true;
    }

    const rcsc::WorldModel & wm = agent->world();
    Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());
    //-----------------------------------------------
    // intercept

    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();
    bool iamfastest = false;
    if (self_min < mate_min && self_min < opp_min)
        iamfastest = true;
    if ((!wm.existKickableTeammate() && self_min < 4)
            || (self_min < mate_min /* && self_min < opp_min */))
    {
        rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": intercept");
        Body_Intercept2009().execute(agent);
        agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
        return true;
    }

    //--------------------------------------------------
    if (iamfastest)
    {
        rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": I am fastest");
        Body_Intercept2009().execute(agent);
        if (wm.ball().distFromSelf() < rcsc::ServerParam::i().visibleDistance())
        {
            agent->setNeckAction(new rcsc::Neck_TurnToLowConfTeammate());
        }
        else
        {
            agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
        }
        return true;
    }

    if (wm.ball().pos().x < -36.0
            && wm.ball().pos().absY() < 18.0
            && wm.ball().distFromSelf() < 5.0
            && !wm.existKickableTeammate())
    {
        rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": ball near");
        if (Body_Intercept2009().execute(agent))
        {
            if (wm.ball().distFromSelf() < rcsc::ServerParam::i().visibleDistance())
            {
                agent->setNeckAction(new rcsc::Neck_TurnToLowConfTeammate());
            }
            else
            {
                agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
            }
            return true;
        }
    }

    ////////////////////////////////////////////////////////
    double dist_opp_to_home = 200.0;
    const rcsc::PlayerObject * opp = wm.getOpponentNearestTo(home_pos, 1,
                                     &dist_opp_to_home);

    ////////////////////////////////////////////////////////
    {
        const double dist_opp_to_ball = (opp ? opp->distFromBall() : 100.0 );
        if (wm.existKickableTeammate()
                && dist_opp_to_ball > 2.5)
        {
            // not found
            return Bhv_BasicMove().execute(agent);
        }
    }

    ////////////////////////////////////////////////////////

    rcsc::Vector2D nearest_opp_pos(rcsc::Vector2D::INVALIDATED);
    if (opp)
    {
        nearest_opp_pos = opp->pos();
    }

    // found candidate opponent
    if (nearest_opp_pos.isValid()
            && (dist_opp_to_home < 7.0 || home_pos.x > nearest_opp_pos.x))
    {
//      std::cerr << __FILE__ << wm.self().unum() << ": domark here?.?.? \n";
        // do mark
    }
    else
    {
        rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": mark target not found");
        // not found
        return Bhv_BasicMove().execute(agent);
    }

    ////////////////////////////////////////////////////////
    // check teammate closer than self
    {
        bool opp_is_not_danger = (nearest_opp_pos.x > -35.0
                                  || nearest_opp_pos.absY() > 17.0 );
        const double dist_opp_to_home2 = dist_opp_to_home * dist_opp_to_home;
        const rcsc::PlayerPtrCont::const_iterator end =
            wm.teammatesFromSelf().end();
        for (rcsc::PlayerPtrCont::const_iterator it =
                    wm.teammatesFromSelf().begin(); it != end; ++it)
        {
            if (opp_is_not_danger && (*it)->pos().x < wm.ourDefenseLineX() + 3.0)
            {
                continue;
            }

            if ((*it)->pos().dist2(nearest_opp_pos) < dist_opp_to_home2
                    && (*it)->pos().dist( wm.ball().pos() ) < 3.0 )       //20140919 23:46 testing...)
            {
                rcsc::dlog.addText(rcsc::Logger::TEAM,
                                   __FILE__": exist other marker(%.1f, %.1f)", (*it)->pos().x,
                                   (*it)->pos().y);
                return Bhv_BasicMove().execute(agent);
            }
        }
    }

    ////////////////////////////////////////////////////////
    rcsc::AngleDeg block_angle = (wm.ball().pos() - nearest_opp_pos).th();
    rcsc::Vector2D block_point = nearest_opp_pos
                                 + rcsc::Vector2D::polar2vector(0.2, block_angle);
    block_point.x -= 0.1;

    ////////////////////////////////////////////////////////
    if (block_point.x < wm.self().pos().x - 1.5)
    {
        block_point.y = wm.self().pos().y;
    }

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

    rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": mark to (%.1f, %.1f)",
                       block_point.x, block_point.y);

    double dist_thr = wm.ball().distFromSelf() * 0.07;
    if (dist_thr < 0.5)
        dist_thr = 0.5;

    agent->debugClient().addMessage("marking");
    agent->debugClient().setTarget(block_point);
    agent->debugClient().addCircle(block_point, dist_thr);

    if (!rcsc::Body_GoToPoint(block_point, dist_thr, dash_power).execute(agent))
    {
        rcsc::Body_TurnToBall().execute(agent);
    }
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());

    return true;
}

void
roleoffensivehalfmove::doGoToCrossPoint( rcsc::PlayerAgent * agent,
        const rcsc::Vector2D & home_pos )
{
    rcsc::dlog.addText( rcsc::Logger::ROLE,
                        __FILE__": doGoToCrossPoint" );

    const rcsc::WorldModel & wm = agent->world();
    //------------------------------------------------------
    // tackle
    if ( Bhv_BasicTackle( 0.75, 90.0 ).execute( agent ) )
    {
        return;
    }

    //----------------------------------------------
    // intercept check
    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();

    if ( self_min < mate_min
            || ( mate_min != 0 // ! wm.existKickableTeammate()
                 && self_min <= 6
                 && wm.ball().pos().dist( home_pos ) < 10.0 )
            //|| wm.interceptTable()->isSelfFastestPlayer()
       )
    {
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doGoToCross. get ball" );
        agent->debugClient().addMessage( "CrossGetBall" );

        rcsc::Body_Intercept2009().execute( agent );

        if ( self_min == 3 && opp_min >= 3 )
        {
            agent->setViewAction( new rcsc::View_Normal() );
        }

        if ( wm.self().pos().x > 30.0 )
        {
            if ( ! doCheckCrossPoint( agent ) )
            {
                agent->setNeckAction( new rcsc::Neck_TurnToGoalieOrScan() );
            }
        }
        else
        {
            agent->setNeckAction( new rcsc::Neck_TurnToBallOrScan() );
        }
        return;
    }

    //----------------------------------------------
    // ball owner check
    if ( ! wm.interceptTable()->isOurTeamBallPossessor() )
    {
        const rcsc::PlayerObject * opp = wm.getOpponentNearestToBall( 3 );

        if ( opp
                && opp->distFromSelf() < 2.0 )
        {
            rcsc::dlog.addText( rcsc::Logger::ROLE,
                                __FILE__": doGoToCross. opp has ball" );
            agent->debugClient().addMessage( "CrossOppOwn(2)" );
            Bhv_BasicMove().execute( agent );
            return;
        }
    }

    //----------------------------------------------
    // set target

    rcsc::Vector2D target_point = home_pos;
    rcsc::Vector2D trap_pos = ( mate_min < 100
                                ? wm.ball().inertiaPoint( mate_min )
                                : wm.ball().pos() );

    if ( mate_min <= opp_min
            && mate_min < 3
            && target_point.x < 38.0
            && wm.self().pos().x < wm.offsideLineX() - 1.0
            //&& target_point.x < wm.self().pos().x
            //&& std::fabs( target_point.x - wm.self().pos().x ) < 20.0
            && std::fabs( target_point.y - wm.self().pos().y ) < 5.0
            && std::fabs( wm.self().pos().y - trap_pos.y ) < 13.0
       )
    {
        target_point.y = wm.self().pos().y * 0.9 + home_pos.y * 0.1;
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doGoToCross. chance keep current." );
        agent->debugClient().addMessage( "CrossCurPos" );
    }

    // consider near opponent
    if ( target_point.x > 36.0 )
    {
        double opp_dist = 200.0;
        const rcsc::PlayerObject * opp = wm.getOpponentNearestTo( target_point,
                                         10,
                                         &opp_dist );
        if ( opp && opp_dist < 2.0 )
        {
            rcsc::Vector2D tmp_target = target_point;
            for ( int i = 0; i < 3; ++i )
            {
                tmp_target.x -= 1.0;

                double d = 0.0;
                opp = wm.getOpponentNearestTo( tmp_target, 10, &d );
                if ( ! opp )
                {
                    opp_dist = 0.0;
                    target_point = tmp_target;
                    break;
                }
                if ( opp
                        && opp_dist < d )
                {
                    opp_dist = d;
                    target_point = tmp_target;
                }
            }
            rcsc::dlog.addText( rcsc::Logger::ROLE,
                                __FILE__": doGoToCross. avoid(%.2f, %.2f)->(%.2f, %.2f)",
                                home_pos.x, home_pos.y,
                                target_point.x, target_point.y );
            agent->debugClient().addMessage( "Avoid" );
        }
    }

    if ( target_point.dist( trap_pos ) < 6.0 )
    {
        rcsc::Circle2D target_circle( trap_pos, 6.0 );
        rcsc::Line2D target_line( target_point, rcsc::AngleDeg( 90.0 ) );
        rcsc::Vector2D sol_pos1, sol_pos2;
        int n_sol = target_circle.intersection( target_line, &sol_pos1, &sol_pos2 );

        if ( n_sol == 1 ) target_point = sol_pos1;
        if ( n_sol == 2 )
        {
            target_point = ( wm.self().pos().dist2( sol_pos1 ) < wm.self().pos().dist2( sol_pos2 )
                             ? sol_pos1
                             : sol_pos2 );

        }

        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doGoToCross. adjust ot avoid the ball owner." );
        agent->debugClient().addMessage( "Adjust" );
    }

    //----------------------------------------------
    // set dash power
    // check X buffer & stamina
    static bool s_recover_mode = false;
    if ( wm.self().pos().x > 35.0
            && wm.self().stamina()
            < rcsc::ServerParam::i().recoverDecThrValue() + 500.0 )
    {
        s_recover_mode = true;
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doGoToCross. recover on" );
    }

    if ( wm.self().stamina() > rcsc::ServerParam::i().staminaMax() * 0.5 )
    {
        s_recover_mode = false;
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doGoToCross. recover off" );
    }

    double dash_power = rcsc::ServerParam::i().maxPower();
    if ( s_recover_mode )
    {
        const double my_inc
            = wm.self().playerType().staminaIncMax()
              * wm.self().recovery();
        dash_power = std::max( 1.0, my_inc - 25.0 );
        //dash_power = wm.self().playerType().staminaIncMax() * 0.6;
    }
    else if ( wm.ball().pos().x > wm.self().pos().x )
    {
        if ( wm.existKickableTeammate()
                && wm.ball().distFromSelf() < 10.0
                && std::fabs( wm.self().pos().x - wm.ball().pos().x ) < 5.0
                && wm.self().pos().x > 30.0
                && wm.ball().pos().x > 35.0 )
        {
            dash_power *= 0.5;
        }
    }
    else if ( wm.self().pos().dist( target_point ) < 3.0 )
    {
        const double my_inc
            = wm.self().playerType().staminaIncMax()
              * wm.self().recovery();
        dash_power = std::min( rcsc::ServerParam::i().maxPower(),
                               my_inc + 10.0 );
        //dash_power = rcsc::ServerParam::i().maxPower() * 0.8;
    }
    else if ( mate_min <= 1
              && wm.ball().pos().x > 33.0
              && wm.ball().pos().absY() < 7.0
              && wm.ball().pos().x < wm.self().pos().x
              && wm.self().pos().x < wm.offsideLineX()
              && wm.self().pos().absY() < 9.0
              && std::fabs( wm.ball().pos().y - wm.self().pos().y ) < 3.5
              && std::fabs( target_point.y - wm.self().pos().y ) > 5.0 )
    {
        dash_power = wm.self().playerType()
                     .getDashPowerToKeepSpeed( 0.3, wm.self().effort() );
        dash_power = std::min( rcsc::ServerParam::i().maxPower() * 0.75,
                               dash_power );
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doGoToCross. slow for cross. power=%.1f",
                            dash_power );
    }

    //----------------------------------------------
    // positioning to make the cross course!!

    double dist_thr = wm.ball().distFromSelf() * 0.1;
    if ( dist_thr < 0.5 ) dist_thr = 0.5;

    agent->debugClient().addMessage( "GoToCross%.0f", dash_power );
    agent->debugClient().setTarget( target_point );
    agent->debugClient().addCircle( target_point, dist_thr );

    rcsc::dlog.addText( rcsc::Logger::ROLE,
                        __FILE__": doGoToCross. to (%.2f, %.2f)",
                        target_point.x, target_point.y );

    if ( wm.self().pos().x > target_point.x + dist_thr
            && std::fabs( wm.self().pos().x - target_point.x ) < 3.0
            && wm.self().body().abs() < 10.0 )
    {
        agent->debugClient().addMessage( "Back" );
        double back_dash_power
            = wm.self().getSafetyDashPower( -dash_power );
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doShootAreaMove. Back Move" );
        agent->doDash( back_dash_power );
    }
    else
    {
        if ( ! rcsc::Body_GoToPoint( target_point, dist_thr, dash_power,
                                     5, // cycle
                                     false, // no back dash
                                     true, // save recovery
                                     30.0 // dir thr
                                   ).execute( agent ) )
        {
            rcsc::Body_TurnToAngle( 0.0 ).execute( agent );
        }
    }

    if ( wm.self().pos().x > 30.0 )
    {
        agent->setNeckAction( new rcsc::Neck_TurnToGoalieOrScan() );
    }
    else
    {
        agent->setNeckAction( new rcsc::Neck_TurnToLowConfTeammate() );
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
roleoffensivehalfmove::doCheckCrossPoint( rcsc::PlayerAgent * agent )
{
    const rcsc::WorldModel & wm = agent->world();

    if ( wm.self().pos().x < 35.0 )
    {
        return false;
    }

    const rcsc::PlayerObject * opp_goalie = wm.getOpponentGoalie();
    if ( opp_goalie && opp_goalie->posCount() > 2 )
    {
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doCheckCrossTarget  goalie should be checked" );
        return false;
    }

    rcsc::Vector2D opposite_pole( 46.0, 7.0 );
    if ( wm.self().pos().y > 0.0 ) opposite_pole.y *= -1.0;

    rcsc::AngleDeg opposite_pole_angle = ( opposite_pole - wm.self().pos() ).th();


    if ( wm.dirCount( opposite_pole_angle ) <= 1 )
    {
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doCheckCrossTarget enough accuracy to angle %.1f",
                            opposite_pole_angle.degree() );
        return false;
    }

    rcsc::AngleDeg angle_diff
        = agent->effector().queuedNextAngleFromBody( opposite_pole );
    if ( angle_diff.abs() > 100.0 )
    {
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doCheckCrossPoint. want to face opposite pole,"
                            " but over view range. angle_diff=%.1f",
                            angle_diff.degree() );
        return false;
    }


    agent->setNeckAction( new rcsc::Neck_TurnToPoint( opposite_pole ) );
    agent->debugClient().addMessage( "NeckToOpposite" );
    rcsc::dlog.addText( rcsc::Logger::ROLE,
                        __FILE__": doCheckCrossPoint Neck to oppsite pole" );
    return true;
}

double
roleoffensivehalfmove::getShootAreaMoveDashPower( rcsc::PlayerAgent * agent,
        const rcsc::Vector2D & target_point )
{
    const rcsc::WorldModel & wm = agent->world();

    static bool s_recover = false;

    double dash_power = 100.0;

    // recover check
    // check X buffer & stamina
    if ( wm.self().stamina() < rcsc::ServerParam::i().effortDecThrValue() + 500.0 )
    {
        if ( wm.self().pos().x > 30.0 )
        {
            s_recover = true;
            rcsc::dlog.addText( rcsc::Logger::ROLE,
                                __FILE__": recover on" );
        }
    }
    else if ( wm.self().stamina() > rcsc::ServerParam::i().effortIncThrValue() )
    {
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": recover off" );
        s_recover = false;
    }

    if ( wm.ball().pos().x > wm.self().pos().x )
    {
        // keep max power
        dash_power = rcsc::ServerParam::i().maxPower();
    }
    else if ( wm.ball().pos().x > 41.0
              && wm.ball().pos().absY() < rcsc::ServerParam::i().goalHalfWidth() + 5.0 )
    {
        // keep max power
        dash_power = rcsc::ServerParam::i().maxPower();
    }
    else if ( s_recover )
    {
        dash_power = wm.self().playerType().staminaIncMax() * 0.6;
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": recovering" );
    }
    else if ( wm.interceptTable()->teammateReachCycle() <= 1
              && wm.ball().pos().x > 33.0
              && wm.ball().pos().absY() < 7.0
              && wm.ball().pos().x < wm.self().pos().x
              && wm.self().pos().x < wm.offsideLineX()
              && wm.self().pos().absY() < 9.0
              && std::fabs( wm.ball().pos().y - wm.self().pos().y ) < 3.5
              && std::fabs( target_point.y - wm.self().pos().y ) > 5.0 )
    {
        dash_power = wm.self().playerType()
                     .getDashPowerToKeepSpeed( 0.3, wm.self().effort() );
        dash_power = std::min( rcsc::ServerParam::i().maxPower() * 0.75,
                               dash_power );
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": slow for cross. power=%.1f",
                            dash_power );
    }
    else
    {
        dash_power = rcsc::ServerParam::i().maxPower() * 0.75;
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": ball is far" );
    }

    return dash_power;
}

/*-------------------------------------------------------------------*/
/*!

*/
rcsc::Vector2D
roleoffensivehalfmove::getShootAreaMoveTarget( rcsc::PlayerAgent * agent,
        const rcsc::Vector2D & home_pos )
{
    const rcsc::WorldModel & wm = agent->world();

    rcsc::Vector2D target_point = home_pos;

    int mate_min = wm.interceptTable()->teammateReachCycle();
    rcsc::Vector2D ball_pos = ( mate_min < 10
                                ? wm.ball().inertiaPoint( mate_min )
                                : wm.ball().pos() );
    bool opposite_side = false;

    if ( ( ball_pos.y > 0.0
            && Strategy::i().getPositionType( agent->config().playerNumber() )==-1 )
            || ( ball_pos.y <= 0.0
                 && Strategy::i().getPositionType( agent->config().playerNumber() )==1 )
            || ( ball_pos.y * home_pos.y < 0.0
                 && Strategy::i().getPositionType( agent->config().playerNumber() )==0 )
       )
    {
        opposite_side = true;
    }

    if ( opposite_side
            && ball_pos.x > 40.0 // very chance
            && 6.0 < ball_pos.absY()
            && ball_pos.absY() < 15.0 )
    {
        rcsc::Circle2D goal_area( rcsc::Vector2D( 47.0, 0.0 ),
                                  7.0 );

        if ( ! wm.existTeammateIn( goal_area, 10, true ) )
        {
            agent->debugClient().addMessage( "GoToCenterCross" );

            target_point.x = 47.0;

            if ( wm.self().pos().x > wm.offsideLineX() - 0.5
                    && target_point.x > wm.offsideLineX() - 0.5 )
            {
                target_point.x = wm.offsideLineX() - 0.5;
            }

            if ( ball_pos.absY() < 9.0 )
            {
                target_point.y = 0.0;
            }
            else
            {
                target_point.y = ( ball_pos.y > 0.0
                                   ? 1.0 : -1.0 );
                //? 2.4 : -2.4 );
            }

            rcsc::dlog.addText( rcsc::Logger::ROLE,
                                __FILE__": ShootAreaMove. center cross point" );
        }
        else
        {
            rcsc::dlog.addText( rcsc::Logger::ROLE,
                                __FILE__": ShootAreaMove. exist teammate in cross point" );
        }
    }

    // consider near opponent
    {
        double opp_dist = 200.0;
        const rcsc::PlayerObject * nearest_opp
            = wm.getOpponentNearestTo( target_point, 10, &opp_dist );

        if ( nearest_opp
                && opp_dist < 2.0 )
        {
            rcsc::dlog.addText( rcsc::Logger::ROLE,
                                __FILE__": ShootAreaMove. Point Blocked. old target=(%.2f, %.2f)",
                                target_point.x, target_point.y );
            agent->debugClient().addMessage( "AvoidOpp" );
            //if ( nearest_opp->pos().x + 3.0 < wm.offsideLineX() - 1.0 )
            if ( nearest_opp->pos().x + 2.0 < wm.offsideLineX() - 1.0  )
            {
                //target_point.x = nearest_opp->pos().x + 3.0;
                target_point.x = nearest_opp->pos().x + 2.0;
            }
            else
            {
                target_point.x = nearest_opp->pos().x - 2.0;
#if 1
                if ( std::fabs( wm.self().pos().y - target_point.y ) < 1.0 )
                {
                    target_point.x = nearest_opp->pos().x - 3.0;
                }
#endif
            }
        }

    }

    // consider goalie
    if ( target_point.x > 45.0 )
    {
        const rcsc::PlayerObject * opp_goalie = wm.getOpponentGoalie();
        if ( opp_goalie
                && opp_goalie->distFromSelf() < wm.ball().distFromSelf() )
        {
            rcsc::Line2D cross_line( ball_pos, target_point );
            if (  cross_line.dist( opp_goalie->pos() ) < 3.0 )
            {
                agent->debugClient().addMessage( "AvoidGK" );
                agent->debugClient().addLine( ball_pos, target_point );
                rcsc::dlog.addText( rcsc::Logger::ROLE,
                                    __FILE__": ShootAreaMove. Goalie is on cross line. old target=(%.2f %.2f)",
                                    target_point.x, target_point.y );

                rcsc::Line2D move_line( wm.self().pos(), target_point );
                target_point.x -= 2.0;
            }
        }
    }

    return target_point;
}

/*-------------------------------------------------------------------*/
/*!

*/
void
roleoffensivehalfmove::doShootAreaMove( rcsc::PlayerAgent* agent,
                                        const rcsc::Vector2D& home_pos )
{
    rcsc::dlog.addText( rcsc::Logger::ROLE,
                        __FILE__": doShootAreaMove" );

    const rcsc::WorldModel & wm = agent->world();

    //------------------------------------------------------
    // tackle
    if ( wm.existKickableOpponent()
            && wm.self().tackleProbability() > 0.8 )
    {
        if ( 60.0 < wm.self().body().abs()
                && wm.self().body().abs() < 120.0 )
        {
            double tackle_power =  rcsc::ServerParam::i().maxPower();
            if ( ( wm.self().pos().y > 0.0
                    && wm.self().body().degree() > 0.0 )
                    || ( wm.self().pos().y < 0.0
                         && wm.self().body().degree() < 0.0 )
               )
            {
                tackle_power *= -1.0;
            }

            if ( agent->config().version() < 12.0
                    && tackle_power >= 0.0 )
            {
                agent->doTackle( tackle_power );
                agent->setNeckAction( new rcsc::Neck_TurnToBallOrScan() );
                return;
            }
        }
    }

    if ( Bhv_BasicTackle( 0.8, 90.0 ).execute( agent ) )
    {
        return;
    }

    //------------------------------------------------------

    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();

    rcsc::dlog.addText( rcsc::Logger::ROLE,
                        __FILE__": doShootAreaMove. intercept cycle. self=%d, mate=%d, opp=%d",
                        self_min, mate_min, opp_min );
    if ( self_min < 4
            || self_min < mate_min
            || ( self_min < mate_min + 2 && mate_min >= 4 )
            || wm.interceptTable()->isSelfFastestPlayer()
            || ( wm.existKickableOpponent() && wm.ball().distFromSelf() < 5.0 ) )
    {
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doShootAreaMove. get ball" );
        agent->debugClient().addMessage( "SFW:GetBall(1)" );

        rcsc::Body_Intercept2009().execute( agent );

        if ( self_min == 4 && opp_min >= 2 )
        {
            agent->setViewAction( new rcsc::View_Wide() );
        }
        else if ( self_min == 3 && opp_min >= 2 )
        {
            agent->setViewAction( new rcsc::View_Normal() );
        }

        if ( wm.self().pos().x > 30.0 )
        {
            agent->setNeckAction( new rcsc::Neck_TurnToGoalieOrScan() );
        }
        else
        {
            agent->setNeckAction( new rcsc::Neck_TurnToBallOrScan() );
        }
        return;
    }

    //------------------------------------------------------
    if ( self_min < 20
            && self_min < mate_min
            && wm.ball().pos().absY() > 19.0
            && wm.interceptTable()->isOurTeamBallPossessor() )
    {
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doShootAreaMove. get ball(2)" );
        agent->debugClient().addMessage( "SFW:GetBall(2)" );

        rcsc::Body_Intercept2009().execute( agent );

        if ( self_min == 4 && opp_min >= 2 )
        {
            agent->setViewAction( new rcsc::View_Wide() );
        }
        else if ( self_min == 3 && opp_min >= 2 )
        {
            agent->setViewAction( new rcsc::View_Normal() );
        }

        agent->setNeckAction( new rcsc::Neck_TurnToBallOrScan() );
        return;
    }

    //------------------------------------------------------
    // decide move target point & dash power
    const rcsc::Vector2D target_point = getShootAreaMoveTarget( agent, home_pos );
    const double dash_power = getShootAreaMoveDashPower( agent, target_point );
    double dist_thr = wm.ball().distFromSelf() * 0.1;
    if ( dist_thr < 1.0 ) dist_thr = 1.0;

    rcsc::dlog.addText( rcsc::Logger::ROLE,
                        __FILE__": doShootAreaMove. go to cross point (%.2f, %.2f)",
                        target_point.x, target_point.y );

    agent->debugClient().addMessage( "ShootMoveP%.0f", dash_power );
    agent->debugClient().setTarget( target_point );
    agent->debugClient().addCircle( target_point, dist_thr );


    if ( wm.self().pos().x > target_point.x + dist_thr*0.5
            && std::fabs( wm.self().pos().x - target_point.x ) < 3.0
            && wm.self().body().abs() < 10.0 )
    {
        agent->debugClient().addMessage( "Back" );
        double back_dash_power
            = wm.self().getSafetyDashPower( -dash_power );
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doShootAreaMove. Back Move" );
        agent->doDash( back_dash_power );
        agent->setNeckAction( new rcsc::Neck_TurnToBallOrScan() );
        return;
    }

    if ( ! rcsc::Body_GoToPoint( target_point, dist_thr, dash_power,
                                 5, // cycle
                                 false, // no back dash
                                 true, // save recovery
                                 20.0 // dir thr
                               ).execute( agent ) )
    {
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doShootAreaMove. already target point. turn to front" );
        rcsc::Body_TurnToAngle( 0.0 ).execute( agent );
    }

    if ( wm.self().pos().x > 35.0 )
    {
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doShootAreaMove. Neck to Goalie or Scan" );
        agent->setNeckAction( new rcsc::Neck_TurnToGoalieOrScan() );
    }
    else
    {
        rcsc::dlog.addText( rcsc::Logger::ROLE,
                            __FILE__": doShootAreaMove. Neck to Ball or Scan" );
        agent->setNeckAction( new rcsc::Neck_TurnToBallOrScan() );
    }
}

/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/*!

 */
/*
    ht: 20140905
        from rolecenterbackmove::doDangerAreaMove(PlayerAgent * agent, const Vector2D & home_pos)
        因为原来是调用关系，为避免混乱，直接copy过来了，后面应据相应role作适当调整
*/
void
roleoffensivehalfmove::doDangerAreaMove(PlayerAgent * agent,
                                        const Vector2D & home_pos)
{
    const WorldModel & wm = agent->world();

#if 1   //ht: 20140831 20:59
    if ( wm.self().pos().x < -46.5    //Danger sitution!
            && wm.self().isKickable() )
    {
        Body_ClearBall().execute(agent);
        agent->setNeckAction(new Neck_ScanField());
        #ifdef DEBUG2014
        std::cerr << agent->world().time().cycle() << __FILE__
                  << ": (Danger sitution!)Clear(testing...) >>> No." << agent->world().self().unum() << std::endl;
        #endif

        return;
    }

#endif // 1

    //-----------------------------------------------
    // tackle
    if (Bhv_DangerAreaTackle(0.9).execute(agent))
    {
        #ifdef DEBUG2014
        std::cerr << agent->world().time().cycle() << __FILE__ << ": Bhv_DangerAreaTackle >>> No." << agent->world().self().unum() << std::endl;
        #endif // DEBUG2014

        return;
    }


#if 2   //ht:20140831 20:13

    //--------------------------------------------------
    // intercept
    if (wm.ball().vel().absY() > 1.5  //!wm.existKickableOpponent() && !wm.existKickableTeammate()
            && wm.ball().vel().x < 0.0)
    {
        rcsc::Line2D ball_line(wm.ball().pos(), wm.ball().vel().th());
        double goal_line_y = ball_line.getX( wm.self().pos().y );
        if (std::fabs(goal_line_y) < 37.0 ) //37?
        {
            if (Body_Intercept2009().execute(agent))  // or gotopoint?
            {
                #ifdef DEBUG2014
                std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": BA_Danger(Body_Intercept) >>>testing(or just go to point)... \n";
                agent->setNeckAction(new rcsc::Neck_TurnToBall());
                #endif

                return;
            }
        }
    }

#endif // 2


    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();


#if 2   //ht:20140831 20:13

    //--------------------------------------------------
    // intercept
    //
    if (wm.ball().vel().x > 1.0  //!wm.existKickableOpponent() && !wm.existKickableTeammate()
            && self_min <= mate_min
            && self_min <= opp_min )
    {
        rcsc::Line2D ball_line(wm.ball().pos(), wm.ball().vel().th());
        double goal_line_y = ball_line.getX( wm.self().pos().y );
        if (std::fabs(goal_line_y) < 37.0 ) //37?
        {
            if (Body_Intercept2009().execute(agent))  // or gotopoint?
            {
                #ifdef DEBUG2014
                std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": BA_Danger(Body_Intercept) >>>testing(or just go to point)... \n";
                agent->setNeckAction(new rcsc::Neck_TurnToBall());
                #endif

                return;
            }
        }
    }

#endif // 2

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


    if (nearest_opp && wm.self().pos().x <= wm.ball().pos().x && fabs(wm.ball().pos().y) < 12.0)
    {
        Vector2D target_point ;
        double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);
        target_point.x = (nearest_opp_pos.x + -52.0 )/2;
        target_point.y = (nearest_opp_pos.y + 0)/2;
        Body_GoToPoint(target_point, 0.1, dash_power);
    }
    if (fastest_opp && fastest_opp_pos.absY() < 13.0)     //fastest_opp_pos.absY() < 13.0  20140831 20:21
    {
        Vector2D target_pos = fastest_opp_pos + fastest_opp->vel();
        Body_GoToPoint(target_pos, 0.1, ServerParam::i().maxDashPower());
    }
//  if (opp_trap_pos.absY() >= ServerParam::i().goalHalfWidth()
//      || mate_min < self_min - 2)
    if ( !wm.interceptTable()->isOurTeamBallPossessor()
            && markCloseOpp(agent) )
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
        Body_Intercept2009().execute( agent );
        agent->setNeckAction( new Neck_OffensiveInterceptNeck() );

        return;
    }

#if 3
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


        rolecenterbackmove().doGoToPoint(agent, target_point, dist_thr, ServerParam::i().maxDashPower(), 15.0); // dir_thr
        if (fastest_opp && opp_min <= 1)
        {
            agent->setNeckAction(new Neck_TurnToBallAndPlayer(fastest_opp));
        }
        else
        {
            agent->setNeckAction(new Neck_TurnToBall());
        }

        return;
    }

    ////////////////////////////////////////////////////////
    // search mark target opponent
    if (self_min < mate_min)
        rolecenterbackmove().doDangerGetBall(agent, home_pos);
    else
    {
        markCloseOpp(agent);
//    dlog.addText(Logger::ROLE, __FILE__": doDangerMove. done doDangetGetBall");
        return;
    }
//  dlog.addText(Logger::ROLE, __FILE__": no gettable point in danger mvve");

    Bhv_BasicMove().execute(agent);
#endif  //3
}

/*-------------------------------------------------------------------*/
/*!

 */
/*
    ht: 20140905
        from rolecenterbackmove::doCrossBlockAreaMove(PlayerAgent * agent, const Vector2D & home_pos)
        因为原来是调用关系，为避免混乱，直接copy过来了，后面应据相应role作适当调整
    20141001 重写了
*/
void
roleoffensivehalfmove::doCrossBlockAreaMove(PlayerAgent * agent,
        const Vector2D & home_pos)
{
    //
    // tackle
    //
    if (Bhv_DangerAreaTackle(0.9).execute(agent))
    {
        return;
    }


    const WorldModel & wm = agent->world();

    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();

    if ( self_min <= mate_min
            && self_min < opp_min
            && ! wm.existKickableTeammate()
            && Body_Intercept2009().execute(agent) )
    {
        agent->setNeckAction(new rcsc::Neck_TurnToBall());
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_Intercept2009... \n";
        #endif // DEBUG2014


        return;
    }

    const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();

    const double fastest_opp_dist = ( fastest_opp
                                      ? fastest_opp->distFromSelf()
                                      : 1000.0 );
    if ( fastest_opp_dist < 2.7 )
    {
        Vector2D target_point = fastest_opp->pos() + fastest_opp->vel() ;
        double dash_power = rcsc::ServerParam::i().maxPower();
        rolecenterbackmove().doGoToPoint(agent, target_point, 0.1,dash_power, 15.0);
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doGoToPoint.\n";
        #endif // DEBUG2014


        return;
    }

    rolecenterbackmove().doMarkMove( agent, home_pos );

    return;
}

//void
//roleoffensivehalfmove::doCrossBlockAreaMove(PlayerAgent * agent,
//    const Vector2D & home_pos)
//{
////-----------------------------------------------
//  //
//  // tackle
//  //
//  if (Bhv_DangerAreaTackle(0.9).execute(agent))
//  {
//    return;
//  }
//
//  const WorldModel & wm = agent->world();//11111
//  const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();
//  const PlayerPtrCont & opps = wm.opponentsFromSelf();
//  const PlayerObject * nearest_opp
//        = ( opps.empty()
//            ? static_cast< PlayerObject * >( 0 )
//            : opps.front() );
//  const double nearest_opp_dist = ( nearest_opp
//                                      ? nearest_opp->distFromSelf()
//                                      : 1000.0 );
//  const Vector2D nearest_opp_pos = ( nearest_opp
//                                       ? nearest_opp->pos()
//                                       : Vector2D( -1000.0, 0.0 ) );
//  int self_min = wm.interceptTable()->selfReachCycle();
//  int mate_min = wm.interceptTable()->teammateReachCycle();
//  int opp_min = wm.interceptTable()->opponentReachCycle();
//
//#if 1
////ht: ht:20140830 01:36
//if (nearest_opp_dist < 3.0)
//{
//    markCloseOpp(agent);
//    return;
//}
//#endif // 1
//
//  if (wm.self().unum() == 8 && wm.ball().pos().y > 1.0)
//  {
//     if (wm.ball().distFromSelf() > 12.0 && wm.ball().pos().y > 24.0)
//     rolecenterbackmove().doMarkMove(agent, home_pos);
//     if (wm.ball().distFromSelf() < 4.0 && wm.ball().pos().y < 18.0 && self_min < opp_min + 2.0)
//     Body_ClearBall().execute( agent );
//
//     Vector2D target_point = wm.ball().pos() + wm.ball().vel();
//    // decide dash power
//    double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);
//
//    double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
//    if (dist_thr < 0.5)
//      dist_thr = 0.5;
//
//    rolecenterbackmove().doGoToPoint(agent, target_point, dist_thr, dash_power, 15.0); // dir_thr
//  }
//  if (wm.self().unum() == 7 && wm.ball().pos().y < -1.0)
//  {
//     if (wm.ball().distFromSelf() > 12.0 && wm.ball().pos().y < -24.0)
//     markCloseOpp(agent);
//     if (wm.ball().distFromSelf() < 4.0 && wm.ball().pos().y > -18.0 && self_min < opp_min + 2.0)
//     Body_ClearBall().execute( agent );
//
//     Vector2D target_point = wm.ball().pos() + wm.ball().vel();
//    // decide dash power
//    double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);
//
//    double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
//    if (dist_thr < 0.5)
//      dist_thr = 0.5;
//
//    rolecenterbackmove().doGoToPoint(agent, target_point, dist_thr, dash_power, 15.0); // dir_thr
//  }
//
//  if (nearest_opp)
//  {
//     Vector2D target_point ;
//     double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);
//     target_point.x = (nearest_opp_pos.x + -52.0 )/2;
//     target_point.y = nearest_opp_pos.y/2;
//     rolecenterbackmove().doGoToPoint(agent, target_point, 0.1,dash_power, 15.0);
//  }
//  if (fastest_opp)
//  {
//     Vector2D target_point = wm.ball().pos() ;
//     double dash_power = rcsc::ServerParam::i().maxPower();
//     rolecenterbackmove().doGoToPoint(agent, target_point, 0.1,dash_power, 15.0);
//  }
//  markCloseOpp(agent);
//}
//
