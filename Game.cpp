#include "Game.h"
#include "CollisionManager.h"
#include <math.h>
#define METER 128;
#define SCREENWIDTH 1024
#define SCREENHEIGHT 768
using namespace sf;
using namespace std;
Clock deltaClock = Clock();
float delta = 0;
bool justStarted = false;
Game::GameState Game::_gameState = Uninitialized;
bool Debug = false;
sf::RenderWindow Game::_mainWindow;
Font *FPSFont = new Font();

void Initialize() {
	Game::_mainWindow.setVerticalSyncEnabled(true);
	//Throw in object declarations and stuff here
	cout << "Physics game! -- Coded by Eric Pfister.\n___________________________________________________";
	//ALL DEBUGGING CODE AHAHAHAHAHAH!
	Texture Ball = Texture();
	Ball.loadFromFile("Ball.png");
	Object::CreateNewObject(Ball, Vector2f(40, 400),Circular);
	Object::CreateNewObject(Ball, Vector2f(305,400),Circular);
    Object::CreateNewObject(Ball, Vector2f(100,325),Circular);
    Object::CreateNewObject(Ball, Vector2f(400,250),Circular);
    Object::CreateNewObject(Ball, Vector2f(500,175),Circular);
	//END OF DEBUGGING CODE! AHAHAHAHA-oh.
	if (!FPSFont->loadFromFile("Font.ttf")) {
		throw io_errc::stream;
	}
	deltaClock.restart();


}
void Object::PhysicsUpdate() {
    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        /*Vector2i mousePos = Mouse::getPosition(Game::_mainWindow);
        Object::ActiveObjects[0].position = Vector2f(mousePos.x - 32,mousePos.y - 32);*/
		for (int i = 0; i < 10; i++) {
			if (Object::ActiveObjects[i].getID() != -1)
				Object::ActiveObjects[i].velocity = Vector2f(i + 2, i + 4);;
		}
	
    }
	if (justStarted) {
		CollisionManager::resolveObjectCollisions();
		CollisionManager::resolveWallCollisions();
	}
    for (int i=0; i < 10; i++) {
		if (i != -1) {
			Object* ActiveObject = &Object::ActiveObjects[i];
			ActiveObject->position += ActiveObject->velocity;
			ActiveObject->velocity += ActiveObject->acceleration;
			ActiveObject->acceleration = Vector2f(0, 0);
			
			//ActiveObject->velocity = Vector2f(0.9 * ActiveObject->velocity.x, 0.9 * ActiveObject->velocity.y);
		}
    }

    
	//cout << Object::ActiveObjects[0].hitbox->intersects(Object::ActiveObjects[1].hitbox).first;
	justStarted = true;
}
void Update() {
	//Put Update per frame code related to game here
	Object::PhysicsUpdate();
	for (int index = 0; index < 10; index++) {
		Object * UpdateObject = &Object::ActiveObjects[index];
		if (UpdateObject->getID() != -1) {
			UpdateObject->O_Sprite.setPosition(Vector2f(UpdateObject->position.x,UpdateObject->position.y));
            UpdateObject->hitbox->position = Vector2f(UpdateObject->position.x,UpdateObject->position.y);
		}
	}
	delta = deltaClock.getElapsedTime().asSeconds();
	deltaClock.restart();
}

void Draw() {
	//Put drawing code in here
	
	Game::_mainWindow.clear(Color(255, 255, 255));
	Text FPS = Text("FPS = " + to_string((Uint8)(1 / delta)), *FPSFont, 30U);
	FPS.setPosition(0, 0);
	FPS.setColor(Color::Red);
	Game::_mainWindow.draw(FPS);
	for (int index = 0; index < 10; index++) {
		if (Object::ActiveObjects[index].getID() != -1) {
			Game::_mainWindow.draw(Object::ActiveObjects[index].O_Sprite);
			
		}
	}
	//cout << endl << test.x << ", " << test.y;
	Game::_mainWindow.display();


}

void Game::Start(void)
{
	if (_gameState != Uninitialized) return;

	_mainWindow.create(VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "Physics!");
	_gameState = Game::Playing;
	Initialize();
	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}
void Game::GameLoop()
{
	Event a;
	while (Game::_mainWindow.pollEvent(a)) {
		if (a.type == Event::Closed) {
			Game::_gameState = Game::GameState::Exiting;
		}
		else {
			if (a.type == Event::KeyReleased && a.key.code == Keyboard::F1) {
				Debug = !Debug;
			}
		}
	}
	Update();
	Draw();
}