#pragma once

#include "MFT_Music.h"
#include "CFugueLib.h"

class Player
{
public:
	Player();
	~Player();
	void start();
	void pause();
	void resume();
	void stop();
	void playMusic();
	void playNote();
	void setMusic(Music *music);
	bool isPaused() const;
	bool canPlay() const;
	bool shouldPlay() const;

private:
	CFugue::Player _player;
	Music *_music;
	int _curNoteNumber;
	bool _is_paused = false;
	bool _should_play = false;
	bool _is_busy; // false while playing a note; true otherwise
};