#include "Game.hpp"

Game::Game(sf::RenderWindow& window) : mRenderTarget(&window), mWorld(window)
{
}

void Game::init(char* input[])
{
	mIsRunning = true;
	mWorld.init(input);
}

void Game::handleEvents(sf::Event event)
{
}

void Game::update(float dTime)
{
	mWorld.update(dTime);
}

void Game::render()
{
	mWorld.render();
}

bool Game::isRunning() const
{
	return mIsRunning;
}

Game::~Game()
{
}
