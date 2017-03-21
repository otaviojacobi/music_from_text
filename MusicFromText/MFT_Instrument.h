#pragma once

class Instrument
{
public:
	Instrument();
	Instrument(int instrument);
	~Instrument();
	void setInstrument(int instrument);
	void setNextInstrument();
	void setDefaultInstrument();
	int toInt() const;
	friend bool operator==(const Instrument &lhs, const Instrument &rhs);
	friend bool operator!=(const Instrument &lhs, const Instrument &rhs);

protected:
	bool isValid(int instrument);

private:
	int _instrument = _default_instrument;
	static const int _min_instrument = 0;
	static const int _max_instrument = 127;
	static const int _default_instrument = 0;
};