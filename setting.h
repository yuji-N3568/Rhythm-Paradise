#pragma once

extern const __declspec(selectany) int SCREEN_X = 960, SCREEN_Y = 500;

__declspec(selectany) int PracticeFont;
__declspec(selectany) int GameBGM;
__declspec(selectany) int GameScene;
__declspec(selectany) int Player[100];
__declspec(selectany) int Object[100];
__declspec(selectany) int UsingMusic[];
__declspec(selectany) int timing[200];
__declspec(selectany) FILE* fp;

void FeedOut();

void FeedIn(int scene);

void FontInit();

void StopMusic(int UsingMusic[10]);

int Click(void);