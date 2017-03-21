#pragma once

#include <unordered_set>
#include "MFT_Music.h"
#include "MFT_Note.h"

class Parser
{
public:
	Parser();
	~Parser();
	Music* musicFromText(int new_volume, int new_bpm, int new_octave, int new_instrument);
	void setMusicString(const std::string& text);

protected:
	std::unordered_set<char> noteChars{ 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	std::unordered_set<char> noteLaChars{ 'A' };
	std::unordered_set<char> noteSiChars{ 'B' };
	std::unordered_set<char> noteDoChars{ 'C' };
	std::unordered_set<char> noteReChars{ 'D' };
	std::unordered_set<char> noteMiChars{ 'E' };
	std::unordered_set<char> noteFaChars{ 'F' };
	std::unordered_set<char> noteSolChars{ 'G' };
	std::unordered_set<char> silenceChars{ };
	std::unordered_set<char> increaseVolume10Chars{ 'I', 'i', 'O', 'o', 'U', 'u' };
	std::unordered_set<char> doubleVolumeChars{ ' ' };
	std::unordered_set<char> halveVolumeChars{ };
	std::unordered_set<char> repeatOrSilenceChars{ };
	std::unordered_set<char> increaseOctaveChars{ '?', '.' };
	std::unordered_set<char> decreaseOctaveChars{ };
	std::unordered_set<char> defaultOctaveChars{ };
	std::unordered_set<char> changeInstrumentChars{ };
	std::unordered_set<char> changeInstrumentGen7Chars{ '!' };
	std::unordered_set<char> changeInstrumentCurrentPlusThisChars{ '0', '1', '2', '3', '4',
																   '5', '6', '7', '8', '9' };
	std::unordered_set<char> changeInstrumentGen15Chars{ '\n' };
	std::unordered_set<char> changeInstrumentGen76Chars{ ';' };
	std::unordered_set<char> changeInstrumentGen20Chars{ ',' };
	std::unordered_set<char> increaseBPMChars{ };
	std::unordered_set<char> decreaseBPMChars{ };
	int getCurPos();
	char getCurChar();
	char getPrevChar();
	void incrementCurPos();
	void resetCurPos();

private:
	Octave _cur_octave;
	Volume _cur_volume;
	Instrument _cur_instrument;
	Key _cur_key;
	BPM _cur_bpm;
	long unsigned int _cur_pos;
	std::string _text;
	int charToKeyInt(char key);
	Note parseNote(char key);
};