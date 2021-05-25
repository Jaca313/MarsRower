#pragma once
#include "State.h"


#include "Model.h"
#include "Camera.h"
#include <filesystem>

class State_Game :
    public State
{
private:
	GLFWwindow* m_window;
public:
    /**
     * Destructor of State_Game
     * 
     */
    ~State_Game();

    /**
     * Constructor of State_Game
     * 
     */
    State_Game(GLFWwindow* window);

	/**
	 * Loop for events
	 *
	 */
	void eventLoop() override;

	/**
	 * Deals with Input
	 *
	 * @param fTime time since last frame
	 */
	void input(float fTime) override;

	/**
	 * Updates State
	 *
	 * @param fTime time since last frame
	 */
	void update(float fTime) override;

	/**
	 * Draws frame from state
	 *
	 */
	void draw(float fTime) override;

	/**
	* Operation to be done when resuming a state
	*
	*/
	void resumeState() override;
    
	/**
	* Final saving/operation to be done when exiting a State
	*
	*/
	void endState() override;
private:
	ResourceManager& r_ResourceManager = ResourceManager::getInstance();

	//TestObject T1;

	//TODO:DONT FORGET TO CLEAN THIS UP :D
	Model* Backpack;

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	//matrices
	glm::mat4 projection;
	glm::mat4 view;
};

