#pragma once
#include <fstream>
#include <string>
#include <stack>
#include <iostream>

#include "State.h"
#include "Timer.h"

class GameSystem
{
public:
	/**
	 * Destructor
	 * TODO: CLeanup
	 */
	~GameSystem();

	/**
	 * Encapsulated Mars Rover Experience :)
	 *  TODO:Create Window etc.?
	 */
	GameSystem();

	/**
	 * Program Entry Point
	 * 
	 */
	void Run();
private:
	/**
	 * Loads basic settings about the window from window.ini
	 */
	void LoadSettings();

	/**
	 * Window Title
	 */
	std::wstring m_sWinName;

	/**
	 * Window Width
	 */
	int m_iWinWidth = 1280;

	/**
	 * Window Height
	 */
	int m_iWinHeight = 720;

	/**
	 * Stack with all initialized States
	 */
	std::stack<State*> m_executionStack;

	/**
	 * Removes the top State from stack while letting it shutdown
	 */
	void PopState();

	/**
	 * Lets a State push a new State
	 */
	void PushState(States requestedState);

	/**
	 * Main Program Loop
	 */
	void MainLoop();

	/**
	 * Closes the Program
	 */
	void ExitGame();

	////////////////
	/// TimeKeeping
	
	Timer m_Clock; 
	float m_fTime = 1/60.f;
	
};


