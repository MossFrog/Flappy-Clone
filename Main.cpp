#include "Main.h"
#include "strutils.h"

int main()
{
	//-- Set the resolution to 16:9 preferred resolution for landscape mobile phones --//
	//-- Disable keyrepeat events to make the game tap oriented --//
	//-- Limit the framerate to prevent screen tearing (although this does cause dirty pixels) --//
	sf::RenderWindow window(sf::VideoMode(720, 405), "Flappy Bird Clone", sf::Style::Close);
	//window.setFramerateLimit(60);
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


	startText.setFont(mainFont);
	startText.setString("- Start -");
	startText.setPosition(100, 200);
	startText.setColor(sf::Color::White);

	

	//-- Starting Variables --//
	countDownText.setFont(mainFont);
	countDownText.setPosition(350,100);
	countDownText.setString("3");

	//-- Defining game over state --//
	GameOverText.setFont(mainFont);
	GameOverText.setString("Game Over");
	GameOverText.setPosition(250,100);

	//-- Restart button --//
	restartText.setPosition(230, 130);
	restartText.setString("- Restart -");
	restartText.setFont(mainFont);
	restartText.setColor(sf::Color::White);

	//-- Set the static sprites --//
	bgSprite.setTexture(backGround);
	bgSprite.setPosition(0,0);

	bgSprite2.setTexture(backGround);
	bgSprite2.setPosition(bgSprite.getGlobalBounds().width,0);

	bgSprite3.setTexture(backGround);
	bgSprite3.setPosition(bgSprite2.getGlobalBounds().width,0);

	Player.setTexture(playerTexture);
	Player.setTextureRect(sf::IntRect(0,0,16,16));
	Player.setOrigin(Player.getGlobalBounds().width/2,Player.getGlobalBounds().height/2);
	Player.setPosition(100,50);
	Player.setScale(3,3);

	sf::CircleShape myCircle;
	myCircle.setFillColor(sf::Color::Red);
	myCircle.setRadius(4);

	//-- Dynamic sprites (the Trees and the Grass) --//
	treeSprite.setTexture(treeTexture);
	treeSprite.setPosition(randomTreeX(),randomTreeY());
	treeSprite.setScale(6,6);

	treeSprite_2.setTexture(treeTexture);
	treeSprite_2.setPosition(randomTreeX(),randomTreeY());
	treeSprite_2.setScale(6,6);

	treeSprite_3.setTexture(treeTexture);
	treeSprite_3.setPosition(randomTreeX(),randomTreeY());
	treeSprite_3.setScale(6,6);

	treeSprite_3.setTexture(treeTexture);
	treeSprite_3.setPosition(randomTreeX(),randomTreeY());
	treeSprite_3.setScale(6,6);

	treeSprite_4.setTexture(treeTexture);
	treeSprite_4.setPosition(randomTreeX(),randomTreeY());
	treeSprite_4.setScale(6,6);

	//-- Initialize the Gold Coins --//
	goldAnimSeq = 0;

	coin_1.setTexture(goldSheet);
	coin_1.setTextureRect(sf::IntRect(goldAnimSeq, 0, 18, 20));
	coin_1.setPosition(1000, 100);
	coin_1.setScale(2, 2);

	coin_2.setTexture(goldSheet);
	coin_2.setTextureRect(sf::IntRect(goldAnimSeq, 0, 18, 20));
	coin_2.setPosition(1100, 100);
	coin_2.setScale(2, 2);

	coin_3.setTexture(goldSheet);
	coin_3.setTextureRect(sf::IntRect(goldAnimSeq, 0, 18, 20));
	coin_3.setPosition(1200, 100);
	coin_3.setScale(2, 2);

	//-- Initialize the Fireballs --//
	//-- The fireballs will all have random alternating segments from the original spritesheet, giving them an async effect --//

	int fireball_1Speed = 0;
	int fireball_2Speed = 0;
	int fireball_3Speed = 0;


	fireball_1.setTexture(fireSheet);
	fireball_1.setTextureRect(sf::IntRect(randomFireballSeq(), 0, 64, 64));
	fireball_1.setPosition(randomFireballX(), 450);
	fireball_1.setScale(-1, 1);
	fireball_1.setOrigin(32, 32);
	fireball_1.setRotation(90);
	

	fireball_2.setTexture(fireSheet);
	fireball_2.setTextureRect(sf::IntRect(randomFireballSeq(), 0, 64, 64));
	fireball_2.setPosition(randomFireballX(), 450);
	fireball_2.setScale(-1, 1);
	fireball_2.setOrigin(32, 32);
	fireball_2.setRotation(90);
	
	fireball_3.setTexture(fireSheet);
	fireball_3.setTextureRect(sf::IntRect(randomFireballSeq(), 0, 64, 64));
	fireball_3.setPosition(randomFireballX(), 450);
	fireball_3.setScale(-1, 1);
	fireball_3.setOrigin(32, 32);
	fireball_3.setRotation(90);

	grassTile.setTexture(grassTexture);
	int grassX;
	int grassY;

	//-- Score Variables --//
	currentScore = 0;
	scoreText.setFont(mainFont);
	scoreText.setString("SCORE: 0");
	scoreText.setPosition(500,10);
	scoreText.setCharacterSize(20);

	//-- Game physics and Animation variables --//
	int playerState = 0;
	int playerFallSpeed = 1;
	int gravity = 1;

	//-- GameState variable, 0 == menu, 3 == starting, 1 == playing, 2 == game over --//
	int GameState = 0;
	int countDown = 0;

	//-- Clock initialization --//
	mainClock.restart();
	animationClock.restart();
	menuClock.restart();
	bgClock.restart();
	fireballClock.restart();


	//-- Audio Variables --//
	sf::Sound flapSound;
	flapSound.setBuffer(flapBuffer);
	flapSound.setVolume(30);

	sf::Sound cawSound;
	cawSound.setBuffer(cawBuffer);
	cawSound.setVolume(75);

	sf::Sound coinSound;
	coinSound.setBuffer(coinSoundBuffer);
	coinSound.setVolume(75);

	mainTheme.setLoop(true);
	mainTheme.setVolume(100);
	mainTheme.play();

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
					if(GameState == 1)
					{ flapSound.play(); }
					Player.setRotation(-40);

				}

				//-- D is a reserved debugging key --//
				if (event.key.code == sf::Keyboard::D)
				{
					

				}
			}
		}

		//-- Get the Mouse position to check button relativity --//
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		//-- Uncomment to see live feed of the mouse position in the console window --//
		//cout << mousePos.x << " " << mousePos.y << endl;

		if (restartText.getGlobalBounds().contains(mousePos.x, mousePos.y) && GameState == 2)
		{
			restartText.setColor(sf::Color::Black);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				GameState = 3;
				countDownClock.restart();

				//-- If this method is called reset all variables to prepare a game restart --//
				playerState = 0;
				playerFallSpeed = 1;
				countDown = 0;
				countDownText.setString("3");
				Player.setPosition(100, 50);
				Player.setRotation(340);
				currentScore = 0;
				scoreText.setString("SCORE: 0");
			}
		}

		else
		{
			restartText.setColor(sf::Color::White);
		}

		if (startText.getGlobalBounds().contains(mousePos.x, mousePos.y) && GameState == 0)
		{
			startText.setColor(sf::Color::Black);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				GameState = 3;
				countDownClock.restart();
				
				//-- If this method is called reset all variables to prepare a game restart --//
				playerState = 0;
				playerFallSpeed = 1;
				countDown = 0;
				countDownText.setString("3");
				Player.setPosition(100, 50);
				Player.setRotation(340);
				currentScore = 0;
				scoreText.setString("SCORE: 0");
			}
		}

		else
		{
			startText.setColor(sf::Color::White);
		}

		

		//-- Start the game if G key is pressed --//
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			if(GameState == 0 || GameState == 2)
			{
				GameState = 3;
				countDownClock.restart();

				//-- If this method is called reset all variables to prepare a game restart --//
				playerState = 0;
				playerFallSpeed = 1;
				countDown = 0;
				countDownText.setString("3");
				Player.setPosition(100,50);
				Player.setRotation(340);
				currentScore = 0;
				scoreText.setString("SCORE: 0");
			}
		}

		//-- Countdown section --//
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
				
				//-- Make sure a fireball doesnt start the moment the countdown ends. --//
				fireballClock.restart();
			}
		}


		//-- Gameplay Section --//
		if(GameState == 1)
		{

			if(mainClock.getElapsedTime() >= sf::milliseconds(15))
			{
				playerFallSpeed += gravity;
				Player.move(0,playerFallSpeed);
				mainClock.restart();
				Player.rotate(2);

				myCircle.setPosition(Player.getPosition());

			}

			if(bgClock.getElapsedTime() >= sf::milliseconds(3))
			{
				treeSprite.move(-1,0);
				treeSprite_2.move(-1,0);
				treeSprite_3.move(-1,0);
				treeSprite_4.move(-1,0);

				//-- Random tree reset function calls --//
				resetTree(treeSprite);
				resetTree(treeSprite_2);
				resetTree(treeSprite_3);
				resetTree(treeSprite_4);

				//-- Shift and reset the coins --//
				coin_1.move(-1, 0);
				coin_2.move(-1, 0);
				coin_3.move(-1, 0);

				//-- Check if the coin is withing the gameplay bounds --//
				checkCoinPos(coin_1);
				checkCoinPos(coin_2);
				checkCoinPos(coin_3);

				//-- Do a simple box collision test for the coins --//
				if (Player.getGlobalBounds().intersects(coin_1.getGlobalBounds()))
				{
					randomGoldReset(coin_1);
					currentScore += 100;
					coinSound.play();
				}

				if (Player.getGlobalBounds().intersects(coin_2.getGlobalBounds()))
				{
					randomGoldReset(coin_2);
					currentScore += 100;
					coinSound.play();
				}

				if (Player.getGlobalBounds().intersects(coin_3.getGlobalBounds()))
				{
					randomGoldReset(coin_3);
					currentScore += 100;
					coinSound.play();
				}

				//-- Shift the three chained background textures --//
				bgSprite.move(-1,0);
				bgSprite2.move(-1,0);
				bgSprite3.move(-1,0);

				if(bgSprite.getPosition().x <= -720)
				{
					bgSprite.setPosition(720, 0);
				}

				if(bgSprite2.getPosition().x <= -720)
				{
					bgSprite2.setPosition(720, 0);
				}

				if(bgSprite3.getPosition().x <= -720)
				{
					bgSprite3.setPosition(720, 0);
				}

				bgClock.restart();

				//-- Shift the fireballs --//

				fireball_1.move(-1, 0);
				fireball_2.move(-1, 0);
				fireball_3.move(-1, 0);

				fireball_1.move(0, -fireball_1Speed);
				fireball_2.move(0, -fireball_2Speed);
				fireball_3.move(0, -fireball_3Speed);

				//-- Make sure the fireballs fall back to earth --//

				if (fireball_1.getPosition().y <= 20)
				{
					fireball_1Speed = -fireball_1Speed;
				}

				if (fireball_2.getPosition().y <= 35)
				{
					fireball_2Speed = -fireball_2Speed;
				}

				if (fireball_3.getPosition().y <= 75)
				{
					fireball_3Speed = -fireball_3Speed;
				}

				//-- Update the texture rectangles of the fireballs --//
				fireball_1.setTextureRect(sf::IntRect(randomFireballSeq(), 0, 64, 64));
				fireball_2.setTextureRect(sf::IntRect(randomFireballSeq(), 0, 64, 64));
				fireball_3.setTextureRect(sf::IntRect(randomFireballSeq(), 0, 64, 64));
			}

			//-- Check if the animation clock has reached its pre requisite --//
			if(animationClock.getElapsedTime() >= sf::milliseconds(100))
			{
				playerState += 16;
				if(playerState > 48)
				{
					playerState = 0;
				}
				Player.setTextureRect(sf::IntRect(playerState,0,16,16));

				//-- Update the coin animations --//

				goldAnimSeq += 18;
				if (goldAnimSeq >= 108)
				{
					goldAnimSeq = 0;
				}

				coin_1.setTextureRect(sf::IntRect(goldAnimSeq, 0, 18, 20));
				coin_2.setTextureRect(sf::IntRect(goldAnimSeq, 0, 18, 20));
				coin_3.setTextureRect(sf::IntRect(goldAnimSeq, 0, 18, 20));

				animationClock.restart();

				//-- We also determine the score to increment every 100ms so its convenient to use this clock --//
				currentScore += 1;
				scoreText.setString("SCORE: " + itoa(currentScore));
			}

			if (fireballClock.getElapsedTime() >= sf::milliseconds(3000))
			{
				fireball_1.setPosition(randomFireballX(), 450);
				fireball_2.setPosition(randomFireballX(), 450);
				fireball_3.setPosition(randomFireballX(), 450);

				fireball_1Speed = randomFireballSpeed();
				fireball_2Speed = randomFireballSpeed();
				fireball_3Speed = randomFireballSpeed();

				fireballClock.restart();
			}
		}

		//-- Update the menu bird animation --//
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

		


		//-- Kill the player if the bird falls out of bounds --//
		if(Player.getPosition().y >= 405)
		{
			if(GameState == 1)
			{ cawSound.play(); }
			GameState = 2;
		}


		//-- Any drawing methods after screen clear --//
		window.clear();

		//-- Render the Background --//
		window.draw(bgSprite);
		window.draw(bgSprite2);
		window.draw(bgSprite3);

		//-- Menu Renders --//
		if(GameState == 0)
		{
			window.draw(menuText);
			window.draw(menuBird);
			window.draw(startText);
		}

		//-- Game Renders --//
		if(GameState == 1)
		{
			window.draw(treeSprite);
			window.draw(treeSprite_2);
			window.draw(treeSprite_3);
			window.draw(treeSprite_4);

			window.draw(scoreText);

			window.draw(Player);

			//-- Debugging circle displays the player's origin co-ordinate --//
			//window.draw(myCircle);

			window.draw(coin_1);
			window.draw(coin_2);
			window.draw(coin_3);

			window.draw(fireball_1);
			window.draw(fireball_2);
			window.draw(fireball_3);

			
		}

		//-- Starting Renders --//

		if(GameState == 3)
		{
			window.draw(countDownText);
		}

		//-- Game over Renders --//
		if(GameState == 2)
		{
			window.draw(GameOverText);
			window.draw(restartText);
		}

		window.display();
	}

	return 0;
}



bool colCheck(sf::Sprite s1, sf::Sprite s2)
{
	if(s1.getPosition().x <= s2.getPosition().x + s2.getGlobalBounds().width)
	{
		if(s1.getPosition().x >= s2.getPosition().x)
		{
			if(s1.getPosition().y >= s2.getPosition().y + s2.getGlobalBounds().height)
			{
				if(s1.getPosition().y <= s2.getPosition().y)
				{
					return true;
				}
			}
		}
	}

	return false;
}