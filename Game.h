#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <memory>


class Game
{

public:
	static sf::RenderWindow _mainWindow;
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	enum GameState {
		Uninitialized, Playing, Exiting
	};

	static GameState _gameState;
};
