#include "Character.h"


Character::Character() :
	_isLoaded(false)
{
}


Character::~Character()
{

}

void Character::Load(std::string filename)
{
	if (_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_image);
		_isLoaded = true;
	}
}

void Character::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded)
	{
		renderWindow.draw(_sprite);
	}
}


void Character::Update(sf::Time tmps)
{
}

void Character::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

sf::Vector2f Character::GetPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}


sf::Sprite& Character::GetSprite()
{
	return _sprite;
}

sf::Texture& Character::GetTexture()
{
	return _image;
}

bool Character::IsLoaded() const
{
	return _isLoaded;
}