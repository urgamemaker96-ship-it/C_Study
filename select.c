#include "select.h"
#include "show.h"
#include "util.h"
#include <stdio.h>


void SelectSleep(int* health, int* Maxhealth, int* stress, int* mana, char* damaname)
{
	if (*health >= *Maxhealth)
	{
		printf("더이상 잘 필요가 없습니다.\n");
		*stress += 10;
	}
	else
	{
		*health += 10;
		printf("%s의 체력이 %d 증가했습니다\n", damaname, 10);

	}

	if (*mana >= 100)
	{
		printf("더이상 마나가 회복될 수 없습니다.\n");
		*stress += 10;
	}
	else
	{
		*mana += 10;
		printf("%s의 마나가 %d 증가했습니다\n", damaname, 10);
	}
}

void SelectPoop(int* poo, char* damaname)
{
	*poo = 0;
	printf("%s의 배변활동지수가 %d 되었습니다\n", damaname, *poo);
}

void SelectEat(int* hungry, int* poo, char* damaname)
{
	if (*hungry >= 200)
	{
		printf("더이상 먹을 필요가 없습니다.\n");
	}
	else
	{
		*hungry += 20;
		*poo += 20;
		printf("%s의 포만감이 %d 증가했습니다\n", damaname, 20);
	}
}

void SelectWalk(int* health, int* mana, int* gochiattack, int* exp, int* rewardgold, int* stress, char* damaname, char* enemyname)
{
	int userInput;
	if (Percent(50)) //0~49니깐 50퍼센트다
	{
		printf("===================================================\n");
		printf("산책 중 %s이 나타났습니다!!.\n", enemyname);

		// 전투 변수 초기화
		int turnon = 1; // while 문 통제 위한 변수선언
		int battle_enemyhealth = 100;  // 적 체력변수 선언
		int battle_enemyattack = 20; // 적 공격력 변수선언

		//while 문 안에 while 문 만들어서 통제할려면 변수가 필요했다
		while (turnon)
		{
			//1. battle_enemyhealth는 따로 포인터 변수로 안받아줘도됨, 이미 위쪽 블록에 선언됨
			//2. ShowBattle(변수,&변수,&변수) 꼴로 받아야 되는데 그럴 경우 health, mana 의 메모리 위치(주소) 값이나옴
			//3-1 이미 SelectWalk 함수 에서 체력과 마나를 포인터 값으로 선언해줘서 
			//3-2 내가 여기 ShowBattle 함수에 또 체력과 마나 포인터 &변수로 써버리면 이중포인터다 그래서 그냥 포인터인 mana, health 써주는거다
			ShowBattle(battle_enemyhealth, health, mana); //&health, &mana 안써주는데는 이유가 있다.
			scanf_s("%d", &userInput);

			switch (userInput) // 분기문 안에 분기문 만들 수 있었다!!!
			{
			case 1: // 공격
				battle_enemyhealth = TakeDamage(*gochiattack, battle_enemyhealth); //이중포인터 문제 생겨서 TakeDamage 함수와 ShowDamage 함수는 포인터 타입으로 선언안함
				printf("%s에게 %d 만큼 피해를 줬습니다!\n", enemyname, *gochiattack);

				if (battle_enemyhealth <= 0) // 적 사망조건
				{
					printf("%s이 사망했습니다!!.\n", enemyname);
					turnon = 0;  // 내부 while 루프 탈출
					*exp += 50;   // 경험치 획득
					printf("경험치를 %d 얻었습니다!\n", 50);
					*rewardgold += 200;
					printf("골드를 %d 얻었습니다!\n", 200);
					*stress -= 10;
					printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
				}
				break;

			case 2: // 적 사망 조건을 스킬에도 적용 해줘야 적 체력 -되면 사망 판정됨
				printf("%s가 스킬을 사용했습니다!.\n", damaname);
				if (*mana < 50) //0으로 하니 타이밍 안맞아서 50으로 맞춤
				{
					printf("마나가 없어 스킬을 사용하지 못합니다.!.\n");

				}
				else
				{
					*mana -= 50;


					int totalDamage = *health + *gochiattack; // ShowDamage 함수 자료형에 맞는 파라미터 사용 위해서 새로운 변수 맞춰줌
					battle_enemyhealth = TakeDamage(totalDamage, battle_enemyhealth);
					ShowDamage(damaname, enemyname, totalDamage); //damaname 은 이미 포인터 타입이라 그냥 변수명 써도됨
					//반드시 값을 초기화 해줘야 적 체력이 깎아진다

				}
				if (battle_enemyhealth <= 0)
				{
					printf("%s이 사망했습니다!!.\n", enemyname);
					turnon = 0;  // 내부 while 루프 탈출
					*exp += 50;   // 경험치 획득
					printf("경험치를 %d 얻었습니다!\n", 50);
					*rewardgold += 200;
					printf("골드를 %d 얻었습니다!\n", 200);
					*stress -= 10;
					printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
				}

				break;

			case 3: // 도망
				printf("도망쳤습니다!\n");
				*stress += 10;
				turnon = 0;  // 내부 while 루프 탈출
				break;


			}

			//적 체력 존재하면 공격함
			if (battle_enemyhealth > 0)
			{
				*health -= battle_enemyattack;
				printf("%s이 당신을 공격했습니다! 체력이 %d 감소했습니다.\n", enemyname, battle_enemyattack);


				if (Percent(30)) // 적스킬은 30퍼센트로 스킬 나감
				{	//TakeDamage 함수는 그냥 단순 계산기다 
					//-> 파라미터 타입에 맞지않는*변수 라고해도 *변수 뜻은 해당 변수의 주소에 있는 값이라는 뜻이다.
					int totalEnemyDagame = battle_enemyhealth + battle_enemyattack;
					*health = TakeDamage(totalEnemyDagame, *health);
					ShowDamage(enemyname, damaname, totalEnemyDagame);
				}
				if (*health <= 0)
				{
					printf("%s가 쓰러졌습니다!\n", damaname);
					turnon = 0;
				}
			}
		}
	}
	else
	{
		if (*stress <= 0)
		{
			*stress = 0;
			printf("더이상 스트레스 지수를 내릴 수 없습니다.\n");
		}
		else
		{
			*stress -= 20;
			printf("스트레스가 산책으로 인해 %d 줄었습니다.\n", 20);
		}
	}
}

