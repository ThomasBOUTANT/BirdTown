#include "Carte.h"
//#include "Game.h"

using namespace std;

Carte::Carte() :
	_isLoaded(false)
{
	clockAnimationCascade.restart();
}

Carte::~Carte() {}

void Carte::Load(std::string filename)
{
	if (texture_map.loadFromFile(filename) == false)
	{
		filename_map = "";
		_isLoaded = false;
	}
	else
	{
		filename_map = filename;
		sprite_map.setTexture(texture_map);
		_isLoaded = true;
	}
}

void Carte::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded)
	{
		renderWindow.draw(GetSprite());
	}
}

void Carte::createTMX(char* nomCarte) {

	if (!GetMap().load(nomCarte)) {
		printf("ca marche pas!\n");
	}
	else {
		std::cout << "Carte TMX created !!!" << std::endl;
	}

	int numeroLayer = 0;
	const auto& layers = GetMap().getLayers();
	for (const auto& layer : layers) {
		if (layer->getType() == tmx::Layer::Type::Tile) {
			auto test = std::make_unique<MapLayer>(GetMap(), numeroLayer);
			std::cout << "Creation layerCarte " << numeroLayer << " : " << layer->getName() << std::endl;
			layerCarte.push_back(std::move(test));
		}
		numeroLayer++;
	}
}

void Carte::updateTMX_before(sf::RenderWindow& rw) {
	sf::Time time = clockAnimationCascade.getElapsedTime();

	int numeroLayer = 0;
	const auto& layers = GetMap().getLayers();
	for (const auto& layer : layers) {
		if (layer->getType() == tmx::Layer::Type::Tile) {
			rw.draw(*layerCarte[numeroLayer]);
			numeroLayer++;
		}
	}

	//std:cout << time.asSeconds() << std::endl;
	if (time.asSeconds() > 1) {
		rw.draw(*layerCarte[3]);
		rw.draw(*layerCarte[5]);
		if (time.asSeconds() > 1.5) {
			clockAnimationCascade.restart();
		}
	}

}
void Carte::updateTMX_after(sf::RenderWindow& rw, int numeroNiveauEtage) {

	int numeroLayer = 0;
	const auto& layers = GetMap().getLayers();
	for (const auto& layer : layers) {
		if (layer->getType() == tmx::Layer::Type::Tile) {
			if (numeroLayer > 5 && numeroLayer < 8) {
				rw.draw(*layerCarte[numeroLayer]);
			}
			numeroLayer++;
		}
	}

	if (numeroNiveauEtage == 0) {
		rw.draw(*layerCarte[8]);
	}

}

sf::Sprite& Carte::GetSprite()
{
	return sprite_map;
}

sf::Texture& Carte::GetTexture()
{
	return texture_map;
}

tmx::Map& Carte::GetMap()
{
	return macarte;
}

bool Carte::IsLoaded() const
{
	return _isLoaded;
}
