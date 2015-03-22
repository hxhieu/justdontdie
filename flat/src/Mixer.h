#ifndef MIXER_H_
#define MIXER_H_

#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

namespace flat2d
{
	class Mixer
	{
		private:
			std::map<int, Mix_Chunk*> effects;
			std::map<int, Mix_Music*> music;

		public:
			~Mixer() {
				for (auto it = effects.begin(); it != effects.end(); it++) {
					Mix_FreeChunk(it->second);
				}
				for (auto it = music.begin(); it != music.end(); it++) {
					Mix_FreeMusic(it->second);
				}
			}

			bool loadEffect(int, std::string);

			void playEffect(int effect);

			bool loadMusic(int, std::string);

			void playMusic(int music);

			bool playingMusic();

			void pauseMusic();

			bool pausedMusic();

			void unpauseMusic();

			void stopMusic();
	};
} // namespace flat2d

#endif // MIXER_H_
