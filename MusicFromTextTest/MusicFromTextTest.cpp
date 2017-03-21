#include "stdafx.h"
#include <iostream>
#include "MFT_Parser.h"
#include "MFT_Music.h"
#include "MFT_Note.h"
#include "MFT_BPM.h"
#include "MFT_Instrument.h"
#include "MFT_Key.h"
#include "MFT_Octave.h"
#include "MFT_Volume.h"


/** MACROS **/

inline void INIT(std::string tname)
{
	std::cout << "Starting " << tname << " tests" << std::endl;
}

template<typename T>
inline void FAIL(std::string fname, T expect, T actual)
{
	std::cout << "Test failed for " << fname << std::endl;
	std::cout << "\t Expected: " << expect << std::endl;
	std::cout << "\t Got: " << actual << std::endl;
}

inline void ALL_PASS(std::string tname)
{
	std::cout << "All " << tname << " tests succeeded!" << std::endl;
}

void FAILED_SOME(std::string tname, int fails, int total)
{
	std::cout << "Failed tests for " << tname << ":" << std::endl;
	std::cout << "\t Passed " << total - fails << "/" << total << std::endl;
}


/** PARSER TESTS **/

class ParserTester : public Parser
{
public:
	static constexpr const char* _tname = "Parser";

	static bool testParserMusicalKeyChars()
	{
		Parser a;
		a.setMusicString("C");
		Music *b = a.musicFromText(100, 120, 5, 0);

		std::string expected = "X[VOLUME_COARSE]=100 T120 I0 C5 ";
		std::string actual = b->toString();

		if (expected == actual)
			return true;

		FAIL("testParserMusicalKeyChars", expected, actual);
		return false;
	}

	static bool testParserChangeInstrumentChars()
	{
		Parser a;
		a.setMusicString("C3C");
		Music *b = a.musicFromText(100, 120, 5, 0);

		std::string expected = "X[VOLUME_COARSE]=100 T120 I0 C5 I3 C5 ";
		std::string actual = b->toString();

		if (expected == actual)
			return true;

		FAIL("testParserChangeInstrumentChars", expected, actual);
		return false;
	}

	static bool testParserIncreaseOctaveChars()
	{
		Parser a;
		a.setMusicString("C?C");
		Music *b = a.musicFromText(100, 120, 5, 0);

		std::string expected = "X[VOLUME_COARSE]=100 T120 I0 C5 C6 ";
		std::string actual = b->toString();

		if (expected == actual)
			return true;

		FAIL("testParserIncreaseOctaveChars", expected, actual);
		return false;
	}

	static bool testParserSelectTubularBells()
	{
		Parser a;
		a.setMusicString("C\nC");
		Music *b = a.musicFromText(100, 120, 5, 0);

		std::string expected = "X[VOLUME_COARSE]=100 T120 I0 C5 I15 C5 ";
		std::string actual = b->toString();

		if (expected == actual)
			return true;

		FAIL("testParserSelectTubularBells", expected, actual);
		return false;
	}

	static bool testParserSelectPanFlute()
	{
		Parser a;
		a.setMusicString("C;C");
		Music *b = a.musicFromText(100, 120, 5, 0);

		std::string expected = "X[VOLUME_COARSE]=100 T120 I0 C5 I76 C5 ";
		std::string actual = b->toString();

		if (expected == actual)
			return true;

		FAIL("testParserSelectPanFlute", expected, actual);
		return false;
	}

	static bool testParserSelectChurchOrgan()
	{
		Parser a;
		a.setMusicString("C,C");
		Music *b = a.musicFromText(100, 120, 5, 0);

		std::string expected = "X[VOLUME_COARSE]=100 T120 I0 C5 I20 C5 ";
		std::string actual = b->toString();

		if (expected == actual)
			return true;

		FAIL("testParserSelectChurchOrgan", expected, actual);
		return false;
	}

