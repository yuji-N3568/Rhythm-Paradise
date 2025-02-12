#include <DxLib.h>
#include "soundefect.h"

void SoundInit()
{
	PauseSE = LoadSoundMem("SE/�J�[�\���ړ�3.mp3");
	PracticeIntro = LoadSoundMem("music/PracticeIntro.wav");
	PracticeMain = LoadSoundMem("music/PracticeMain.wav");
	moveSE = LoadSoundMem("SE/�J�[�\���ړ�7.mp3");
	clickSE = LoadSoundMem("SE/����{�^��������53.mp3");
	Clap = LoadSoundMem("SE/�吨�Ŕ���.mp3");
	MissSE = LoadSoundMem("SE/�{����.mp3");
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
