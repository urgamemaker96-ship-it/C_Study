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
	damagochi mainDamagochi = { 100, 100, 100, 50, 40, 50, 40, 0, 1, "",""};
   

	int rewardgold = 8000; // 상점 시스템 만들기 위해서 선언한 변수
	int mainInput;
	char enemyname[20] = "오후의태양단";
    char* userName = NULL; //동적할당 하기 위해선 먼저 NULL값으로 초기화 시켜주는게 중요하다, 포인터에 임의의 주소값이 있어서
    char* damaName = NULL; //동적할당 하기 위해선 먼저 NULL값으로 초기화 시켜주는게 중요하다, 포인터에 임의의 주소값이 있어서

  
    // 게임 초기화
    Init();

    // 유저 이름 입력
    JustPrint("유저");
    userName = InputName_Malloc();
    // 다마고치 이름 입력  
    JustPrint("다마고치");
    damaName = InputName_Malloc();

    // 구조체에 다마고치이름 설정 후 복사해 오기
    if (damaName != NULL) {
        
        strcpy(mainDamagochi.damaname, damaName);
    }

    // 구조체에 주인이름 설정 후 복사해 오기
    if (userName != NULL) {
       
        strcpy(mainDamagochi.mastername, userName);
    }

    // 메모리 정리-> 동적메모리는 할당해주고 반드시 free로 해체해줘야 낭비가 안됨
    if (userName != NULL) {
        free(userName);
        userName = NULL;  // 안전을 위해 NULL 설정
    }
    if (damaName != NULL) {
        free(damaName);
        damaName = NULL;  // 안전을 위해 NULL 설정
    }


	while (!IsGameOver(&mainDamagochi)) // 반복문 지속
	{
		//레벨업 상태 체크
		LevelUpRule(&mainDamagochi);
		
		// 상태 정보 출력
		ShowStatus(&mainDamagochi.health, &mainDamagochi.mana, &mainDamagochi.hungry, &mainDamagochi.poo, &mainDamagochi.stress, &mainDamagochi.exp, &rewardgold, mainDamagochi.mastername, mainDamagochi.damaname);

		// 유저 입력 메뉴 출력
		ShowChoice();

		// 유저 입력 대기
		mainInput = UserInput();

		// 유저 입력에 따른 액션		
		Action(mainInput,&mainDamagochi.health, &mainDamagochi.Maxhealth, &mainDamagochi.stress, &mainDamagochi.mana, &mainDamagochi.poo, &mainDamagochi.hungry, &mainDamagochi.gochiattack, &mainDamagochi.exp, &rewardgold, &mainDamagochi.currentlevel, mainDamagochi.damaname, enemyname);
	}
}