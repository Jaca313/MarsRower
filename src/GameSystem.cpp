#include "GameSystem.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void GameSystem::initGLFW()
{
	//glfw: initialize and configure
	//------------------------------
	int l_majorContext = 4;
	int l_minorContext = 0;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, l_majorContext);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, l_minorContext);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::cout << "REQUESTED::OPENGL::VERSION(" << l_majorContext << "."<< l_minorContext << ")" << std::endl;

	// glfw window creation
	// --------------------
	char* windowTitle = new char[m_sWinName.length()];
	wcstombs(windowTitle, m_sWinName.c_str(), m_sWinName.length());


	window = glfwCreateWindow(m_iWinWidth, m_iWinHeight, windowTitle, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

}

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

	initGLFW();

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
	while (!glfwWindowShouldClose(window) && !m_executionStack.empty()) {

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
