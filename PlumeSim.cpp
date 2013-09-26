/*
 *  PlumeSim.cpp
 *  
 *
 *  Created by Gonçalo Cabrita and Pedro Sousa on 02/02/2010.
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
 * \file PlumeSim.cpp
 *
 * \brief This file implements the PlumeSim driver.
 *
 * \author Gonçalo Cabrita
 * \author Pedro Sousa
 * \date 02/02/2010
 * \version 0.1
 *
 * \bug none discovered
 *
 * \note
 *
 */


#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <libplayercore/playercore.h>

#include "config.h"
#include "replace.h"

// Types of sources
#include "utils/PSSources.h"

// Message levels
#define MESSAGE_ERROR 0
#define MESSAGE_INFO 1
#define MESSAGE_DEBUG 2

// *****************************************************************************
// The class for the driver
/*!
 * 
 * \class PlumeSim PlumeSim.cpp
 * \brief Extends the ThreadedDriver class. Plugin driver for plume simulation.
 *
 */
class PlumeSim:public ThreadedDriver
{
	public:
		
	/*!
	 *
	 * \fn PlumeSim(ConfigFile * cf, int section)
	 * \brief PlumeSim constructor. This is the class constructor.
	 * \param The config file.
	 * \param Section index.
	 * \return none.
	 *
	 */
	PlumeSim(ConfigFile * cf, int section);
	//! PlumeSim destructor.
    /*!
	 * This is the class destructor.
     */
	~PlumeSim();
	
	/*!
	 *
	 * \fn virtual int ProcessMessage(QueuePointer &resp_queue, player_msghdr * hdr, void * data)
	 * \brief This method will be invoked on each incoming message.
	 * \param N/A
	 * \return N/A
	 *
	 */
	virtual int ProcessMessage(QueuePointer &resp_queue, player_msghdr * hdr, void * data);
		
	odor_data_t odor_data;					/**< Structure for the odor data.*/
	
	private:
		
	/*!
	 *
	 * \fn virtual void Main()
	 * \brief Main function for device thread.
	 * \param N/A
	 * \return N/A
	 *
	 */
	virtual void Main();
	/*!
	 *
	 * \fn virtual void MainSetup()
	 * \brief Setup function for device thread.
	 * \param N/A
	 * \return N/A
	 *
	 */
	virtual int MainSetup();
	/*!
	 *
	 * \fn virtual void MainQuit()
	 * \brief Quit function for device thread.
	 * \param N/A
	 * \return N/A
	 *
	 */
	virtual void MainQuit();
	
	/*!
	 *
	 * \fn int SetupOdom()
	 * \brief Setup the position2d device.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int SetupOdom();
	/*!
	 *
	 * \fn int ShutdownOdom()
	 * \brief Shutdown the position2d device.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int ShutdownOdom();
	/*!
	 *
	 * \fn int SetupPencil()
	 * \brief Setup the graphics3d device.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int SetupPencil();
	/*!
	 *
	 * \fn int ShutdownPencil()
	 * \brief Shutdown the graphics3d device.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int ShutdownPencil();
	
	/*!
	 *
	 * \fn ProcessOdom(player_position2d_data_t * data)
	 * \brief Process message from position2d device.
	 * \param Position2d data.
	 * \return none.
	 *
	 */
	void ProcessOdom(player_position2d_data_t * data);
	
	/*!
	 *
	 * \fn int DrawPoints()
	 * \brief Draw the plume points in stage.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int DrawPoints();
	/*!
	 *
	 * \fn int ClearPoints()
	 * \brief Clear current plume points in stage.
	 * \param none.
	 * \return 0 - if successful
	 * \return -1 - otherwise
	 *
	 */
	int ClearPoints();
	
	PSSource * source;						/**< Plume generation source class.*/
	int sensorUpdate;						/**< Sensor update in ms.*/
	int plumeUpdate;						/**< Draw update multiplier.*/
	
	player_opaque_data_t opaque_data;		/**< This is the data we store and send.*/
	
	// Odometry device info
	Device * odom;							/**< Position2d device.*/
	player_devaddr_t odom_addr;				/**< Position2d adress.*/
	player_pose2d_t odom_pose;				/**< Structure to hold the robot odometric data.*/
	
	// Graphics3d device info
	Device * pencil;						/**< Graphics3d device.*/
	player_devaddr_t pencil_addr;			/**< Graphics3d adress.*/
	
	player_color_t drawColor;				/**< Color in which the plume points will be drawn.*/
	
	player_point_3d_t sensorPosition;		/**< Position of the odor sensor relative to the center of the robot.*/
	int modelSensor;						/**< This is the data we store and send.*/
};


// *****************************************************************************
// A factory creation function, declared outside of the class so that it
// can be invoked without any object context (alternatively, you can
// declare it static in the class).  In this function, we create and return
// (as a generic Driver*) a pointer to a new instance of this driver.
Driver * PlumeSim_Init(ConfigFile * cf, int section)
{
	// Create and return a new instance of this driver
	return((Driver*)(new PlumeSim(cf, section)));
}


