#pragma once

class Octave
{
public:
	Octave();
	Octave(int octave);
	~Octave();
	void setOctave(int octave);
	void incrementOctave();
	void decrementOctave();
	void setDefaultOctave();
	int toInt() const;
	friend bool operator==(const Octave &lhs, const Octave &rhs);
	friend bool operator!=(const Octave &lhs, const Octave &rhs);

protected:
	bool isValid(int octave);

private:
	int _octave = _default_octave;
	static const int _min_octave = 0;
	static const int _max_octave = 10;
	static const int _default_octave = 5;
	static const int _octave_increment = 1;
	static const int _octave_decrement = 1;
};