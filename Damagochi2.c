#include <stdio.h>
#include <stdlib.h> // rand()함수 포함 라이브러리
#include <time.h> // time()함수 포함 라이브러리


//함수 선언들 main 함수 위에서 함수 정의 선언해줬기 때문에 함수선언 따로 할 필요없다.
#pragma region  Select
void SelectSleep(int*,int*,int*,int*,char*);
void SelectPoop(int*, char*);
void SelectEat(int*, int*, char*);
void SelectWalk(int*, int*, int*, int*, int*, int*,char*,char*);
void SelectTug(int*, int*, int*, int*, int*, int*,char*, char*);
void SelectShop(int*, int*, int*, int*);
void SelectGuide(char*);
#pragma endregion

#pragma region Show
void ShowStatus(int*, int*, int*, int*, int*, int*, int*,char*,char*);
void ShowShop();
void ShowChoice();
void ShowBattle(int, int*, int*);
void ShowDamage(char*, char*, int,int);
#pragma endregion

#pragma region Util
int UserInput();
int Percent(int);
void UserNameInput(char*, int);
void DamagochiNameInput(char*, int);

#pragma endregion

#pragma region GameStatus
void Init();
int IsGameOver(int*, int*, int*, int*, char*);
void Action(int, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*,char*,char*);
void LevelUpRule(int*, int*, int*);
#pragma endregion

#pragma region Battle
int TakeDamage(int, int);

#pragma endregion



