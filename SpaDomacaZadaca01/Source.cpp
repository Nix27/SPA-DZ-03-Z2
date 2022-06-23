#include <SFML/Graphics.hpp>
#include "PronadiPut.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 600), "Find a way");
	window.setFramerateLimit(60);

	PronadiPut p(&window);
	p.KreirajMapu();
	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		p.iscrtaj();
		window.display();
	}

	return 0;
}