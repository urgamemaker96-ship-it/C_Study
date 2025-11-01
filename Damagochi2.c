#include <stdio.h>
#include <stdlib.h> // rand()함수 포함 라이브러리
#include <time.h> // time()함수 포함 라이브러리


//함수 선언들 main 함수 위에서 함수 정의 선언해줬기 때문에 함수선언 따로 할 필요없다.
#pragma region  Select
void SelectSleep();

void SelectPoop();

void SelectEat();

void SelectWalk();

void SelectTug();

void SelectShop();

void SelectGuide();
#pragma endregion

#pragma region Show
void ShowStatus();
void ShowShop();
void ShowChoice();
void ShowBattle(int, int, int);
#pragma endregion

#pragma region Util
int UserInput();
int Percent(int);
#pragma endregion

#pragma region GameStatus
void Init();
int IsGameOver();
void Action(int);
void LevelUpRule();
#pragma endregion

#pragma region Battle
int AttackAddHealth1(int, int, int);
int AttackAddHealth2(int, int, int);
#pragma endregion

// 전역 변수 선언
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

int main(void)
{
	int mainInput;

	// 게임 초기화
	Init();

	while (!IsGameOver()) // 반복문 지속
	{
		//레벨업 상태 체크
		LevelUpRule();
		
		// 상태 정보 출력
		ShowStatus();

		// 유저 입력 메뉴 출력
		ShowChoice();

		// 유저 입력 대기
		mainInput = UserInput();

		// 유저 입력에 따른 액션		
		Action(mainInput);
	}
}

void SelectSleep()
{
	if (health >= Maxhealth)
	{
		printf("더이상 잘 필요가 없습니다.\n");
		stress += 10;
	}
	else
	{
		health += 10;
		printf("다마고치의 체력이 %d 증가했습니다\n", 10);

	}

	if (mana >= 100)
	{
		printf("더이상 마나가 회복될 수 없습니다.\n");
		stress += 10;
	}
	else
	{
		mana += 10;
		printf("다마고치의 마나가 %d 증가했습니다\n", 10);
	}
}

void SelectPoop()
{
	poo = 0;
	printf("다마고치의 배변활동지수가 %d 되었습니다\n", poo);
}

void SelectEat()
{
	if (hungry >= 200)
	{
		printf("더이상 먹을 필요가 없습니다.\n");
	}
	else
	{
		hungry += 20;
		poo += 20;
		printf("다마고치의 포만감이 %d 증가했습니다\n", 20);
	}
}

void SelectWalk()
{
	int userInput;
	if (Percent(50)) //0~49니깐 50퍼센트다
	{
		printf("===================================================\n");
		printf("산책 중 적이 나타났습니다!!.\n");

		// 전투 변수 초기화
		int turnon = 1; // while 문 통제 위한 변수선언
		int battle_enemyhealth = 100;  // 적 체력변수 선언
		int battle_enemyattack = 20; // 적 공격력 변수선언

		//while 문 안에 while 문 만들어서 통제할려면 변수가 필요했다
		while (turnon)
		{
			ShowBattle(battle_enemyhealth, health, mana);
			scanf_s("%d", &userInput);

			switch (userInput) // 분기문 안에 분기문 만들 수 있었다!!!
			{
			case 1: // 공격
				battle_enemyhealth -= gochiattack;
				printf("적에게 %d 만큼 피해를 줬습니다!\n", gochiattack);

				if (battle_enemyhealth <= 0) // 적 사망조건
				{
					printf("적이 사망했습니다!!.\n");
					turnon = 0;  // 내부 while 루프 탈출
					exp += 50;   // 경험치 획득
					printf("경험치를 %d 얻었습니다!\n", 30);
					rewardgold += 200;
					printf("골드를 %d 얻었습니다!\n", 200);
					stress -= 10;
					printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
				}
				break;

			case 2: // 적 사망 조건을 스킬에도 적용 해줘야 적 체력 -되면 사망 판정됨
				printf("다마고치가 스킬을 사용했습니다!.\n");
				if (mana < 50) //0으로 하니 타이밍 안맞아서 50으로 맞춤
				{
					printf("마나가 없어 스킬을 사용하지 못합니다.!.\n");

				}
				else
				{
					mana -= 50;

					battle_enemyhealth = AttackAddHealth1(health, gochiattack, battle_enemyhealth);
					//반드시 값을 초기화 해줘야 적 체력이 깎아진다

				}
				if (battle_enemyhealth <= 0)
				{
					printf("적이 사망했습니다!!.\n");
					turnon = 0;  // 내부 while 루프 탈출
					exp += 50;   // 경험치 획득
					printf("경험치를 %d 얻었습니다!\n", 30);
					rewardgold += 200;
					printf("골드를 %d 얻었습니다!\n", 200);
					stress -= 10;
					printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
				}

				break;

			case 3: // 도망
				printf("도망쳤습니다!\n");
				stress += 10;
				turnon = 0;  // 내부 while 루프 탈출
				break;


			}

			//적 체력 존재하면 공격함
			if (battle_enemyhealth > 0)
			{
				health -= battle_enemyattack;
				printf("적이 당신을 공격했습니다! 체력이 %d 감소했습니다.\n", battle_enemyattack);


				if (Percent(30)) // 적스킬은 30퍼센트로 스킬 나감
				{
					health = AttackAddHealth2(battle_enemyhealth, battle_enemyattack, health);
				}
				if (health <= 0)
				{
					printf("다마고치가 쓰러졌습니다!\n");
					turnon = 0;
				}
			}
		}
	}
	else
	{
		if (stress <= 0)
		{
			stress = 0;
			printf("더이상 스트레스 지수를 내릴 수 없습니다.\n");
		}
		else
		{
			stress -= 20;
			printf("스트레스가 산책으로 인해 %d 줄었습니다.\n", 20);
		}
	}
}

