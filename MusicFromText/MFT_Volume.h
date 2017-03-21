#pragma once

class Volume
{
public:
	Volume();
	Volume(int volume);
	~Volume();
	void setVolume(int volume);
	void setHalfVolume();
	void setDoubleVolume();
	void setDefaultVolume();
	void increase10PercentVolume();
	int toInt() const;
	friend bool operator==(const Volume &lhs, const Volume &rhs);
	friend bool operator!=(const Volume &lhs, const Volume &rhs);

protected:
	bool isValid(int volume);

private:
	int _volume = _default_volume;
	static const int _min_volume = 0;
	static const int _max_volume = 100;
	static const int _default_volume = 100;
};