/*
 *  PSOdorSensor.cpp
 *  
 *
 *  Created by Gonçalo Cabrita and Pedro Sousa on 03/25/2010.
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
 * \file PSOdorSensor.cpp
 *
 * \brief This file implements the class PSOdorSensor. This class contains the configuration parameters of the simulated odor sensor as well as the required methods to provide simulated odor sensor readings.
 *
 * \author Gonçalo Cabrita
 * \author Pedro Sousa
 * \date 03/25/2010
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

#include "PSOdorSensor.h"

// *****************************************************************************
// Constructor.
PSOdorSensor::PSOdorSensor()
{
	// Nothing...
}

// *****************************************************************************
// Destructor.
PSOdorSensor::~PSOdorSensor()
{
	// Clean up...
}

// *****************************************************************************
// Calculate the sensor reading based on the sensor model.
double PSOdorSensor::sensorReading(double input)
{
	return 0.0;
}

// EOF

