/*
 *  PSOdorSensor.h
 *  
 *
 *  Created by Gonçalo Cabrita and Pedro Sousa on 03/25/2010.
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
 * \file PSOdorSensor.h
 *
 * \brief This file defines the class PSOdorSensor. This class contains the configuration parameters of the simulated odor sensor as well as the required methods to provide simulated odor sensor readings.
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

// The sensor class
class PSOdorSensor
{
	public:
		
	//! PSOdorSensor constructor.
    /*!
	 * This is the class constructor.
     */
	PSOdorSensor();
	//! PSOdorSensor destructor.
    /*!
	 * This is the class destructor.
     */
	~PSOdorSensor();
	
	/*!
	 *
	 * \fn double sensorReading(double input)
	 * \brief Calculate the sensor reading based on the sensor model.
	 * \param Odor from plume.
	 * \return none.
	 *
	 */
	double sensorReading(double input);
		
	private:
	
	// Sensor model constants
	
};

// EOF
