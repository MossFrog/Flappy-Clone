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

sf::Texture treeTexture;
sf::Sprite treeSprite;
sf::Sprite treeSprite_2;
sf::Sprite treeSprite_3;
sf::Sprite treeSprite_4;

//-- Enemies --//


//-- Menu variables --//
sf::Texture idleBird;
sf::Sprite menuBird;
sf::Font mainFont;
sf::Text menuText;
sf::Text countDownText;

//-- Score Variables --//
sf::Text scoreText;
int currentScore;


//-- Game over Variables --//
sf::Text GameOverText;

//-- Clocks --//
sf::Clock mainClock;
sf::Clock animationClock;
sf::Clock countDownClock; // Countdown when the game starts
sf::Clock menuClock; // Clock for any menu animation effects

//-- Audio --//
sf::SoundBuffer flapBuffer;
sf::SoundBuffer cawBuffer;

sf::Music mainTheme;



//-- Get all the external resources, sprites and fonts --//
void loadResources()
{
	//-- Fonts --//
	if (!mainFont.loadFromFile("Pixel Emulator.ttf"))
	{}
	else
	{ cout << "Loaded the font 'Pixel Emulator'" << endl; }

	//-- Textures --//
	if (!backGround.loadFromFile("backGround.jpg"))
	{}
	else
	{ cout << "Loaded the texture 'background'" << endl; }

	if (!treeTexture.loadFromFile("treeTexture.png"))
	{}
	else
	{ cout << "Loaded the texture 'Tree'" << endl; }


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

	//-- Audio --//
	if (!flapBuffer.loadFromFile("Randomize3.wav"))
	{ }
	else
	{ cout << "Loaded the music file 'Randomize3.wav'" << endl; }

	if(!cawBuffer.loadFromFile("CrowCaw.ogg"))
	{ }
	else
	{ cout << "Loaded 'CrowCaw.ogg'" << endl; }

	if (!mainTheme.openFromFile("Blind Shift.ogg"))
	{}
	else
	{ cout << "Loaded the audio file 'Blind Shift.ogg'" << endl; }
}

float randomTreeX()
{
	float x = rand() % 500 + 100;
	return x;
}

float randomTreeY()
{
	float y = rand() % 125 + 175;
	return y;
}

void resetTree(sf::Sprite & tree)
{
	if(tree.getPosition().x < -100)
	{
		tree.setPosition(rand() % 200 + 720, randomTreeY());
	}
}

#endif