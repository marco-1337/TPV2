// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <string>
#include <SDL_mixer.h>

class Music {
public:

	// cannot copy objects of this type!
	Music& operator=(Music &other) = delete;
	Music(const Music&) = delete;

	Music(const std::string &fileName) {
		_music = Mix_LoadMUS(fileName.c_str());
		assert(_music != nullptr);
	}

	Music(Music &&other) noexcept {
		_music = other._music;
		other._music = nullptr;
	}

	Music& operator=(Music &&other) noexcept {
		this->~Music();
		_music = other._music;
		other._music = nullptr;
		return *this;
	}

	virtual ~Music() {
		if (_music != nullptr)
			Mix_FreeMusic(_music);
	}

	inline void play(int loops = -1) const {
		assert(loops >= -1 && _music != nullptr);
		Mix_PlayMusic(_music, loops);
	}

	inline static int setMusicVolume(int volume) {
		assert(volume >= 0 && volume <= 128);
		return Mix_VolumeMusic(volume);
	}

	inline static void haltMusic() {
		Mix_HaltMusic();
	}

	inline static void pauseMusic() {
		Mix_PauseMusic();
	}

	inline static void resumeMusic() {
		Mix_ResumeMusic();
	}


private:
	Mix_Music *_music;
};

