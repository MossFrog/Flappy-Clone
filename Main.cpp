#include <SFML/Graphics.hpp>

int main()
{
	//--  Set the resolution to 9:16 preferred resolution for mobile phones --//
	//-- Disable keyrepeat events to make the game tap oriented --//
	//-- Limit the framerate to prevent screen tearing --//
	sf::RenderWindow window(sf::VideoMode(405, 720), "Flappy Bird Clone", sf::Style::Close);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::RectangleShape player;
	player.setSize(sf::Vector2f(100,50));
	player.setPosition(152,360);
	player.setFillColor(sf::Color::Red);

	int playerFallSpeed = 1;
	int gravity = 1;

	//-- initialize the main game clock --//
	sf::Clock mainClock;
	mainClock.restart();


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
				if (event.key.code == sf::Keyboard::A)
				{
					playerFallSpeed -= 30;
				}
			}
		}

		if(mainClock.getElapsedTime() >= sf::milliseconds(15))
		{
			playerFallSpeed += gravity;
			player.move(0,playerFallSpeed);
			mainClock.restart();
		}



		if(playerFallSpeed <= -30)
		{
			playerFallSpeed = -30;
		}


		//-- Any drawing methods after screen clear --//
		window.clear();

		window.draw(player);

		window.display();
	}

	return 0;
}