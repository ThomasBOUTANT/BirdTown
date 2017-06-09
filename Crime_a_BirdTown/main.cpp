#pragma region includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <cmath>

/* Fichiers appeles */
#include "PNJ.h"
#include "Map.h"
#include "Perso.h"
#include "View.h"

/* Pour le chargement de la map (format .tmx) */
#include <sfeMovie/Movie.hpp>
#include "tmxlite/Map.hpp"
#include "SFMLOrthogonalLayer.hpp"

#pragma endregion includes

using namespace std;

#pragma region variables
sf::RenderWindow window;
sf::RenderWindow menu;

sf::Music music;

//sfe::Movie movie;
tmx::Map macarte;

int speed = 20;
enum Dir { Down, Left, Right, Up };
sf::Vector2i anim(1, Down);
bool updateFPS = true;
float fpsCount = 0, switchFps = 50, fpsSpeed = 500;

sf::Vector2f position_perso(0, 0);
sf::Vector2i positionSouris;

Map mapMonde;
Map mapMenu; /* fenetre menu */

Perso heros;

View vue;
View vue2; /* minimap */

PNJ PNJ_1;
PNJ PNJ_2;

PNJ PNJ_1_menu;
PNJ PNJ_2_menu;

sf::Text text;
//bool textExisted = false;
#pragma endregion variables

#pragma region prototypes
void gestion_clavier();
void gestion_mouse();
void update(bool, sf::Clock);
//void affichage_texte(char* texte, int x, int y);
void nettoyage_window();
void affichage_window();
//void dialoguePNJ();
#pragma endregion prototypes


int main()
{
	//affichage_texte("ESSAI", position_perso.x - 30, position_perso.y + 30);
	menu.create(sf::VideoMode(350, 600), "Menu");
	menu.setPosition(sf::Vector2i(100, 100));

	window.create(sf::VideoMode(800, 600), "BirdTown");
	window.setPosition(sf::Vector2i(500, 100));
	window.setFramerateLimit(60);

	sf::Clock clock;

	/* Creation Maps */
	mapMonde.create("map.png"); // on s'en sert encore pour la minimap

	if (!macarte.load("./carte02.tmx")) {
		printf("ca marche pas!\n");
	}

	MapLayer layerZero(macarte, 0);
	MapLayer layerOne(macarte, 1);
	MapLayer layerTwo(macarte, 2);
	MapLayer layerThree(macarte, 3);
	MapLayer layerFour(macarte, 4);
	MapLayer layerFive(macarte, 5);

	mapMenu.create("menu_birdtown.png");

	/* Creation Heros */
	heros.create("perso.png", 32, 48, 1960, 720);

	/* Creation d'un PNJ -> pas encore de prise en compte du code de Marie */
	PNJ_1.create("PNJ_1", 1590, 1630, "sprite_foulard.png", "triste.png");
	PNJ_2.create("PNJ_2", 1890, 1950, "sprite_mousquetaire.png", "triste.png");
	PNJ_1_menu = PNJ_1.create_menu(PNJ_1, 0, 100);
	PNJ_2_menu = PNJ_2.create_menu(PNJ_2, 100, 100);

	/* Ouverture d'une musique */
	if (!music.openFromFile("chocobo.ogg")) {
		return -1; // erreur
	}
	music.play();
	music.setLoop(true);

	while (window.isOpen() && menu.isOpen() )
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				updateFPS = true;
			}
			else {
				updateFPS = false;
				//textExisted = false;
			}
		}
		
		/* Gestion clavier*/
		gestion_clavier();

		/* Gestion souris*/
		gestion_mouse();

		/* Update du jeu */
		update(updateFPS, clock);
		clock.restart();

		/* Affichage des differentes fenetres*/
		nettoyage_window();
		
		window.setView(vue.view);
		window.draw(layerZero); // j'ai mis ces draw ici, mais c'est moche... cependant ca marche mieux comme ca pour l'instant
		window.draw(layerOne);
		window.draw(layerTwo);
		window.draw(layerThree);
		window.draw(layerFour);
		window.draw(layerFive);
		
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

	//On appuie sur E pour interroger un villageois
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		//dialoguePNJ();
	}

	//On appuie sur G pour le désigner comme coupable (guilty)
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		//TODO
		std::cout << "GUILTY" << std::endl;
	}


	//On appuie sur M pour redemarrer la musique
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		music.stop();
		music.play();
		music.setLoop(true);
	}
	//On appuie sur P pour mettre en pause la musique
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		music.pause();
	}

	//On appuie sur L pour arreter la musique
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		music.stop();
	}
	//On appuie sur O pour continuer la musique
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
		music.play();
		music.setLoop(true);
	}

	//On appuie sur V pour commencer la video
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
		//if (!movie.openFromFile("video.mp4")) {
		//	printf("erreur!!");
		//}
	}

}

