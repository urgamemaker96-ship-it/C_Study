#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "show.h"
#include "select.h"
#include "util.h"
#include "game_status.h"
#include "Struct.h"

int main(void)
{	
	damagochi mainDamagochi = { 100, 100, 100, 50, 40, 50, 40, 0, 1, "" };
		
	int rewardgold = 8000; // 상점 시스템 만들기 위해서 선언한 변수
	int mainInput;
	char name[20]; // 유저이름 받기위한 초기값 설정
	char enemyname[20] = "오후의태양단";

	// 게임 초기화
	Init();
	UserNameInput(name,sizeof(name)); //유저 이름을 생성한다
	DamagochiNameInput(mainDamagochi.damaname, sizeof(mainDamagochi.damaname));//다마고치 이름을 생성한다

	while (!IsGameOver(&mainDamagochi.poo, &mainDamagochi.stress, &mainDamagochi.currentlevel, &mainDamagochi.health, mainDamagochi.damaname)) // 반복문 지속
	{
		//레벨업 상태 체크
		LevelUpRule(&mainDamagochi);
		
		// 상태 정보 출력
		ShowStatus(&mainDamagochi.health, &mainDamagochi.mana, &mainDamagochi.hungry, &mainDamagochi.poo, &mainDamagochi.stress, &mainDamagochi.exp, &rewardgold,name, mainDamagochi.damaname);

		// 유저 입력 메뉴 출력
		ShowChoice();

		// 유저 입력 대기
		mainInput = UserInput();

		// 유저 입력에 따른 액션		
		Action(mainInput,&mainDamagochi.health, &mainDamagochi.Maxhealth, &mainDamagochi.stress, &mainDamagochi.mana, &mainDamagochi.poo, &mainDamagochi.hungry, &mainDamagochi.gochiattack, &mainDamagochi.exp, &rewardgold, &mainDamagochi.currentlevel, mainDamagochi.damaname, enemyname);
	}
}