void SelectTug()
{
	int userInput;
	if (Percent(60))
	{
		printf("===================================================\n");
		printf("터그놀이 중 적이 나타났습니다!!.\n");

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
				battle_enemyhealth -= gochiattack;
				printf("적에게 %d 만큼 피해를 줬습니다!\n", gochiattack);

				if (battle_enemyhealth <= 0)
				{
					printf("적이 사망했습니다!!.\n");
					turnon = 0;  // while 문 속 while 문 탈출하고 일반 while문으로 감
					exp += 50;
					printf("경험치를 %d 얻었습니다!\n", 20);
					rewardgold += 200;
					printf("골드를 %d 얻었습니다!\n", 200);
					stress -= 10;
					printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
				}
				break;

			case 2: // 스킬
				printf("다마고치가 스킬을 사용했습니다!.\n");
				if (mana < 50)
				{
					printf("마나가 없어 스킬을 사용하지 못합니다.!.\n");
				}
				else
				{

					battle_enemyhealth = AttackAddHealth1(health, gochiattack, battle_enemyhealth);
					//값 초기화 해줘야지 적 체력 깎인다, 이거 제일 중요함!!

				}
				if (battle_enemyhealth <= 0)
				{
					printf("적이 사망했습니다!!.\n");
					turnon = 0;  // 내부 while 루프 탈출
					exp += 50;   // 경험치 획득
					printf("경험치를 %d 얻었습니다!\n", 30);
					rewardgold += 200;
					printf("골드를 %d 얻었습니다!\n", 200);
					stress -= 10;
					printf("스트레스가를 %d 만큼 떨어졌습니다\n", 10);
				}



				break;

			case 3: // 도망
				printf("도망쳤습니다!\n");
				stress += 10;
				turnon = 0;  // while 문 탈출한다. 만약 0으로 값 초기화 안해주면 도망 못하고 계속 진행됨
				break;


			}

			// 적 체력이 존재하면 공격함
			if (battle_enemyhealth > 0)
			{
				health -= battle_enemyattack;
				printf("적이 당신을 공격했습니다! 체력이 %d 감소했습니다.\n", battle_enemyattack);

				if (Percent(30)) // 적스킬은 30퍼센트로 스킬 나감
				{
					health = AttackAddHealth2(battle_enemyhealth, battle_enemyattack, health);
				}
				if (health <= 0)
				{
					printf("다마고치가 쓰러졌습니다!\n");
					turnon = 0;
				}
			}
		}
	}
	else
	{
		if (stress <= 0)
		{
			stress = 0;
			printf("더이상 스트레스 지수를 내릴 수 없습니다.\n");
		}
		else
		{
			stress -= 30;
			printf("스트레스가 터그활동으로 인해 %d 줄었습니다.\n", 30);
		}
	}
}

void SelectShop()
{
	int userInput;

	if (rewardgold < 200)
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
			rewardgold -= 200;
			Maxhealth += 100;

			printf("최대체력이 %d 증가하여 %d이 되었습니다.", 100, Maxhealth);
			break;

		case 2:
			rewardgold -= 300;
			gochiattack += 50;
			printf("공격력이 %d 증가하여 %d이 되었습니다.", 50, gochiattack);
			break;


		case 3:
			rewardgold -= 400;
			currentlevel += 1;
			printf("레벨이 %d 증가하여 %d이 되었습니다.", 1, currentlevel);
			break;
		}
	}


}

void SelectGuide()
{
	printf("다마고치는 스트레스가 100을 찍거나 배변지수가 100일 경우 사망 그리고 전투 시 체력이 떨어지면 사망합니다.\n");
	printf("다마고치는 레벨이 10이되면 최종성장하며 게임이 클리어 됩니다..\n");
	printf("다마고치는 불가능한 선택을 할때 ,도망칠때 스트레스를 10씩 받습니다.\n");
	printf("다마고치는 잠을 자거나, 적을 쓰러뜨릴 경우 스트레스를 회복합니다 .\n");
}

