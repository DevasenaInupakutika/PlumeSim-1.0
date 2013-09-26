/*
 *  PSRect.h
 *  
 *
 *  Created by Gonçalo Cabrita and Pedro Sousa on 02/15/2010.
 *  Copyright 2010 ISR. All rights reserved.
 *
 *	Comments:
 *	No comments.
 *
 */

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/*!
 *
 * \file PSRect.h
 *
 * \brief This file includes the structure PSRect.
 *
 * \author Gonçalo Cabrita
 * \author Pedro Sousa
 * \date 02/15/2010
 * \version 0.1
 *
 * \bug none discovered
 *
 * \note
 */
 
#include <libplayercore/playercore.h>

/*!
 *
 * \struct PSRect
 * It defines a rectangle from a 2D starting point and a 2D ending point.
 * It already defines an object.
 *
 */
typedef struct
{
	player_point_2d_t startPoint;
	player_point_2d_t endPoint;
	
} PSRect;

// EOF
