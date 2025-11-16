#include <stdio.h>
#include <stdlib.h> // 랜덤함수 헤더
#include <time.h>
#include <string.h> // strcpy를 사용 위한 헤더

#include "show.h"
#include "select.h"
#include "util.h"
#include "game_status.h"
#include "Struct.h"
#include <stdbool.h> // bool 타입 써줄려면 헤더파일 추가해줘야됨

int main(void)
{	// 내가 선택한 다마고치
	damagochi mainDamagochi = { 100, 100, 100, 50, 40, 50, 40, 0, 1, NULL,NULL,1,0};
    damagochi isanghaessi = { 100, 150, 150, 50, 40, 50, 40, 0, 1, NULL,NULL,20,8000 }; // 이상해씨는 체력이 높다-2,3번멤버변수
    damagochi paili = { 100, 100, 100, 50, 60, 50, 40, 0, 1, NULL,NULL,20,8000 }; // 파이리는 공격력이 높다-5번멤버변수
    damagochi kkobugi = { 150, 100, 100, 50, 40, 50, 40, 0, 1, NULL,NULL,20,8000 }; // 꼬북이는 마나가 높다-1번멤버변수

    // 야생 다마고치 생성 (적으로 사용)
    damagochi wild_isanghaessi = { 100, 120, 120, 50, 35, 50, 40, 0, 1, NULL, NULL, 15, 0 };
    damagochi wild_paili = { 100, 90, 90, 50, 45, 50, 40, 0, 1, NULL, NULL, 15, 0 };
    damagochi wild_kkobugi = { 120, 90, 90, 50, 35, 50, 40, 0, 1, NULL, NULL, 15, 0 };

    // 야생 다마고치 이름 설정
    wild_isanghaessi.damaname = AllocateAndCopyName("야생 이상해씨");
    wild_paili.damaname = AllocateAndCopyName("야생 파이리");
    wild_kkobugi.damaname = AllocateAndCopyName("야생 꼬부기");



    // 선택된 다마고치를 가리킬 포인터 -> 처음주소값이 가비지 값으로 설정되어 있을 수 있어서 null값으로 초기화해줌
    damagochi* selectedDamagochi = NULL;



    // 포획 컬렉션 초기화
    capture collection;
    ManageCaptureCollection(&collection, 0, 3); // 0: 초기화, 초기 용량 3


	int mainInput;
    char* userName = NULL; //동적할당 하기 위해선 먼저 NULL값으로 초기화 시켜주는게 중요하다, 포인터에 임의의 주소값이 있어서
    int damaType; // SelectDamagochiType() 함수 처리위한 변수선언 -> 이걸로 분기문 변수도 받음
  
    // 유저 이름 입력
    JustPrint("유저");
    userName = InputName_Malloc();


    // 다마고치 종류 선택
    damaType = SelectDamagochiType();

    // 선택한 다마고치에 따라 포인터 설정
    switch (damaType)
    {
    case 1:
        selectedDamagochi = &mainDamagochi;
        selectedDamagochi->damaname = AllocateAndCopyName("기본형");
        printf("\n기본 다마고치를 선택하셨습니다!\n");
        break;
    case 2:
        selectedDamagochi = &isanghaessi;
        selectedDamagochi->damaname = AllocateAndCopyName("이상해씨");
        printf("\n이상해씨를 선택하셨습니다!\n");
        break;
    case 3:
        selectedDamagochi = &paili;
        selectedDamagochi->damaname = AllocateAndCopyName("파이리");
        printf("\n파이리를 선택하셨습니다!\n");
        break;
    case 4:
        selectedDamagochi = &kkobugi;
        selectedDamagochi->damaname = AllocateAndCopyName("꼬부기");
        printf("\n꼬부기를 선택하셨습니다!\n");
        break;
    }


    // 임시 주인 이름 설정 (동적 할당)
    if (userName != NULL && selectedDamagochi != NULL)
    {
        selectedDamagochi->mastername = AllocateAndCopyName(userName);
    }


    // 선택했으면 해당 다마고치 스킬상태 초기화 해주기
    InitializeSkills(selectedDamagochi, damaType);
    // 야생 다마고치 스킬 초기화
    InitializeSkills(&wild_isanghaessi, 2);
    InitializeSkills(&wild_paili, 3);
    InitializeSkills(&wild_kkobugi, 4);
  
    //임시로 만든 유저 이름 메모리 해제
    if (userName != NULL)
    {
        free(userName);
        userName = NULL;  // 안전을 위해 NULL 설정
    }

    // 게임 초기화 -> 랜덤쓸려고 한번 초기화 해주는거임
    Init();

    // 선택된 다마고치로 게임 진행
    while (!IsGameOver(selectedDamagochi))
    {
        // 상태 정보 출력 (selectedDamagochi 사용) -> 해당 구조체에서 받아와서 전달함
        ShowStatus(selectedDamagochi);

        // 유저 입력 메뉴 출력
        ShowChoice();

        // 유저 입력 대기
        mainInput = UserInput();

        // main.c의 메인 루프 전에 야생 다마고치 배열 생성
        damagochi* wild_enemies[3] = { &wild_isanghaessi, &wild_paili, &wild_kkobugi };

        // 게임 루프 내에서 랜덤 적 선택 수정
        // 랜덤하게 야생 다마고치 선택
        damagochi* randomEnemy = wild_enemies[rand() % 3];
        // 야생 다마고치 체력 초기화 (매 전투마다 풀체력으로)
        randomEnemy->health = randomEnemy->Maxhealth;

        Action(mainInput, selectedDamagochi, randomEnemy, &collection);
        LevelUpRule(selectedDamagochi, false);
    }
    //프로그램 종료 전에 메모리 해제해주기 -> 동적할당을 해줬으면 반드시 내가 해제처리해줘야됨
    FreeDamagochiNames(selectedDamagochi);
    FreeDamagochiNames(&wild_isanghaessi);
    FreeDamagochiNames(&wild_paili);
    FreeDamagochiNames(&wild_kkobugi);
    FreeDamagochiNames(selectedDamagochi);
    ManageCaptureCollection(&collection, 2, 0); // 컬렉션 메모리 해제
}