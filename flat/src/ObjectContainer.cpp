#include "ObjectContainer.h"

using namespace flat2d;

ObjectContainer::~ObjectContainer()
{
	for (auto it = objects.begin(); it != objects.end(); it++) {
		delete it->second;
	}
	objects.clear();
}

void ObjectContainer::registerObject(GameObject* object)
{
	if (objects.find(object->getStringId()) != objects.end()) {
		return;
	}
	objects[object->getStringId()] = object;
}

void ObjectContainer::unregisterObject(GameObject* object)
{
	objects.erase(object->getStringId());
}

void ObjectContainer::preHandle()
{
	for (auto it = objects.begin(); it != objects.end(); it++) {
		it->second->preHandle();
	}
}

void ObjectContainer::handle(const SDL_Event& event)
{
	for (auto it = objects.begin(); it != objects.end(); it++) {
		it->second->handle(event);
	}
}

void ObjectContainer::postHandle()
{
	for (auto it = objects.begin(); it != objects.end(); it++) {
		it->second->postHandle();
	}
}

void ObjectContainer::preRender() 
{
	for (auto it = objects.begin(); it != objects.end(); it++) {
		it->second->preRender();
	}
}

void ObjectContainer::render(SDL_Renderer* renderer) const
{
	for (auto it = objects.begin(); it != objects.end(); it++) {
		it->second->render(renderer);
	}
}

void ObjectContainer::postRender() 
{
	for (auto it = objects.begin(); it != objects.end(); it++) {
		it->second->postRender();
	}
}

size_t ObjectContainer::getObjectCount() {
	return objects.size();
}
