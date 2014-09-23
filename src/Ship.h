#ifndef _SHIP_H
#define _SHIP_H

#include <flat-2d/GameObject.h>

class Ship : public GameObject
{
	private:
		static const unsigned int WIDTH 	= 10;
		static const unsigned int HEIGHT 	= 10;

		int xpos, ypos;

	public:

		Ship(unsigned int x, unsigned int y) : xpos(x), ypos(y) { };

		void preHandle() { }; // Do nothing, override
		void handle(const SDL_Event& event) { } // Do nothing, override
		void postHandle();

		void preRender() { }; // Do nothing, override
		void render(SDL_Surface& surface) const;
		void postRender() { }; // Do nothing, override

		bool isCollider() const { return true; }
		SDL_Rect getBoundingBox() const;
};

#endif