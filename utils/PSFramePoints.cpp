/*
 *  PSFramePoints.cpp
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
 * \file PSFramePoints.cpp
 *
 * \brief This file implements the class PSFramePoints.  This class is a linked list for holding the odor data through out the map for a given time frame.
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

#include <stdio.h>
#include "PSFramePoints.h"

PSFramePoints::PSFramePoints()
{
	startNode = NULL;
	
	length = 0;
}

PSFramePoints::~PSFramePoints()
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

PSFramePoints::node* PSFramePoints::getNodeAt(int index)
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

void PSFramePoints::copy(PSFramePoints * toCopy)
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
		push(&aNode->data);
        aNode = aNode->link;
	}
}

// Adds one element to the end of an array and returns the new length of the array.
int PSFramePoints::push(frame_point_data_t * newPoint)
{
	node * aNode, * newNode;
	
	if( startNode == NULL )
	{
        startNode = new node;
		startNode->data.point.px = newPoint->point.px;
		startNode->data.point.py = newPoint->point.py;
		startNode->data.point.pz = newPoint->point.pz;
		startNode->data.odor.chemical = newPoint->odor.chemical;
		startNode->data.odor.windSpeed = newPoint->odor.windSpeed;
		startNode->data.odor.windDirection = newPoint->odor.windDirection;
		startNode->link = NULL;
	}
	else
	{
        aNode = startNode;
		while( aNode->link != NULL ) aNode = aNode->link;
		
		newNode = new node;
		newNode->data.point.px = newPoint->point.px;
		newNode->data.point.py = newPoint->point.py;
		newNode->data.point.pz = newPoint->point.pz;
		newNode->data.odor.chemical = newPoint->odor.chemical;
		newNode->data.odor.windSpeed = newPoint->odor.windSpeed;
		newNode->data.odor.windDirection = newPoint->odor.windDirection;
		newNode->link = NULL;
		aNode->link = newNode;
	}
	
	length++;
	
	return length;
}

// Removes the last element from an array and returns the value of that element.
frame_point_data_t* PSFramePoints::pop()
{
	return removeAt(length-1);
}

// Adds one alement to the array and returns the new length of the array.
int PSFramePoints::addAt(frame_point_data_t * newPoint, int index)
{
	node * aNode, * newNode;
	
	if(index == 0)
	{
		newNode = new node;
		newNode->data.point.px = newPoint->point.px;
		newNode->data.point.py = newPoint->point.py;
		newNode->data.point.pz = newPoint->point.pz;
		newNode->data.odor.chemical = newPoint->odor.chemical;
		newNode->data.odor.windSpeed = newPoint->odor.windSpeed;
		newNode->data.odor.windDirection = newPoint->odor.windDirection;
		newNode->link = startNode;
		startNode = newNode;
		
		length++;
		
		return length;
	}
	
	aNode = getNodeAt(index-1);
	if( aNode == NULL ) return -1;
	
	newNode = new node;
	newNode->data.point.px = newPoint->point.px;
	newNode->data.point.py = newPoint->point.py;
	newNode->data.point.pz = newPoint->point.pz;
	newNode->data.odor.chemical = newPoint->odor.chemical;
	newNode->data.odor.windSpeed = newPoint->odor.windSpeed;
	newNode->data.odor.windDirection = newPoint->odor.windDirection;
	newNode->link = aNode->link;
	aNode->link = newNode;
			
	length++;
	
	return length;
}

// Removes one element from an array and returns the value of that element.
frame_point_data_t* PSFramePoints::removeAt(int index)
{
	node * aNode, * deleteNode;
	
	if(index == 0)
	{
		aNode = startNode->link;
		deleteNode = startNode;
		startNode = aNode;
		
		length--;
		
		return &deleteNode->data;
	}
	
	aNode = getNodeAt(index-1);
	if( aNode == NULL ) return NULL;
	
	deleteNode = aNode->link;
	aNode->link = deleteNode->link;
	
	length--;
	
	return &deleteNode->data;
}

// Returns the value of an element.
frame_point_data_t* PSFramePoints::itemAt(int index)
{
	node * aNode;
	
	aNode = getNodeAt(index);
	if( aNode == NULL ) return NULL;
	
	return &aNode->data;
}

// Updates the value of an element.
int PSFramePoints::updateAt(frame_point_data_t * newPoint, int index)
{
	node * aNode;
	
	aNode = getNodeAt(index);
	if( aNode == NULL ) return -1;
	
	aNode->data.point.px = newPoint->point.px;
	aNode->data.point.py = newPoint->point.py;
	aNode->data.point.pz = newPoint->point.pz;
	aNode->data.odor.chemical = newPoint->odor.chemical;
	aNode->data.odor.windSpeed = newPoint->odor.windSpeed;
	aNode->data.odor.windDirection = newPoint->odor.windDirection;
	
	return 0;
}

// Reset the pointer variable
void PSFramePoints::resetPointer()
{
	pointer = startNode;
}

// Move the pointer to the next node
frame_point_data_t* PSFramePoints::nextPoint()
{
	node * aNode = pointer;
	if(aNode != NULL)
	{
		pointer = aNode->link;
		return &aNode->data;
	}
	else
	{
		return NULL;
	}
}

// EOF
