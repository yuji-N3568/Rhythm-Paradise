#include <DxLib.h>
#include <string.h>
#include "utikomi.h"
#include "soundefect.h"
#include "pause.h"
#include "setting.h"
#include <string>

int UtikomiMusic[10];
int Sun[2];

void UtikomiInit()
{
	int count=0;
	GameBGM = LoadSoundMem("music/Mountain_bike.mp3");
	ChangeVolumeSoundMem(75, GameBGM);
	HitSE = LoadSoundMem("SE/�J���b.mp3");
	NotHitSE = LoadSoundMem("SE/�f�U��.mp3");
	ChangeVolumeSoundMem(75, NotHitSE);
	GameScene = LoadGraph("image/UtikomiBack.png");
	UtikomiMusic[0] = GameBGM;
	UtikomiMusic[1] = PracticeIntro;
	UtikomiMusic[2] = PracticeMain;
	UtikomiMusic[3] = Clap;
	UtikomiMusic[4] = clickSE;
	UtikomiMusic[5] = HitSE;
	fopen_s(&fp, "data/timing.dat", "r");
	while (fscanf_s(fp, "%d", &timing[count]) == 1) {
		count++;
	}
	fclose(fp);
	LoadDivGraph("image/Hammers.png", 7, 7, 1, 270, 300, Player);
	LoadDivGraph("image/nails.png", 4, 4, 1, 133, 125, Object);
	LoadDivGraph("image/suns.png", 2, 2, 1, 100, 100, Sun);
	PlayMovie("image/UtikomiIntro2.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
	FeedOut();
	ClsDrawScreen();
} 

int UtikomiPractice()
{
	int frame = 0;
	int ClickCount = 0;
	int Clickflag = 0;
	int Loopflag = 0;
	int Clapflag = 0;
	int i = 0; //hammer�̌���
	clickSE = LoadSoundMem("SE/�N���b�N.mp3");
	ChangeVolumeSoundMem(200, clickSE);
	FeedIn(GameScene);
	while (1) {
		DrawExtendGraph(0, 0, 959, 499, GameScene, false);
		DrawString(0, 0, "s�ŃX�L�b�v", 0xffffff);
		switch (ClickCount)
		{
		case 0:
			if (frame >= 60) {
				DrawBox(100, 50, 860, 150, 0xFFFFFF, true);
				DrawStringFToHandle(360, 80, "����ɂ��́B", 0x000000, PracticeFont);
			}
			break;

		case 1:
			if (frame >= 60) {
				DrawBox(100, 50, 860, 150, 0xFFFFFF, true);
				DrawStringFToHandle(220, 80, "�ł����݂����Ă��炢�܂��B", 0x000000, PracticeFont);
			}
			break;

		case 2:
			if (frame >= 60) {
				DrawBox(100, 50, 860, 150, 0xFFFFFF, true);
				DrawStringFToHandle(140, 80, "�܂��̓n���}�[��U���Ă݂܂��傤�B", 0x000000, PracticeFont);
			}
			break;

		case 3:
			if (frame >= 30) {
				DrawGraph(300, 50, Player[i], true);
			}
			else {
				DrawGraph(frame * 10, 50, Player[0], true);
			}
			DrawStringFToHandle(400, 400, "����3��", 0x000000, PracticeFont);
			ScreenFlip();
			if (i == 0 && frame >= 30) {
				WaitKey();
			}
			else if (i > 0) {
				i++;
			}
			if (CheckHitKey(KEY_INPUT_ESCAPE)) {
				if (Pause(UtikomiMusic)) {
					return 0;
				}
			}
			if (CheckHitKey(KEY_INPUT_S)) {
				return 1;
			}
			if (Click() && i == 0 && frame >= 30) {
				i++;
				PlaySoundMem(clickSE, DX_PLAYTYPE_BACK);
			}
			if (i > 6) {
				i = 0;
				ClickCount++;
			}
			break; 
		
		case 4: case 5:
			DrawGraph(300, 50, Player[i], true);
			DrawFormatStringToHandle(400, 400, 0x000000, PracticeFont, "����%d��", 6 - ClickCount);
			ScreenFlip();
			if (i == 0) {
				WaitKey();
			}
			else if (i > 0) {
				i++;
			}
			if (CheckHitKey(KEY_INPUT_S)) {
				return 1;
			}
			if (Click() && i == 0 && frame >= 30) {
				i++;
				PlaySoundMem(clickSE, DX_PLAYTYPE_BACK);
			}
			if (i > 6) {
				i = 0;
				ClickCount++;
			}
			break;

		case 6:
			DrawGraph(300, 50, Player[i], true);
			if (!Clapflag) {
				PlaySoundMem(Clap, DX_PLAYTYPE_BACK);
				Clapflag = 1;
			}else {
				if (!CheckSoundMem(Clap)) {
					ClickCount++;
					Clapflag = 0;
					frame = 0;
				}
			}
			break;
			
		case 7:
			DrawGraph(300, 50, Player[i], true);
			if (frame >= 60) {
				DrawBox(100, 50, 860, 150, 0xFFFFFF, true);
				DrawStringFToHandle(280, 80, "�ǂ��U����Ղ�ł��B", 0x000000, PracticeFont);
			}
			break;

		case 8:
			DrawGraph(300, 50, Player[i], true);
			if (frame >= 60) {
				DrawBox(100, 50, 860, 150, 0xFFFFFF, true);
				DrawStringFToHandle(100, 80, "�ł̓��Y���ɍ��킹�Ă���Ă݂܂��傤�B", 0x000000, PracticeFont);
			}
			break;

		default:
			DrawGraph(300, 50, Player[i], true);
			if (frame == 30) {
				PlaySoundMem(PracticeIntro, DX_PLAYTYPE_BACK);
			}
			if (!Loopflag && frame > 30 && !CheckSoundMem(PracticeIntro)) {
				PlaySoundMem(PracticeMain, DX_PLAYTYPE_LOOP);
				Loopflag = 1;
			}
			break;
		}
		ScreenFlip();
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			if (Pause(UtikomiMusic)) {
				return 0;
			}
		}
		if (Click() && frame > 60 && i == 0 && Clapflag == 0 && !Clickflag) {
			ClickCount++;
			if (ClickCount >= 9) { Clickflag = 1; }
			PlaySoundMem(clickSE, DX_PLAYTYPE_NORMAL);
			frame = 0;
		}
		if (CheckHitKey(KEY_INPUT_S)) {
			StopSoundMem(Clap);
			StopSoundMem(PracticeIntro);
			StopSoundMem(PracticeMain);
			return 1;
		}
		frame++;
		ClsDrawScreen();
	}

	return 0;
}

