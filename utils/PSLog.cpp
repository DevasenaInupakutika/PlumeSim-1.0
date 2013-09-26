/*
 *  PSLog.cpp
 *  
 *
 *  Created by Gonçalo Cabrita and Pedro Sousa on 02/23/2010.
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
 * \file PSLog.cpp
 *
 * \brief This file implements the class PSLog. This class contains the PlumeSim log file reading code.
 *
 * \author Gonçalo Cabrita
 * \author Pedro Sousa
 * \date 02/23/2010
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
PSLog::PSLog(ConfigFile * cf, int section)
{
	this->maxPointsPerCell = cf->ReadInt(section, "maxpointspercell", 10);
	
	this->logFilePath = (char*)cf->ReadString(section, "filepath", "log.ens");
}

// *****************************************************************************
// Destructor.
PSLog::~PSLog()
{
	// Clean up...
}

// *****************************************************************************
// Setup routine.
int PSLog::setup()
{
	// Open the file
	this->logFile = fopen(logFilePath, "r");
	// Take out the settings...
	// period ppFrame nFrames cellSize maxOdor
	fscanf(this->logFile, "%d,%d,%lf\n", &this->period, &this->numOfFrames, &this->cellSize);
	
	if(this->numOfFrames > 1) this->changesOverTime = true;
	else this->changesOverTime = false;
	this->isPlaying = true;
	
	return 0;
}

// *****************************************************************************
// Cleanup routine.
int PSLog::cleanup()
{
	// Close the file
	fclose(logFile);
	// Clean up...
	delete frame;
	delete plumePoints;
	
	return 0;
}

// *****************************************************************************
// Read points from the log file.
int PSLog::generatePoints()
{
	int i, j;
	int pointsCount;
	int pointsInFrame;
	player_point_3d_t point;
	frame_point_data_t pointFromFrame;
	
	if(frame != NULL)
	{
		delete frame;
		frame = NULL;
	}
	frame = new PSFramePoints();
	
	if(plumePoints != NULL)
	{
		delete plumePoints;
		plumePoints = NULL;
	}
	plumePoints = new PSPoints2Draw();
	
	if( !feof(logFile) )
	{
		// +t
		fscanf(logFile, "+%d %d\n", &currentFrame, &pointsInFrame);
		
		for(i=0 ; i<pointsInFrame ; i++)
		{
			// x y z windSpeed windDirection chemical
			fscanf(logFile, "%lf,%lf,%lf,%lf,%lf,%lf\n", &pointFromFrame.point.px, &pointFromFrame.point.py, &pointFromFrame.point.pz,  &pointFromFrame.odor.windSpeed, &pointFromFrame.odor.windDirection, &pointFromFrame.odor.chemical);
			
			frame->push(&pointFromFrame);
			
			pointsCount = round(maxPointsPerCell * pointFromFrame.odor.chemical/100.0);
			for(j=0 ; j<pointsCount ; j++)
			{
				point.px = pointFromFrame.point.px + cellSize * randomNormal();
				point.py = pointFromFrame.point.py + cellSize * randomNormal();
				// TODO: Complete for full 3D support!
				point.pz = 0.0;
				plumePoints->push(&point);
			}
		}
	}
	else
	{
		isPlaying = false;
	}
	return(0);
}

// *****************************************************************************
// Sends the chemical reading for a given position.
int PSLog::getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data)
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

