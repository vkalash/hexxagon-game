#include "Menu.h"
#include <iostream>
#include "Game.h"

Menu::Menu()
{
	this->initVariables();
	this->initWindow();
	this->initGUI();
}

Menu::~Menu()
{
	delete this->window;
}

void Menu::initVariables()
{
	this->window = nullptr;
}

void Menu::initWindow()
{
	this->videoMode.width = 1280;
	this->videoMode.height = 720;


	this->window = new sf::RenderWindow(this->videoMode, "Hexagon game", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(144);
}

void Menu::initGUI()
{
	if (!font.loadFromFile("Fonts/Rubik.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
	}

	this->menu[0].setFont(font);
	this->menu[0].setCharacterSize(40);
	this->menu[0].setFillColor(sf::Color::Red);
	this->menu[0].setString("PLAY VS FRIEND");
	this->menu[0].setPosition(sf::Vector2f(900, 250));


	this->menu[1].setFont(font);
	this->menu[1].setCharacterSize(40);
	this->menu[1].setFillColor(sf::Color::White);
	this->menu[1].setString("PLAY VS BOT");
	this->menu[1].setPosition(sf::Vector2f(900, 350));


	this->menu[2].setFont(font);
	this->menu[2].setCharacterSize(40);
	this->menu[2].setFillColor(sf::Color::White);
	this->menu[2].setString("EXIT GAME");
	this->menu[2].setPosition(sf::Vector2f(900, 450));
	
	this->gameName.setFont(font);
	this->gameName.setCharacterSize(60);
	this->gameName.setFillColor(sf::Color::White);
	this->gameName.setString("H E X X A G O N  G A M E");
	this->gameName.setPosition(sf::Vector2f(100, 100));

	this->selectedItemIndex = 0;


	//background
	if (!this->worldBackgroundTexture.loadFromFile("Textures/Background.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTexture);
}


bool Menu::running()
{
	return this->window->isOpen();
}

void Menu::MoveUp()
{
	//Move up
	if (selectedItemIndex - 1 >= 0)
	{
		this->menu[selectedItemIndex].setFillColor(sf::Color::White);
		this->selectedItemIndex--;
		this->menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	//Move down
	if (selectedItemIndex + 1 < 3)
	{
		this->menu[selectedItemIndex].setFillColor(sf::Color::White);
		this->selectedItemIndex++;
		this->menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::getPressedItem() const
{
	return selectedItemIndex;
}

void Menu::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::KeyReleased:
			switch (this->ev.key.code)
			{
			case sf::Keyboard::Up:
				this->MoveUp();
				break;

			case sf::Keyboard::Down:
				this->MoveDown();
				break;

			case sf::Keyboard::Return:
				switch (this->getPressedItem())
				{
				case 0:
					this->window->close();
					runGame();
					break;
				case 1:
					this->window->close();
					runSoloGame();
					break;
				case 2:
					this->window->close();
					break;
				}

				break;
			}
		break;

		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Menu::runGame()
{
	Game game;
	//Game loop
	while (game.running())
	{

		//Update
		game.update();


		//Render
		game.render();
	}
}

void Menu::runSoloGame()
{
	Game game;
	game.enableSoloMode();

	//Game loop
	while (game.running())
	{
		//Update
		game.update();

		//Render
		game.render();
	}
}

void Menu::update()
{
	pollEvents();
}

void Menu::render()
{
	this->window->clear();

	this->window->draw(worldBackground);

	for (auto& text : this->menu) {
		this->window->draw(text);
	}
	this->window->draw(gameName);

	this->window->display();
}
