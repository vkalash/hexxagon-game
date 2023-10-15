#pragma once
#include "SFML/Graphics.hpp"

class Piece
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	int teamColor;
	void initTexture();
	void initSprite();

public:
	Piece(int teamColor_);
	virtual ~Piece();
	sf::Sprite getShape();
	int getTeamColor() const;
	void setPosition(sf::Vector2f pos);
	void setTeamColor(int teamColor);

};

