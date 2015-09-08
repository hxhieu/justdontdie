#include <string>

#include "MapTileObject.h"
#include "Rocket.h"
#include "CustomGameData.h"
#include "LayerService.h"

void MapTileObject::setProperty(std::string prop, bool value)
{
	properties[prop] = value;
}

bool MapTileObject::hasProperty(std::string prop) const
{
	auto pair = properties.find(prop);
	if (pair == properties.end()) {
		return false;
	}
	return pair->second;
}

void MapTileObject::preMove(const flat2d::GameData *gameData)
{
	if (hasProperty("rocketLauncher") && (!launchTimer.isStarted() || launchTimer.getTicks() > 2000)) {
		launchTimer.start();

		Rocket::Mode mode = Rocket::Mode::NORMAL;
		if (hasProperty("ghost")) {
			mode = Rocket::Mode::GHOST;
		} else if (hasProperty("multi")) {
			mode = Rocket::Mode::MULTI;
		}

		LayerService *layerService = static_cast<CustomGameData*>(gameData->getCustomGameData())->getLayerService();

		Rocket *rocket = new Rocket(entityProperties.getXpos(), entityProperties.getYpos(), mode, !hasProperty("shootRight"));
		rocket->init(gameData);
		gameData->getEntityContainer()->registerObject(rocket, layerService->getLayerIndex(FRONT_LAYER));
	}
}

void MapTileObject::render(const flat2d::RenderData *data) const
{
	Entity::render(data);
#ifdef DEBUG
	if (texture == nullptr && !dead) {
		SDL_SetRenderDrawColor(data->getRenderer(), 0x00, 0x00, 0xFF, 0xFF );
		SDL_Rect boundingBox = entityProperties.getBoundingBox();
		boundingBox.x = data->getCamera()->getScreenXposFor(boundingBox.x);
		boundingBox.y = data->getCamera()->getScreenYposFor(boundingBox.y);
		SDL_RenderDrawRect( data->getRenderer(), &boundingBox);
	}
#endif
}
