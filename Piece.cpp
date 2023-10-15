#include "Piece.h"
#include <iostream>

void Piece::initTexture()
{
	//Load a texture from file
	if (this->teamColor == 1) {
		if (!this->texture.loadFromFile("Textures/red_circle.png"))
		{
			std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
		}
	}
	else
	{
		if (!this->texture.loadFromFile("Textures/blue_circle.png"))
		{
			std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
		}
	}
	
}

void Piece::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.26f, 0.26f);
}

Piece::Piece(int teamColor_) : teamColor(teamColor_)
{
	initTexture();
	initSprite();
}

Piece::~Piece()
= default;

sf::Sprite Piece::getShape()
{
	return sprite;
}

int Piece::getTeamColor() const
{
	return teamColor;
}


void Piece::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(sf::Vector2f(pos.x + 14.0f, pos.y + 8.0f));
}




void Piece::setTeamColor(const int color)
{
	this->teamColor = color;
	initTexture();
}
