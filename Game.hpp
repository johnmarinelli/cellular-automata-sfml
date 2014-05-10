#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"

class Game
{
private:
	sf::RenderWindow* mRenderTarget;
	CA::World mWorld;
	bool mIsRunning;

public:
	Game(sf::RenderWindow& window);

	void init();

	void handleEvents(sf::Event event);
	void update(float dTime);
	void render();

	bool isRunning() const;

	~Game();
};

#endif
