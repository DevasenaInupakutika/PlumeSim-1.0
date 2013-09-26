/*
 *  PSMeadering.cpp
 *  
 *
 *  Created by Gonçalo Cabrita and Pedro Sousa on 02/15/2010.
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
 * \file PSMeadering.cpp
 *
 * \brief This file implements the class PSMeadering. This class contains the meandering plume generation algorithm.
 *
 * \author Gonçalo Cabrita
 * \author Pedro Sousa
 * \date 02/15/2010
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
PSMeadering::PSMeadering(ConfigFile * cf, int section)
{
	this->changesOverTime = false;
	
	this->startPoint.px = cf->ReadTupleLength(section, "releasepoint", 0, 0.0);
	this->startPoint.py = cf->ReadTupleLength(section, "releasepoint", 1, 0.0);
	this->startPoint.pz = cf->ReadTupleLength(section, "releasepoint", 2, 0.0);
	
	this->arenaRect.startPoint.px = cf->ReadTupleLength(section, "arena", 0, 0.0);
	this->arenaRect.startPoint.py = cf->ReadTupleLength(section, "arena", 1, 0.0);
	this->arenaRect.endPoint.px = cf->ReadTupleLength(section, "arena", 2, 0.0);
	this->arenaRect.endPoint.py = cf->ReadTupleLength(section, "arena", 3, 0.0);
	
	this->numOfPlumePoints = cf->ReadInt(section, "numberofpoints", 200);
	this->releaseRate = cf->ReadFloat(section, "releaserate", 10.0);
	this->dispersionCoeficient = cf->ReadFloat(section, "dispersioncoeficient", 0.1);
	this->radius = cf->ReadFloat(section, "radius", 0.1);
}

// *****************************************************************************
// Destructor.
PSMeadering::~PSMeadering()
{
	// Clean up...
}

// *****************************************************************************
// Setup routine.
int PSMeadering::setup()
{
	plumePoints = new PSPoints2Draw();
	return 0;
}

// *****************************************************************************
// Cleanup routine.
int PSMeadering::cleanup()
{
	delete plumePoints;
	return 0;
}

// *****************************************************************************
// Generate points.
int PSMeadering::generatePoints()
{
	int i;
	
	player_point_3d_t startupPoints[MIN_NUM_OF_POINTS];
	
	double step = (arenaRect.endPoint.px - startPoint.px)/MIN_NUM_OF_POINTS;
	// Fill the startup array
	for(i=0 ; i<MIN_NUM_OF_POINTS ; i++) startupPoints[i].px = startPoint.px + i * step;
	
	double sigma = 0.2*step;
	// Posicao do centro da pluma na origem
	startupPoints[0].py = startPoint.py;
	
	double ay[MIN_NUM_OF_POINTS];
	// Fill the array
	for(i=0 ; i<MIN_NUM_OF_POINTS ; i++) ay[i] = sigma*randomNormal();
	
	double vy[MIN_NUM_OF_POINTS];
	// Velocidade lateral da pluma na origem
	vy[0] = sigma*randomNormal();
	
	for(i=1 ; i<MIN_NUM_OF_POINTS ; i++)
	{
		// Perturbacao da velocidade lateral
		vy[i] = vy[i-1] + ay[i-1];
		// Actualizacao do centro da pluma
		startupPoints[i].py = startupPoints[i-1].py + vy[i-1];
	}
	
	linearInterpolation(startupPoints, MIN_NUM_OF_POINTS, plumePoints);
	
	player_point_3d_t * plumePoint;
	plumePoints->resetPointer();
	for(i=0 ; i<plumePoints->length ; i++)
	{
		plumePoint = plumePoints->nextPoint();
		// TODO: test for other release points
		plumePoint->py = plumePoint->py + ( dispersionCoeficient * (plumePoint->px - startPoint.px) * (releaseRate * randomNormal()));
	}
	
	player_point_3d_t center;
	center.px = startPoint.px + radius;
	center.py = startPoint.py;
	center.pz = 0.0;
	
	maxPoints = plumePoints->countPoints(&center, radius);
	
	return(0);
}

// *****************************************************************************
// Sends the chemical reading for a given position.
int PSMeadering::getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data)
{	
	int pointCount = plumePoints->countPoints(point, radius);
	
	odor_data->chemical = fmin(100.0, 100.0*pointCount/maxPoints);
	// Constants
	// TODO: Maybe get this from the .cfg file
	odor_data->windDirection = 0.0;		// rad
	odor_data->windSpeed = 0.5;			// m/s
	
	return(0);
}

// *****************************************************************************
// Linear interpolation
void PSMeadering::linearInterpolation(player_point_3d_t * points, int numOfPoints, PSPoints2Draw * newPoints)
{
	double b, m;
	int i, j;
	player_point_3d_t point;
	
	int pointsOnThisSection;
	
	double x_step = (points[numOfPoints-1].px - points[0].px) / numOfPlumePoints;
	
	for(i=0 ; i<numOfPoints-1 ; i++)
	{
		point.px = points[i].px;
		point.py = points[i].py;
		point.pz = 0.0;
		newPoints->push(&point);
		
		m = (points[i+1].py - points[i].py)/(points[i+1].px - points[i].px);
		b = points[i].py - m * points[i].px;
		
		pointsOnThisSection = (points[i+1].px - points[i].px) / x_step;
		
		for(j=0 ; j<pointsOnThisSection ; j++)
		{
			point.px = points[i].px + (j+1)*x_step;
			point.py = m * point.px + b;
			point.pz = 0.0;
			newPoints->push(&point);
		}
	}
	point.px = points[numOfPoints-1].px;
	point.py = points[numOfPoints-1].py;
	point.pz = 0.0;
	newPoints->push(&point);
}

// EOF

