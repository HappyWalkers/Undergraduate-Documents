// -*-c++-*-

/*
 *Copyright:

 Copyright (C) Hiroki SHIMORA

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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sample_field_evaluator.h"
#include "field_analyzer.h"
#include "simple_pass_checker.h"
#include "strategy.h"

#include <rcsc/player/player_evaluator.h>
#include <rcsc/common/server_param.h>
#include <rcsc/common/logger.h>
#include <rcsc/math_util.h>

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cfloat>

// #define DEBUG_PRINT

using namespace rcsc;
using namespace std;

static const int VALID_PLAYER_THRESHOLD = 8;


/*-------------------------------------------------------------------*/
/*!

 */
static double evaluate_state( const PredictState & state );


/*-------------------------------------------------------------------*/
/*!

 */
SampleFieldEvaluator::SampleFieldEvaluator()
{

}

/*-------------------------------------------------------------------*/
/*!

 */
SampleFieldEvaluator::~SampleFieldEvaluator()
{

}

/*-------------------------------------------------------------------*/
/*!

 */
double
SampleFieldEvaluator::operator()( const PredictState & state,
                                  const std::vector< ActionStatePair > & /*path*/ ) const
{
    const double final_state_evaluation = evaluate_state( state );

    //
    // ???
    //

    double result = final_state_evaluation;

    return result;
}


/*-------------------------------------------------------------------*/
/*!

 */
static
double
evaluate_state( const PredictState & state )
{
    const ServerParam & SP = ServerParam::i();

    Vector2D theirGoalPos = ServerParam::i().theirTeamGoalPos();
    theirGoalPos.x-=5.0;

    const AbstractPlayerObject * holder = state.ballHolder();

#ifdef DEBUG_PRINT
    dlog.addText( Logger::ACTION_CHAIN,
                  "========= (evaluate_state) ==========" );
#endif

    //
    // if holder is invalid, return bad evaluation
    //
    if ( ! holder )
    {
#ifdef DEBUG_PRINT
        dlog.addText( Logger::ACTION_CHAIN,
                      "(eval) XXX null holder" );
#endif
        return - DBL_MAX / 2.0;
    }

    const int holder_unum = holder->unum();


    //
    // ball is in opponent goal
    //
    if ( state.ball().pos().x > + ( SP.pitchHalfLength() - 0.1 )
         && state.ball().pos().absY() < SP.goalHalfWidth() + 2.0 )
    {
#ifdef DEBUG_PRINT
        dlog.addText( Logger::ACTION_CHAIN,
                      "(eval) *** in opponent goal" );
#endif
        return +1.0e+7;
    }

    //
    // ball is in our goal
    //
    if ( state.ball().pos().x < - ( SP.pitchHalfLength() - 0.1 )
         && state.ball().pos().absY() < SP.goalHalfWidth() )
    {
#ifdef DEBUG_PRINT
        dlog.addText( Logger::ACTION_CHAIN,
                      "(eval) XXX in our goal" );
#endif

        return -1.0e+7;
    }


    //
    // out of pitch
    //
    if ( state.ball().pos().absX() > SP.pitchHalfLength()
         || state.ball().pos().absY() > SP.pitchHalfWidth() )
    {
#ifdef DEBUG_PRINT
        dlog.addText( Logger::ACTION_CHAIN,
                      "(eval) XXX out of pitch" );
#endif

        return - DBL_MAX / 2.0;
    }


    //
    // set basic evaluation
    //
#if 1
    double point = state.ball().pos().x;
    if(state.ball().pos().x>32.0)
     {     
    	 //if(fabs(state.ball().pos().y)<14)
    		 point += std::max( 0.0,
    				 60.0 - ServerParam::i().theirTeamGoalPos().dist( state.ball().pos() ) - fabs(state.ball().pos().y)/15 );
    	 //else
    		// point += std::max( 0.0,
    			//	 40.0 - ServerParam::i().theirTeamGoalPos().dist( state.ball().pos() ) );
     }
     else
		 point += std::max( 0.0,
				 40.0 - ServerParam::i().theirTeamGoalPos().dist( state.ball().pos() ) );
#endif

#if 0
    double point = state.ball().pos().x;
     if(fabs(state.ball().pos().y)>14)
      point += std::max( 0.0,
                       40.0 - ServerParam::i().theirTeamGoalPos().dist( state.ball().pos() ) );
     else
      point += std::max( 0.0,
    		  60.0 - ServerParam::i().theirTeamGoalPos().dist( state.ball().pos() ) - fabs(state.ball().pos().y)/15 );
#endif

#if 1
     if(holder->side()==state.ourSide())
    {
      if(state.ball().pos().x>40.0)
      {
    	  if(FieldAnalyzer::get_dist_player_nearest_to_point(state.ball().pos(),state.opponents(),1.0)>3.0)
    		  point+=20.0;
    	  else
    		  point-=40.0;
      }
      else if(state.ball().pos().x>25.0)
      {
    	  if(FieldAnalyzer::get_dist_player_nearest_to_point(state.ball().pos(),state.opponents(),1.0)>3.0)
    		  point+=30.0;
    	  else
    		  point-=60.0;
      }
      else if(state.ball().pos().x>0.0)
      {
    	  if(FieldAnalyzer::get_dist_player_nearest_to_point(state.ball().pos(),state.opponents(),1.0)>4.0)
    		  point+=30.0;
    	  else
    		  point-=60.0;
      }
    }
#endif

#ifdef DEBUG_PRINT
    dlog.addText( Logger::ACTION_CHAIN,
                  "(eval) ball pos (%f, %f)",
                  state.ball().pos().x, state.ball().pos().y );

    dlog.addText( Logger::ACTION_CHAIN,
                  "(eval) initial value (%f)", point );
#endif

    //
    // add bonus for goal, free situation near offside line
    //
    if ( FieldAnalyzer::can_shoot_from
         ( holder->unum() == state.self().unum(),
           holder->pos(),
           state.getPlayerCont( new OpponentOrUnknownPlayerPredicate( state.ourSide() ) ),
           VALID_PLAYER_THRESHOLD ) )
    {

   // 	cout<<"point1: "<<point<<endl;
    //	cout<<"这里进入可以射门的范围"<<endl;
        point += 1.0e+6;
     //   cout<<"point2: "<<point<<endl;
#ifdef DEBUG_PRINT
        dlog.addText( Logger::ACTION_CHAIN,
                      "(eval) bonus for goal %f (%f)", 1.0e+6, point );
#endif

        if ( holder_unum == state.self().unum() )
        {
            point += 5.0e+5;
#ifdef DEBUG_PRINT
            dlog.addText( Logger::ACTION_CHAIN,
                          "(eval) bonus for goal self %f (%f)", 5.0e+5, point );
#endif
        }
    }




    return point;
}
