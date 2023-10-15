#include "Hex.h"
#include <iostream>

void Hex::initVariables()
{
    this->piece = nullptr;
}

void Hex::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/hexagon.png"))
	{	
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
	this->texture.setSmooth(true);
}

void Hex::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.8f, 0.8f);
}


Hex::Hex(int q_, int r_, int s_)
{	
	this->hexCords = new HexCoord(q_, r_, s_);
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Hex::~Hex()
{
	delete this->piece;
	delete this->piece;
}

void Hex::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Hex::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}


void Hex::move(const float dirX, const float dirY)
{
	this->sprite.move(dirX, dirY);
}

void Hex::setDefault()
{
	initTexture();
	this->sprite.setTexture(this->texture);
}

void Hex::setSelected()
{
	if (!this->texture.loadFromFile("Textures/selectedHexagon.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
	this->sprite.setTexture(this->texture);
}


void Hex::setSize(const float size)
{
	//Resize the sprite
	this->sprite.scale(size * 10, size * 10);
}

void Hex::setPiece(int teamColor)
{
	this->piece = new Piece(teamColor);
}

void Hex::removePiece()
{
	this->piece = nullptr;
}

void Hex::setPieceTeam(int team)
{
	this->piece->setTeamColor(team);
}


int Hex::getCurrentTeam()
{
	return this->piece->getTeamColor();
}

sf::Sprite Hex::getShape()
{
	return this->sprite;
}


int Hex::getQCord() const
{
	return this->hexCords->getQ();
}

int Hex::getRCord() const
{
	return this->hexCords->getR();
}

int Hex::getSCord() const
{
	return this->hexCords->getS();
}

bool Hex::isOccupied()
{
	return this->piece != nullptr;
}


//Functions
void Hex::update()
{

}

void Hex::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (piece != nullptr) {
		this->piece->setPosition(sprite.getPosition());
		target.draw(this->piece->getShape());
	}
}