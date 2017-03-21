#include "stdafx.h"
#include "MFT_Volume.h"


/**
Constructor.
*/
Volume::Volume()
{
}


/**
Constructor.
*/
Volume::Volume(int volume)
{
	setVolume(volume);
}

/**
Destructor.
*/
Volume::~Volume()
{
}

/**
Try to set the Volume to the specified value.
If the value is not in the valid range, do nothing.
*/
void Volume::setVolume(int volume)
{
	if (isValid(volume))
		_volume = volume;
}

/**
Set Volume to half of actual value if possible.
*/
void Volume::setHalfVolume()
{
	setVolume(_volume/2);
}

/**
Double the volume if in range.
*/
void Volume::setDoubleVolume()
{
	setVolume(_volume*2);
}

/**
Set Volume to its default value.
*/
void Volume::setDefaultVolume()
{
	_volume = _default_volume;
}

/**
Increase volume by 10%.
*/
void Volume::increase10PercentVolume()
{
	setVolume(static_cast<int>(1.1*_volume));
}

/**
Integer representation of the Volume.
*/
int Volume::toInt() const
{
	return _volume;
}

/**
Check if the value of volume in correct range.
*/
bool Volume::isValid(int volume)
{
	return (volume >= _min_volume && volume <= _max_volume);
}

/**
Comparison operator.
*/
bool operator==(const Volume &lhs, const Volume &rhs)
{
	return lhs.toInt() == rhs.toInt();
}

/**
Comparison operator.
*/
bool operator!=(const Volume &lhs, const Volume &rhs)
{
	return !(lhs == rhs);
}
