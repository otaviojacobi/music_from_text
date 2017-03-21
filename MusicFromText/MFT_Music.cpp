#include "stdafx.h"
#include "MFT_Music.h"

/**
Constructor.
*/
Music::Music()
{
}

/**
Destructor.
*/
Music::~Music()
{
	for (auto& note : _notes)
		delete note;
}

/**
Remove all notes from the music.
*/
void Music::clear()
{
	for (auto& note : _notes)
		delete note;

	_notes.clear();
}

/**
Return whether or not the song has zero notes.
*/
bool Music::isEmpty() const
{
	return _notes.empty();
}

/**
Add the new note at the and of song.
*/
bool Music::addNoteToSongEnd(Note note)
{
	try
	{
		Note *new_note = new Note(note);
		_notes.push_back(new_note);
		return true;
	}
	catch (std::bad_alloc)
	{
		return false;
	}
}

/**
Return the string representation of the entire music on *Fugue format.
*/
std::string Music::toString()
{
	std::stringstream result;
	Note *prev = nullptr;

	for (auto &note : _notes)
	{
		if (prev == nullptr)
		{
			result << "X[VOLUME_COARSE]=" << note->getVolume().toInt() << " ";
			result << "T" << note->getBPM().toInt() << " ";
			result << "I" << note->getInstrument().toInt() << " ";
		}
		else
		{
			if (note->getVolume() != prev->getVolume())
				result << "X[VOLUME_COARSE]=" << note->getVolume().toInt() << " ";
			if (note->getBPM() != prev->getBPM())
				result << "T" << note->getBPM().toInt() << " ";
			if (note->getInstrument() != prev->getInstrument())
				result << "I" << note->getInstrument().toInt() << " ";
		}

		result << note->getKey().toChar() << note->getOctave().toInt() << " ";
		prev = note;
	}

	return result.str();
}

/**
Return the first note and delete it from the music.
*/
Note Music::takeNoteFromSongStart()
{
	Note *first = _notes.front();
	Note note = *first;
	_notes.pop_front();
	delete first;
	return note;
}
