#include <DxLib.h>
#include <string.h>
#include "soundefect.h"
#include "pause.h"
#include "setting.h"
#include "utikomi.h"

int MenuScene;
int MenuBGM;
int MenuMusic[10];
int icon[50][3] = { {0},{0} };
int iconstate[50] = { 0 };
int grade[50] = { 0 };

bool menuinit() {
	MenuScene = LoadGraph("image/menu.jpg");
	MenuBGM = LoadSoundMem("music/パズル気分.mp3");
	ChangeVolumeSoundMem(75, MenuBGM);
	MenuMusic[0] = MenuBGM;
	MenuMusic[1] = clickSE;

	int count = 0;
	char icontxt[100];	// アイコンのパスを格納する配列
	fopen_s(&fp, "data/icon.txt", "r");
	while (fscanf_s(fp, "%s", icontxt, 100) == 1) {
		icon[count][0] = LoadGraph("image/hatena_icon.png");	// 初期状態は「？」
		icon[count][1] = LoadGraph(icontxt);	// icon.txtからアイコンのパスを持ってきて代入
		count++;
	}
	fclose(fp);

	int save = 0;
	count = 0;
	fopen_s(&fp, "data/save.dat", "r");	// セーブデータの復元
	while (fscanf_s(fp, "%d", &save) == 1) {
		if (save == 3) {
			iconstate[count] = 2;	// 成績グレード
		}
		else {
			iconstate[count] = 1;	// それ以外
		}
	}
	fclose(fp);
	
	return true;
}

int menu() {
	bool initflag = false;
	int i;	// x座標変更用の変数
	int j;	// 何番目のアイコンを描画するかの変数
	int y;	// 選んでいるゲームを揺らすための変数
	int selected = 0;	// 今選ばれているゲームの順番
	int holdleft = 0;	// 長押し判定
	int holdright = 0;
	bool holdleftflag = true;	// 同じ
	bool holdrightflag = true;	// 同じ
	int frame = 0;	// menuに入ってからの経過フレーム数
	int result = 0;	// ゲームの評価

	if (!initflag) { initflag = menuinit(); }	// 初期化
	PlaySoundMem(MenuBGM, DX_PLAYTYPE_LOOP);

	while (1) {
		DrawExtendGraph(0, 0, 959, 499, MenuScene, false);

		if (CheckSoundMem(MenuBGM) == 0) {
			PlaySoundMem(MenuBGM, DX_PLAYTYPE_LOOP);
		}

		if (CheckHitKey(KEY_INPUT_LEFT)) {	// 左に移動
			if (selected != 0 && holdleftflag) {	// 左端かどうか、長押しかどうか
				frame = 0;
				selected--;
				PlaySoundMem(moveSE, DX_PLAYTYPE_BACK);
				holdleft++;
				holdleftflag = false;
			}
			else if (!holdleftflag) {
				holdleft++;
				if (holdleft > 30) {
					holdleftflag = true;
				}
			}
		}
		else {
			holdleft = 0;
			holdleftflag = true;
		}

		if (CheckHitKey(KEY_INPUT_RIGHT)) {	// 右に移動
			if (selected != 49 && holdrightflag) {	// 右端かどうか、長押しかどうか
				frame = 0;
				selected++;
				PlaySoundMem(moveSE, DX_PLAYTYPE_BACK);
				holdright++;
				holdrightflag = false;
			}
			else if (!holdrightflag) {
				holdright++;
				if (holdright > 30) {
					holdrightflag = true;
				}
			}
		}
		else {
			holdright = 0;
			holdrightflag = true;
		}

		j = selected - 3;
		for (i = -20; i < 960; i += 150) {
			if (j >= 0 && j < selected + 4) {
				if (j == selected) {
					y = frame % 65 - 32;
					DrawGraph(i, 350 - y * y / 30 , icon[j][iconstate[j]], true);	// 選択中のゲームのみ動かす
				}
				else {
					DrawGraph(i, 350, icon[j][iconstate[j]], true);	// その他のゲームアイコンの描画
				}
			}
			j++;
		}

		if (Click()) {
			StopSoundMem(MenuBGM);
			PlaySoundMem(decideSE, DX_PLAYTYPE_BACK);
			FeedOut();
			result = Utikomi();
			if (result != 0) {

			}
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {	// ポーズ処理
			if (Pause(MenuMusic)) {
				return 0;
			}
		}
		ScreenFlip();
		ClsDrawScreen();
		frame++;
	}
}