#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>


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
