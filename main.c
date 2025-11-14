#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // strcpy를 사용 위한 헤더

#include "show.h"
#include "select.h"
#include "util.h"
#include "game_status.h"
#include "Struct.h"
#include <stdbool.h> // bool 타입 써줄려면 헤더파일 추가해줘야됨

int main(void)
{	
	damagochi mainDamagochi = { 100, 100, 100, 50, 40, 50, 40, 0, 1, NULL,NULL,1,0};
    damagochi isanghaessi = { 100, 150, 150, 50, 40, 50, 40, 0, 1, NULL,NULL,20,8000 }; // 이상해씨는 체력이 높다-2,3번멤버변수
    damagochi paili = { 100, 100, 100, 50, 60, 50, 40, 0, 1, NULL,NULL,20,8000 }; // 파이리는 공격력이 높다-5번멤버변수
    damagochi kkobugi = { 150, 100, 100, 50, 40, 50, 40, 0, 1, NULL,NULL,20,8000 }; // 꼬북이는 마나가 높다-1번멤버변수

    // 선택된 다마고치를 가리킬 포인터 -> 처음주소값이 가비지 값으로 설정되어 있을 수 있어서 null값으로 초기화해줌
    damagochi* selectedDamagochi = NULL;


	int mainInput;
	char enemyname[20] = "오후의태양단";
    char* userName = NULL; //동적할당 하기 위해선 먼저 NULL값으로 초기화 시켜주는게 중요하다, 포인터에 임의의 주소값이 있어서
    int damaType; // SelectDamagochiType() 함수 처리위한 변수선언 -> 이걸로 분기문 변수도 받음
  
    // 유저 이름 입력
    JustPrint("유저");
    userName = InputName_Malloc();


    // 다마고치 종류 선택
    damaType = SelectDamagochiType();

    // 선택한 다마고치에 따라 포인터 설정
    switch (damaType) {
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
    if (userName != NULL && selectedDamagochi != NULL) {
        selectedDamagochi->mastername = AllocateAndCopyName(userName);
    }


    // 선택했으면 해당 다마고치 스킬상태 초기화 해주기
    InitializeSkills(selectedDamagochi, damaType);
   
  
    //임시로 만든 유저 이름 메모리 해제
    if (userName != NULL) {
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

        // 유저 입력에 따른 액션 (selectedDamagochi 사용) -> 전부 구조체에서 받아옴
        Action(mainInput, selectedDamagochi, enemyname);

        // 레벨업 상태 체크 (selectedDamagochi 사용) -> 구조체에서 받아온 레벨이랑 경험치 이용함
        LevelUpRule(selectedDamagochi,false);
    }
    //프로그램 종료 전에 메모리 해제해주기 -> 동적할당을 해줬으면 반드시 내가 해제처리해줘야됨
    FreeDamagochiNames(selectedDamagochi);
}