void SelectTug(int* health, int* mana, int* gochiattack, int* exp, int* rewardgold, int* stress, char* damaname, char* enemyname)
{
	int userInput;
	if (Percent(60))
	{
		printf("===================================================\n");
		printf("터그놀이 중 %s이 나타났습니다!!.\n", enemyname);

		// while 문 안에 또 while 문 만들어야 전투 상태 창 만들 수 있음
		int turnon = 1; // while 문 안에 while 문 통제위한 변수선언 및 초기화
		int battle_enemyhealth = 80;  // 산책과 비교해서 체력 낮다
		int battle_enemyattack = 30;   // 

		while (turnon)
		{
			ShowBattle(battle_enemyhealth, health, mana);
			scanf_s("%d", &userInput);

			switch (userInput)
			{
			case 1: // 공격
				battle_enemyhealth = TakeDamage(*gochiattack, battle_enemyhealth);
				printf("%s에게 %d 만큼 피해를 줬습니다!\n", enemyname, *gochiattack);

				if (battle_enemyhealth <= 0)
				{
					printf("%s이 사망했습니다!!.\n", enemyname);
					turnon = 0;  // while 문 속 while 문 탈출하고 일반 while문으로 감
					*exp += 50;
					printf("경험치를 %d 얻었습니다!\n", 50);
					*rewardgold += 200;
					printf("골드를 %d 얻었습니다!\n", 200);
					*stress -= 10;
					printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
				}
				break;

			case 2: // 스킬
				printf("%s가 스킬을 사용했습니다!.\n", damaname);
				if (*mana < 50)
				{
					printf("마나가 없어 스킬을 사용하지 못합니다.!.\n");
				}
				else
				{

					int totalDamage = *health + *gochiattack;
					battle_enemyhealth = TakeDamage(totalDamage, battle_enemyhealth);
					ShowDamage(damaname, enemyname, totalDamage);
					//값 초기화 해줘야지 적 체력 깎인다, 이거 제일 중요함!!

				}
				if (battle_enemyhealth <= 0)
				{
					printf("%s이 사망했습니다!!.\n", enemyname);
					turnon = 0;  // 내부 while 루프 탈출
					*exp += 50;   // 경험치 획득
					printf("경험치를 %d 얻었습니다!\n", 50);
					*rewardgold += 200;
					printf("골드를 %d 얻었습니다!\n", 200);
					*stress -= 10;
					printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
				}



				break;

			case 3: // 도망
				printf("도망쳤습니다!\n");
				*stress += 10;
				turnon = 0;  // while 문 탈출한다. 만약 0으로 값 초기화 안해주면 도망 못하고 계속 진행됨
				break;


			}

			// 적 체력이 존재하면 공격함
			if (battle_enemyhealth > 0)
			{
				*health -= battle_enemyattack;
				printf("%s이 당신을 공격했습니다! 체력이 %d 감소했습니다.\n", enemyname, battle_enemyattack);

				if (Percent(30)) // 적스킬은 30퍼센트로 스킬 나감
				{
					int totalEnemyDagame = battle_enemyhealth + battle_enemyattack;
					*health = TakeDamage(totalEnemyDagame, *health);
					ShowDamage(enemyname, damaname, totalEnemyDagame);
				}
				if (*health <= 0)
				{
					printf("%s가 쓰러졌습니다!\n", damaname);
					turnon = 0;
				}
			}
		}
	}
	else
	{
		if (*stress <= 0)
		{
			*stress = 0;
			printf("더이상 스트레스 지수를 내릴 수 없습니다.\n");
		}
		else
		{
			*stress -= 30;
			printf("스트레스가 터그활동으로 인해 %d 줄었습니다.\n", 30);
		}
	}
}

