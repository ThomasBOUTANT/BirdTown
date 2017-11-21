#pragma once
#include "StdAfx.h"

class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(sf::Time tmps);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual bool IsLoaded() const;

	//std::vector<unique_ptr<PNJ>> vec_PNJ;

protected:
	sf::Sprite& GetSprite();
	sf::Texture& GetTexture();

private:
	sf::Sprite  _sprite;
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;

};
