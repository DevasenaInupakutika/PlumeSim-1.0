/*
 *  PSSources.h
 *  
 *
 *  Created by Gonçalo Cabrita and Pedro Sousa on 02/15/2010.
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
 * \file PSSources.h
 *
 * \brief This file contains the definitions for all the plume generation source classes.
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

#include "PSRect.h"
#include "PSPoints2Draw.h"
#include "PSFramePoints.h"

#define MIN_NUM_OF_POINTS	20


/*!
 * 
 * \class PSSource PSSource.h
 * \brief Base class for all the plume source algorithms.
 *
 */
class PSSource
{
	public:
		
	//! PSSource constructor.
    /*!
	 * This is the class constructor.
     */
	PSSource();
	//! PSSource destructor.
    /*!
	 * This is the class destructor.
     */
	~PSSource();
	
	/*!
	 *
	 * \fn virtual int setup()
	 * \brief Virtual function for setting up the class.
	 * \param none.
	 * \return none.
	 *
	 */
	virtual int setup();
	/*!
	 *
	 * \fn virtual int cleanup()
	 * \brief Virtual function for cleaning up the class.
	 * \param none.
	 * \return none.
	 *
	 */
	virtual int cleanup();
	
	PSPoints2Draw * plumePoints;	/**< Linked list of plume points to draw.*/
	
	/*!
	 *
	 * \fn virtual int generatePoints()
	 * \brief Virtual function for generating plume points.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	virtual int generatePoints();
	/*!
	 *
	 * \fn virtual int getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data)
	 * \brief Virtual function for reading a single chemical point based on the robot current position.
	 * \param A 3D point containning the current position of the robot.
	 * \param The odor data structure where the result is written.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	virtual int getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data);
	
	/*!
	 *
	 * \fn PSPoints2Draw* getPointsToDraw()
	 * \brief Get the points for display.
	 * \param none.
	 * \return Pointer to the linked list containning the points to draw.
	 *
	 */
	PSPoints2Draw* getPointsToDraw();
	/*!
	 *
	 * \fn bool ChangesOverTime()
	 * \brief If the class is time invariant or not.
	 * \param none.
	 * \return true - if the plume changes over time
	 * \return false - otherwise
	 *
	 */
	bool ChangesOverTime();
	/*!
	 *
	 * \fn bool IsPlaying()
	 * \brief If the class is still processing data.
	 * \param none.
	 * \return true - if the plume is still playing
	 * \return false - otherwise
	 *
	 */
	bool IsPlaying();
		
	protected:
	
	/*!
	 *
	 * \fn float drand()
	 * \brief Uniform distribution, [0 ... 1]
	 * \param none.
	 * \return Random generated value.
	 *
	 */
	float drand();
	/*!
	 *
	 * \fn double randomNormal()
	 * \brief Normal distribution, centered on 0, std dev 1
	 * \param none.
	 * \return Random generated value.
	 *
	 */
	double randomNormal();
		
	bool changesOverTime;		/**< Stores if the plume changes over time or not.*/
	bool isPlaying;				/**< Stores if the plume is playing ot not.*/
};


/*!
 * 
 * \class PSMeadering PSSource.h
 * \brief Extends the PSSource class to provide plume generation based on the meandering algorithm.
 *
 */
class PSMeadering:public PSSource
{
	public:
		
	/*!
	 *
	 * \fn PSMeadering(ConfigFile * cf, int section)
	 * \brief PSMeadering constructor. This is the class constructor.
	 * \param The config file.
	 * \param Section index.
	 * \return none.
	 *
	 */
	PSMeadering(ConfigFile * cf, int section);
	//! PSMeadering destructor.
    /*!
	 * This is the class destructor.
     */
	~PSMeadering();
	
	/*!
	 *
	 * \fn int setup()
	 * \brief Function for setting up the class.
	 * \param none.
	 * \return none.
	 *
	 */
	int setup();
	/*!
	 *
	 * \fn int cleanup()
	 * \brief Function for cleaning up the class.
	 * \param none.
	 * \return none.
	 *
	 */
	int cleanup();
	
	/*!
	 *
	 * \fn int generatePoints()
	 * \brief Function for generating plume points based on the meandering algorithm.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int generatePoints();
	/*!
	 *
	 * \fn int getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data)
	 * \brief Function for reading a single chemical point based on the robot current position.
	 * \param A 3D point containning the current position of the robot.
	 * \param The odor data structure where the result is written.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data);
		
	private:
	
	player_point_3d_t startPoint;		/**< Odor release point.*/
	PSRect arenaRect;					/**< Rectangle containing the environment.*/
	double releaseRate;					/**< Release rate.*/
	double dispersionCoeficient;		/**< Dispersion coeficient.*/
	double radius;						/**< Radius of the odor reading sphere.*/
	int maxPoints;						/**< Maximum number of points to be drawn for each point.*/
	int numOfPlumePoints;				/**< Total number of plume points.*/
	
	/*!
	 *
	 * \fn void linearInterpolation(player_point_3d_t * points, int numOfPoints, PSPoints2Draw * newPoints)
	 * \brief Linear interpolation
	 * \param Pointer to array of points to interpolate.
	 * \param Number of points in the array.
	 * \param Pointer to linked list of points to write the result to.
	 * \return none.
	 *
	 */
	void linearInterpolation(player_point_3d_t * points, int numOfPoints, PSPoints2Draw * newPoints);
};


/*!
 * 
 * \class PSGaussian PSSource.h
 * \brief Extends the PSSource class to provide plume generation based on the gaussian algorithm.
 *
 */