void SelectShop(int* rewardgold, int* Maxhealth, int* gochiattack, int* currentlevel)
{
	int userInput;

	if (*rewardgold < 200)
	{
		printf("돈이 없어 이용할 수 없습니다!!\n");

	}
	else
	{
		ShowShop();
		//분기문 안에 분기문 만들 수 있다, 입력 받을 변수 num2로 만드려고 했으나 그럴 필요 없어 num1만 씀, 입력받는건 의미가 없다 하나면 충분하다.
		scanf_s("%d", &userInput);
		switch (userInput)
		{
		case 1:
			*rewardgold -= 200;
			*Maxhealth += 100;

			printf("최대체력이 %d 증가하여 %d이 되었습니다.", 100, *Maxhealth);
			break;

		case 2:
			*rewardgold -= 300;
			*gochiattack += 50;
			printf("공격력이 %d 증가하여 %d이 되었습니다.", 50, *gochiattack);
			break;


		case 3:
			*rewardgold -= 400;
			*currentlevel += 1;
			printf("레벨이 %d 증가하여 %d이 되었습니다.", 1, *currentlevel);
			break;
		}
	}


}

void SelectGuide(char* damaname)
{
	printf("%s는 스트레스가 100을 찍거나 배변지수가 100일 경우 사망 그리고 전투 시 체력이 떨어지면 사망합니다.\n", damaname);
	printf("%s는 레벨이 10이되면 최종성장하며 게임이 클리어 됩니다..\n", damaname);
	printf("%s는 불가능한 선택을 할때 ,도망칠때 스트레스를 10씩 받습니다.\n", damaname);
	printf("%s는 잠을 자거나, 적을 쓰러뜨릴 경우 스트레스를 회복합니다 .\n", damaname);
}