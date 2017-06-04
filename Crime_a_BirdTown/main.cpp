#pragma region includes
#include "monMain.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "../Crime_a_BirdTown/PNJ.h"
#include "../Crime_a_BirdTown/Map.h"
#include "../Crime_a_BirdTown/Perso.h"
#include "../Crime_a_BirdTown/View.h"

#pragma endregion includes

using namespace std;

#pragma region variables
sf::RenderWindow window;
sf::RenderWindow menu;

int speed = 4;
enum Dir { Down, Left, Right, Up };
sf::Vector2i anim(1, Down);
bool updateFPS = true;
float fpsCount = 0, switchFps = 50, fpsSpeed = 500;

sf::Vector2f position_perso(0, 0);
sf::Vector2i positionSouris;

Map mapMonde;
Map mapMenu;

Perso heros;

View vue;
View vue2; //minimap

PNJ PNJ_1;
PNJ PNJ_2;

PNJ PNJ_1_menu;
PNJ PNJ_2_menu;
#pragma endregion variables

#pragma region prototypes
void gestion_clavier();
void gestion_mouse();
void update(bool, sf::Clock);
void affichage_texte(char* texte, int x, int y);
void affichage_window();
#pragma endregion prototypes

int monMain()
{
	menu.create(sf::VideoMode(350, 600), "Menu");
	menu.setPosition(sf::Vector2i(100, 100));

	window.create(sf::VideoMode(800, 600), "BirdTown");
	window.setPosition(sf::Vector2i(500, 100));
	window.setFramerateLimit(60);

	
	sf::Clock clock;

	// Creation Map
	mapMonde.create("map.png");
	mapMenu.create("menu_birdtown.png");



	// Creation Heros
	heros.create("sprite.png", 32, 48, 1960, 720);
	
	//Creation d'un PNJ
	PNJ_1.create("PNJ_1", 1590, 1630, "sprite_foulard.png", "triste.png");
	PNJ_2.create("PNJ_2", 1890, 1950, "sprite_mousquetaire.png", "triste.png");

	PNJ_1_menu = PNJ_1.create_menu(PNJ_1, 0, 100);
	PNJ_2_menu = PNJ_2.create_menu(PNJ_2, 100, 100);

	while (window.isOpen() && menu.isOpen() )
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (event.type == sf::Event::KeyPressed) {
				updateFPS = true;
			}
			else {
				updateFPS = false;
			}
		}
		

		/* Gestion clavier*/
		gestion_clavier();

		/* Gestion souris*/
		gestion_mouse();

		update(updateFPS, clock);
		clock.restart();

		affichage_window();
	}

	return 0;
}

void gestion_clavier() {

	position_perso = heros.sprite_perso.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		anim.y = Up;
		heros.sprite_perso.move(0, -speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		anim.y = Down;
		heros.sprite_perso.move(0, speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		anim.y = Left;
		heros.sprite_perso.move(-speed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		anim.y = Right;
		heros.sprite_perso.move(speed, 0);
	}

	//On appuie sur I pour interroger un villageois
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		//Si on se trouve près du mousquetaire
		if (position_perso.x > 1860 && position_perso.x < 1990 && position_perso.y > 1915 && position_perso.y < 2045) {
			window.draw(PNJ_2.indice_PNJ);
		}
		else {
			affichage_texte("Il n'y a personne a interroger pres de moi...\n", position_perso.x, position_perso.y);

		}
	}

	//On appuie sur D pour le désigner comme coupable
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		//TODO
	}
}

void gestion_mouse() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		positionSouris = sf::Mouse::getPosition(window);
		//sprite_perso.setPosition(positionSouris.x, positionSouris.y);
	}
}

void affichage_texte(char* texte, int x, int y) {
	//Affichage du texte dans la console (test)
	printf(texte);

	//Affichage du texte à l'écran
	sf::Font MyFont;
	if (!MyFont.loadFromFile("calibri.ttf"))
	{
		printf("Probleme de chargement de police");
	}

	sf::Text text;
	text.setFont(MyFont);
	text.setString(texte);
	text.setCharacterSize(60);
	text.setColor(sf::Color::Black);
	text.setOrigin(0, 0);

	window.draw(text); //N'affiche pas
}

void update(bool updateFPS, sf::Clock clock) {
	sf::Time time = clock.getElapsedTime();
	if (updateFPS) {
		fpsCount += fpsSpeed * time.asSeconds();
	}
	else {
		fpsCount = 0;
	}

	if (fpsCount >= switchFps) {
		anim.x++;
		if (anim.x * heros.largeur_sprite_perso >= heros.perso.getSize().x) {
			anim.x = 1;
		}
		fpsCount = 0;
	}

	heros.sprite_perso.setTextureRect(sf::IntRect(anim.x * heros.largeur_sprite_perso, anim.y * heros.hauteur_sprite_perso, heros.largeur_sprite_perso, heros.hauteur_sprite_perso));

	// Gestion des collisions sur les bords
	heros.gestionCollisionBords();
	
	// Creation des vues
	vue.create(heros, 800, 600);
	vue2.create(heros, 1600, 1200);
	vue2.view.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

}

void affichage_window() {
	menu.clear();
	window.clear();
	window.setView(vue.view);
	window.draw(mapMonde.sprite_map);
	window.draw(heros.sprite_perso);

	//Dessin des PNJs sur la map
	window.draw(PNJ_1.sprite_PNJ);
	window.draw(PNJ_2.sprite_PNJ);

	menu.draw(mapMenu.sprite_map);
	menu.draw(PNJ_1_menu.sprite_PNJ);
	menu.draw(PNJ_2_menu.sprite_PNJ);

	//Ajout de la minimap
	window.setView(vue2.view);
	window.draw(mapMonde.sprite_map);
	window.draw(heros.sprite_perso);


	menu.display();
	window.display();
}

// Version corrigée

int factorielle(int const n)
{
	int fact = 1;
	for (int i = 2; i <= n; ++i) // Correction : "<=" au lieu de "<"
		fact *= i;
	return fact;
}

bool estUnCarreParfait(int const n)
{
	int i;
	for (i = 0; i*i < n; ++i); // Correction : "i = 0" au lieu de "i = 1"
	return (i*i == n);
}