	static void testAll()
	{
		INIT(_tname);

		int fails = 0, total = 0;

		total++;
		if (testParserMusicalKeyChars())
			fails++;

		total++;
		if (testParserChangeInstrumentChars())
			fails++;

		total++;
		if (testParserIncreaseOctaveChars())
			fails++;

		total++;
		if (testParserSelectTubularBells())
			fails++;

		total++;
		if (testParserSelectPanFlute())
			fails++;

		total++;
		if (testParserSelectChurchOrgan())
			fails++;

		if (fails == total)
			ALL_PASS(_tname);
		else
			FAILED_SOME(_tname, fails, total);
	}
};


/** BPM TESTS **/

class BPMTester : public BPM
{
public:
	static constexpr const char* _tname = "BPM";

	static bool testBPMLowerBound()
	{
		BPM b(120);

		b.setBPM(30);

		int expected = 120;
		int actual = b.toInt();

		if (expected == actual)
			return true;

		FAIL("testBPMLowerBound", expected, actual);
		return false;
	}

	static bool testBPMUpperBound()
	{
		BPM b(120);

		b.setBPM(750);

		int expected = 120;
		int actual = b.toInt();

		if (expected == actual)
			return true;

		FAIL("testBPMUpperBound", expected, actual);
		return false;
	}

	static void testAll()
	{
		INIT(_tname);

		int fails = 0, total = 0;

		total++;
		if (testBPMLowerBound())
			fails++;

		total++;
		if (testBPMUpperBound())
			fails++;

		if (fails == total)
			ALL_PASS(_tname);
		else
			FAILED_SOME(_tname, fails, total);
	}
};


/** INSTRUMENT TESTS **/

class InstrumentTester : public Instrument
{
public:
	static constexpr const char* _tname = "Instrument";

	static bool testInstrumentLowerBound()
	{
		Instrument i(5);

		i.setInstrument(-1);

		int expected = 5;
		int actual = i.toInt();

		if (expected == actual)
			return true;

		FAIL("testInstrumentLowerBound", expected, actual);
		return false;
	}

	static bool testInstrumentUpperBound()
	{
		Instrument i(5);

		i.setInstrument(130);

		int expected = 5;
		int actual = i.toInt();

		if (expected == actual)
			return true;

		FAIL("testInstrumentUpperBound", expected, actual);
		return false;
	}

	static void testAll()
	{
		INIT(_tname);

		int fails = 0, total = 0;

		total++;
		if (testInstrumentLowerBound())
			fails++;

		total++;
		if (testInstrumentUpperBound())
			fails++;

		if (fails == total)
			ALL_PASS(_tname);
		else
			FAILED_SOME(_tname, fails, total);
	}
};


/** KEY TESTS **/

class KeyTester : public Key
{
public:
	static constexpr const char* _tname = "Key";

	static bool testKeyLowerBound()
	{
		Key k(DO);

		k.setKey(-1);

		int expected = DO;
		int actual = k.toInt();

		if (expected == actual)
			return true;

		FAIL("testKeyLowerBound", expected, actual);
		return false;
	}

	static bool testKeyUpperBound()
	{
		Key k(DO);

		k.setKey(KEYS_COUNT);

		int expected = DO;
		int actual = k.toInt();

		if (expected == actual)
			return true;

		FAIL("testKeyUpperBound", expected, actual);
		return false;
	}

	static void testAll()
	{
		INIT(_tname);

		int fails = 0, total = 0;

		total++;
		if (testKeyLowerBound())
			fails++;

		total++;
		if (testKeyUpperBound())
			fails++;

		if (fails == total)
			ALL_PASS(_tname);
		else
			FAILED_SOME(_tname, fails, total);
	}
};


/** MUSIC TESTS **/

class MusicTester : public Music
{
public:
	static constexpr const char* _tname = "Music";

	static bool testMusicToString()
	{
		Octave octave(3);
		Volume volume(70);
		Instrument instrument(0);
		Key key(Key::Keys::DO);
		BPM bpm(120);

		Note n1(octave, volume, instrument, key, bpm);

		octave.decrementOctave();
		volume.increase10PercentVolume();
		instrument.setNextInstrument();
		key.setKey(Key::Keys::FA);
		bpm.setBPM(150);

		Note n2(octave, volume, instrument, key, bpm);

		Music *m = new Music();

		m->addNoteToSongEnd(n1);
		m->addNoteToSongEnd(n2);

		std::string actual = m->toString();
		std::string expected = "X[VOLUME_COARSE]=70 T120 I0 C3 X[VOLUME_COARSE]=77 T150 I1 F2 ";

		if (expected == actual)
			return true;

		FAIL("testKeyLowerBound", expected, actual);
		return false;
	}

