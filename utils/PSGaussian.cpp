/*
 *  PSGaussian.cpp
 *  
 *
 *  Created by Gonçalo Cabrita and Pedro Sousa on 03/01/2010.
 *  Copyright 2010 ISR. All rights reserved.
 *
 *	Comments:
 *	Player v3.x specific plugin driver.
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
 * \file PSGaussian.cpp
 *
 * \brief This file implements the class PSGaussian.  This class contains the gaussian plume generation algorithm.
 *
 * \author Gonçalo Cabrita
 * \author Pedro Sousa
 * \date 03/01/2010
 * \version 0.1
 *
 * \bug none discovered
 *
 * \note
 *
 */

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <libplayercore/playercore.h>

#include "PSSources.h"

// *****************************************************************************
// Constructor.
PSGaussian::PSGaussian(ConfigFile * cf, int section)
{	
	this->changesOverTime = true;
	
	this->startPoint.px = cf->ReadTupleLength(section, "releasepoint", 0, 0.0);
	this->startPoint.py = cf->ReadTupleLength(section, "releasepoint", 1, 0.0);
	this->startPoint.pz = cf->ReadTupleLength(section, "releasepoint", 2, 0.0);
	
	this->arenaRect.startPoint.px = cf->ReadTupleLength(section, "arena", 0, 0.0);
	this->arenaRect.startPoint.py = cf->ReadTupleLength(section, "arena", 1, 0.0);
	this->arenaRect.endPoint.px = cf->ReadTupleLength(section, "arena", 2, 0.0);
	this->arenaRect.endPoint.py = cf->ReadTupleLength(section, "arena", 3, 0.0);
	
	this->cellSize = cf->ReadFloat(section, "cellsize", 0.1);
	
	this->diffX = cf->ReadFloat(section, "diffx", 0.2);
	this->diffY = cf->ReadFloat(section, "diffy", 0.005);
	
	this->radius = cf->ReadFloat(section, "radius", 0.1);
	
	this->maxPointsPerCell = cf->ReadInt(section, "maxpointspercell", 10);
	
	this->frame = new PSFramePoints();
}

// *****************************************************************************
// Destructor.
PSGaussian::~PSGaussian()
{
	// Clean up...
	delete frame;
}

// *****************************************************************************
// Setup routine.
int PSGaussian::setup()
{
	int i, j;
	
	int numXpoints = (this->arenaRect.endPoint.px - this->arenaRect.startPoint.px)/this->cellSize;
	int numYpoints = (this->arenaRect.endPoint.py - this->arenaRect.startPoint.py)/this->cellSize;
	
	frame_point_data_t frameCell;
	
	for(i=0 ; i<numXpoints ; i++)
	{
		for(j=0 ; j<numYpoints ; j++)
		{
			frameCell.point.px = startPoint.px + this->cellSize*i;
			frameCell.point.py = startPoint.py + this->cellSize*j;
			frameCell.point.pz = 0.0;
			
			frameCell.odor.chemical = 0.0;			// Start value
			frameCell.odor.windDirection = 0.0;		// rad
			frameCell.odor.windSpeed = 0.5;			// m/s
			
			this->frame->push(&frameCell);
		}
	}
	t = 1;
	this->isPlaying = true;
	this->plumePoints = NULL;
	
	return 0;
}

// *****************************************************************************
// Cleanup routine.
int PSGaussian::cleanup()
{
	delete plumePoints;
	return 0;
}

// *****************************************************************************
// Generate points.
int PSGaussian::generatePoints()
{
	frame_point_data_t * frameCell;
	player_point_3d_t point;
	int pointsCount;
	int j;
	
	if(plumePoints != NULL)
	{
		delete plumePoints;
		plumePoints = NULL;
	}
	plumePoints = new PSPoints2Draw();
	
	this->frame->resetPointer();
	for(int i=0 ; i<this->frame->length ; i++)
	{
		frameCell = this->frame->nextPoint();
		
		frameCell->odor.chemical = 100.0/(4*M_PI*sqrt(this->diffX)*sqrt(this->diffY)*t)*exp(-(((frameCell->point.px - this->startPoint.px)*(frameCell->point.px - this->startPoint.px)/this->diffX)+((frameCell->point.py - this->startPoint.py)*(frameCell->point.py - this->startPoint.py)/this->diffY))/(4*t));

		pointsCount = round(maxPointsPerCell * frameCell->odor.chemical/100.0);
		for(j=0 ; j<pointsCount ; j++)
		{
			point.px = frameCell->point.px + cellSize * randomNormal();
			point.py = frameCell->point.py + cellSize * randomNormal();
			// TODO: Complete for full 3D support!
			point.pz = 0.0;
			this->plumePoints->push(&point);
		}
	}
	t++;
	if(t > 25) t = 20;
	//isPlaying = false; 
	
	return(0);
}

// *****************************************************************************
// Sends the chemical reading for a given position.
int PSGaussian::getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data)
{	
	double distance;
	double minDistance = cellSize;
	
	odor_data->chemical = 0.0;
	odor_data->windSpeed = 0.0;
	odor_data->windDirection = 0.0;
	
	frame_point_data_t * framePoint;
	frame->resetPointer();
	for(int i=0 ; i<frame->length ; i++)
	{
		framePoint = frame->nextPoint();
		
		distance = sqrt((point->px - framePoint->point.px)*(point->px - framePoint->point.px) + (point->py - framePoint->point.py)*(point->py - framePoint->point.py) + (point->pz - framePoint->point.pz)*(point->pz - framePoint->point.pz));
		if(distance < minDistance)
		{
			odor_data->chemical = framePoint->odor.chemical;
			odor_data->windSpeed = framePoint->odor.windSpeed;
			odor_data->windDirection = framePoint->odor.windDirection;
			
			minDistance = distance;
		}
	}
	return(0);
}

// EOF

