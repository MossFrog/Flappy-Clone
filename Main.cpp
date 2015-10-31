#include "Main.h"

int main()
{
	//--  Set the resolution to 9:16 preferred resolution for mobile phones --//
	//-- Disable keyrepeat events to make the game tap oriented --//
	//-- Limit the framerate to prevent screen tearing --//
	sf::RenderWindow window(sf::VideoMode(720, 405), "Flappy Bird Clone", sf::Style::Close);
	window.setFramerateLimit(100);
	window.setKeyRepeatEnabled(false);

	//-- Call the loadResources function --//
	loadResources();

	//-- Menu Variables --//
	menuText.setFont(mainFont);
	menuText.setString("Flappy Crow");
	menuText.setPosition(100,100);

	menuBird.setTexture(idleBird);
	menuBird.setPosition(400,200);
	menuBird.setScale(10,10);
	menuBird.setTextureRect(sf::IntRect(0,0,16,16));
	int menuBirdState = 0;
	//-- Starting Variables --//
	countDownText.setFont(mainFont);
	countDownText.setPosition(350,100);
	countDownText.setString("3");



	//-- Set the static sprites --//
	bgSprite.setTexture(backGround);
	bgSprite.setPosition(0,0);

	Player.setTexture(playerTexture);
	Player.setTextureRect(sf::IntRect(0,0,16,16));
	Player.setPosition(100,152);
	Player.setScale(3,3);


	//-- Game physics and Animation variables --//
	int playerState = 0;
	int playerFallSpeed = 1;
	int gravity = 1;

	//-- GameState variable, 0 == menu, 3 == starting, 1 == playing, 2 == game over --//
	int GameState = 0;
	int countDown = 0;

	//-- initialize the main game clock and animation clock --//
	mainClock.restart();
	animationClock.restart();
	menuClock.restart();




	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//-- If the specified key is pressed push the player upwards --//
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					playerFallSpeed = -15;
				}
			}
		}


		//-- Start the game if G key is pressed --//
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			if(GameState == 0)
			{
				GameState = 3;
				countDownClock.restart();

			}
		}

		if(GameState == 3)
		{
			if(countDownClock.getElapsedTime() >= sf::seconds(1))
			{
				countDown += 1;
				countDownClock.restart();
			}

			if(countDown == 1)
			{
				countDownText.setString("2");
			}

			else if(countDown == 2)
			{
				countDownText.setString("1");
			}

			else if(countDown == 3)
			{
				GameState = 1;
			}
		}

		if(GameState == 1)
		{

			if(mainClock.getElapsedTime() >= sf::milliseconds(15))
			{
				playerFallSpeed += gravity;
				Player.move(0,playerFallSpeed);
				mainClock.restart();
			}

			if(animationClock.getElapsedTime() >= sf::milliseconds(100))
			{
				playerState += 16;
				if(playerState > 48)
				{
					playerState = 0;
				}
				Player.setTextureRect(sf::IntRect(playerState,0,16,16));
				animationClock.restart();
			}

		}

		if(GameState == 0)
		{
			if(menuClock.getElapsedTime() >= sf::milliseconds(500))
			{
				menuBirdState += 16;
				if(menuBirdState > 48)
				{ menuBirdState = 0; }
				menuBird.setTextureRect(sf::IntRect(menuBirdState,0,16,16));
				menuClock.restart();
			}
		}

		//-- Limit the speeds on the x and y axis --//
		if(playerFallSpeed <= -25)
		{
			playerFallSpeed = -25;
		}

		if(playerFallSpeed >= 25)
		{
			playerFallSpeed = 25;
		}


		//-- Any drawing methods after screen clear --//
		window.clear(sf::Color::White);
		window.draw(bgSprite);

		//-- Menu Renders --//
		if(GameState == 0)
		{
			window.draw(menuText);
			window.draw(menuBird);
		}

		//-- Game renders --//
		if(GameState == 1)
		{
			window.draw(Player);
		}

		//-- Starting renders --//

		if(GameState == 3)
		{
			window.draw(countDownText);
		}

		

		window.display();
	}

	return 0;
}