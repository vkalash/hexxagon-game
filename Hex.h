#pragma once
#include <cassert>
#include "SFML/Graphics.hpp"
#include <vector>
#include "Piece.h"
#include "HexCoord.h"

class Hex
{
private:
	sf::Sprite sprite;
	sf::ConvexShape hexagon;
	sf::Texture texture;
	Piece *piece;

    /*
     * Vector of hex neighbors
     */
	std::vector<std::vector<int>> hex_directions;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	HexCoord* hexCords;
	Hex(int q_, int r_, int s_);
	virtual ~Hex();

	//Accessor
	int getQCord() const;
	int getRCord() const;
	int getSCord() const;
	bool isOccupied();
	int getCurrentTeam();

	//Modifiers
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);


	//logic functions


	//Functions
	void move(float dirX, float dirY);
    /*
     * Setting default (not selected) texture
     */
	void setDefault();
	void setSelected();
	void setSize(float size);
	void setPiece(int teamColor);
	void removePiece();
	void setPieceTeam(int team);
	sf::Sprite getShape();
	void update();
	void render(sf::RenderTarget& target);

};

