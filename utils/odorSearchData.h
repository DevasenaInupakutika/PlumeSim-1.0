/*
 *  odorSearchData.cpp
 *  
 *
 *  Created by Gonçalo Cabrita and Pedro Sousa on 12/23/09.
 *  Copyright 2009 ISR. All rights reserved.
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
 * \file odorSearchData.h
 *
 * \brief This file includes the structure odor_data_t
 *
 * \author Gonçalo Cabrita
 * \author
 * \date 12/23/2009
 * \version 0.1
 *
 * \bug none discovered
 *
 * \note
 */
 
 
/*!
 *
 * \struct odor_data_t
 * It includes a chemical value as well as the wind speed and direction.
 * It already defines an object.
 *
 */
typedef struct
{
	double chemical;		// ??
	double windSpeed;		// m/s
	double windDirection;	// rad
	
} odor_data_t;

// EOF