void gestion_mouse() { // ne sert a rien pour l'instant
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		positionSouris = sf::Mouse::getPosition(window);
		//sprite_perso.setPosition(positionSouris.x, positionSouris.y);
	}
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

void nettoyage_window() {
	menu.clear();
	window.clear();
}

void affichage_window() {

	/* Affichage de window */
	
	//window.draw(mapMonde.sprite_map);
	window.draw(heros.sprite_perso);

	//Dessin des PNJs sur la map
	window.draw(PNJ_1.sprite_PNJ);
	window.draw(PNJ_2.sprite_PNJ);

	//Ajout de la minimap
	window.setView(vue2.view);
	window.draw(mapMonde.sprite_map);
	window.draw(heros.sprite_perso);

	window.draw(text);

	window.display();

	/* Affichage de menu */
	menu.draw(mapMenu.sprite_map);
	menu.draw(PNJ_1_menu.sprite_PNJ);
	menu.draw(PNJ_2_menu.sprite_PNJ);

	menu.display();	
}

/*
void dialoguePNJ() {


	//Si on se trouve près du mousquetaire
	if ((position_perso.x >= PNJ_1.x - heros.largeur_sprite_perso) && (position_perso.x <= PNJ_1.x + heros.largeur_sprite_perso) && position_perso.y >= (PNJ_1.y - heros.hauteur_sprite_perso) && (position_perso.y <= PNJ_1.y + heros.hauteur_sprite_perso)) {
		affichage_texte("Bonjour PNJ1", position_perso.x - 30, position_perso.y + 30);
		std::cout << "BONJOUR PNJ1" << std::endl;
		//window.draw(PNJ_2.indice_PNJ);
	}
	//Si on se trouve près du mousquetaire
	if ((position_perso.x >= PNJ_2.x - heros.largeur_sprite_perso) && (position_perso.x <= PNJ_2.x + heros.largeur_sprite_perso) && position_perso.y >= (PNJ_2.y - heros.hauteur_sprite_perso) && (position_perso.y <= PNJ_2.y + heros.hauteur_sprite_perso)) {
		affichage_texte("Coucou PNJ2", position_perso.x, position_perso.y);
		std::cout << "COUCOU PNJ2" << std::endl;
		//window.draw(PNJ_2.indice_PNJ);
	}
	else {
		affichage_texte("personne a interroger", position_perso.x, position_perso.y);
	}
}
*/

/*
void affichage_texte(sf::String texte, int x, int y) {
//Affichage du texte à l'écran
sf::Font myFont;
if (!myFont.loadFromFile("calibri.ttf"))
{
printf("Probleme de chargement de police");
}
else {
printf("ok, ca marche !");
}

text.setFont(myFont);
text.setString(texte);
text.setCharacterSize(20);
text.setColor(sf::Color::Blue);
//text.setOrigin(0, 0);
text.setPosition(x, y);

}
*/
