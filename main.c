#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "show.h"
#include "select.h"
#include "util.h"
#include "game_status.h"

int main(void)
{	
	//지역변수들 초기값 설정
	int mana = 100; // 마나, 스킬 함수만들시 다마고치한테 필요
	int Maxhealth = 100; // 상점구현 시 필요해서 숫자 증감이 아니라 새로운 변수선언함
	int health = 100;  // 초기값 선언
	int hungry = 50;  // 초기값 선언
	int gochiattack = 40; //적 어카운팅 시스템 만들다 보니 필요한 변수라서 초기화해줌
	int poo = 50; // 배변활동정도
	int stress = 40; // 스트레스 지수, 사망판정 위해 변수 선언
	int exp = 0; // 레벨업 시스템 만들다 보니 필요한 변수라서 초기화 해줌
	int currentlevel = 1; // 레벨업 시스템 만들다 보니 필요한 변수라서 초기화 해줌
	int rewardgold = 8000; // 상점 시스템 만들기 위해서 선언한 변수

	int mainInput;
	char name[20]; // 유저이름 받기위한 초기값 설정
	char damaname[20]; // 다마고치 이름 받기위한 초기값 설정
	char enemyname[20] = "오후의태양단";

	// 게임 초기화
	Init();
	UserNameInput(name,sizeof(name)); //유저 이름을 생성한다
	DamagochiNameInput(damaname, sizeof(damaname));//다마고치 이름을 생성한다

	while (!IsGameOver(&poo, &stress, &currentlevel, &health, damaname)) // 반복문 지속
	{
		//레벨업 상태 체크
		LevelUpRule(&exp, &currentlevel, &gochiattack);
		
		// 상태 정보 출력
		ShowStatus(&health, &mana, &hungry, &poo, &stress, &exp, &rewardgold,name,damaname);

		// 유저 입력 메뉴 출력
		ShowChoice();

		// 유저 입력 대기
		mainInput = UserInput();

		// 유저 입력에 따른 액션		
		Action(mainInput,&health, &Maxhealth, &stress, &mana, &poo, &hungry, &gochiattack, &exp, &rewardgold, &currentlevel,damaname, enemyname);
	}
}