int UtikomiGame()
{
	int timingcount = 0;	// �^�C�~���O�c���p�̃J�E���^
	int judgecount = 0;	// ����p�̃J�E���^
	int EndFlag = 1;	// Game���I���������ǂ���
	int EndCount = 0;	// Game�̏I������̂��߂̃J�E���^
	int frame = 0;		// Game�J�n���_����̌o�߃t���[����
	bool onClick = false;	// ���N���b�N���Ă��邩�ǂ���
	bool Clickflag = false;		// �N���b�N��w�𗣂�����
	int Playercount = 0;	// �n���}�[�̏�ԗp�ϐ�
	bool playflag = false;	// �n���}�[�𑀍�\���ǂ���
	int objectx[50];	// �B��x���W�̔z��
	int objecty[50];	// �B��y���W�̔z��
	int objectstate[50] = { 0 };	// �B�̏�Ԃ̔z��
	int objectcount = 0;	// ������B�̐�
	int objectnowx = -100;	// ���̓B�̈ʒu
	int hitcount = 0;	// �ł����B�̐�
	int suny = 0;	// ���z��y���W
	int sunstate = 0;	// ���z�̏��
	int suncount = 0;	// �j�A�~�X���̕\��ύX�b���J�E���^
	LONGLONG nowtime;	// �����J�n���_�̎���(�}�C�N���b)
	LONGLONG fpschecktime;	// �����I�����_�̎���(�}�C�N���b)
	int playerx = -740;	// player�̏���x���W

	DrawExtendGraph(0, 0, 959, 499, GameScene, false);
	DrawGraph(800, 0, Sun[0], true);
	ScreenFlip();
	ClsDrawScreen();
	WaitTimer(1000);
	PlaySoundMem(GameBGM, DX_PLAYTYPE_BACK);
	while (EndFlag) {
		nowtime = GetNowHiPerformanceCount();	// �����J�n���_�̎���
		DrawExtendGraph(0, 0, 959, 499, GameScene, false);

		if (Click()) {	// �N���b�N�ƒ������̔���
			if (!Clickflag) {
				onClick = true;
				Clickflag = true;
			}
			else {
				onClick = false;
			}
		}
		else {
			onClick = false;
			Clickflag = false;
		}

		if (onClick) {	// �N���b�N���ꂽ�Ƃ�
			if (true) {
				Playercount = 1;
				PlaySoundMem(NotHitSE, DX_PLAYTYPE_BACK);
				while (timing[judgecount] + 250 < frame) {	// �B��ʂ�߂��Ă�����
					judgecount++;
					hitcount++;
				}
				if (timing[judgecount] + 235 <= frame && frame <= timing[judgecount] + 245) {	// �B��@������
					PlaySoundMem(HitSE, DX_PLAYTYPE_BACK);
					objectstate[hitcount] = 3;
					hitcount++;
					judgecount++;
				}
				else if (timing[judgecount] + 230 <= frame && frame <= timing[judgecount] + 250) {	// �j�A�~�X
					PlaySoundMem(MissSE, DX_PLAYTYPE_BACK);
					objectstate[hitcount] = 2;
					hitcount++;
					judgecount++;
					sunstate = 1;
					suncount = 1;
				}
			}
		}
		else if (Playercount > 6) {
			Playercount = 0;
		}
		else if(Playercount > 0){
			Playercount++;
		}

		if (frame >= 480) {		// ���W�̌v�Z
			if (frame / 240 % 2 == 0) {
				if (playerx > -20) {
					playerx -= 200;
					if (playerx <= 100) {
						playerx = -736;
					}
				}
				else {
					playerx += 3;
				}
				playflag = false;
				objectnowx = frame % 240 * 3 + 155;
			}
			else {
				playerx = frame % 240 * 3 - 20;
				playflag = true;
				objectnowx = -100;
				if (frame % 240 > 235) {	// �B�̕ЂÂ�
					for (int i = 0; i < objectcount; i++) {
						objectx[i] -= 200;
					}
				}
			}
		}

		if (frame == timing[timingcount]) {		// �B�̔���
			objectstate[objectcount] = 0;
			objectx[objectcount] = objectnowx;
			objecty[objectcount] = 0;
			objectcount++;
			timingcount++;
		}

		if (frame % 480 == 0) {		// ��ʏ�̓B�ƃ^�C�~���O����̃��Z�b�g
			objectcount = 0;
			hitcount = 0;
		}

		if (frame % 30 < 5) {	// ���z��y���W�ύX
			suny = 10;
		}
		else {
			suny = 0;
		}

		if (suncount > 15) {	// �~�X�����Ƃ��̑��z�̋���
			suncount = 0;
			sunstate = 0;
		}
		else if(suncount > 0){
			suncount++;
		}

		DrawGraph(800, suny, Sun[sunstate], true);	// ���z�̕`��

		for (int i = 0; i < objectcount; i++) {
			if (objectstate[i] == 0) {
				if (objecty[i] == 0) {
					objecty[i] = 102;
				}
				else if (objecty[i] = 102) {
					objecty[i] = 204;
					objectstate[i] = 1;
					PlaySoundMem(HitSE, DX_PLAYTYPE_BACK);
				}
			}
			DrawGraph(objectx[i], objecty[i], Object[objectstate[i]], true);	// �B�̕`��
		}

		DrawGraph(playerx, 50, Player[Playercount], true);	// �n���}�[�̕`��

		if (!CheckSoundMem(GameBGM)) {		// �I������(BGM�I������̌o�߃t���[��)
			EndCount++;
			if (EndCount >= 120) {
				EndFlag = 0;
			}
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {	// �|�[�Y����
			if (Pause(UtikomiMusic)) {
				return 0;
			}
		}

		fpschecktime = GetNowHiPerformanceCount();	// �����I�����_�̎���

		if (fpschecktime - nowtime < 16667) {
			WaitTimer((16667 - (fpschecktime - nowtime)) / 1000);	// fps�̒���
		}

		frame++;
		ScreenFlip();
		ClsDrawScreen();
	}
	return 0;
}

void UtikomiDelete()
{
	DeleteSoundMem(GameBGM);
	for (int i = 0; i < 13; i++) {
		DeleteGraph(Player[i]);
	}
}

int Utikomi()
{
	int result = 0;
	UtikomiInit();
	/*if (UtikomiPractice()) {
		UtikomiGame();
	}*/
	result = UtikomiGame();
	UtikomiDelete();
	return result;
	
}
