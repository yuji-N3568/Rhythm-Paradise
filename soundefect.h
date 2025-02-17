#ifndef DEF_SE_H
#define DEF_SE_H

__declspec(selectany) int PauseSE;
__declspec(selectany) int PracticeIntro;
__declspec(selectany) int PracticeMain;
__declspec(selectany) int clickSE;
__declspec(selectany) int moveSE;
__declspec(selectany) int decideSE;
__declspec(selectany) int Clap;
__declspec(selectany) int HitSE;
__declspec(selectany) int NotHitSE;
__declspec(selectany) int MissSE;

void SoundInit();

void SoundDelete();

#endif // !DEF_SE_H