#pragma once
#include"Struct.h"
#include <stdbool.h> // bool 타입 써줄려면 헤더파일 추가해줘야됨
void Init();
int IsGameOver(damagochi*);
void Action(int, damagochi*, damagochi*,capture*);
void LevelUpRule(damagochi*,bool);
