#pragma once

class BPM
{
public:
	BPM();
	BPM(int bpm);
	~BPM();
	void setBPM(int bpm);
	void decrementBPM();
	void incrementBPM();
	void setDefaultBPM();
	int toInt() const;
	friend bool operator==(const BPM &lhs, const BPM &rhs);
	friend bool operator!=(const BPM &lhs, const BPM &rhs);

protected:
	bool isValid(int bpm);

private:
	int _bpm = _default_bpm;
	static const int _default_bpm = 120;
	static const int _min_bpm = 60;
	static const int _max_bpm = 720;
	static const int _bpm_increment = 50;
	static const int _bpm_decrement = 50;
};

