#pragma once
int UserInput();
void JustPrint(char*);
int Percent(int);
char* InputName_Malloc();
int SelectDamagochiType();
void TakeDamage(int, int*); // 처음파라메터 매겨변수 포인터로 안받음
int GetSubstractResultOrZero(int, int);
int GetAddResultOrZero(int num1, int num2, int max);