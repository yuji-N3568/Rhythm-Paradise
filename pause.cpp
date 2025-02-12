#include <DxLib.h>
#include "pause.h"
#include "setting.h"
#include "soundefect.h"

int Pause(int UsingMusic[10]) {
	int soundflag[10];
	int i;
	for (i = 0; i < 10; i++) {
		soundflag[i] = 0;
		if (CheckSoundMem(UsingMusic[i])) {
			StopSoundMem(UsingMusic[i]);
			soundflag[i] = 1;
		}
	}
	ChangeVolumeSoundMem(75, PauseSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, SCREEN_X - 1, SCREEN_Y - 1, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawString(0, 0, "ポーズ中\nEsc:タイトルに戻る\nEnter:キャンセル", 0xffffff);
	ScreenFlip();
	PlaySoundMem(PauseSE, DX_PLAYTYPE_NORMAL);
	while (1) {
		if (CheckHitKey(KEY_INPUT_RETURN)) {
			for (i = 0; i < 10; i++) {
				if (soundflag[i]) {
					if (UsingMusic[i] == PracticeMain) {
						PlaySoundMem(UsingMusic[i], DX_PLAYTYPE_LOOP, 0);
					}else {
						PlaySoundMem(UsingMusic[i], DX_PLAYTYPE_BACK, 0);
					}
				}
			}
			return 0;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			FeedOut();
			return 1;
		}
	}
}

bool TitlePause(int PlayingMusic) {
	StopSoundMem(PlayingMusic);
	ChangeVolumeSoundMem(75, PauseSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, SCREEN_X - 1, SCREEN_Y - 1, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawString(0, 0, "ポーズ中\nEsc:ゲームを終了\nEnter:キャンセル", 0xffffff);
	ScreenFlip();
	PlaySoundMem(PauseSE, DX_PLAYTYPE_NORMAL);
	while (1) {
		if (CheckHitKey(KEY_INPUT_RETURN)) {
			PlaySoundMem(PlayingMusic, DX_PLAYTYPE_BACK, 0);
			return false;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			return true;
		}
	}
}