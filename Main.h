#ifndef MAIN_H_
#define MAIN_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
using namespace std;

//-- Player Variables --//

sf::Texture playerTexture;
sf::Sprite Player;

//-- Environmental Textures --//
sf::Texture backGround;
sf::Sprite bgSprite;

sf::Texture towerTexture;
sf::Sprite towerMoving;

//-- Menu variables --//
sf::Texture idleBird;
sf::Sprite menuBird;

//-- Clocks --//
sf::Clock mainClock;
sf::Clock animationClock;
sf::Clock countDownClock; // Countdown when the game starts

//-- Get all the external resources, sprites and fonts --//
void loadResources()
{
	//-- Fonts --//


	//-- Textures --//
	if (!backGround.loadFromFile("backGround.jpg"))
	{}
	else
	{ cout << "Loaded the texture 'background'" << endl; }

	if (!towerTexture.loadFromFile("towerTexture.png"))
	{}
	else
	{ cout << "Loaded the texture 'Tower'" << endl; }


	//-- Spritesheets --//
	if (!playerTexture.loadFromFile("ravenFlying.png"))
	{}
	else
	{ cout << "Loaded the spritesheet for 'Raven Flying'" << endl; }

	//-- Menu --//
	if (!idleBird.loadFromFile("ravenSitting.png"))
	{}
	else
	{ cout << "Loaded the spritesheet for 'Raven Sitting'" << endl; }
}



#endif