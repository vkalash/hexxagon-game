#pragma once
#include "SFML/Graphics.hpp"
#include  <vector>
#include "Hex.h"
#include <unordered_set>

/*
	Game functionality class
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window{};
	sf::VideoMode videoMode;
	sf::Event ev{};


	//GUI
	sf::Font font;
	sf::Text pointTextTeamOne;
	sf::Text pointTextTeamTwo;
	sf::Text gameOverText;
	sf::RectangleShape pointsBarTeamOne;
	sf::RectangleShape pointsBarTeamTwo;


	//Background
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackground;

    /*
     * Number of rows in hex grid
     */
	int N{};
	float hexSize{};

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game logic
	unsigned pointsTeamOne{};
	unsigned pointsTeamTwo{};

	bool selected{};
	bool mouseHeld{};
	Hex* selectedHex{};
	int teamTurn{};
	int winnerTeam{};
	bool isGameEnd{};


	//Game objects
    /*
     * Vector of hexagons
     */
	std::unordered_set<Hex*> hexagons;
    /*
     * Vector of hexagons within range of movement
     */
	std::vector<Hex*> hexesInRange;

	//game mechanic functions
	void selectPiece();
	void movePiece();

	//logic functions
	Hex * findHexByCords(const HexCoord& hexCoord);
	std::vector<Hex*> getNeighbors(Hex *hex, int range);
	void occupyNeighbors(Hex *hex);
	bool onePlayerMode{};
	bool canMove(Hex* hex);
	void changeTeam();
	void calcPoints();
	int calcFreeHexes();
	void resetPoints();
	void checkForGameEnd();
    /*
     * Finding the best move for bot and making it
     */
	void makeBestMove();

    /*
     * Finding all team members and returning vector of pointers
     *
     * @return @std::vector<Hex*>
     */
	std::vector<Hex*> getTeamByColor(int teamTurn);

	//Private functions
	void initVariables();
	void initWindow();
    /*
     * Initializing hexes and adding them to unordered_set
     */
	void initHexes();
	void initGUI();
	void initText(sf::Text &text);

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	bool running();

	//logic
    /*
     * Enables game with the bot state
     */
	void enableSoloMode();

	//Function
    /*Event Polling*/
	void pollEvents();
    /*
     * Updating mouse position to track clicks
     */
	void updateMousePosition();
	void updateHexes();
    void updateGUI();

    /*
     * Putting all update function together
     *
     * Update functions are handling input from the user
     */
    void update();

    void renderGUI();
    void renderGameEnd();

    /*
     * Putting all render function together
     *
     * Render functions are updating the window
     * each call is a new frame
     */
	void render();

};


