#pragma once

class Key
{
public:
	Key();
	Key(int key);
	~Key();
	enum Keys { LA , SI , DO , RE , MI, FA , SOL, KEYS_COUNT };
	void setKey(int key);
	void setDefaultKey();
	int toInt() const;
	char toChar() const;
	friend bool operator==(const Key &lhs, const Key &rhs);
	friend bool operator!=(const Key &lhs, const Key &rhs);

protected:
	bool isValid(int key) const;

private:
	int _key = _default_key;
	static const int _default_key = Keys::DO;
};