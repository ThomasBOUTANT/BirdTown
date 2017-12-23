#pragma once
#include "Character.h"


class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, Character* gameObject);
	void Remove(std::string name);
	int GetObjectCount() const;
	Character* Get(std::string name) const;

	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();

private:
	std::map<std::string, Character*> _gameObjects;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, Character*> & p) const
		{
			delete p.second;
		}
	};
};