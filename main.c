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
	damagochi mainDamagochi = { 100, 100, 100, 50, 40, 50, 40, 0, 1, "기본형","",1,0};
    damagochi isanghaessi = { 100, 150, 150, 50, 40, 50, 40, 0, 1, "이상해씨","",20,8000 }; // 이상해씨는 체력이 높다-2,3번멤버변수
    damagochi paili = { 100, 100, 100, 50, 60, 50, 40, 0, 1, "파이리","",20,8000 }; // 파이리는 공격력이 높다-5번멤버변수
    damagochi kkobugi = { 150, 100, 100, 50, 40, 50, 40, 0, 1, "꼬북이","",20,8000 }; // 꼬북이는 마나가 높다-1번멤버변수

    // 선택된 다마고치를 가리킬 포인터 -> 처음주소값이 가비지 값으로 설정되어 있을 수 있어서 null값으로 초기화해줌
    damagochi* selectedDamagochi = NULL;


	int mainInput;
	char enemyname[20] = "오후의태양단";
    char* userName = NULL; //동적할당 하기 위해선 먼저 NULL값으로 초기화 시켜주는게 중요하다, 포인터에 임의의 주소값이 있어서
    char* damaName = NULL; //동적할당 하기 위해선 먼저 NULL값으로 초기화 시켜주는게 중요하다, 포인터에 임의의 주소값이 있어서
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
        printf("\n기본 다마고치를 선택하셨습니다!\n");
        break;
    case 2:
        selectedDamagochi = &isanghaessi;
        printf("\n이상해씨를 선택하셨습니다!\n");
        break;
    case 3:
        selectedDamagochi = &paili;
        printf("\n파이리를 선택하셨습니다!\n");
        break;
    case 4:
        selectedDamagochi = &kkobugi;
        printf("\n꼬부기를 선택하셨습니다!\n");
        break;
    }
    

   

    // 구조체에 주인이름 설정 후 복사해 오기
    if (userName != NULL && selectedDamagochi != NULL) { //선택한 다마고치의 주소랑 입력한유저네임의 주소가 비어있지 않을때
        strcpy_s(selectedDamagochi->mastername, sizeof(selectedDamagochi->mastername), userName);  //strcpy_s 로 처리해야 오류안뜸
    }

  
    // 메모리 정리-> 동적메모리는 할당해주고 반드시 free로 해체해줘야 낭비가 안됨, 스택메모리는 자동삭제되나 힙은 수동임
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
}