#pragma once
#ifndef DEF_MAP
#define DEF_MAP
#include "stdafx.h"
#include "tmxlite/Map.hpp"
#include "SFMLOrthogonalLayer.hpp"

class Carte
{
	//Attributes
public:
	Carte();
	~Carte();

	//Functions
	void createTMX(char*);
	void updateTMX_before(sf::RenderWindow&);
	void updateTMX_after(sf::RenderWindow&, int);

	void Load(std::string filename);
	void Draw(sf::RenderWindow &);
	bool IsLoaded() const;

	sf::Sprite& GetSprite();
	sf::Texture& GetTexture();
	tmx::Map& GetMap();
	std::vector<std::unique_ptr<MapLayer>> layerCarte;

	sf::Clock clockAnimationCascade;

private:
	sf::Texture texture_map;
	sf::Sprite sprite_map;
	std::string filename_map;
	bool _isLoaded;
	tmx::Map macarte;

};

#endif
