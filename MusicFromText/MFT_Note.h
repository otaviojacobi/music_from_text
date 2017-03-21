#pragma once

#include <string>
#include "MFT_Octave.h"
#include "MFT_Volume.h"
#include "MFT_Instrument.h"
#include "MFT_Key.h"
#include "MFT_BPM.h"

class Note
{
public:
	Note();
	Note(Octave octave, Volume volume, Instrument instrument, Key key, BPM bpm);
	~Note();
	Octave getOctave() const;
	Volume getVolume() const;
	Instrument getInstrument() const;
	Key getKey() const;
	BPM getBPM() const;
	void setOctave(Octave octave);
	void setVolume(Volume volume);
	void setInstrument(Instrument instrument);
	void setKey(Key key);
	void setBPM(BPM bpm);
	void setMute();
	std::string toString() const;
	friend bool operator==(const Note &lhs, const Note &rhs);
	friend bool operator!=(const Note &lhs, const Note &rhs);

private:
	Octave _octave;
	Volume _volume;
	Instrument _instrument;
	Key _key;
	BPM _bpm;
};