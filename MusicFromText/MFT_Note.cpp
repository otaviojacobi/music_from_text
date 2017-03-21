#include "stdafx.h"
#include "MFT_Note.h"
#include <sstream>

/**
Constructor.
*/
Note::Note()
{
}

/**
Constructor.
*/
Note::Note(Octave octave, Volume volume, Instrument instrument, Key key, BPM bpm)
{
	setOctave(octave);
	setVolume(volume);
	setInstrument(instrument);
	setKey(key);
	setBPM(bpm);
}

/**
Destructor.
*/
Note::~Note()
{
}

/**
Return the Octave instance.
*/
Octave Note::getOctave() const
{
	return _octave;
}

/**
Return the Volume instance.
*/
Volume Note::getVolume() const
{
	return _volume;
}

/**
Return the Instrument instance.
*/
Instrument Note::getInstrument() const
{
	return _instrument;
}

/**
Return the Key instance.
*/
Key Note::getKey() const
{
	return _key;
}

/**
Return the BPM instance.
*/
BPM Note::getBPM() const
{
	return _bpm;
}

/**
Set the Octave instance.
Being an existing object, the new Octave is surely valid.
*/
void Note::setOctave(Octave octave)
{
	_octave = octave;
}

/**
Set the Volume instance.
Being an existing object, the new Volume is surely valid.
*/
void Note::setVolume(Volume volume)
{
	_volume = volume;
}

/**
Set the Instrument instance.
Being an existing object, the new Instrument is surely valid.
*/
void Note::setInstrument(Instrument instrument)
{
	_instrument = instrument;
}

/**
Set the Key instance.
Being an existing object, the new Key is surely valid.
*/
void Note::setKey(Key key)
{
	_key = key;
}

/**
Set the BPM instance.
Being an existing object, the new BPM is surely valid.
*/
void Note::setBPM(BPM bpm)
{
	_bpm = bpm;
}

/**
Set the volume to zero.
*/
void Note::setMute()
{
	_volume.setVolume(0);
}

/**
String representation of the note on *Fugue format.
*/
std::string Note::toString() const
{
	// CFugue Format:
	// X[VOLUME_COARSE]={volume int} T{bpm int} I{instrument int} {key upper char}{octave int}
	std::stringstream ss;
	ss << "X[VOLUME_COARSE]=" << _volume.toInt() << " ";
	ss << "T" << _bpm.toInt() << " ";
	ss << "I" << _instrument.toInt() << " ";
	ss << _key.toChar() << _octave.toInt();
	return ss.str();
}

/**
Comparison operator.
*/
bool operator==(const Note &lhs, const Note &rhs)
{
	return lhs.toString() == rhs.toString();
}

/**
Comparison operator.
*/
bool operator!=(const Note &lhs, const Note &rhs)
{
	return !(lhs == rhs);
}
