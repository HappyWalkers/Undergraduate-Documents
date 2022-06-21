// -*-c++-*-

/*!
  \file bhv_shoot2008.h
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

#ifndef RCSC_ACTION_BHV_SHOOT2008_H
#define RCSC_ACTION_BHV_SHOOT2008_H

#include "shoot_table2008.h"

#include <rcsc/player/soccer_action.h>
#include <rcsc/geom/vector_2d.h>

using namespace rcsc;

namespace rcsc {

/*!
  \class Bhv_Shoot2008
  \brief advanced shoot planning and behavior.
 */
class Bhv_Shoot2008
    : public SoccerBehavior {
private:

    Vector2D M_shoot_point;
    bool     M_shoot_check;

    //! cached shoot table
    static ShootTable2008 S_shoot_table;
//
//    /*!
//	\return return best shoot point.
//	\brief if return true means that prob of goal is above 95 %.
//    */
//    bool get_best_shoot( PlayerAgent * agent , Vector2D& point_ );

public:
    /*!
      \brief accessible from global.
     */
    Bhv_Shoot2008()
    : M_shoot_point( Vector2D::INVALIDATED )
    , M_shoot_check( false )
    {
    }

    /*!
      \brief execute action
      \param agent pointer to the agent itself
      \return true if action is performed
     */
    bool execute( PlayerAgent * agent );

    /*!
      \brief execute action
      \param agent pointer to the agent itself
      \return true if action is performed
     */
    bool execute_test( PlayerAgent * agent );

    /*!
      \brief get the current shoot table
      \return const reference to the shoot table instance.
     */

    /*!
	\return return best shoot point.
	\brief if return true means that prob of goal is above 95 %.
    */
    bool get_best_shoot( PlayerAgent * agent , Vector2D& point_ );


    static
    ShootTable2008 & shoot_table()
      {
          return S_shoot_table;
      }

};

}

#endif
