#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

extern std::vector<std::unique_ptr<PNJ>> vec_PNJ;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, Character* gameObject)
{
	_gameObjects.insert(std::pair<std::string, Character*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
	std::map<std::string, Character*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

Character* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, Character*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;

}

int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}


void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{

	std::map<std::string, Character*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}

	//Drawing the PNJs - bad way...
	for each(auto const &pnj in vec_PNJ) {
		pnj->Draw(renderWindow);
		if (pnj->indice_affiche) {
			renderWindow.draw(pnj->indice_PNJ);
			//menu.draw(pnj->indice_menu);
		}
	}

	//Drawing the clues
}

void GameObjectManager::UpdateAll()
{
	std::map<std::string, Character*>::const_iterator itr = _gameObjects.begin();
	//float timeDelta = Game::GetWindow().GetFrameTime();
	//New version  de SFML : creer une clock

	sf::Clock clock;

	while (itr != _gameObjects.end())
	{
		itr->second->Update(clock.restart());
		itr++;
	}

}

