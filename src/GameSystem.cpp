#include "GameSystem.h"

GameSystem::~GameSystem()
{
	//Exit from Stack in order (saving data if need be)
	while (!m_executionStack.empty()) {
		PopState();
	}
}

GameSystem::GameSystem()
{
	LoadSettings();


}

void GameSystem::Run()
{
	//TODO:FIX STATE
	//PushState(States::Gameplay);
	MainLoop();
}

void GameSystem::LoadSettings()
{
	//Default Values
	m_iWinWidth = 1280;
	m_iWinHeight = 720;
	m_sWinName = L"Default Title!";

	//Grab Settings from Window.ini
	std::wifstream ifs("Config/Window.ini");
	if (ifs.is_open()) {
		std::getline(ifs, m_sWinName);//Load Title
		ifs >> m_iWinWidth >> m_iWinHeight;//Load Window Dimensions
	}
	else {
		std::cout << "PROGRAM::SETTINGS::ERROR_LOADING_WINDOW.INI" << std::endl;
	}
	ifs.close();
}

void GameSystem::PopState()
{
	m_executionStack.top()->endState();
	delete m_executionStack.top();
	m_executionStack.pop();
}

void GameSystem::PushState(States requestedState)
{
	//TODO: Get States up and running
	//Push state that is requested by another State
	switch (requestedState) {
	case States::Gameplay:
		///m_executionStack.push(new Gamessssss)
		break;
	case States::Menu:
		///m_executionStack.push(new Gamessssss)
		break;
	default:
		std::cout << "PROGRAM::EXECUTIONSTACK::STATES::INVALID_PUSH " << std::endl;
	}
}

void GameSystem::MainLoop()
{
	//Main App Loop
	while (/*window is open and*/ !m_executionStack.empty()) {

		//if we resume a state that has been paused run some actions before resuming
		if (m_executionStack.top()->getResumeState())m_executionStack.top()->resumeState();

		m_executionStack.top()->eventLoop();//Resolve events
		m_executionStack.top()->input(m_fTime);//Resolve Input
		m_executionStack.top()->update(m_fTime);//Update State
		m_executionStack.top()->draw();//Render State

		//TODO:LEGACY
		////Display
		//m_window->draw(sf::Sprite(m_screenBuffer.getTexture()), &Resources.m_sFlipScreen);//Draw ScreenBuffer to Window
		//m_window->display();//Display Window

		//Timing
		m_fTime = m_Clock.Count();//Get Frame Time

		//GameState Controller
		if (m_executionStack.top()->getRequestState())PushState(m_executionStack.top()->requestState());//Check if push state
		if (m_executionStack.top()->quitState())PopState();//Check if pop State
		if (m_executionStack.size() && m_executionStack.top()->forceState() != States::INVALID) {//Force go to state that is lower in stack, pop unwanted
			States WantedState = m_executionStack.top()->forceState();

			while (!m_executionStack.empty() && m_executionStack.top()->getID() != WantedState) {
				PopState();
			}
		}
	}
	ExitGame();//Exit App
}

void GameSystem::ExitGame()
{
	//TODO: Properly exit the window
}
