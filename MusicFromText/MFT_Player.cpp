#include "stdafx.h"
#include "MFT_Player.h"

/**
Constructor.
*/
Player::Player()
{
}

/**
Destructor.
*/
Player::~Player()
{
	delete _music;
}

/**
Start playing music.
*/
void Player::start()
{
	_should_play = true;
}

/**
Pause music reproduction.
Resuming keeps playing where it stopped.
*/
void Player::pause()
{
	if (_is_paused)
		return;

	_should_play = false;

	if (_player.IsPlaying())
	{
		_is_paused = true;
		_player.PausePlay();
	}
}

/**
Resume playing from where it left off.
*/
void Player::resume()
{
	_is_paused = false;

	_player.ResumePlay();
	_player.WaitTillDone();

	if (!_is_paused)
		stop();
}

/**
Stop music reproduction.
Resuming plays from the beginning.
*/
void Player::stop()
{
	_should_play = false;
	_is_paused = false;

	if (_player.IsPlaying())
		_player.StopPlay();
}

/**
Play the entire music at once.
*/
void Player::playMusic()
{
	if (_music->isEmpty())
		return;

	_player.PlayAsync(CFugue::MString(_music->toString().c_str()));
	_player.WaitTillDone();

	if (!_is_paused)
		stop();
}

/**
Play the first note from the song, removing it in the process.
*/
void Player::playNote()
{
	if (!canPlay())
		return;

	_is_busy = true;
		
	Note note = _music->takeNoteFromSongStart();
	_player.PlayAsync(CFugue::MString(note.toString().c_str()));

	_is_busy = false;
}

/**
Set the music for the player.
*/
void Player::setMusic(Music *music)
{
	_music = music;
}

/**
True if the Player's state is set to 'paused'.
False otherwise.
*/
bool Player::isPaused() const
{
	return _is_paused;
}

/**
True if the Player can play a note right now.
False if it's busy already playing a note or if there are no notes to play.
*/
bool Player::canPlay() const
{
	return !(_is_busy || _music->isEmpty());
}

/**
True if the Player should be called to Play or Resume the music.
False otherwise.
*/
bool Player::shouldPlay() const
{
	return _should_play;
}