#include "stdafx.h"
#include "MFT_Instrument.h"

/**
Constructor.
*/
Instrument::Instrument()
{
}

/**
Constructor.
*/
Instrument::Instrument(int instrument)
{
	setInstrument(instrument);
}

/**
Destructor.
*/
Instrument::~Instrument()
{
}

/**
Try to set the Key to the specified value.
If the value is not in the valid range, do nothing.
*/
void Instrument::setInstrument(int instrument)
{
	if (isValid(instrument))
		_instrument = instrument;
}

/**
Go to next instrument in a circular order.
*/
void Instrument::setNextInstrument()
{
	setInstrument((_instrument + 1) % _max_instrument); // circular
}

/**
Set Instrument to its default value.
*/
void Instrument::setDefaultInstrument()
{
	_instrument = _default_instrument;
}

/**
Integer representation of the Instrument.
*/
int Instrument::toInt() const
{
	return _instrument;
}

/**
Check if the instrument is a valid instrument.
*/
bool Instrument::isValid(int instrument)
{
	return (instrument >= _min_instrument && instrument <= _max_instrument);
}

/**
Comparison operator.
*/
bool operator==(const Instrument &lhs, const Instrument &rhs)
{
	return lhs.toInt() == rhs.toInt();
}

/**
Comparison operator.
*/
bool operator!=(const Instrument &lhs, const Instrument &rhs)
{
	return !(lhs == rhs);
}
