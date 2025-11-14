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

void RenameCharacter(damagochi*, bool);//다마고치랑 주인 이름 메모리 재할당 해주는 함수
void FreeDamagochiNames(damagochi*);  // 이름 메모리 해제 함수
char* AllocateAndCopyName(char*);  // 메모리 할당 및 복사 함수 -> 이름전달하는거 간편화 시켜주기 위해 동적할당으로만듬