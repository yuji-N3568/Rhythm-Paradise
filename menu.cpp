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
	MenuBGM = LoadSoundMem("music/�p�Y���C��.mp3");
	ChangeVolumeSoundMem(75, MenuBGM);
	MenuMusic[0] = MenuBGM;
	MenuMusic[1] = clickSE;

	int count = 0;
	char icontxt[100];	// �A�C�R���̃p�X���i�[����z��
	fopen_s(&fp, "data/icon.txt", "r");
	while (fscanf_s(fp, "%s", icontxt, 100) == 1) {
		icon[count][0] = LoadGraph("image/hatena_icon.png");	// ������Ԃ́u�H�v
		icon[count][1] = LoadGraph(icontxt);	// icon.txt����A�C�R���̃p�X�������Ă��đ��
		count++;
	}
	fclose(fp);

	int save = 0;
	count = 0;
	fopen_s(&fp, "data/save.dat", "r");	// �Z�[�u�f�[�^�̕���
	while (fscanf_s(fp, "%d", &save) == 1) {
		if (save == 3) {
			iconstate[count] = 2;	// ���уO���[�h
		}
		else {
			iconstate[count] = 1;	// ����ȊO
		}
	}
	fclose(fp);
	
	return true;
}

int menu() {
	bool initflag = false;
	int i;	// x���W�ύX�p�̕ϐ�
	int j;	// ���Ԗڂ̃A�C�R����`�悷�邩�̕ϐ�
	int y;	// �I��ł���Q�[����h�炷���߂̕ϐ�
	int selected = 0;	// ���I�΂�Ă���Q�[���̏���
	int holdleft = 0;	// ����������
	int holdright = 0;
	bool holdleftflag = true;	// ����
	bool holdrightflag = true;	// ����
	int frame = 0;	// menu�ɓ����Ă���̌o�߃t���[����
	int result = 0;	// �Q�[���̕]��

	if (!initflag) { initflag = menuinit(); }	// ������
	PlaySoundMem(MenuBGM, DX_PLAYTYPE_LOOP);

	while (1) {
		DrawExtendGraph(0, 0, 959, 499, MenuScene, false);

		if (CheckSoundMem(MenuBGM) == 0) {
			PlaySoundMem(MenuBGM, DX_PLAYTYPE_LOOP);
		}

		if (CheckHitKey(KEY_INPUT_LEFT)) {	// ���Ɉړ�
			if (selected != 0 && holdleftflag) {	// ���[���ǂ����A���������ǂ���
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

		if (CheckHitKey(KEY_INPUT_RIGHT)) {	// �E�Ɉړ�
			if (selected != 49 && holdrightflag) {	// �E�[���ǂ����A���������ǂ���
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
					DrawGraph(i, 350 - y * y / 30 , icon[j][iconstate[j]], true);	// �I�𒆂̃Q�[���̂ݓ�����
				}
				else {
					DrawGraph(i, 350, icon[j][iconstate[j]], true);	// ���̑��̃Q�[���A�C�R���̕`��
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

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {	// �|�[�Y����
			if (Pause(MenuMusic)) {
				return 0;
			}
		}
		ScreenFlip();
		ClsDrawScreen();
		frame++;
	}
}