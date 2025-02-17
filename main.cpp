#include <DxLib.h>
#include "soundefect.h"
#include "setting.h"
#include "menu.h"
#include "pause.h"
#include "utikomi.h"



int EscapeFlag = 0;


int WINAPI WinMain(_In_ HINSTANCE hinstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	SetWindowText("Rhythm Paradise");
	SetGraphMode(SCREEN_X, SCREEN_Y, 32);
	ChangeWindowMode(true); //true=ウィンドウ, false=フルスク
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetWaitVSyncFlag(false);

	SoundInit();
	FontInit();

	int state = 0; // 0:タイトル 1ゲーム画面 2:リザルト
	int titleimg = LoadGraph("image/publicdomainq-0009258ydy.jpg");
	int logo = LoadGraph("image/logos.png");
	int gameimg = LoadGraph("image/space.jpg");
	int titlebgm = LoadSoundMem("music/Carrots.mp3");
	int clickflag = 0;
	int frame = 0;
	int alpha;
	bool endflag = false;

	ChangeVolumeSoundMem(75, titlebgm);
	ChangeVolumeSoundMem(75, clickSE);

	PlaySoundMem(titlebgm, DX_PLAYTYPE_LOOP);
	
	while (ProcessMessage() == 0 && !endflag) {
		SetDrawScreen(DX_SCREEN_BACK);
		DrawExtendGraph(0, 0, 959, 499, titleimg, false);
		DrawGraph(280, 50, logo, true);
		alpha = abs(350 - (frame % 175) * 4);
		if (alpha > 255) { alpha = 255; }
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawString(380, 450, "Click or Press Space Key", 0xffffff);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			endflag = TitlePause(titlebgm);
		}

		if (CheckSoundMem(titlebgm) == 0) {
			PlaySoundMem(titlebgm, DX_PLAYTYPE_BACK);
		}

		if (Click() != 0 && clickflag != 1) {
			PlaySoundMem(clickSE,DX_PLAYTYPE_BACK);
			FeedOut();
			StopSoundMem(titlebgm);
			clickflag = 1;
		}

		if ((CheckSoundMem(clickSE) != 1) && (clickflag != 0)) {
			clickflag = 0;
			menu();
			frame = 0;
		}

		frame++;
		ScreenFlip();
		ClsDrawScreen();
	}

	DeleteGraph(titleimg);
	DeleteGraph(logo);

	SoundDelete();


	DxLib_End();
	return 0;

}