#pragma once

#include <list>
#include <string>
#include <sstream>
#include "MFT_Note.h"

class Music
{
public:
	Music();
	~Music();
	void clear();
	bool isEmpty() const;
	bool addNoteToSongEnd(Note note);
	std::string toString();
	Note takeNoteFromSongStart();
	
private:
	std::list<Note *> _notes;
};