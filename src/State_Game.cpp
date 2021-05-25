#include "State_Game.h"

State_Game::~State_Game()
{
}

State_Game::State_Game(GLFWwindow* window)
{
	ID = States::Gameplay;
	m_window = window;

	stbi_set_flip_vertically_on_load(true);
	
	//Backpack = new Model((char*)"Models/bob/bob.obj");
	//Backpack = new Model((char*)"Models/tankus/tankus.obj");
	Backpack = new Model((char*)"Models/backpack/backpack.obj");
}

void State_Game::eventLoop()
{
}

void State_Game::input(float fTime)
{
	//Close window on Escape
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_window, true);

	if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_window, true);
	}

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, fTime);
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, fTime);
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, fTime);
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, fTime);

}

void State_Game::update(float fTime)
{

}

void State_Game::draw(float fTime)
{
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	r_ResourceManager.getShader("Model").use();
	// view/projection transformations
	int wWidth, wHeight;
	glfwGetWindowSize(m_window, &wWidth, &wHeight);
	projection = glm::perspective(glm::radians(camera->Zoom), (float)wWidth / (float)wHeight, 0.1f, 100.0f);
	view = camera->GetViewMatrix();
	r_ResourceManager.getShader("Model").setMat4("projection", projection);
	r_ResourceManager.getShader("Model").setMat4("view", view);



	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	model = glm::rotate(model,glm::radians(fTime * 25.f), glm::vec3(0.0f, 1.0f, 0.0f));	// it's a bit too big for our scene, so scale it down
	r_ResourceManager.getShader("Model").setMat4("model", model);
	Backpack->Draw(r_ResourceManager.getShader("Model"));

	//Backpack->Draw(r_ResourceManager.getShader("Model"));
	//T1.drawRenderable();
}

void State_Game::resumeState()
{
	m_bResume = false;

}

void State_Game::endState()
{

}
