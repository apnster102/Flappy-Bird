#ifndef GAMELOOP__H_
#define GAMELOOP__H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "BackGround.h"
#include "Player.h"


class GameLoop
{
private:
	const int SCREEN_WIDTH = 960;
	const int SCREEN_HEIGHT = 540;
	const char* WINDOW_TITLE = "This is a little box";
	bool GameState;
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* background;

	SDL_Event event1;

	Player gPlayer;

public:
	GameLoop();
	bool getGameState();
	void logSDLError(std::ostream& os, const std::string &msg, bool fatal);
	void InitSDL();
	void Event();
	void Update();
	void Render();
	void QuitSDL();
	~GameLoop();

};



#endif
