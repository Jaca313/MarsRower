#pragma once
class GameSystem
{
public:
	/**
	 * Encapsulated Mars Rover Experience :)
	 *  
	 */
	GameSystem();

	/**
	 * Program Entry Point
	 * 
	 */
	void Run();
private:
	/**
	 * Player Input/etc.
	 * 
	 */
	void input();

	/**
	 * Deals with events
	 * 
	 */
	void updateEvents();

	/**
	 * Updates GameState
	 * 
	 */
	void update();

	/**
	 * Rendering
	 * 
	 */
	void render();

	/**
	 * Displays
	 * 
	 */
	void display();

};

