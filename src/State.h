#pragma once
#include "OpenGLHelper.h"
#include "Shader.h"
#include "ResourceManager.h"

/**
 * All of the Valid State IDs
 */
enum class States {
	INVALID = 0,
	Gameplay = 100,
	Menu = 200,
	Pause = 300,
	Loading = 400
};

class State
{
public:
	/**
	 * Virtual Destructor to be overwritten
	 * 
	 */
	virtual ~State() = default;

protected:
	/**
	 * ID of the State
	 */
	States ID = States::INVALID;

public:
	/**
	 * Loop for events
	 * 
	 */
	virtual void eventLoop() = 0;

	/**
	 * Deals with Input
	 * 
	 * @param fTime time since last frame
	 */
	virtual void input(float fTime) = 0;

	/**
	 * Updates State
	 * 
	 * @param fTime time since last frame
	 */
	virtual void update(float fTime) = 0;

	/**
	 * Draws frame from state
	 * 
	 */
	virtual void draw(float fTime) = 0;

	/////////////////////////////////////
	/**
	 * Checks if the State wants to quit
	 * 
	 * @return Does the state want to quit
	 */
	virtual bool quitState() const;

	/**
	 * Checks if the State wants to push another State onto the Stack
	 * @warning CLEARS THE REQUESTED STATE
	 * @return ID of the State it requests
	 */
	virtual States requestState();

	/**
	 * Operation to be done when resuming a state
	 * 
	 */
	virtual void resumeState() = 0;

	/**
	 * Checks if state wants to force change further down to a state
	 * Forces the Stack to dump all the States not matching the ID from the Top of the Stack
	 * 
	 * @return ID of the State it wants to push down to
	 */
	virtual States forceState() const;

	/**
	 * Final saving/operation to be done when exiting a State
	 * 
	 */
	virtual void endState() = 0;

protected:
	/**
	 * Is the state ready to quit
	 */
	bool m_bWantsQuit = false;

	/**
	 * Requested State
	 */
	States m_iRequestState = States::INVALID;

	/**
	 * Is the State to be resumed
	 */
	bool m_bResume = false;

	/**
	 * State to be pushed down to
	 */
	States m_iForceState = States::INVALID;

public:
	/**
	 * Check if state is to be resumed
	 * 
	 * @return is the state to be resumed
	 */
	bool getResumeState();

	/**
	 * Check if State requests a State
	 * 
	 * @return is the state requesting another
	 */
	bool getRequestState();

	/**
	 * Get State ID
	 * 
	 * @return ID of the State
	 */
	States getID();
};

