#include <SFML/Graphics.hpp>

int main()
{
	//--  Set the resolution to 9:16 preferred resolution for mobile phones --//
	sf::RenderWindow window(sf::VideoMode(405, 720), "Flappy Bird Clone", sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();


        window.display();
    }

    return 0;
}