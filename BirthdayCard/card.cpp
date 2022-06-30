#include <windows.h>
#include <mmeapi.h>
#pragma comment (lib, "Winmm.lib")

int main(int argc, char** argv)
{
	HMIDIOUT hmidi;
	midiOutOpen(&hmidi, MIDI_MAPPER, 0, 0, 0);

	const char* keys      = "GGAGCBGGAGDCGGGECBA FFECDC";
	const char* octave    = "0000100000110011100 111111";
	const char* durations = "31444831444831444451314448";
	
	midiOutShortMsg(hmidi, 0xC0 | (0 << 8));
	static int keyMap[]{ 9, 11, 0, 2, 4, 5, 7 };
	
	for (int i = 0; i < strlen(keys); ++i) {
		if (keys[i] == ' ') {
			Sleep((durations[i] - '0') * 150); continue;
		}

		int key = keyMap[keys[i] - 'A'] + 60 + (octave[i] - '0') * 12;		

		midiOutShortMsg(hmidi, 0x90 | (key << 8) | (127 << 16));
		Sleep((durations[i] - '0') * 150);
		midiOutShortMsg(hmidi, 0x80 | (key << 8) | (127 << 16));
	}
	midiOutClose(hmidi);
}