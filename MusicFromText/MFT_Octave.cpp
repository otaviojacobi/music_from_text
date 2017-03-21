#include "stdafx.h"
#include "MFT_Octave.h"


/**
Constructor.
*/
Octave::Octave()
{
}

/**
Constructor.
*/
Octave::Octave(int octave)
{
	setOctave(octave);
}

/**
Destructor.
*/
Octave::~Octave()
{
}

/**
Try to set the Octave to the specified value.
If the value is not in the valid range, do nothing.
*/
void Octave::setOctave(int octave)
{
	if( isValid(octave) )
		_octave = octave;
}

/**
Increment octave to its next POSSIBLE value.
*/
void Octave::incrementOctave()
{
	if (isValid(_octave + _octave_increment))
		setOctave(_octave + _octave_increment);
	else
		setDefaultOctave();
}

/**
Decrement octave to its previous POSSIBLE value.
*/
void Octave::decrementOctave()
{
	setOctave(_octave - _octave_decrement);
}

/**
Set Octave to its default value.
*/
void Octave::setDefaultOctave()
{
	_octave = _default_octave;
}

/**
Integer representation of the Octave.
*/
int Octave::toInt() const
{
	return _octave;
}

/**
Check if the value of octave in correct range.
*/
bool Octave::isValid(int octave)
{
	return (octave >= _min_octave && octave <= _max_octave);
}

/**
Comparison operator.
*/
bool operator==(const Octave &lhs, const Octave &rhs)
{
	return lhs.toInt() == rhs.toInt();
}

/**
Comparison operator.
*/
bool operator!=(const Octave &lhs, const Octave &rhs)
{
	return !(lhs == rhs);
}
