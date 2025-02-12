#include <DxLib.h>
#include "soundefect.h"

void SoundInit()
{
	PauseSE = LoadSoundMem("SE/カーソル移動3.mp3");
	PracticeIntro = LoadSoundMem("music/PracticeIntro.wav");
	PracticeMain = LoadSoundMem("music/PracticeMain.wav");
	moveSE = LoadSoundMem("SE/カーソル移動7.mp3");
	clickSE = LoadSoundMem("SE/決定ボタンを押す53.mp3");
	Clap = LoadSoundMem("SE/大勢で拍手.mp3");
	MissSE = LoadSoundMem("SE/ボヨン.mp3");
	ChangeVolumeSoundMem(100, PauseSE);
	ChangeVolumeSoundMem(75, PracticeIntro);
	ChangeVolumeSoundMem(75, PracticeMain);
	ChangeVolumeSoundMem(75, clickSE);
	ChangeVolumeSoundMem(75, Clap);
}

void SoundDelete() 
{
	DeleteSoundMem(PracticeIntro);
	DeleteSoundMem(PracticeMain);
}
