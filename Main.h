#ifndef MAIN_H_
#define MAIN_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "randgen.h"

using namespace std;

//-- Player Variables --//

sf::Texture playerTexture;
sf::Sprite Player;

//-- Environmental Textures --//
sf::Texture backGround;

sf::Sprite bgSprite;
sf::Sprite bgSprite2;
sf::Sprite bgSprite3;

sf::Texture grassTexture;
sf::Sprite grassTile;

sf::Texture treeTexture;
sf::Sprite treeSprite;
sf::Sprite treeSprite_2;
sf::Sprite treeSprite_3;
sf::Sprite treeSprite_4;

//-- Gold Pieces --//
sf::Texture goldSheet;

sf::Sprite coin_1;
sf::Sprite coin_2;
sf::Sprite coin_3;

int goldAnimSeq;


//-- Enemies --//
sf::Texture fireSheet;

sf::Sprite fireball_1;
sf::Sprite fireball_2;
sf::Sprite fireball_3;

int fireRand1 = 0;
int fireRand2 = 0;
int fireRand3 = 0;

//-- Menu variables --//
sf::Texture idleBird;
sf::Sprite menuBird;
sf::Font mainFont;
sf::Text menuText;
sf::Text countDownText;
sf::Text startText;


//-- Score Variables --//
sf::Text scoreText;
int currentScore;


//-- Game over Variables --//
sf::Text GameOverText;
sf::Text restartText;

//-- Clocks --//
sf::Clock mainClock;
sf::Clock animationClock;
sf::Clock countDownClock; // Countdown when the game starts
sf::Clock menuClock; // Clock for any menu animation effects
sf::Clock bgClock; // Clock for background parallax effects
sf::Clock fireballClock;

//-- Audio --//
sf::SoundBuffer flapBuffer;
sf::SoundBuffer cawBuffer;
sf::SoundBuffer coinSoundBuffer;

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
	{
		cout << "Loaded the texture 'Background'" << endl;
	}

	if (!treeTexture.loadFromFile("treeTexture.png"))
	{
	}
	else
	{
		cout << "Loaded the texture 'Tree'" << endl;
	}

	if (!grassTexture.loadFromFile("grassTexture.png"))
	{
	}
	else
	{
		cout << "Loaded the texture 'Grass'" << endl;
	}


	//-- Spritesheets --//
	if (!playerTexture.loadFromFile("ravenFlying.png"))
	{
	}
	else
	{
		cout << "Loaded the spritesheet for 'Raven Flying'" << endl;
	}

	if (!goldSheet.loadFromFile("Gold.png"))
	{
	}
	else
	{
		cout << "Loaded the spritesheet for 'gold coin'" << endl;
	}

	if (!fireSheet.loadFromFile("fireball.png"))
	{
	}
	else
	{
		cout << "Loaded the spritesheet for 'fireball'" << endl;
	}

	//-- Menu --//
	if (!idleBird.loadFromFile("ravenSitting.png"))
	{
	}
	else
	{
		cout << "Loaded the spritesheet for 'Raven Sitting'" << endl;
	}

	//-- Audio --//
	if (!flapBuffer.loadFromFile("Randomize3.wav"))
	{
	}
	else
	{
		cout << "Loaded the audio file 'Randomize3.wav'" << endl;
	}

	if (!cawBuffer.loadFromFile("CrowCaw.ogg"))
	{
	}
	else
	{
		cout << "Loaded the audio file 'CrowCaw.ogg'" << endl;
	}

	if (!coinSoundBuffer.loadFromFile("Score.ogg"))
	{
	}
	else
	{
		cout << "Loaded the audio file 'Score.ogg'" << endl;
	}

	if (!mainTheme.openFromFile("Blind Shift.ogg"))
	{
	}
	else
	{
		cout << "Loaded the audio file 'Blind Shift.ogg'" << endl;
	}


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
	if (tree.getPosition().x < -100)
	{
		tree.setPosition(rand() % 200 + 720, randomTreeY());
	}
}

float randomRotation90()
{
	float z = rand() % 360;

	if (z < 90)
	{
		z = 0;
	}

	else if (z >= 90 && z < 180)
	{
		z = 90;
	}

	else if (z >= 180 && z < 270)
	{
		z = 180;
	}

	else if (z >= 270)
	{
		z = 270;
	}

	return z;
}

void randomGoldReset(sf::Sprite & goldSprite)
{
	RandGen newRand;
	int randX = newRand.RandInt(50, 250);
	int randY = newRand.RandInt(0, 250);

	goldSprite.setPosition(randX + 1000, randY);
}

void checkCoinPos(sf::Sprite & goldSprite)
{
	if (goldSprite.getPosition().x <= -15)
	{
		randomGoldReset(goldSprite);
	}
}

//-- Returns a Random Segment from the Fireball Spritesheet --//
int randomFireballSeq()
{
	RandGen newGen;
	int sequence = newGen.RandInt(0, 3);

	sequence = sequence * fireSheet.getSize().x / 4;
	return sequence;
}

int randomFireballY()
{
	RandGen newGen;
	int posY = newGen.RandInt(50, 350);

	return posY;
}

int randomFireballX()
{
	RandGen newGen;
	int posX = newGen.RandInt(1350, 1650);

	return posX;
}

#endif