// *****************************************************************************
// A driver registration function, again declared outside of the class so
// that it can be invoked without object context.  In this function, we add
// the driver into the given driver table, indicating which interface the
// driver can support and how to create a driver instance.
void PlumeSim_Register(DriverTable * table)
{
	table->AddDriver("PlumeSim", PlumeSim_Init);
}


// *****************************************************************************
// Constructor.  Retrieve options from the configuration file and do any
// pre-Setup() setup.
PlumeSim::PlumeSim(ConfigFile * cf, int section) : ThreadedDriver(cf, section, false, PLAYER_MSGQUEUE_DEFAULT_MAXLEN, PLAYER_OPAQUE_CODE)
{	
	this->odom = NULL;
	if(cf->ReadDeviceAddr(&this->odom_addr, section, "requires", PLAYER_POSITION2D_CODE, -1, NULL) != 0)
	{
		this->SetError(-1);
		return;
	}
	
	this->pencil = NULL;
	memset(&this->pencil_addr, 0, sizeof(player_devaddr_t));
	cf->ReadDeviceAddr(&this->pencil_addr, section, "requires", PLAYER_GRAPHICS3D_CODE, -1, NULL);
	
	char * type = (char*)cf->ReadString(section, "type", "default");
	
	if(strcmp(type, "meadering") == 0)
	{
		source = new PSMeadering(cf, section);
	}
	else if(strcmp(type, "gaussian") == 0)
	{
		source = new PSGaussian(cf, section);
	}
	else if(strcmp(type, "fluent") == 0)
	{
		source = new PSFluent(cf, section);
	}
	else if(strcmp(type, "pslog") == 0)
	{
		source = new PSLog(cf, section);
	}
	else
	{
		PLAYER_ERROR("No type of simulation was defined!");
	}
	
	drawColor.alpha = cf->ReadTupleLength(section, "color", 0, 1);
	drawColor.red = cf->ReadTupleLength(section, "color", 1, 0);
	drawColor.green = cf->ReadTupleLength(section, "color", 2, 0);
	drawColor.blue = cf->ReadTupleLength(section, "color", 3, 0);
	
	sensorUpdate = cf->ReadInt(section, "sensorupdate", 100);
	plumeUpdate = cf->ReadInt(section, "plumeupdate", 10);
	
	sensorPosition.px = cf->ReadTupleLength(section, "sensorposition", 0, 0.0);
	sensorPosition.py = cf->ReadTupleLength(section, "sensorposition", 1, 0.0);
	sensorPosition.pz = cf->ReadTupleLength(section, "sensorposition", 2, 0.0);
	
	modelSensor = cf->ReadInt(section, "modelsensor", 0);
	
	opaque_data.data_count = sizeof(odor_data_t);
	opaque_data.data = reinterpret_cast<uint8_t*>(&odor_data);
}

// *****************************************************************************
// Destructor.
PlumeSim::~PlumeSim()
{
	delete source;
}

// *****************************************************************************
// Set up the device.  Return 0 if things go well, and -1 otherwise.
int PlumeSim::MainSetup()
{   
	PLAYER_MSG0(MESSAGE_INFO,"> PlumeSim > Driver starting up...");
	
	// Initialise the underlying position device.
	if(this->SetupOdom() != 0) return -1;
	
	// Initialise the graphics3d device.
	if(this->pencil_addr.interf) if(this->SetupPencil() != 0) return -1;
	
	source->setup();
    
	PLAYER_MSG0(MESSAGE_INFO,"> PlumeSim > Driver is ready.");
	
	return(0);
}

// *****************************************************************************
// Shutdown the device
void PlumeSim::MainQuit()
{
	PLAYER_MSG0(MESSAGE_INFO,"> PlumeSim > Shutting down...");
	
	// Clean up...
	source->cleanup();
	
	// Stop the graphics3d device.
	if(this->pencil_addr.interf) this->ShutdownPencil();
	// Stop the odom device.
	this->ShutdownOdom();
	
	PLAYER_MSG0(MESSAGE_INFO,"> PlumeSim > Driver shutdown complete.");
}

// *****************************************************************************
// Set up the underlying odom device.
int PlumeSim::SetupOdom()
{
	// Setup the output position device
	if( !(this->odom = deviceTable->GetDevice(this->odom_addr)) )
	{
		PLAYER_ERROR("Unable to locate a suitable position device.");
		return -1;
	}
	if( this->odom->Subscribe(this->InQueue) != 0 )
	{
		PLAYER_ERROR("Unable to subscribe to a position device.");
		return -1;
	}
	memset(&this->odom_pose, 0, sizeof(this->odom_pose));
	
	return(0);
}

// *****************************************************************************
// Shutdown the underlying odom device.
int PlumeSim::ShutdownOdom()
{
	// Stop the robot before unsubscribing
	this->odom->Unsubscribe(this->InQueue);
	return(0);
}

// *****************************************************************************
// Set up the laser
int PlumeSim::SetupPencil()
{
	if( !(this->pencil = deviceTable->GetDevice(this->pencil_addr)) )
	{
		PLAYER_ERROR("Unable to locate a suitable graphics3d device.");
		return -1;
	}
	if(this->pencil->Subscribe(this->InQueue) != 0)
	{
		PLAYER_ERROR("Unable to subscribe to the graphics3d device.");
		return -1;
	}
	
	return(0);
}

