#include "Level.h"
#include <math.h>
int inX;
int inY;
bool pressMode = false;

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "Error\n";
	}

	text.setFont(font);
	text.setString(coordDisplay());
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	

	if (input->isKeyDown(sf::Keyboard::W)) {
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W was pressed\n";
	}

	if ((input->isKeyDown(sf::Keyboard::J)) && (input->isKeyDown(sf::Keyboard::K)) && (input->isKeyDown(sf::Keyboard::L))) {
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		std::cout << "J,K and L were pressed\n";		
	}

	if (input->isMouseLDown()) {
		if (pressMode == false) {
			pressMode = true;
			inX = input->getMouseX();
			inY = input->getMouseY();
		}
	}

	if (!(input->isMouseLDown())) {
		// this must only start activating after the first one
		if (pressMode == true) {
			pressMode = false;
			int fiX = input->getMouseX();
			int fiY = input->getMouseY();
			int disp = sqrt((fiX - inX)*(fiX - inX) + (fiY - inY)*(fiY - inY));
			std::cout << "Distance was " << fiX + fiY - inX - inY << ", Displacement was " << disp << "\n";
			
		}
	}

	if (input->isKeyDown(sf::Keyboard::Escape)) {
		window->close();
	}

}

// Update game objects
void Level::update()
{
	text.setString(coordDisplay());
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(text);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}

std::string Level::coordDisplay(){
	int x = input->getMouseX();
	int y = input->getMouseY();
	std::string s("Mouse: " + std::to_string(x) + "x, " + std::to_string(y) + "y\n");
	return s;
}