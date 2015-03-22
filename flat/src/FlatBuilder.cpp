#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "FlatBuilder.h"
#include "GameData.h"
#include "RenderData.h"
#include "EntityContainer.h"
#include "CollisionDetector.h"
#include "Camera.h"
#include "Window.h"
#include "Mixer.h"
#include "DeltatimeMonitor.h"
#include "GameControllerContainer.h"

using namespace flat2d;

FlatBuilder::~FlatBuilder()
{
	delete renderData;
	delete gameData;
	delete collisionDetector;
	delete entityContainer;
	delete window;
	delete camera;
	delete mixer;
	delete deltatimeMonitor;
	delete controllerContainer;

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
}

bool FlatBuilder::initSDL(std::string title, int screenWidth, int screenHeight)
{
	if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER ) < 0) {
		std::cerr << "Failed to init video: " << SDL_GetError() << std::endl;
		return false;
	}

	if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
		std::cerr << "Warning: Linear texture filtering not enabled" << std::endl;
	}

	window = new Window(title, screenWidth, screenHeight);
	if (!window->init()) {
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init( imgFlags ) & imgFlags )) {
		std::cerr << "Unable to initialize SDL_image: " << IMG_GetError() << std::endl;
		return false;
	}

	/*
	if (TTF_Init() == -1) {
		std::cerr << "Unable to initiate SDL2_ttf: " << TTF_GetError() << std::endl;
		return false;
	}
	*/

	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
		std::cerr << "Could not initialize SDL_Mixer: " << Mix_GetError() << std::endl;
		return false;
	}

	camera = new Camera(screenWidth, screenHeight);
	return true;
}

bool FlatBuilder::initContainers()
{
	entityContainer = new EntityContainer();
	collisionDetector = new CollisionDetector(entityContainer);
	renderData = new RenderData(window->getRenderer(), camera);
	mixer = new Mixer();
	deltatimeMonitor = new DeltatimeMonitor();
	controllerContainer = new GameControllerContainer();
	gameData = new GameData(entityContainer, collisionDetector, mixer, renderData, deltatimeMonitor);

	return true;
}

GameData* FlatBuilder::getGameData() const
{
	return gameData;
}