	static void testAll()
	{
		INIT(_tname);

		int fails = 0, total = 0;

		total++;
		if (testMusicToString())
			fails++;

		if (fails == total)
			ALL_PASS(_tname);
		else
			FAILED_SOME(_tname, fails, total);
	}
};


/** NOTE TESTS **/

class NoteTester : public Note
{
public:
	static constexpr const char* _tname = "Note";

	static bool testNoteToString()
	{
		Octave octave(3);
		Volume volume(100);
		Instrument instrument(0);
		Key key(Key::Keys::DO);
		BPM bpm(120);

		Note n(octave, volume, instrument, key, bpm);

		std::string expected = "X[VOLUME_COARSE]=100 T120 I0 C3";
		std::string actual = n.toString();

		if (expected == actual)
			return true;

		FAIL("testNoteToString", expected, actual);
		return false;
	}

	static void testAll()
	{
		INIT(_tname);

		int fails = 0, total = 0;

		total++;
		if (testNoteToString())
			fails++;

		if (fails == total)
			ALL_PASS(_tname);
		else
			FAILED_SOME(_tname, fails, total);
	}
};


/** OCTAVE TESTS **/

class OctaveTester : public Octave
{
public:
	static constexpr const char* _tname = "Octave";

	static bool testOctaveLowerBound()
	{
		Octave o(3);

		o.setOctave(-1);

		int expected = 3;
		int actual = o.toInt();

		if (expected == actual)
			return true;

		FAIL("testOctaveLowerBound", expected, actual);
		return false;
	}

	static bool testOctaveUpperBound()
	{
		Octave o(3);

		o.setOctave(11);

		int expected = 3;
		int actual = o.toInt();

		if (expected == actual)
			return true;

		FAIL("testOctaveUpperBound", expected, actual);
		return false;
	}


	static void testAll()
	{
		INIT(_tname);

		int fails = 0, total = 0;

		total++;
		if (testOctaveLowerBound())
			fails++;

		total++;
		if (testOctaveUpperBound())
			fails++;

		if (fails == total)
			ALL_PASS(_tname);
		else
			FAILED_SOME(_tname, fails, total);
	}
};


/** VOLUME TESTS **/

class VolumeTester : public Volume
{
public:
	static constexpr const char* _tname = "Volume";

	static bool testVolumeLowerBound()
	{
		Volume v(50);

		v.setVolume(-1);

		int expected = 50;
		int actual = v.toInt();

		if (expected == actual)
			return true;

		FAIL("testVolumeLowerBound", expected, actual);
		return false;
	}

	static bool testVolumeUpperBound()
	{
		Volume v(50);

		v.setVolume(101);

		int expected = 50;
		int actual = v.toInt();

		if (expected == actual)
			return true;

		FAIL("testVolumeUpperBound", expected, actual);
		return false;
	}

	static bool testVolumeIncrease10Percent()
	{
		Volume v(50);

		v.increase10PercentVolume();

		int expected = 55;
		int actual = v.toInt();

		if (expected == actual)
			return true;

		FAIL("testVolumeIncrease10Percent", expected, actual);
		return false;
	}

	static void testAll()
	{
		INIT(_tname);

		int fails = 0, total = 0;

		total++;
		if (testVolumeLowerBound())
			fails++;

		total++;
		if (testVolumeUpperBound())
			fails++;

		total++;
		if (testVolumeIncrease10Percent())
			fails++;

		if (fails == total)
			ALL_PASS(_tname);
		else
			FAILED_SOME(_tname, fails, total);
	}
};


int main()
{
	ParserTester::testAll();
	BPMTester::testAll();
	InstrumentTester::testAll();
	KeyTester::testAll();
	MusicTester::testAll();
	NoteTester::testAll();
	OctaveTester::testAll();
	VolumeTester::testAll();

	std::cout << "Press ENTER to exit." << std::endl;
	std::cin.ignore();

    return 0;
}

