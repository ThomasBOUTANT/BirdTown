#include "StdAfx.h"
#include "Player.h"
#include "PNJ.h"
//#include "Game.h"

Player::Player() :
	speed(5.0),
	maxSpeed(5.0f)
{
	Load("Images/Sprites_personnages/sprite.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getScale().x / 2, GetSprite().getScale().y / 2);
	niveauEtage = 1;
	fpsCount = 0;
	switchFps = 200;
	fpsSpeed = 500;
	animationPlayer = false;
	clockAnimationPlayer.restart();
}

Player::~Player() {}

void Player::gestionCollisionBords() {

	// Gestion des collisions
	if (GetPosition().x < 0) {
		SetPosition(0, GetPosition().y);
	}
	if (GetPosition().y < 0) {
		SetPosition(GetPosition().x, 0);
	}
	if (GetPosition().x > 3200 - largeur_sprite_heros) {
		SetPosition(3200 - largeur_sprite_heros, GetPosition().y);
	}
	if (GetPosition().y > 3200 - hauteur_sprite_heros) {
		SetPosition(GetPosition().x, 3200 - hauteur_sprite_heros);
	}

}

void Player::Update(tmx::Map& carteTMX) {
	sf::Time time = clockAnimationPlayer.getElapsedTime();
	//std::cout << time.asSeconds() << std::endl;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if (animation_heros.y == Up) {
			switch (entreeDansGrotte(GetPosition().x + speed, GetPosition().y, carteTMX)) {
			case 0: {break; }
			case 1:
			{
				SetPosition(1990, 920);
				animation_heros.y = Down;
				break;
			}
			case 2:
			{
				SetPosition(2000, 1700);
				animation_heros.y = Down;
				break;
			}
			}
		}
	}


	//Movements of the player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		animation_heros.y = Down;
		if (!collision(GetPosition().x, GetPosition().y + speed, carteTMX)) {
			GetSprite().move(0, speed);
		}
		animationPlayer = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		animation_heros.y = Up;
		if (!collision(GetPosition().x, GetPosition().y - speed, carteTMX)) {
			GetSprite().move(0, -speed);
		}
		animationPlayer = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		animation_heros.y = Left;
		if (!collision(GetPosition().x - speed, GetPosition().y, carteTMX)) {
			GetSprite().move(-speed, 0);
		}
		animationPlayer = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		animation_heros.y = Right;
		if (!collision(GetPosition().x + speed, GetPosition().y, carteTMX)) {
			GetSprite().move(speed, 0);
		}
		animationPlayer = true;
	}

	//Interactions with the PNJs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		sf::Vector2f position = GetPosition();
		float x = position.x;
		float y = position.y;
		PNJ_interroger(x, y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sf::Vector2f position = GetPosition();
		float x = position.x;
		float y = position.y;
		PNJ_designer(x, y);
	}

	if (animationPlayer) {
		fpsCount += fpsSpeed * time.asSeconds();
	}
	if (fpsCount >= switchFps) {
		animation_heros.x++;
		if (animation_heros.x++ * GetLargeurPlayer() >= GetTexture().getSize().x) {
			animation_heros.x = 1;
		}
		clockAnimationPlayer.restart();
		fpsCount = 0;
		animationPlayer = false;
	}


	gestionCollisionBords();
	GetSprite().setTextureRect(sf::IntRect(animation_heros.x * (int)largeur_sprite_heros, animation_heros.y * (int)hauteur_sprite_heros, (int)largeur_sprite_heros, (int)hauteur_sprite_heros));
}

void Player::Draw(sf::RenderWindow & rw)
{
	Character::Draw(rw);
}

float Player::GetSpeed() const
{
	return speed;
}

float Player::GetLargeurPlayer() const {
	return largeur_sprite_heros;
}

float Player::GetHauteurPlayer() const {
	return hauteur_sprite_heros;
}


