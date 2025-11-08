#include "util.h"

#include <stdio.h>
#include <stdlib.h>

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
	scanf_s("%s", name, size); // scanf_s("%s", name,size); 오류로 확인되며 3번째에 반드시 버퍼크기를 적어줘야지 오류를 줄일 수 있기 때문에 입력이 강제된다.
	printf("\n입력하신 이름은 : %s 입니다\n", name);


}

void DamagochiNameInput(char* damaname, int size)
{

	printf("\n다마고치의 이름을 입력해주세요 : ");
	scanf_s("%s", damaname, size); // scanf_s("%s", name,size); 오류로 확인되며 3번째에 반드시 버퍼크기를 적어줘야지 오류를 줄일 수 있기 때문에 입력이 강제된다.
	printf("\n입력하신 이름은 : %s 입니다\n", damaname);

}

int TakeDamage(int damage, int health)//이미 윗쪽 지역변수 health 선언되어 있어서 따로 포인터 자료형변수로 안만듬
{
	return health - damage;
}
int Percent(int num1) // 확률조건을 출력해주는 함수
{
	return (rand() % 100) < num1; // 0에서99까지 랜덤하게 나오는데 < 70면 0~69까지 반환됨 -> 조건 자체가 반환된다.
	//0과 1로 판단 -> 조건이 참이면 실행되는거다!
}

int GetSubstractResultOrZero(int num1, int num2)
{
	int result = num1 - num2;

	return result >= 0 ?
		result : 0;
}

int GetAddResultOrZero(int num1, int num2, int max)
{
	int result = num1 + num2;

	return result >= max ?
		max : result;
}