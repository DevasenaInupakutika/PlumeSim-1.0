/*
 *  PSFramePoints.h
 *  
 *
 *  Created by Gonçalo Cabrita and Pedro Sousa on 02/25/2010.
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
 * \file PSFramePoints.h
 *
 * \brief This file defines the class PSFramePoints.  This class is a linked list for holding the odor data through out the map for a given time frame.
 *
 * \author Gonçalo Cabrita
 * \author Pedro Sousa
 * \date 02/25/2010
 * \version 0.1
 *
 * \bug none discovered
 *
 * \note
 *
 */

#include <libplayercore/playercore.h>
#include <math.h>
#include "odorSearchData.h"

/*!
 *
 * \struct frame_point_data_t
 * It defines a data structure holding a 3D point and an odor data structure.
 * It already defines an object.
 *
 */
typedef struct
{
	player_point_3d_t point;
	odor_data_t odor;	

} frame_point_data_t;

class PSFramePoints
{
	public:
	
	/*!
	 * 
	 * \struct node
	 * It includes data concerning odor and position and a pointer to the next node.
	 * It also declares the startNode.
	 *
	 */
	struct node
	{
		frame_point_data_t data;
		node * link;
		
	} * startNode;
	
	int length;		/**< Contains the length of the linked list.*/
	
	//! PSFramePoints constructor.
    /*!
	 * This is the class constructor.
     */
	PSFramePoints();
	//! PSFramePoints destructor.
    /*!
	 * This is the class destructor.
     */
	~PSFramePoints();
	
	/*!
	 *
	 * \fn copy(PSFramePoints * toCopy)
	 * \brief Copy a PSFramePoints object.
	 * \param toCopy A pointer to a PSFramePoints object.
	 * \return none.
	 *
	 */
	void copy(PSFramePoints * toCopy);
	
	/*!
	 * 
	 * \fn push(frame_point_data_t * newPoint)
	 * \brief Adds one element to the end of the list and returns the new length of the list.
	 * \param newPoint A pointer to a frame_point_data_t object.
	 * \return An integer with the length of the list.
	 *
	 */
	int push(frame_point_data_t * newPoint);
	
	/*!
	 *
	 * \fn frame_point_data_t* pop();
	 * \brief Removes the last element from the list and returns the pointer to that item.
	 * \param none.
	 * \return none.
	 *
	 */
	frame_point_data_t* pop();
	
	/*!
	 *
	 * \fn int addAt(frame_point_data_t * newPoint, int index)
	 * \brief Adds one element to the list at a specific index and returns the new length of the list.
	 * \param newPoint A pointer to a frame_point_data_t object.
	 * \param index The integer index.
	 * \return An integer with the length of the list.
	 *
	 */
	int addAt(frame_point_data_t * newPoint, int index);
	
	/*!
	 *
	 * \fn frame_point_data_t* removeAt(int index)
	 * \brief Removes one element from a list at a specific index and returns the pointer to that item.
	 * \param index The integer index.
	 * \return A pointer to the removed item.
	 *
	 */
	frame_point_data_t* removeAt(int index);
	
	/*!
	 *
	 * \fn frame_point_data_t* itemAt(int index)
	 * \brief Returns the pointer to an item on a specific index.
	 * \param index The integer index.
	 * \return The pointer to the item for the provided index.
	 *
	 */
	frame_point_data_t* itemAt(int index);
	
	/*!
	 *
	 * \fn int updateAt(frame_point_data_t * newPoint, int index)
	 * \brief Updates the frame_point_data_t data of an item at a specified index.
	 * \param newPoint A pointer to a frame_point_data_t object.
	 * \param index The integer index.
	 * \return 	0 - if successful
	 * \return	-1 - otherwise
	 *
	 */
	int updateAt(frame_point_data_t * newPoint, int index);
	
	/*!
	 *
	 * \fn void resetPointer()
	 * \brief Reset the list pointer variable.
	 * \param none.
	 * \return none.
	 *
	 */
	void resetPointer();
	
	/*!
	 *
	 * \fn frame_point_data_t* nextPoint()
	 * \brief Returns the item currently pointed by the list pointer and moves the list pointer to the next item on the list.
	 * \param none.
	 * \return The pointer to the current item.
	 */
	frame_point_data_t* nextPoint();
	
	private:

	node * pointer;		/**< The list pointer.*/
	
	/*!
	 *
	 * \fn node* getNodeAt(int index)
	 * \brief Get the node in the index position.
	 * \param index The index.
	 * \return A pointer to the node.
	 *
	 */
	node* getNodeAt(int index);
	
};

// EOF
