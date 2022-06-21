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
#include "role_defensive_half_move.h"
#include "role_offensive_half_move.h"
#include <rcsc/action/body_go_to_point2010.h>
#include "bhv_basic_move.h"
#include <rcsc/geom.h>
#include "bhv_dangerAreaTackle.h"
#include <rcsc/geom/ray_2d.h>
#include "strategy.h"
#include <rcsc/action/bhv_go_to_point_look_ball.h>
#include "bhv_basic_tackle.h"
#include "role_center_back_move.h"

#include <rcsc/action/basic_actions.h>
#include <rcsc/action/body_go_to_point.h>
#include <rcsc/action/body_clear_ball.h>
#include <rcsc/action/body_intercept.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_ball_or_scan.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>
#include <rcsc/action/neck_turn_to_ball_and_player.h>
#include <iostream>
#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>
#include <rcsc/player/intercept_table.h>
#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>

#include "neck_offensive_intercept_neck.h"
using namespace std;
using namespace rcsc;

/*-------------------------------------------------------------------*/
/*!

 */
void
roledefensivehalfmove::doCrossBlockMove(rcsc::PlayerAgent* agent)
{
    const WorldModel & wm = agent->world();
    Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());

    //-----------------------------------------------
    // tackle
    if (Bhv_BasicTackle(0.8, 80.0).execute(agent))
    {
        return;
    }

    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();
    bool meFastest = false;
    if (self_min < mate_min && self_min < opp_min)
        meFastest = true;
    if (meFastest)
    {
        Body_Intercept2009().execute(agent);
        agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
        return;
    }

#if 1
    //
    //mark    ht:20140906 17:07
    //
    if ( ( wm.existKickableOpponent() || !wm.existKickableTeammate() )
            && roleoffensivehalfmove().markCloseOpp(agent) )
    {
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": markCloseOpp...\n";
        #endif

        return;
    }
#endif  //1

    if (roledefensivehalfmove().doDangerGetBall(agent,home_pos))
    {
//    //      cout<<"91"<<endl;
        return;
    }
    double dash_power;

    if (wm.ball().distFromSelf() > 30.0)
    {
        dash_power = wm.self().playerType().staminaIncMax() * 0.9;
//    rcsc::dlog.addText(rcsc::Logger::ROLE,
//        __FILE__": ball is too far. dash_power=%.1f", dash_power);
    }
    else if (wm.ball().distFromSelf() > 20.0)
    {
        dash_power = rcsc::ServerParam::i().maxPower() * 0.5;
    }
    else
    {
        dash_power = rcsc::ServerParam::i().maxPower() * 0.9;
    }

    if (wm.existKickableTeammate())
    {
        dash_power = std::min(rcsc::ServerParam::i().maxPower() * 0.5, dash_power);
    }

    dash_power = wm.self().getSafetyDashPower(dash_power);

    double dist_thr = wm.ball().distFromSelf() * 0.1;
    if (dist_thr < 0.5)
        dist_thr = 0.5;

    if (!rcsc::Body_GoToPoint(home_pos, dist_thr, dash_power).execute(agent))
    {
        rcsc::AngleDeg body_angle(
            wm.ball().angleFromSelf().abs() < 80.0 ? 0.0 : 180.0);
        rcsc::Body_TurnToAngle(body_angle).execute(agent);
    }

    agent->setNeckAction(new rcsc::Neck_TurnToBall());
}

/*-------------------------------------------------------------------*/
/*!

 */
void
roledefensivehalfmove::doOffensiveMove(rcsc::PlayerAgent * agent)
{
    Vector2D ballPos = agent->world().ball().pos();
    const WorldModel & wm = agent->world();
    Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());

    static bool s_recover_mode = false;
//************************************************add jelly
    const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();
    const Vector2D fastest_opp_pos = ( fastest_opp
                                       ? fastest_opp->pos()
                                       : Vector2D( -1000.0, 0.0 ) );
//***********************************************************

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
            && ( self_min <= 3 || (self_min <= mate_min && self_min <= opp_min + 1) ) )    //self_min <= opp_min && self_min < mate_min?
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
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_Intercept(1)...\n";
        #endif // DEBUG2014


        return;
    }

#if 1
    //
    //mark  ht:20140906 13:01
    //
    if ( ( !wm.existKickableTeammate() || wm.existKickableOpponent() )
            && roleoffensivehalfmove().markCloseOpp(agent) )
    {
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << ": No.6 markCloseOpp...\n";
        #endif // DEBUG2014

        return;
    }

