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

#include "bhv_dangerAreaTackle.h"

#include <rcsc/action/neck_turn_to_ball_or_scan.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>

/*-------------------------------------------------------------------*/
/*!
 execute action
 */
bool
Bhv_DangerAreaTackle::execute(rcsc::PlayerAgent * agent)
{
  rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": Bhv_DangerAreaTackle");

  if (!agent->world().existKickableOpponent()
      || agent->world().self().tackleProbability() < M_min_probability)
  {
    rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": failed");
    return false;
  }

  if (agent->world().self().pos().absY()
      > rcsc::ServerParam::i().goalHalfWidth() + 5.0)
  {
    double power_or_dir = 0.0;
    if (agent->config().version() >= 12.0)
    {
      if (agent->world().self().body().abs() < 10.0)
      {
        // nothing to do
      }
      else if (agent->world().self().body().abs() > 170.0)
      {
        power_or_dir = 180.0;
      }
      else if (agent->world().self().body().degree()
          * agent->world().self().pos().y < 0.0)
      {
        power_or_dir = 180.0;
      }
    }
    else
    {
      // out of goal
      power_or_dir = rcsc::ServerParam::i().maxTacklePower();
      if (agent->world().self().body().abs() < 10.0)
      {
        // nothing to do
      }
      else if (agent->world().self().body().abs() > 170.0)
      {
        power_or_dir = -rcsc::ServerParam::i().maxBackTacklePower();
        if (power_or_dir >= -1.0)
        {
          return false;
        }
      }
      else if (agent->world().self().body().degree()
          * agent->world().self().pos().y < 0.0)
      {
        power_or_dir = -rcsc::ServerParam::i().maxBackTacklePower();
        if (power_or_dir >= -1.0)
        {
          return false;
        }
      }

      if (std::fabs(power_or_dir) < 1.0)
      {
        return false;
      }
    }

    rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": out of goal width");
    agent->debugClient().addMessage("tackle(1)");
    agent->doTackle(power_or_dir);
    agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
    return true;
  }
  else
  {
    // within goal width
    double power_sign = 0.0;
    double abs_body = agent->world().self().body().abs();

    if (abs_body < 70.0)
      power_sign = 1.0;
    if (abs_body > 110.0)
      power_sign = -1.0;
    if (power_sign == 0.0)
    {
      power_sign = (agent->world().self().body().degree() > 0.0 ? 1.0 : -1.0 );
      if (agent->world().ball().pos().y < 0.0)
      {
        power_sign *= -1.0;
      }
    }

    if (agent->config().version() >= 12.0)
    {
      if (power_sign != 0.0)
      {
        double tackle_dir = 0.0;
        if (power_sign < 0.0)
        {
          tackle_dir = 180.0;
        }

        rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": power_sign = %.0f",
            power_sign);
        agent->debugClient().addMessage("tackle(%.0f)", power_sign);
        agent->doTackle(tackle_dir);
        agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
        return true;
      }
    }
    else
    {
      double tackle_power = (
          power_sign >= 0.0 ?
              rcsc::ServerParam::i().maxTacklePower() :
              -rcsc::ServerParam::i().maxBackTacklePower() );
      if (std::fabs(tackle_power) < 1.0)
      {
        return false;
      }

      if (power_sign != 0.0)
      {
        rcsc::dlog.addText(rcsc::Logger::TEAM, __FILE__": power_sigh =%.0f",
            power_sign);
        agent->debugClient().addMessage("tackle(%.0f)", power_sign);
        agent->doTackle(tackle_power);
        agent->setNeckAction(new rcsc::Neck_TurnToBallOrScan());
        return true;
      }
    }
  }

  return false;
}
