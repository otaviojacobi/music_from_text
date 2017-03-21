#include "stdafx.h"
#include "MFT_BPM.h"

/**
Constructor.
*/
BPM::BPM()
{
}

/**
Constructor.
*/
BPM::BPM(int bpm)
{
	setBPM(bpm);
}

/**
Destructor.
*/
BPM::~BPM()
{
}

/**
Try to set the BPM to the specified value.
If the value is not in the valid range, do nothing.
*/
void BPM::setBPM(int bpm)
{
	if (isValid(bpm))
		_bpm = bpm;
}

/**
Decrement bpm to its previous POSSIBLE value.
*/
void BPM::decrementBPM()
{
	setBPM(_bpm - _bpm_decrement);
}

/**
Increment bpm to its previous POSSIBLE value.
*/
void BPM::incrementBPM()
{
	setBPM(_bpm + _bpm_increment);
}

/**
Set BPM to its default value.
*/
void BPM::setDefaultBPM()
{
	_bpm = _default_bpm;
}

/**
Integer representation of the BPM.
*/
int BPM::toInt() const
{
	return _bpm;
}

/**
Check if the value of bpm in correct range.
*/
bool BPM::isValid(int bpm)
{
	return (bpm >= _min_bpm && bpm <= _max_bpm);
}

/**
Comparison operator.
*/
bool operator==(const BPM &lhs, const BPM &rhs)
{
	return lhs.toInt() == rhs.toInt();
}

/**
Comparison operator.
*/
bool operator!=(const BPM &lhs, const BPM &rhs)
{
	return !(lhs == rhs);
}