int main(void)
{	
	//1.모든 변수 지역변수로 설정해서 포인터 이용해가지고 잘 작동하는지 테스트 해보기!
	//2.모든 변수를 지역변수로 변경하니 만든 함수에서 빨간불 들어옴
	//3.해당 오류난 함수 확인하니 전부 변수가 없어서 일어남, 해당 함수 파라메터값을 새롭게 선언 
	//4.함수 파라메터 값을 지역변수로 설정하고 이 변수의 타입을 포인터 타입으로 설정해준뒤 오류 안나게 수정해줌
	
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

void SelectSleep(int* health, int* Maxhealth , int* stress, int* mana, char* damaname)
{
	if (*health >= *Maxhealth)
	{
		printf("더이상 잘 필요가 없습니다.\n");
		*stress += 10;
	}
	else
	{
		*health += 10;
		printf("%s의 체력이 %d 증가했습니다\n", damaname,10);

	}

	if (*mana >= 100)
	{
		printf("더이상 마나가 회복될 수 없습니다.\n");
		*stress += 10;
	}
	else
	{
		*mana += 10;
		printf("%s의 마나가 %d 증가했습니다\n", damaname,10);
	}
}

void SelectPoop(int* poo,char* damaname)
{
	*poo = 0;
	printf("%s의 배변활동지수가 %d 되었습니다\n",damaname, *poo);
}

void SelectEat(int* hungry,int* poo,char* damaname)
{
	if (*hungry >= 200)
	{
		printf("더이상 먹을 필요가 없습니다.\n");
	}
	else
	{
		*hungry += 20;
		*poo += 20;
		printf("%s의 포만감이 %d 증가했습니다\n", damaname,20);
	}
}

void SelectWalk(int* health, int* mana, int* gochiattack, int* exp, int* rewardgold,int* stress,char* damaname,char* enemyname)
{
	int userInput;
	if (Percent(50)) //0~49니깐 50퍼센트다
	{
		printf("===================================================\n");
		printf("산책 중 %s이 나타났습니다!!.\n",enemyname);

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
				printf("%s에게 %d 만큼 피해를 줬습니다!\n",enemyname, *gochiattack);

				if (battle_enemyhealth <= 0) // 적 사망조건
				{
					printf("%s이 사망했습니다!!.\n",enemyname);
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
				printf("%s가 스킬을 사용했습니다!.\n",damaname);
				if (*mana < 50) //0으로 하니 타이밍 안맞아서 50으로 맞춤
				{
					printf("마나가 없어 스킬을 사용하지 못합니다.!.\n");

				}
				else
				{
					*mana -= 50;

					
					int totalDamage = *health + *gochiattack; // ShowDamage 함수 자료형에 맞는 파라미터 사용 위해서 새로운 변수 맞춰줌
					battle_enemyhealth = TakeDamage(totalDamage, battle_enemyhealth);
					ShowDamage(damaname,enemyname, totalDamage,1); //damaname 은 이미 포인터 타입이라 그냥 변수명 써도됨
					//반드시 값을 초기화 해줘야 적 체력이 깎아진다

				}
				if (battle_enemyhealth <= 0)
				{
					printf("%s이 사망했습니다!!.\n",enemyname);
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
				printf("%s이 당신을 공격했습니다! 체력이 %d 감소했습니다.\n", enemyname,battle_enemyattack);


				if (Percent(30)) // 적스킬은 30퍼센트로 스킬 나감
				{	//TakeDamage 함수는 그냥 단순 계산기다 
					//-> 파라미터 타입에 맞지않는*변수 라고해도 *변수 뜻은 해당 변수의 주소에 있는 값이라는 뜻이다.
					int totalEnemyDagame = battle_enemyhealth + battle_enemyattack;
					*health = TakeDamage(totalEnemyDagame, *health);
					ShowDamage(damaname, enemyname,totalEnemyDagame,2);
				}
				if (*health <= 0)
				{
					printf("%s가 쓰러졌습니다!\n",damaname);
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

void SelectTug(int* health, int* mana, int* gochiattack, int* exp, int* rewardgold, int* stress,char* damaname,char* enemyname)
{
	int userInput;
	if (Percent(60))
	{
		printf("===================================================\n");
		printf("터그놀이 중 %s이 나타났습니다!!.\n");

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
				printf("%s에게 %d 만큼 피해를 줬습니다!\n",enemyname, *gochiattack);

				if (battle_enemyhealth <= 0)
				{
					printf("%s이 사망했습니다!!.\n",enemyname);
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
				printf("%s가 스킬을 사용했습니다!.\n",damaname);
				if (*mana < 50)
				{
					printf("마나가 없어 스킬을 사용하지 못합니다.!.\n");
				}
				else
				{
					
					int totalDamage = *health + *gochiattack;
					battle_enemyhealth = TakeDamage(totalDamage, battle_enemyhealth);
					ShowDamage(damaname, enemyname, totalDamage,2);
					//값 초기화 해줘야지 적 체력 깎인다, 이거 제일 중요함!!

				}
				if (battle_enemyhealth <= 0)
				{
					printf("%s이 사망했습니다!!.\n",enemyname);
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
				printf("%s이 당신을 공격했습니다! 체력이 %d 감소했습니다.\n",enemyname, battle_enemyattack);

				if (Percent(30)) // 적스킬은 30퍼센트로 스킬 나감
				{
					int totalEnemyDagame = battle_enemyhealth + battle_enemyattack;
					*health = TakeDamage(totalEnemyDagame, *health);
					ShowDamage(damaname, enemyname, totalEnemyDagame,2);
				}
				if (*health <= 0)
				{
					printf("%s가 쓰러졌습니다!\n",damaname);
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

void SelectShop(int* rewardgold,int* Maxhealth, int* gochiattack, int* currentlevel)
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
	printf("%s는 레벨이 10이되면 최종성장하며 게임이 클리어 됩니다..\n",damaname);
	printf("%s는 불가능한 선택을 할때 ,도망칠때 스트레스를 10씩 받습니다.\n", damaname);
	printf("%s는 잠을 자거나, 적을 쓰러뜨릴 경우 스트레스를 회복합니다 .\n", damaname);
}

//함수 정의들 > 함수 리턴 부분과 함수 이름명 앞 맞춰줘야됨 , 그리고 리턴값은 반드시 1개다


int TakeDamage(int damage, int health)//이미 윗쪽 지역변수 health 선언되어 있어서 따로 포인터 자료형변수로 안만듬
{
	return health - damage;
}
int Percent(int num1) // 확률조건을 출력해주는 함수
{
	return (rand() % 100) < num1; // 0에서99까지 랜덤하게 나오는데 < 70면 0~69까지 반환됨 -> 조건 자체가 반환된다.
	//0과 1로 판단 -> 조건이 참이면 실행되는거다!
}
void ShowStatus(int* health, int* mana, int* hungry, int* poo, int* stress, int* exp, int* rewardgold,char* name, char* damaname)
{
	printf("===================================================\n");
	printf("상태창\n");
	printf("다마고치의 이름은 : %s\n", damaname); // 어차피 배열은 포인터라 &안적어도된다.
	printf("%s의 주인의 이름은 : %s\n",damaname,name ); // 어차피 배열은 포인터라 &안적어도된다.
	printf("체력: %d\n", *health);
	printf("마나: %d\n", *mana);
	printf("포만감: %d\n", *hungry);
	printf("화장실: %d\n", *poo);
	printf("스트레스: %d\n", *stress);
	printf("경험치: %d\n", *exp);
	printf("현재골드: %d\n", *rewardgold);
	printf("===================================================\n");
}
void ShowChoice()
{
	printf("\n=======================================================================================\n");
	printf("1.잠자기 2.응가하기 3.밥주기 4.산책하기 5.터그놀이 6.상점 7.다마고치 가이드라인\n");
	printf("=======================================================================================\n");
}
void ShowBattle(int num1, int* num2, int* num3)// 적 체력은 윗 블록에 지역변수로 이미 들어가 있으나 나머지 체력, 마나 변수들은 그러지 못해 포인터 타입으로 만들어줌
{
	printf("\n----- 전투 -----\n");
	printf("적 체력: %d\n", num1);
	printf("내 체력: %d\n", *num2);
	printf("내 마나: %d\n", *num3);
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


void LevelUpRule(int* exp, int* currentlevel, int* gochiattack)
{
	if (*exp >= 100 * *currentlevel * 1.2)
	{
		(*currentlevel)++; //*(currentlevel)++ 이렇게해서 포인터가 가르키는 값을 증가시켜야 되는데 포인터 값 자체를 증가시킴 -> 오류수정
		*exp = 0; //포인터로 참조한 변수의값을 0으로 초기화해줌
		*gochiattack += 10; //포인터로 참조한 변수의값을 10씩 증감해줌
		printf("\n 레벨 업! 현재 레벨: %d\n", *currentlevel);
		printf("공격력이 %d로 증가했습니다!\n", *gochiattack);
	}

}

void Init()
{
	// rand() 초기화는 한 번만!
	srand((unsigned int)time(NULL)); // 여러번 돌릴 필요없다, 프로그램 실행시 한번만 초기화 해줘도됨
}

int IsGameOver(int* poo, int* stress, int* currentlevel, int*health,char* damaname)
{
	//배변지수가 100을 달성 시 게임오버 상태 -> break를 함수 내에서 처리하지 못할것 같아 남겨둠
	if (*poo >= 100 || *stress >= 100)
	{
		printf("%s가 병에 걸렸습니다.\n", damaname);
		printf("게임이 종료되었습니다.\n");
		return 1; // 게임 종료
	}
	//승리 조건달아주기 -> break를 함수 내에서 처리하지 못할것 같아 남겨둠
	if (*currentlevel == 10)
	{
		printf("%s가 완전히 성장했습니다!!\n", damaname);
		printf("게임이 종료되었습니다.\n");
		return 1;  // 게임 종료
	}
	// 다마고치 사망
	if (*health <= 0)
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

void UserNameInput(char* name, int size)
{
	
	printf("다마고치의 주인이 될 본인의 이름을 입력해주세요 : ");
	scanf_s("%s", name,size); // scanf_s("%s", name,size); 오류로 확인되며 3번째에 반드시 버퍼크기를 적어줘야지 오류를 줄일 수 있기 때문에 입력이 강제된다.
	printf("\n입력하신 이름은 : %s 입니다\n", name);
	

}

void DamagochiNameInput(char* damaname, int size)
{
	
	printf("\n다마고치의 이름을 입력해주세요 : ");
	scanf_s("%s",damaname, size); // scanf_s("%s", name,size); 오류로 확인되며 3번째에 반드시 버퍼크기를 적어줘야지 오류를 줄일 수 있기 때문에 입력이 강제된다.
	printf("\n입력하신 이름은 : %s 입니다\n", damaname);
	
}




void Action(int num1,int* health, int* Maxhealth, int* stress, int* mana, int* poo, int* hungry, int* gochiattack,int* exp, int* rewardgold, int* currentlevel,char* damaname,char* enemyname)
{	//전부 이중포인터 문제 때문에 파라미터변수 앞에 &안달아준거다.
	switch (num1)
	{
	case 1:
		SelectSleep(health, Maxhealth, stress, mana,damaname);
		break;
	case 2:
		SelectPoop(poo,damaname);
		break;
	case 3:
		SelectEat(hungry, poo,damaname);
		break;
	case 4:
		SelectWalk(health, mana, gochiattack, exp, rewardgold, stress,damaname,enemyname);
		break;
	case 5:
		SelectTug(health, mana, gochiattack, exp, rewardgold, stress,damaname,enemyname);
		break;
	case 6:
		SelectShop(rewardgold, Maxhealth, gochiattack, currentlevel);
		break;
	case 7:
		SelectGuide(damaname);
		break;
	}
}

void ShowDamage(char* damaname, char* enemyname, int damage, int turn)
{
	
	if (turn % 2 == 1)
	{
		// 다마고치 -> 적
		printf("%s가 체력과 공격력을 합친 스킬(총공격력:%d)을 사용했습니다!\n", damaname, damage);
		printf("%s에게 %d의 피해를 입혔습니다!\n", enemyname,damage);
	}
	
	 // 적 -> 다마고치
	else
	{
		printf("%s이 체력과 공격력을 합친 스킬(총공격력:%d)을 사용했습니다!\n", enemyname, damage);
		printf("%s에게 %d의 피해를 입혔습니다!\n", damaname, damage);
	}
	
}