// *****************************************************************************
// Shut down the laser
int PlumeSim::ShutdownPencil()
{
	this->pencil->Unsubscribe(this->InQueue);
	return(0);
}

// *****************************************************************************
// Process Manage function
int PlumeSim::ProcessMessage(QueuePointer & resp_queue, player_msghdr * hdr, void * data)
{
	// Process messages here.  Send a response if necessary, using Publish().
	// If you handle the message successfully, return 0.  Otherwise,
	// return -1, and a NACK will be sent for you, if a response is required.
	assert(hdr);
	
	// Is it new odometry data?
	if(Message::MatchMessage(hdr, PLAYER_MSGTYPE_DATA, PLAYER_POSITION2D_DATA_STATE, this->odom_addr))
	{
		this->ProcessOdom((player_position2d_data_t*)data);
		return(0);
	}
	// Is it a cmd from the robot?
	else if(Message::MatchMessage(hdr, PLAYER_MSGTYPE_DATA, PLAYER_OPAQUE_CMD_DATA, this->device_addr))
	{
		//this->ProcessCmd((_data_t*)data);
		return(0);
	}
	
	PLAYER_MSG0(MESSAGE_INFO,"> PlumeSim > Received an unknown message type.");
	return(-1);
}

// *****************************************************************************
// Function for processing incoming odometry data
void PlumeSim::ProcessOdom(player_position2d_data_t * data) 
{	
	this->odom_pose = data->pos;
}

// *****************************************************************************
// Draw points into stage using the graphics3d interface
int PlumeSim::DrawPoints()
{	
	PSPoints2Draw * points2draw = source->getPointsToDraw();
	
	player_graphics3d_cmd_draw toDraw;
	
	memset(&toDraw, 0, sizeof(player_graphics3d_cmd_draw));
	
	toDraw.draw_mode = PLAYER_DRAW_POINTS;
	
	toDraw.color.alpha = drawColor.alpha;
	toDraw.color.red = drawColor.red;
	toDraw.color.green = drawColor.green;
	toDraw.color.blue = drawColor.blue;
	
	toDraw.points_count = points2draw->length;
	toDraw.points = new player_point_3d_t[points2draw->length];
	
	player_point_3d_t * point;
	points2draw->resetPointer();
	for(int i=0 ; i<points2draw->length ; i++)
	{
		point = points2draw->nextPoint();
		toDraw.points[i].px = point->px;
		toDraw.points[i].py = point->py;
		toDraw.points[i].pz = point->pz;
	}
	
	this->pencil->PutMsg(this->InQueue, PLAYER_MSGTYPE_CMD, PLAYER_GRAPHICS3D_CMD_DRAW, (void*)&toDraw, sizeof(toDraw), NULL);
	
	delete [] toDraw.points;
	
	return(0);
}

// *****************************************************************************
// Clear the points drawn in stage
int PlumeSim::ClearPoints() 
{	
	this->pencil->PutMsg(this->InQueue, PLAYER_MSGTYPE_CMD, PLAYER_GRAPHICS3D_CMD_CLEAR, NULL, 0, NULL);

	return(0);
}

// *****************************************************************************
// Main function for device thread
void PlumeSim::Main()
{	
	int t = 0;
	
	// First generation (and last for static plumes)
	source->generatePoints();
	if(this->pencil_addr.interf) this->DrawPoints();
		
	// The main loop
	// Interact with the device here
	while(true)
	{
		// Test if we are supposed to cancel
		pthread_testcancel();
		
		// Process incoming messages. PlumeSim::ProcessMessage() is called on each message.
		ProcessMessages();
		
		if(source->ChangesOverTime() && source->IsPlaying() && t==plumeUpdate)
		{
			source->generatePoints();
			if(this->pencil_addr.interf)
			{
				this->ClearPoints();
				this->DrawPoints();
			}
			t = 0;
		}
	
		player_point_3d_t position;
		position.px = odom_pose.px + sensorPosition.px;
		position.py = odom_pose.py + sensorPosition.py;
		position.pz = 0.0;

		source->getChemicalReading(&position, &odor_data);
		
		// Publish data
		uint32_t size = sizeof(opaque_data) - sizeof(opaque_data.data) + opaque_data.data_count;
		// Publish() the data encapsulated on the opaque data structure
		Publish(device_addr, PLAYER_MSGTYPE_DATA, PLAYER_OPAQUE_DATA_STATE, reinterpret_cast<void*>(&opaque_data), size, NULL);
	
		// Sleep (you might, for example, block on a read() instead)
		usleep(1000*sensorUpdate);
		t++;
	}
}


////////////////////////////////////////////////////////////////////////////////
// Extra stuff for building a shared object.

/* need the extern to avoid C++ name-mangling  */
extern "C" {
	int player_driver_init(DriverTable* table)
	{
		puts("PlumeSim driver initializing");
		PlumeSim_Register(table);
		puts("PlumeSim done");
		return(0);
	}
}

// EOF

