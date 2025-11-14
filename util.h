#pragma once
#include "Struct.h"
#include <stdbool.h> // bool 타입 써줄려면 헤더파일 추가해줘야됨

int UserInput();
void JustPrint(char*);
int Percent(int);
char* InputName_Malloc();
int SelectDamagochiType();
void TakeDamage(int, int*); // 처음파라메터 매겨변수 포인터로 안받음
int GetSubstractResultOrZero(int, int);
int GetAddResultOrZero(int , int , int );

void InitializeSkills(damagochi* , int );
int CountSkillDamage(damagochi*, int,bool);//불타입으로 현재 데미지 계산 및 레벨업 후 계산 동시처리해줌 -> 중복함수 처리방지위해서
