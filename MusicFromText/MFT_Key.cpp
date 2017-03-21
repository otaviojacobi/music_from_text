#include "stdafx.h"
#include "MFT_Key.h"

/**
Constructor.
*/
Key::Key()
{
}

/**
Constructor.
*/
Key::Key(int key)
{
	setKey(key);
}

/**
Destructor.
*/
Key::~Key()
{
}

/**
Try to set the Key to the specified value.
If the value is not in the valid range, do nothing.
*/
void Key::setKey(int key)
{
	if (isValid(key))
		_key = key;
}

/**
Set Key to its default value.
*/
void Key::setDefaultKey()
{
	_key = _default_key;
}

/**
Int representation of the Key.
*/
int Key::toInt() const
{
	return _key;
}

/**
Char representation of the key.
*/
char Key::toChar() const
{
	switch (_key)
	{
		case Key::Keys::LA:
			return 'A';
		case Key::Keys::SI:
			return 'B';
		case Key::Keys::DO:
			return 'C';
		case Key::Keys::RE:
			return 'D';
		case Key::Keys::MI:
			return 'E';
		case Key::Keys::FA:
			return 'F';
		case Key::Keys::SOL:
			return 'G';
		default:
			return 'C';
	}
}

/**
Check if the value of key is in the correct range.
*/
bool Key::isValid(int key) const
{
	return (key >= 0 && key < Keys::KEYS_COUNT);
}

/**
Comparison operator.
*/
bool operator==(const Key &lhs, const Key &rhs)
{
	return lhs.toInt() == rhs.toInt();
}

/**
Comparison operator.
*/
bool operator!=(const Key &lhs, const Key &rhs)
{
	return !(lhs == rhs);
}
