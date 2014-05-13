#ifndef RUN_HPP
#define RUN_HPP

#include "Game.hpp"

const float FRAMERATE = 1;
const float FPS = 1000 / FRAMERATE;

int Run(Game& game, sf::RenderWindow& window)
{
	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();

	while(game.isRunning())
	{
		sf::Event event;
		while(window.pollEvent(event)){
			game.handleEvents(event);
		}

		game.update(time.asMilliseconds());

		window.clear(sf::Color::Black);
		game.render();
		window.display();

		time = clock.getElapsedTime();
	
		printf("%d\n", time.asMilliseconds());
		if(time.asMilliseconds() < FPS){
			printf("sleeping");
			sf::sleep(sf::milliseconds(FPS - time.asMilliseconds()));
		}
	
		clock.restart();
	}

	return 0;
}

#endif
