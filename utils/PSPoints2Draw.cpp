/*
 *  PSPoints2Draw.cpp
 *  
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
 * \file PSPoints2Draw.cpp
 *
 * \brief This file implements the class PSPoints2Draw.This class holds a linked list of points to be drawn by stage in order to provide a graphical representation of the plume.
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

#include <stdio.h>
#include "PSPoints2Draw.h"

PSPoints2Draw::PSPoints2Draw()
{
	startNode = NULL;
	
	length = 0;
}

PSPoints2Draw::~PSPoints2Draw()
{
	node * aNode;
	
	if( startNode == NULL )
        return;
	
	while( startNode != NULL )
	{
        aNode = startNode->link;
		delete startNode;
		startNode = aNode;
	}
	
	length = 0;
}

PSPoints2Draw::node* PSPoints2Draw::getNodeAt(int index)
{
	node * aNode;
	int i;
	
	if(index > length-1 || index < 0) return NULL;
	
	for( i = 0 , aNode = startNode ; i < index ; i++ )
	{
        aNode = aNode->link;
		if( aNode == NULL )
		{
			return NULL;
		}
	}
	
	return aNode;
}

void PSPoints2Draw::copy(PSPoints2Draw * toCopy)
{
	node * aNode;
	int i;
	
	// If we have any actual data, get rid of it!
	if(startNode != NULL)
	{
		while( startNode != NULL )
		{
			aNode = startNode->link;
			delete startNode;
			startNode = aNode;
		}
		
		length = 0;
	}
	
	// Start copying...
	for( i = 0 , aNode = toCopy->startNode ; i < toCopy->length ; i++ )
	{
		push(&aNode->point);
        aNode = aNode->link;
	}
}

// Adds one element to the end of an array and returns the new length of the array.
int PSPoints2Draw::push(player_point_3d_t * newPoint)
{
	node * aNode, * newNode;
	
	if( startNode == NULL )
	{
        startNode = new node;
		startNode->point.px = newPoint->px;
		startNode->point.py = newPoint->py;
		startNode->link = NULL;
	}
	else
	{
        aNode = startNode;
		while( aNode->link != NULL ) aNode = aNode->link;
		
		newNode = new node;
		newNode->point.px = newPoint->px;
		newNode->point.py = newPoint->py;
		newNode->link = NULL;
		aNode->link = newNode;
	}
	
	length++;
	
	return length;
}

// Removes the last element from an array and returns the value of that element.
player_point_3d_t* PSPoints2Draw::pop()
{
	return removeAt(length-1);
}

// Adds one alement to the array and returns the new length of the array.
int PSPoints2Draw::addAt(player_point_3d_t * newPoint, int index)
{
	node * aNode, * newNode;
	
	if(index == 0)
	{
		newNode = new node;
		newNode->point.px = newPoint->px;
		newNode->point.py = newPoint->py;
		newNode->link = startNode;
		startNode = newNode;
		
		length++;
		
		return length;
	}
	
	aNode = getNodeAt(index-1);
	if( aNode == NULL ) return -1;
	
	newNode = new node;
	newNode->point.px = newPoint->px;
	newNode->point.py = newPoint->py;
	newNode->link = aNode->link;
	aNode->link = newNode;
			
	length++;
	
	return length;
}

// Removes one element from an array and returns the value of that element.
player_point_3d_t* PSPoints2Draw::removeAt(int index)
{
	node * aNode, * deleteNode;
	
	if(index == 0)
	{
		aNode = startNode->link;
		deleteNode = startNode;
		startNode = aNode;
		
		length--;
		
		return &deleteNode->point;
	}
	
	aNode = getNodeAt(index-1);
	if( aNode == NULL ) return NULL;
	
	deleteNode = aNode->link;
	aNode->link = deleteNode->link;
	
	length--;
	
	return &deleteNode->point;
}

// Returns the value of an element.
player_point_3d_t* PSPoints2Draw::itemAt(int index)
{
	node * aNode;
	
	aNode = getNodeAt(index);
	if( aNode == NULL ) return NULL;
	
	return &aNode->point;
}

// Updates the value of an element.
int PSPoints2Draw::updateAt(player_point_3d_t * newPoint, int index)
{
	node * aNode;
	
	aNode = getNodeAt(index);
	if( aNode == NULL ) return -1;
	
	aNode->point.px = newPoint->px;
	aNode->point.py = newPoint->py;
	
	return 0;
}

// Reset the pointer variable
void PSPoints2Draw::resetPointer()
{
	pointer = startNode;
}

// Move the pointer to the next node
player_point_3d_t* PSPoints2Draw::nextPoint()
{
	node * aNode = pointer;
	if(aNode != NULL)
	{
		pointer = aNode->link;
		return &aNode->point;
	}
	else
	{
		return NULL;
	}
}

// Count the points in a sphere
int PSPoints2Draw::countPoints(player_point_3d_t * center, double radius)
{
	node * aNode = startNode;
	
	int pointCount = 0;
	while(aNode != NULL)
	{
		if(sqrt((center->px - aNode->point.px)*(center->px - aNode->point.px) + (center->py - aNode->point.py)*(center->py - aNode->point.py) + (center->pz - aNode->point.pz)*(center->pz - aNode->point.pz)) <= radius) pointCount++;
		aNode = aNode->link;
	}
	return pointCount;
}

// EOF