bool Player::collision(float new_x, float new_y, tmx::Map& carteTMX)
{
	const auto& mapProperties = carteTMX.getProperties();

	for (const auto& prop : mapProperties)
	{
		std::cout << "Found property: " << prop.getName() << std::endl;
		std::cout << "Type: " << int(prop.getType()) << std::endl;
	}

	const auto& layers = carteTMX.getLayers();
	for (const auto& layer : layers) {
		if (layer->getType() == tmx::Layer::Type::Object) {
			const auto& objects = dynamic_cast<tmx::ObjectGroup*>(layer.get())->getObjects();
			for (const auto& object : objects) {
				if (object.getName() == "Object") {
					const auto& properties = object.getProperties();

					tmx::FloatRect rectangle = object.getAABB();

					for (const auto& prop : properties) {
						if (prop.getName() == "collision") {
							float new_x_right = new_x + GetLargeurPlayer();
							float rectangle_right = rectangle.left + rectangle.width;
							float new_y_bottom = new_y + GetHauteurPlayer();
							float rectangle_bottom = rectangle.top + rectangle.height;
							if ((
								(new_x > rectangle.left && new_x < rectangle_right)
								|| (new_x_right > rectangle.left && new_x_right < rectangle_right)
								|| (rectangle.left > new_x && rectangle.left < new_x_right)
								)
								&&
								(
								(new_y > rectangle.top && new_y < rectangle_bottom)
									|| (new_y_bottom > rectangle.top && new_y_bottom < rectangle_bottom)
									|| (rectangle.top > new_y && rectangle.top < new_y_bottom)
									)
								) {
								return true;
							}
						}
					}
				}
				else if (object.getName() == "CollisionSurPont" && niveauEtage == 1) {
					tmx::FloatRect rectangle = object.getAABB();

					float new_x_right = new_x + GetLargeurPlayer();
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + GetHauteurPlayer();
					float rectangle_bottom = rectangle.top + rectangle.height;
					if ((
						(new_x > rectangle.left && new_x < rectangle_right)
						|| (new_x_right > rectangle.left && new_x_right < rectangle_right)
						|| (rectangle.left > new_x && rectangle.left < new_x_right)
						)
						&&
						(
						(new_y > rectangle.top && new_y < rectangle_bottom)
							|| (new_y_bottom > rectangle.top && new_y_bottom < rectangle_bottom)
							|| (rectangle.top > new_y && rectangle.top < new_y_bottom)
							)
						) {
						return true;
					}
				}
				else if (object.getName() == "CollisionSousPont" && niveauEtage == 0) {
					tmx::FloatRect rectangle = object.getAABB();

					float new_x_right = new_x + GetLargeurPlayer();
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + GetHauteurPlayer();
					float rectangle_bottom = rectangle.top + rectangle.height;
					if ((
						(new_x > rectangle.left && new_x < rectangle_right)
						|| (new_x_right > rectangle.left && new_x_right < rectangle_right)
						|| (rectangle.left > new_x && rectangle.left < new_x_right)
						)
						&&
						(
						(new_y > rectangle.top && new_y < rectangle_bottom)
							|| (new_y_bottom > rectangle.top && new_y_bottom < rectangle_bottom)
							|| (rectangle.top > new_y && rectangle.top < new_y_bottom)
							)
						) {
						return true;
					}
				}


				else if (object.getName() == "SousPont") {
					tmx::FloatRect rectangle = object.getAABB();

					float new_x_right = new_x + GetLargeurPlayer();
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + GetHauteurPlayer();
					float rectangle_bottom = rectangle.top + rectangle.height;
					if ((
						(new_x > rectangle.left && new_x < rectangle_right)
						|| (new_x_right > rectangle.left && new_x_right < rectangle_right)
						|| (rectangle.left > new_x && rectangle.left < new_x_right)
						)
						&&
						(
						(new_y > rectangle.top && new_y < rectangle_bottom)
							|| (new_y_bottom > rectangle.top && new_y_bottom < rectangle_bottom)
							|| (rectangle.top > new_y && rectangle.top < new_y_bottom)
							)
						) {
						niveauEtage = 0;
					}
				}
				else if (object.getName() == "SurPont") {
					tmx::FloatRect rectangle = object.getAABB();

					float new_x_right = new_x + GetLargeurPlayer();
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + GetHauteurPlayer();
					float rectangle_bottom = rectangle.top + rectangle.height;
					if ((
						(new_x > rectangle.left && new_x < rectangle_right)
						|| (new_x_right > rectangle.left && new_x_right < rectangle_right)
						|| (rectangle.left > new_x && rectangle.left < new_x_right)
						)
						&&
						(
						(new_y > rectangle.top && new_y < rectangle_bottom)
							|| (new_y_bottom > rectangle.top && new_y_bottom < rectangle_bottom)
							|| (rectangle.top > new_y && rectangle.top < new_y_bottom)
							)
						) {
						niveauEtage = 1;
					}
				}
			}
		}
	}
	return false;
}

int Player::entreeDansGrotte(float new_x, float new_y, tmx::Map& carteTMX)
{
	const auto& mapProperties = carteTMX.getProperties();

	for (const auto& prop : mapProperties)
	{
		std::cout << "Found property: " << prop.getName() << std::endl;
		std::cout << "Type: " << int(prop.getType()) << std::endl;
	}

	const auto& layers = carteTMX.getLayers();
	for (const auto& layer : layers) {
		if (layer->getType() == tmx::Layer::Type::Object) {
			const auto& objects = dynamic_cast<tmx::ObjectGroup*>(layer.get())->getObjects();
			for (const auto& object : objects) {
				if (object.getName() == "GrotteNiveau0") {
					tmx::FloatRect rectangle = object.getAABB();

					float new_x_right = new_x + GetLargeurPlayer();
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + GetHauteurPlayer();
					float rectangle_bottom = rectangle.top + rectangle.height;
					if ((
						(new_x > rectangle.left && new_x < rectangle_right)
						|| (new_x_right > rectangle.left && new_x_right < rectangle_right)
						|| (rectangle.left > new_x && rectangle.left < new_x_right)
						)
						&&
						(
						(new_y > rectangle.top && new_y < rectangle_bottom)
							|| (new_y_bottom > rectangle.top && new_y_bottom < rectangle_bottom)
							|| (rectangle.top > new_y && rectangle.top < new_y_bottom)
							)
						) {
						return 1;
					}
				}
				if (object.getName() == "GrotteNiveau1") {
					tmx::FloatRect rectangle = object.getAABB();

					float new_x_right = new_x + GetLargeurPlayer();
					float rectangle_right = rectangle.left + rectangle.width;
					float new_y_bottom = new_y + GetHauteurPlayer();
					float rectangle_bottom = rectangle.top + rectangle.height;
					if ((
						(new_x > rectangle.left && new_x < rectangle_right)
						|| (new_x_right > rectangle.left && new_x_right < rectangle_right)
						|| (rectangle.left > new_x && rectangle.left < new_x_right)
						)
						&&
						(
						(new_y > rectangle.top && new_y < rectangle_bottom)
							|| (new_y_bottom > rectangle.top && new_y_bottom < rectangle_bottom)
							|| (rectangle.top > new_y && rectangle.top < new_y_bottom)
							)
						) {
						return 2;
					}
				}
			}
		}
	}
	return 0;
}