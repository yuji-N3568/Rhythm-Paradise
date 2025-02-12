#include <DxLib.h>
#include "setting.h"

void FeedOut() {
	for (int i = 0; i < 128; i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, i);
		DrawBox(0, 0, SCREEN_X - 1, SCREEN_Y - 1, 0x000000, true);
		ScreenFlip();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void FeedIn(int scene) {
	for (int i = 255; i >= 0; i -= 5) {
		DrawExtendGraph(0, 0, 959, 499, scene, false);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, i);
		DrawBox(0, 0, SCREEN_X - 1, SCREEN_Y - 1, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		ScreenFlip();
		ClearDrawScreen();
	}
}

void FontInit()
{
	PracticeFont = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_ANTIALIASING);
}

void StopMusic(int UsingMusic[10]) {
	for (int i = 0; i < 10; i++) {
		StopSoundMem(UsingMusic[i]);
	}
}

int Click(void) {
	if ((GetMouseInput() && (MOUSE_INPUT_LEFT || MOUSE_INPUT_RIGHT)) || CheckHitKey(KEY_INPUT_SPACE)) {
		return 1;
	}
	else {
		return 0;
	}
}