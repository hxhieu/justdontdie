#ifndef _RENDER_DATA_H
#define _RENDER_DATA_H

#include <SDL2/SDL.h>

namespace flat2d
{
	class Camera;
	class EntityContainer;
	class CollisionDetector;

	class RenderData
	{
		private:
			SDL_Renderer *renderer;
			Camera *camera;
			void *customData = nullptr;

		public:
			RenderData(SDL_Renderer *ren, Camera *cam) : 
				renderer(ren),
				camera(cam) { };

			SDL_Renderer* getRenderer() const { return renderer; };
			Camera* getCamera() const { return camera; };
			void* getCustomData() { return customData; };
	};
}

#endif
