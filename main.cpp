#pragma once
#include <iostream>
#include "..\SGPE\Graphics.hpp"
#include "GraphicsSFML.hpp"
#include "..\SGPE\GameObject.hpp"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "InputHandler.hpp"
#include "Grid.hpp"
#include "..\SGPE\Level.hpp"
#include "..\SGPE\SGPE.hpp"



class Player :
	public GameObject

{
private:
	// TODO gameobject id
	std::shared_ptr<Canvas> canvas;
	std::shared_ptr<InputHandler> input;
protected:
	int currentIndex;
public:
	Player(std::shared_ptr<Canvas> canvas, std::shared_ptr<InputHandler> input) :canvas(canvas), input(input) {};
	~Player() {};
	void ButtonAction(const sf::Keyboard::Key key) {};
	void onUpdate() {};
	void onCall() {};
	void onStart() {};
	void onCollision() {};
	void onInteract() {};
	int getCurrentIndex() {
		return currentIndex;
	}
};




class LevelGame : public Level
{
private:
	std::vector<GameObject*>  gameObjects;
	std::shared_ptr<GraphicsSFML> graphics;

public:
	LevelGame(std::vector<GameObject*>  gameObjects, std::shared_ptr<GraphicsSFML> graphics):gameObjects(gameObjects), graphics(graphics){};
	void Update() {};
	void Start() {};

	void Render() {};
	
	~LevelGame() {};
};


class LevelManagerPocketAnimals : public LevelManager
{
private:
	std::vector<LevelGame*> levels;
public:
	LevelManagerPocketAnimals(std::vector<LevelGame*> levels) :levels(levels){}
	~LevelManagerPocketAnimals() {};
	void Start() {}
	void Update() {};
	void Render() {};

};



int main( int argc, char *argv[] ){

	// create window
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode{ 640, 480 }, "SFML window");


	// create game objects
	std::shared_ptr<InputHandler> inputHandler(new InputHandler());

	
	// create canvas connected to the window
	//std::shared_ptr<Grid> grid =  std::make_shared<Grid>();
	//std::shared_ptr<GraphicsSFML> graphics = std::make_shared<GraphicsSFML>(window, grid);

	
	
	//Player p1(grid, inputHandler);
	
	//std::vector<GameObject*> svg;
	//svg.push_back(&p1);
	// create a level connected to the canvas
	//LevelGame lg(svg, graphics);


	//std::vector<LevelGame*> vlg{&lg};
	//LevelManagerPocketAnimals lm(vlg);

	//Core c1(lm);

	
	std::cout << "start\n";

	//c1.Run();
	std::cout << "Terminating application\n";
	return 0;
}