//함수 정의들 > 함수 리턴 부분과 함수 이름명 앞 맞춰줘야됨 , 그리고 리턴값은 반드시 1개다
int AttackAddHealth2(int num1, int num2, int num3)
{
	int totalDamage = num1 + num2;
	printf("적이 체력과 공격력을 합친 스킬(총공격력:%d)을 사용했습니다!\n", totalDamage);
	printf("다마고치에게 %d의 피해를 입혔습니다!\n", totalDamage);
	return num3 - totalDamage;
}

int AttackAddHealth1(int num1, int num2, int num3)
{
	int totalDamage = num1 + num2;
	printf("다마고치가 체력과 공격력을 합친 스킬(총공격력:%d)을 사용했습니다!\n", totalDamage);
	printf("적에게 %d의 피해를 입혔습니다!\n", totalDamage);
	return num3 - totalDamage;

}
int Percent(int num1) // 확률조건을 출력해주는 함수
{
	return (rand() % 100) < num1; // 0에서99까지 랜덤하게 나오는데 < 70면 0~69까지 반환됨 -> 조건 자체가 반환된다.
	//0과 1로 판단 -> 조건이 참이면 실행되는거다!
}
void ShowStatus()
{
	printf("===================================================\n");
	printf("상태창\n");
	printf("체력: %d\n", health);
	printf("마나: %d\n", mana);
	printf("포만감: %d\n", hungry);
	printf("화장실: %d\n", poo);
	printf("스트레스: %d\n", stress);
	printf("경험치: %d\n", exp);
	printf("현재골드: %d\n", rewardgold);
	printf("===================================================\n");
}
void ShowChoice()
{
	printf("\n=======================================================================================\n");
	printf("1.잠자기 2.응가하기 3.밥주기 4.산책하기 5.터그놀이 6.상점 7.다마고치 가이드라인\n");
	printf("=======================================================================================\n");
}
void ShowBattle(int num1, int num2, int num3)
{
	printf("\n----- 전투 -----\n");
	printf("적 체력: %d\n", num1);
	printf("내 체력: %d\n", num2);
	printf("내 마나: %d\n", num3);
	printf("원하는 숫자를 눌러 대응 하십쇼\n");
	printf("1.공격 2.스킬 3.도망\n");
	printf("입력: ");
}
void ShowShop()
{
	printf("원하는 물품을 구입하여 주십쇼!!\n");
	// 입력해달라는 안내 메시지를 출력
	printf("=========================================================================\n");
	printf("1.최대체력증가포션:200골드 2.공격력증가포션:300골드 3.레벨업포션:400골드\n");
	printf("=========================================================================\n");
	printf("입력: ");

}


void LevelUpRule()
{
	if (exp >= 100 * currentlevel * 1.2)
	{
		currentlevel++;
		exp = 0;
		gochiattack += 10;
		printf("\n 레벨 업! 현재 레벨: %d\n", currentlevel);
		printf("공격력이 %d로 증가했습니다!\n", gochiattack);
	}

}

void Init()
{
	// rand() 초기화는 한 번만!
	srand((unsigned int)time(NULL)); // 여러번 돌릴 필요없다, 프로그램 실행시 한번만 초기화 해줘도됨
}

int IsGameOver()
{
	//배변지수가 100을 달성 시 게임오버 상태 -> break를 함수 내에서 처리하지 못할것 같아 남겨둠
	if (poo >= 100 || stress >= 100)
	{
		printf("다마고치가 병에 걸렸습니다.\n");
		printf("게임이 종료되었습니다.\n");
		return 1; // 게임 종료
	}
	//승리 조건달아주기 -> break를 함수 내에서 처리하지 못할것 같아 남겨둠
	if (currentlevel == 10)
	{
		printf("다마고치가 완전히 성장했습니다!!\n");
		printf("게임이 종료되었습니다.\n");
		return 1;  // 게임 종료
	}
	// 다마고치 사망
	if (health <= 0)
	{
		printf("게임이 종료되었습니다.\n");
		return 1; // 게임 종료
	}

	return 0;
}

int UserInput()
{
	int inputNum;

	printf("입력: ");
	scanf_s("%d", &inputNum);
	return inputNum;
}

void Action(int num1)
{
	switch (num1)
	{
	case 1:
		SelectSleep();
		break;
	case 2:
		SelectPoop();
		break;
	case 3:
		SelectEat();
		break;
	case 4:
		SelectWalk();
		break;
	case 5:
		SelectTug();
		break;
	case 6:
		SelectShop();
		break;
	case 7:
		SelectGuide();
		break;
	}
}