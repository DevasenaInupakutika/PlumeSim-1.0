/*
 *  PSPoints2Draw.h
 *  
 *  Created by Gonçalo Cabrita and Pedro Sousa on 02/24/2010.
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
 * \file PSPoints2Draw.h
 *
 * \brief This file defines the class PSPoints2Draw. This class holds a linked list of points to be drawn by stage in order to provide a graphical representation of the plume.
 *
 * \author Gonçalo Cabrita
 * \author Pedro Sousa
 * \date 02/24/2010
 * \version 0.1
 *
 * \bug none discovered
 *
 * \note
 *
 */
 
#include <libplayercore/playercore.h>
#include <math.h>

/*!
 * 
 * \class PSPoints2Draw PSPoints2Draw.h
 * \brief This class ...
 * More information about it
 *
 */
class PSPoints2Draw
{
	public:
	
	/*!
	 * 
	 * \struct node
	 * It includes a 3D point and a pointer to the next node.
	 * It also declares the startNode.
	 *
	 */
	struct node
	{
		player_point_3d_t point;
		node * link;
		
	} * startNode;
	
	int length;		/**< Contains the length of the linked list.*/
	
	//! PSPoints2Draw constructor.
    /*!
	 * This is the class constructor.
     */
	PSPoints2Draw();
	//! PSPoints2Draw destructor.
    /*!
	 * This is the class destructor.
     */
	~PSPoints2Draw();
	
	/*!
	 *
	 * \fn copy(PSPoints2Draw * toCopy)
	 * \brief Copy a PSPoints2Draw object.
	 * \param toCopy A pointer to a PSPoints2Draw object.
	 * \return none.
	 *
	 */
	void copy(PSPoints2Draw * toCopy);
		
	/*!
	 * 
	 * \fn push(player_point_3d_t * newPoint)
	 * \brief Adds one element to the end of the list and returns the new length of the list.
	 * \param newPoint A pointer to a player_point_3d_t object.
	 * \return An integer with the length of the list.
	 *
	 */
	int push(player_point_3d_t * newPoint);
	
	/*!
	 *
	 * \fn player_point_3d_t* pop();
	 * \brief Removes the last element from the list and returns the pointer to that item.
	 * \param none.
	 * \return none.
	 *
	 */
	player_point_3d_t* pop();
	
	/*!
	 *
	 * \fn int addAt(player_point_3d_t * newPoint, int index)
	 * \brief Adds one element to the list at a specific index and returns the new length of the list.
	 * \param newPoint A pointer to a player_point_3d_t object.
	 * \param index The integer index.
	 * \return An integer with the length of the list.
	 *
	 */
	int addAt(player_point_3d_t * newPoint, int index);
	
	/*!
	 *
	 * \fn player_point_3d_t* removeAt(int index)
	 * \brief Removes one element from a list at a specific index and returns the pointer to that item.
	 * \param index The integer index.
	 * \return A pointer to the removed item.
	 *
	 */
	player_point_3d_t* removeAt(int index);
	
	/*!
	 *
	 * \fn player_point_3d_t* itemAt(int index)
	 * \brief Returns the pointer to an item on a specific index.
	 * \param index The integer index.
	 * \return The pointer to the item for the provided index.
	 *
	 */
	player_point_3d_t* itemAt(int index);
	
	/*!
	 *
	 * \fn int updateAt(player_point_3d_t * newPoint, int index)
	 * \brief Updates the player_point_3d_t data of an item at a specified index.
	 * \param newPoint A pointer to a player_point_3d_t object.
	 * \param index The integer index.
	 * \return 	0 - if successful
	 * \return	-1 - otherwise
	 *
	 */
	int updateAt(player_point_3d_t * newPoint, int index);
	
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
	 * \fn player_point_3d_t* nextPoint()
	 * \brief Returns the item currently pointed by the list pointer and moves the list pointer to the next item on the list.
	 * \param none.
	 * \return The pointer to the current item.
	 */
	player_point_3d_t* nextPoint();
	
	/*!
	 *
	 * \fn int countPoints(player_point_3d_t * center, double radius)
	 * \brief Count the number of points in the list contained inside a sphere defined by a center point and a radius.
	 * \param denter A pointer to the center of the sphere.
	 * \param radius The radius of the sphere.
	 * \return The number of points from the list inside the sphere.
	 * \todo This is working for 2D, upgrade it to also work for 3D.
	 *
	 */
	int countPoints(player_point_3d_t * center, double radius);
	
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
