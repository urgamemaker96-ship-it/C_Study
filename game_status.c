#include "game_status.h"
#include "select.h"
#include "Struct.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void LevelUpRule(damagochi* target)
{
	if (target->exp >= 100 * target->currentlevel * 1.2)
	{
		(target->currentlevel)++; //*(currentlevel)++ 이렇게해서 포인터가 가르키는 값을 증가시켜야 되는데 포인터 값 자체를 증가시킴 -> 오류수정
		target->exp = 0; //포인터로 참조한 변수의값을 0으로 초기화해줌
		target->gochiattack += 10; //포인터로 참조한 변수의값을 10씩 증감해줌
		printf("\n 레벨 업! 현재 레벨: %d\n", target->currentlevel);
		printf("공격력이 %d로 증가했습니다!\n", target->gochiattack);
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
		return 1; // 게임 종료
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

	return 0;
}





void Action(int num1, int* health, int* Maxhealth, int* stress, int* mana, int* poo, int* hungry, int* gochiattack, int* exp, int* rewardgold, int* currentlevel, char* damaname, char* enemyname)
{	//전부 이중포인터 문제 때문에 파라미터변수 앞에 &안달아준거다.
	switch (num1)
	{
	case 1:
		SelectSleep(health, Maxhealth, stress, mana, damaname);
		break;
	case 2:
		SelectPoop(poo, damaname);
		break;
	case 3:
		SelectEat(hungry, poo, damaname);
		break;
	case 4:
		SelectWalk(health, mana, gochiattack, exp, rewardgold, stress, damaname, enemyname);
		break;
	case 5:
		SelectTug(health, mana, gochiattack, exp, rewardgold, stress, damaname, enemyname);
		break;
	case 6:
		SelectShop(rewardgold, Maxhealth, gochiattack, currentlevel);
		break;
	case 7:
		SelectGuide(damaname);
		break;
	}
}