#endif // 1

//
// back to home_pos
//

    if (wm.self().stamina() < rcsc::ServerParam::i().staminaMax() * 0.5)
    {
        s_recover_mode = true;
    }
    else if (wm.self().stamina() > rcsc::ServerParam::i().staminaMax() * 0.7)
    {
        s_recover_mode = false;
    }

    double dash_power = rcsc::ServerParam::i().maxPower();
    const double my_inc = wm.self().playerType().staminaIncMax()
                          * wm.self().recovery();

//  if (wm.ourDefenseLineX() <wm.self().pos().x      //">" gai"<" jelly 2014-8-11
//      && wm.ball().pos().x < wm.ourDefenseLineX() + 20.0)
//  {
//    dash_power = rcsc::ServerParam::i().maxPower();
//
//  }
////******************************
//if(fastest_opp&&(wm.ourDefenseLineX()+5 > wm.ball().pos().x))//add jelly
// {
//         Vector2D Pos =fastest_opp_pos;
//        double dash_power = rolecenterbackmove().get_dash_power(agent, Pos);
//        //Body_GoToPoint2010(wm.ball().pos(),0.1,ServerParam::i().maxDashPower()*1.2);
//        Body_GoToPoint(Pos,0.1,dash_power);
//         dlog.addText( Logger::TEAM,
//                      __FILE__": intercept" );
//        Body_Intercept().execute( agent );
//        agent->setNeckAction( new Neck_TurnToBall());
//   }
////*************************************
    if (s_recover_mode)
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
roledefensivehalfmove::doDefensiveMove(rcsc::PlayerAgent * agent)
{
//  //      cout<<"BA_DefMidField-begin"<<endl;
    Vector2D ballPos = agent->world().ball().pos();
    const WorldModel & wm = agent->world();
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

    //////////////////////////////////////////////////////

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

    const rcsc::Vector2D self_reach_point = wm.ball().inertiaPoint(self_min);
    const rcsc::Vector2D opp_reach_point = wm.ball().inertiaPoint(opp_min);

    if (!wm.existKickableTeammate()
            && self_min <= opp_min    //20140906
#if 1
            && self_reach_point.dist(home_pos) < 13.0
#endif
            && (self_min <= mate_min
                || self_min <= 3 && wm.ball().pos().dist2(home_pos) < 10.0 * 10.0
                || self_min <= 5 && wm.ball().pos().dist2(home_pos) < 8.0 * 8.0))
    {
        if ( opp_min < mate_min - 1
                && rolecenterbackmove().Bhv_BlockDribble(agent) )
        {
            agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
            #ifdef DEBUG2014
            std::cerr << wm.time().cycle() << __FILE__ << ": No.6 Bhv_BlockDribble...\n";
            #endif // DEBUG2014

            return;
        }

        if ( Body_Intercept2009().execute(agent) )
        {
            if (self_min == 4 && opp_min >= 2)
            {
                agent->setViewAction(new rcsc::View_Wide());
            }
            else if (self_min == 3 && opp_min >= 2)
            {
                agent->setViewAction(new rcsc::View_Normal());
            }

            agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
            #ifdef DEBUG2014
            std::cerr << wm.time().cycle() << __FILE__ << ": No.6 Body_Intercept...\n";
            #endif // DEBUG2014

            return;
        }

    }

#if 1
    //
    //mark    ht: 20140906 12:09
    //
    if ( home_pos.absY() < 17
            && ( !wm.existKickableTeammate() || wm.existKickableOpponent() )
            && roleoffensivehalfmove().markCloseOpp(agent) )
    {
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << ": No.6 markCloseOpp...\n";
        #endif // DEBUG2014

        return;
    }

#endif  //1


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
roledefensivehalfmove::doDribbleBlockMove(rcsc::PlayerAgent* agent)
{
    Vector2D ballPos = agent->world().ball().pos();
    const WorldModel & wm = agent->world();
    Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());
    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();
    bool meFastest = false;
    if (self_min < mate_min && self_min < opp_min)
        meFastest = true;
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
roledefensivehalfmove::doCrossAreaMove(rcsc::PlayerAgent * agent)
{
    if ( ! doDistMark( agent ) )
    {
        Bhv_BasicMove().execute(agent);
    }
}

bool
roledefensivehalfmove::doDangerGetBall(PlayerAgent * agent,
                                       const rcsc::Vector2D & home_pos)
{
//  //      cout<<"479"<<endl;
    //////////////////////////////////////////////////////////////////
    // tackle
    if (Bhv_DangerAreaTackle().execute(agent))
    {
//    dlog.addText(Logger::ROLE, __FILE__": doDangetGetBall done tackle");
        return true;
    }
//  //      cout<<"487"<<endl;
    const WorldModel & wm = agent->world();

    //--------------------------------------------------
    if (wm.existKickableTeammate() || wm.ball().pos().x > -36.0
            || wm.ball().pos().dist(home_pos) > 7.0 || wm.ball().pos().absY() > 9.0)
    {
//    dlog.addText(Logger::ROLE,
//        __FILE__": doDangetGetBall. no danger situation");
        return false;
    }

    const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();

    if (wm.existKickableOpponent())
    {
        Vector2D opp_pos = wm.opponentsFromBall().front()->pos();

        if (wm.self().pos().x < opp_pos.x
                && std::fabs(wm.self().pos().y - opp_pos.y) < 0.8)
        {

            Vector2D opp_vel = wm.opponentsFromBall().front()->vel();
            opp_pos.x -= 0.2;
            if (opp_vel.x < -0.1)
            {
                opp_pos.x -= 0.1;
            }
            if (opp_pos.x > wm.self().pos().x
                    && fabs(opp_pos.y - wm.self().pos().y) > 0.8)                               //??????????????????
            {
                opp_pos.x = wm.self().pos().x;
            }

            //      //      cout<<"526"<<endl;
            Body_GoToPoint(opp_pos, 0.1, ServerParam::i().maxPower()).execute(agent);
            //      cout<<"528"<<endl;
            if (fastest_opp)
            {
                agent->setNeckAction(new Neck_TurnToBallAndPlayer(fastest_opp));
            }
            else
            {
                agent->setNeckAction(new Neck_TurnToBall());
            }
            //      cout<<"the strange point"<<endl;
            return true;
        }
    }
    else
    {
        int self_min = wm.interceptTable()->selfReachCycle();
        Vector2D selfInterceptPoint = wm.ball().inertiaPoint(self_min);
        if (self_min <= 2 && selfInterceptPoint.dist(home_pos) < 10.0)                         //need to change?
        {
//      dlog.addText(Logger::ROLE,
//          __FILE__": doDangetGetBall. intercept. reach cycle = %d", self_min);
//      agent->debugClient().addMessage("DangerGetBall");
            //      cout<<"550"<<endl;
            Body_Intercept2009().execute(agent);
            //      cout<<"551"<<endl;
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
roledefensivehalfmove::doDangerAreaMove(PlayerAgent * agent)
{
    //-----------------------------------------------
    // tackle
    if (Bhv_DangerAreaTackle().execute(agent))
    {
        return;
    }

    const WorldModel & wm = agent->world();

#if 1   //ht: 20140929 09:20
    if ( wm.self().isKickable()
            && (wm.self().pos().x > wm.ball().pos().x || wm.ball().pos().x < -50.0) )
    {
        //（每个球员）可以再加一个禁区罚球（x<-47）时，可以tackle就直接tackle?
        Body_ClearBall().execute(agent);
        agent->setNeckAction(new Neck_ScanField());
        #ifdef DEBUG2014
        std::cerr << agent->world().time().cycle() << __FILE__ << ": Clear(testing...) >>> No." << agent->world().self().unum() << std::endl;
        #endif

    }

#endif // 1


    Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());
    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();
    const PlayerObject * fastest_opp = wm.interceptTable()->fastestOpponent();

    Vector2D opp_trap_pos = wm.ball().inertiaPoint(opp_min);

    if ( !wm.existKickableOpponent()
            && !wm.existKickableTeammate()
            && self_min <= mate_min
            && self_min <= opp_min
            && Body_Intercept2009().execute( agent ) )
    {
        agent->setNeckAction(new rcsc::Neck_TurnToBall());
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_Intercept... \n";
        #endif // DEBUG2014


        return;
    }

    if (opp_trap_pos.absY() >= ServerParam::i().goalHalfWidth()
            || mate_min < self_min - 2)
    {
        rolecenterbackmove().doMarkMove(agent, home_pos);   //need to change
        return;
    }

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
        double dash_power = rolecenterbackmove().get_dash_power(agent, target_point);

        //double dist_thr = wm.ball().distFromSelf() * 0.1;
        double dist_thr = wm.ball().pos().dist(target_point) * 0.1;
        if (dist_thr < 0.5)
            dist_thr = 0.5;

//    dlog.addText(Logger::ROLE,
//        __FILE__": doDangerMove correct target point to block center");
//    agent->debugClient().addMessage("CB:DangerBlockCenter%.0f", dash_power);
//    agent->debugClient().setTarget(target_point);
//    agent->debugClient().addCircle(target_point, dist_thr);

        rolecenterbackmove().doGoToPoint(agent, target_point, dist_thr, dash_power, 15.0); // dir_thr
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
    if ( self_min < mate_min
            && doDangerGetBall(agent, home_pos))
    {
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": doDangerGetBall... \n";
        #endif // DEBUG2014

        return;
    }
    else
    {
        rolecenterbackmove().doMarkMove(agent, home_pos);
//    dlog.addText(Logger::ROLE, __FILE__": doDangerMove. done doDangetGetBall");
        return;
    }
//  dlog.addText(Logger::ROLE, __FILE__": no gettable point in danger mvve");
}

/*-------------------------------------------------------------------*/
/*!

 */
void
roledefensivehalfmove::doShootChanceMove(PlayerAgent * agent)
{
    const WorldModel & wm = agent->world();

    Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());

    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();

    ///////////////////////////////////////////////////
    // tackle
    if (Bhv_BasicTackle(0.8, 80.0).execute(agent))
    {
        return;
    }

    //
    //intercept
    //
    if ( self_min < mate_min
            && self_min <= opp_min
            && !wm.existKickableTeammate()
            && Body_Intercept2009().execute( agent ) )
    {
        agent->setNeckAction(new rcsc::Neck_TurnToBall());
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_Intercept... \n";
        #endif // DEBUG2014


        return;
    }

    //
    //mark
    //
    if ( ! doDistMark( agent ) )
    {
        Bhv_BasicMove().execute( agent );
    }
    rolecenterbackmove().doMarkMove( agent, home_pos );

    return;
}

/*-------------------------------------------------------------------*/
/*!
    ht: 20141002
    for half
*/
bool
roledefensivehalfmove::doDistMark( PlayerAgent * agent )
{
    const WorldModel & wm = agent->world();
    Vector2D home_pos = Strategy::i().getPosition(wm.self().unum());

    int self_min = wm.interceptTable()->selfReachCycle();
    int mate_min = wm.interceptTable()->teammateReachCycle();
    int opp_min = wm.interceptTable()->opponentReachCycle();

    //
    //intercept
    //
    if ( wm.interceptTable()->isSelfFastestPlayer()
            && self_min < 7    //testing...
            && Body_Intercept2009().execute(agent) )
    {
        agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
        #ifdef DEBUG2014
        std::cerr << wm.time().cycle() << __FILE__ << wm.self().unum() << ": Body_Intercept... \n";
        #endif // DEBUG2014


        return true;
    }

    //
    //check mark
    //

    //ball to home_pos too close
    if ( home_pos.dist( wm.ball().pos() ) < 10.0 )
    {
        return false;
    }

    //check opp
    double dist_opp_to_home = 222.0;
    const PlayerObject * nearest_opp = wm.getOpponentNearestTo( home_pos, 3, &dist_opp_to_home );

//    //check any other mates
//
//    const double dist_mate_to_opp = wm.getDistTeammateNearestTo( nearest_opp->pos(), 1 );

    if ( nearest_opp
            && wm.ball().pos().dist2( nearest_opp->pos() ) + 3.0*3.0 > wm.ball().pos().dist2( home_pos )
            && wm.getDistTeammateNearestTo( nearest_opp->pos(), 1 ) > 3.5 )
    {
        //doDistMark
    }
    else
    {
        return false;
    }

    //decide mark_point
    AngleDeg mark_angle = ( wm.ball().pos() - nearest_opp->pos()).th();
    double dist_thr = wm.ball().pos().dist( nearest_opp->pos() ) * 0.15;
//    double dist_thr = wm.ball().pos().dist( nearest_opp->pos() ) - wm.ball().pos().dist( wm.self().pos() );   //testing...
    Vector2D mark_point = nearest_opp->pos() + Vector2D::polar2vector( dist_thr, mark_angle );

    //decide dash_power
    const double dash_power = ServerParam::i().maxDashPower() * 0.8;

    if ( ! Body_GoToPoint( mark_point,
                           0.1,
                           dash_power
                         ).execute( agent ) )
    {
        // already there
        Body_TurnToBall().execute( agent );

    }
    agent->setNeckAction( new Neck_TurnToBall() );

    return true;

}
