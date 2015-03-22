#ifndef _RENDERED_GAME_OBJECT_H
#define _RENDERED_GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "EntityProperties.h"

namespace flat2d
{
	class Camera;
	class RenderData;
	class GameData;

	class Entity
	{
		private:
			boost::uuids::uuid id;

		protected:
			EntityProperties entityProperties;
			bool dead = false, collidable = false;
			SDL_Texture *texture = nullptr;
			SDL_Rect clip;
			SDL_Rect collider;
			bool fixedPosition = false;

		public:
			Entity(int x, int y, int w, int h) : 
				entityProperties(x, y, w, h),
				dead(false) {

					/* Not providing ran creates valgrind warnings */
					static boost::mt19937 ran;
					id = boost::uuids::random_generator(ran)();

					clip = { x, y, w, h };
					collider = { 0, 0, 0, 0 };
				}

			virtual ~Entity() { };

			/* Operators */
			virtual bool operator==(const Entity& o) const {
				return id == o.id;
			};

			virtual bool operator!=(const Entity& o) const {
				return id != o.id;
			};

			virtual Entity& operator=(const Entity& o) {
				id = o.id;
				return *this;
			};

			virtual std::string getStringId() const {
				return boost::lexical_cast<std::string>(id);
			};

			virtual int getType() {
				return -1;
			};

			/* Own methods */
			void setClip(SDL_Rect&);
			void setDead(bool);
			void setCollidable(bool);
			void setColliderBox(SDL_Rect collider);
			bool isFixedPosition();
			void setFixedPosition(bool);

			/* Implemented override methods */
			virtual bool isDead() const;
			virtual void render(const RenderData*) const;
			virtual bool isCollider() const;
			virtual SDL_Rect getBoundingBox() const;
			virtual const SDL_Texture* getTexture() const;
			virtual void setTexture(SDL_Texture*);
			virtual EntityProperties& getEntityProperties();
			virtual const EntityProperties& getEntityProperties() const;

			/* Empty methods */
			virtual void init(const GameData*) { };
			virtual void preHandle(const GameData*) { };
			virtual void handle(const SDL_Event& event) { };
			virtual void postHandle(const GameData*) { };
			virtual void preRender(const GameData*) { };
			virtual void postRender(const GameData*) { };

	};
}

#endif