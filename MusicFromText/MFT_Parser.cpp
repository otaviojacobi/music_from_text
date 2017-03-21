#include "stdafx.h"
#include "MFT_Parser.h"

/**
Constructor.
*/
Parser::Parser()
{
}

/**
Destructor.
*/
Parser::~Parser()
{
}

/**
Create a music from the string set.
*/
Music *Parser::musicFromText(int new_volume, int new_bpm, int new_octave, int new_instrument)
{
	resetCurPos();

	_cur_octave.setOctave(new_octave);
	_cur_volume.setVolume(new_volume);
	_cur_instrument.setInstrument(new_instrument);
	_cur_bpm.setBPM(new_bpm);

	Music *music = new Music();
	char curChar;
	bool alloc_ok = true;
	while (getCurPos() != _text.length() && alloc_ok)
	{
		curChar = getCurChar();

		if (noteChars.count(curChar) != 0)
		{
			Note note = parseNote(curChar);

			alloc_ok = music->addNoteToSongEnd(note);
		}
		else if (silenceChars.count(curChar) != 0)
		{
			Note note;
			note.setMute();

			alloc_ok = music->addNoteToSongEnd(note);
		}
		else if (increaseVolume10Chars.count(curChar) != 0)
		{
			_cur_volume.increase10PercentVolume();
		}
		else if (doubleVolumeChars.count(curChar) != 0)
		{
			_cur_volume.setDoubleVolume();
		}
		else if (halveVolumeChars.count(curChar) != 0)
		{
			_cur_volume.setHalfVolume();
		}
		else if (increaseOctaveChars.count(curChar) != 0)
		{
			_cur_octave.incrementOctave();
		}
		else if (decreaseOctaveChars.count(curChar) != 0)
		{
			_cur_octave.decrementOctave();
		}
		else if (defaultOctaveChars.count(curChar) != 0)
		{
			_cur_octave.setDefaultOctave();
		}
	 	else if (changeInstrumentChars.count(curChar) != 0)
		{
			int instrument = curChar - '0'; // convert '1' -> 1, etc.
			_cur_instrument.setInstrument(instrument);
		}
		else if (changeInstrumentGen7Chars.count(curChar) != 0)
		{
			_cur_instrument.setInstrument(7);
		}
		else if (changeInstrumentCurrentPlusThisChars.count(curChar) != 0)
		{
			int cur_instrument = _cur_instrument.toInt();
			int increment = curChar - '0'; // convert '1' -> 1, etc.
			_cur_instrument.setInstrument(cur_instrument + increment);
		}
		else if (changeInstrumentGen15Chars.count(curChar) != 0)
		{
			_cur_instrument.setInstrument(15);
		}
		else if (changeInstrumentGen76Chars.count(curChar) != 0)
		{
			_cur_instrument.setInstrument(76);
		}
		else if (changeInstrumentGen20Chars.count(curChar) != 0)
		{
			_cur_instrument.setInstrument(20);
		}
		else if (increaseBPMChars.count(curChar) != 0)
		{
			_cur_bpm.incrementBPM();
		}
		else if (decreaseBPMChars.count(curChar) != 0)
		{
			_cur_bpm.decrementBPM();
		}
		else
		{
			Note note;
			if (noteChars.count(getPrevChar()) != 0)
				note = parseNote(getPrevChar());
			else
				note.setMute();

			alloc_ok = music->addNoteToSongEnd(note);
		}

		if (!alloc_ok)
			; // TODO: warn about the song being truncated

		incrementCurPos();
	}

	return music;			
}

/**
Set the string to create the music from.
*/
void Parser::setMusicString(const std::string &text)
{
	_text = text;
}

/**
Create a note from a note char.
*/
Note Parser::parseNote(char key)
{
	Key newKey;
	int newKeyValue = charToKeyInt(key);
	newKey.setKey(newKeyValue);
	_cur_key = newKey;

	Note note;
	note.setOctave(_cur_octave);
	note.setVolume(_cur_volume);
	note.setInstrument(_cur_instrument);
	note.setKey(newKey);
	note.setBPM(_cur_bpm);

	return note;
}

/**
Return the current seek position in the text.
*/
int Parser::getCurPos()
{
	return _cur_pos;
}

/**
Return the current char in the text.
*/
char Parser::getCurChar()
{
	return _text[getCurPos()];
}

/**
Return the previous char in the text.
*/
char Parser::getPrevChar()
{
	if (getCurPos() == 0)
		return '\0';

	return _text[getCurPos() - 1];
}

/**
Increment the current seek position.
*/
void Parser::incrementCurPos()
{
	_cur_pos += 1;
}

/**
Set the current seek position to 0.
*/
void Parser::resetCurPos()
{
	_cur_pos = 0;
}

/**
Parse a key from a note char.
*/
int Parser::charToKeyInt(char key)
{
	if (noteLaChars.count(key) != 0)
		return Key::Keys::LA;
	else if (noteSiChars.count(key) != 0)
		return Key::Keys::SI;
	else if (noteDoChars.count(key) != 0)
		return Key::Keys::DO;
	else if (noteReChars.count(key) != 0)
		return Key::Keys::RE;
	else if (noteMiChars.count(key) != 0)
		return Key::Keys::MI;
	else if (noteFaChars.count(key) != 0)
		return Key::Keys::FA;
	else
		return Key::Keys::SOL;
}
