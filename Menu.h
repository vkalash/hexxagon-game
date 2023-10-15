#pragma once
#include "SFML/Graphics.hpp"

class Menu
{
private:
	//window
	sf::RenderWindow* window{};
	sf::VideoMode videoMode;
	sf::Event ev{};

	//background
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackground;



	//logic
	int selectedItemIndex{};
	sf::Font font;
	sf::Text menu[3];
	sf::Text gameName;
	
	//logic functions
	static void runGame();
	static void runSoloGame();

public:
	Menu();
	virtual ~Menu();

	//init
	void initVariables();
	void initWindow();
	void initGUI();

	//Accessors
	bool running();

	//logic
	void MoveUp();
	void MoveDown();
	int getPressedItem() const;

	void pollEvents();
	void update();
	
	void render();
};