class PSGaussian:public PSSource
{
	public:
	
	/*!
	 *
	 * \fn PSGaussian(ConfigFile * cf, int section)
	 * \brief PSGaussian constructor. This is the class constructor.
	 * \param The config file.
	 * \param Section index.
	 * \return none.
	 *
	 */
	PSGaussian(ConfigFile * cf, int section);
	//! PSGaussian destructor.
    /*!
	 * This is the class destructor.
     */
	~PSGaussian();
	
	/*!
	 *
	 * \fn int setup()
	 * \brief Function for setting up the class.
	 * \param none.
	 * \return none.
	 *
	 */
	int setup();
	/*!
	 *
	 * \fn int cleanup()
	 * \brief Function for cleaning up the class.
	 * \param none.
	 * \return none.
	 *
	 */
	int cleanup();
	
	/*!
	 *
	 * \fn int generatePoints()
	 * \brief Function for generating plume points based on the gaussian algorithm.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int generatePoints();
	/*!
	 *
	 * \fn int getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data)
	 * \brief Function for reading a single chemical point based on the robot current position.
	 * \param A 3D point containning the current position of the robot.
	 * \param The odor data structure where the result is written.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data);
	
	private:
	
	player_point_3d_t startPoint;		/**< Odor release point.*/
	PSRect arenaRect;					/**< Rectangle containing the environment.*/
	double radius;						/**< Radius of the odor reading sphere.*/
	double cellSize;					/**< Cell size of the grid in meters.*/
	int maxPointsPerCell;				/**< Maximum number of points to be drawn for each cell.*/
	int t;								/**< Current time frame.*/
	
	double diffX;						/**< Diffusivity constant in x.*/
	double diffY;						/**< Diffusivity constant in y.*/
	
	PSFramePoints * frame;				/**< Current frame.*/
};


/*!
 * 
 * \class PSLog PSSource.h
 * \brief Extends the PSSource class to provide plume generation based on .pslog files.
 *
 */
class PSLog:public PSSource
{
	public:
		
	/*!
	 *
	 * \fn PSLog(ConfigFile * cf, int section)
	 * \brief PSLog constructor. This is the class constructor.
	 * \param The config file.
	 * \param Section index.
	 * \return none.
	 *
	 */
	PSLog(ConfigFile * cf, int section);
	//! PSLog destructor.
    /*!
	 * This is the class destructor.
     */
	~PSLog();
	
	/*!
	 *
	 * \fn int setup()
	 * \brief Function for setting up the class.
	 * \param none.
	 * \return none.
	 *
	 */
	int setup();
	/*!
	 *
	 * \fn int cleanup()
	 * \brief Function for cleaning up the class.
	 * \param none.
	 * \return none.
	 *
	 */
	int cleanup();
	
	/*!
	 *
	 * \fn int generatePoints()
	 * \brief Function for generating plume points based on a .pslog file.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int generatePoints();
	/*!
	 *
	 * \fn int getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data)
	 * \brief Function for reading a single chemical point based on the robot current position.
	 * \param A 3D point containning the current position of the robot.
	 * \param The odor data structure where the result is written.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data);
		
	private:
		
	FILE * logFile;				/**< Pointer to the log file.*/
	char * logFilePath;			/**< Path to the log file.*/
	
	int period;					/**< Original period in ms.*/
	int numOfFrames;			/**< Number of frames.*/
	int currentFrame;			/**< Current index.*/
	double cellSize;			/**< Cell size of the grid in meters.*/
	int maxPointsPerCell;		/**< Maximum number of points to be drawn for each cell.*/
	
	PSFramePoints * frame;		/**< Current frame.*/
};


/*!
 * 
 * \class PSFluent PSSource.h
 * \brief Extends the PSSource class to provide plume generation based on Fluent log files.
 *
 */
class PSFluent:public PSSource
{
	public:
	
	/*!
	 *
	 * \fn PSFluent(ConfigFile * cf, int section)
	 * \brief PSFluent constructor. This is the class constructor.
	 * \param The config file.
	 * \param Section index.
	 * \return none.
	 *
	 */
	PSFluent(ConfigFile * cf, int section);
	//! PSFluent destructor.
    /*!
	 * This is the class destructor.
     */
	~PSFluent();
	
	/*!
	 *
	 * \fn int setup()
	 * \brief Function for setting up the class.
	 * \param none.
	 * \return none.
	 *
	 */
	int setup();
	/*!
	 *
	 * \fn int cleanup()
	 * \brief Function for cleaning up the class.
	 * \param none.
	 * \return none.
	 *
	 */
	int cleanup();
	
	/*!
	 *
	 * \fn int generatePoints()
	 * \brief Function for generating plume points based on a set of Fluent log files.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int generatePoints();
	/*!
	 *
	 * \fn int getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data)
	 * \brief Function for reading a single chemical point based on the robot current position.
	 * \param A 3D point containning the current position of the robot.
	 * \param The odor data structure where the result is written.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int getChemicalReading(player_point_3d_t * point, odor_data_t * odor_data);
	
	private:
	
	FILE * logFile;				/**< Pointer to the log file.*/
	char * fileName;			/**< Path to the log file.*/
	
	int numOfFrames;			/**< Number of frames.*/
	int currentFrame;			/**< Current frame index.*/	
	double cellSize;			/**< Cell size of the grid in meters.*/
	int maxPointsPerCell;		/**< Maximum number of points to be drawn for each cell.*/
	double maxOdorValue;		/**< Maximum odor value.*/
	
	PSFramePoints * frame;		/**< Current frame.*/
};

// EOF
