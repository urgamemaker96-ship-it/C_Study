#include "game_status.h"
#include "select.h"
#include "Struct.h"
#include "util.h"
#include "show.h"
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include <stdio.h>
#include <stdbool.h> // bool 타입 써줄려면 헤더파일 추가해줘야됨

void LevelUpRule(damagochi* target,bool forceLevelUp) // bool 타입은 기본적으로 파라메터에 false 적용시켜놔야됨
{
	if (forceLevelUp ||target->exp >= 100 * target->currentlevel * 1.2)
	{
		(target->currentlevel)++; //*(currentlevel)++ 이렇게해서 포인터가 가르키는 값을 증가시켜야 되는데 포인터 값 자체를 증가시킴 -> 오류수정
		target->exp = 0; //포인터로 참조한 변수의값을 0으로 초기화해줌
		
		target->skillpoint++;
		printf("스킬 포인트 1개를 얻었습니다! (현재 %d개)\n", target->skillpoint);

		// 레벨업 하면 동시에 스킬 강화 선택지 제공 
		printf("스킬을 강화하시겠습니까? (1: 예, 0: 아니오): ");
		int choice;
		scanf_s("%d", &choice);

		if (choice == 1) {
			
			UpgradeSkill(target);
		}

		// 캐릭터 이름에 따라 다른 능력치 증가
		if (strcmp(target->damaname, "파이리") == 0) {
			// 파이리: 공격력 성장
			target->gochiattack += 15;
			printf("\n 레벨 업! 현재 레벨: %d\n", target->currentlevel);
			printf("공격력이 크게 증가하여 %d로 증가했습니다!\n", target->gochiattack);

		}
		else if (strcmp(target->damaname, "꼬북이") == 0) {
			// 꼬북이: 마나 성장
			target->gochiattack += 10;
			target->mana += 50;
			printf("\n 레벨 업! 현재 레벨: %d\n", target->currentlevel);
			printf("공격력이 %d, 마나가 %d로 증가했습니다!\n", target->gochiattack, target->mana);

		}
		else if (strcmp(target->damaname, "이상해씨") == 0) {
			// 이상해씨: 최대체력 성장
			target->gochiattack += 10;
			target->Maxhealth += 50;
			printf("\n 레벨 업! 현재 레벨: %d\n", target->currentlevel);
			printf("공격력이 %d, 최대체력이 %d로 증가했습니다!\n", target->gochiattack, target->Maxhealth);

		}
		else {
			// 기본타입 -> 꼬북이, 이상해씨, 파이리 이름이 아니면 기본으로 나옴
			target->gochiattack += 10;
			printf("\n 레벨 업! 현재 레벨: %d\n", target->currentlevel);
			printf("공격력이 %d로 증가했습니다!\n", target->gochiattack);
		}
	}

}


void Init()
{
	// rand() 초기화는 한 번만!
	srand((unsigned int)time(NULL)); // 여러번 돌릴 필요없다, 프로그램 실행시 한번만 초기화 해줘도됨
}

int IsGameOver(damagochi* damagochi)
{
	//배변지수가 100을 달성 시 게임오버 상태 -> break를 함수 내에서 처리하지 못할것 같아 남겨둠
	if (damagochi->poo >= 100 || damagochi->stress >= 100)
	{
		printf("%s가 병에 걸렸습니다.\n", damagochi->damaname);
		printf("게임이 종료되었습니다.\n");
		return 1; // 게임 종료 -> 이거 삭제해 버리면 죽어도 계속 다마고치로 진행됨
		
	}
	//승리 조건달아주기 -> break를 함수 내에서 처리하지 못할것 같아 남겨둠
	if (damagochi->currentlevel == 10)
	{
		printf("%s가 완전히 성장했습니다!!\n", damagochi->damaname);
		printf("게임이 종료되었습니다.\n");
		return 1;  // 게임 종료
	}
	// 다마고치 사망
	if (damagochi->health <= 0)
	{
		printf("게임이 종료되었습니다.\n");
		return 1; // 게임 종료
	}

	return 0; // 위에 사망조건 3개 가 아니면 그냥 함수 종료
}





void Action(int num1, damagochi* target, damagochi* enemy, capture* collection)
{	//전부 이중포인터 문제 때문에 파라미터변수 앞에 &안달아준거다.
	switch (num1)
	{
	case 1:
		SelectSleep(target);
		break;
	case 2:
		SelectPoop(target);
		break;
	case 3:
		SelectEat(target);
		break;
	case 4:
		SelectWalk(target, enemy,collection);
		break;
	case 5:
		SelectTug(target, enemy, collection);
		break;
	case 6:
		SelectShop(target);
		break;
	case 7:
		SelectGuide(target);
		break;
	case 8: //스킬강화
		UpgradeSkill(target);
		break;
	case 9: // 스킬정보
		ShowSkillInfo(target);
		break;
	case 10:  // 이름 변경 서브 메뉴
	{
		int renameChoice;
		ShowRenameMenu();
		scanf_s("%d", &renameChoice);

		switch (renameChoice) {
		case 1:
			RenameCharacter(target, true);  // 다마고치 이름 변경
			break;
		case 2:
			RenameCharacter(target, false); // 주인 이름 변경
			break;
		case 0:
			printf("이름 변경을 취소했습니다.\n");
			break;
		}
		
	}
	break;
	case 11: // 포획 관리 메뉴
	{
		int captureChoice;
		ShowCaptureMenu();
		scanf_s("%d", &captureChoice);

		switch (captureChoice) {
		case 1:
			// 포획된 다마고치 목록 보기
			HandleCaptureMenu(&target, collection, true);
			break;
		case 2:
			// 다마고치 교체하기
			HandleCaptureMenu(&target, collection, false);
			break;
		case 3:
			// 포획된 다마고치 상세 정보 보기
			ShowDetailedCaptureInfo(collection);
			break;
		case 0:
			printf("포획 관리 메뉴를 종료합니다.\n");
			break;
		}
	}
	break;
	}
}
