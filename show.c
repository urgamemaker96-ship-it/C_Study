#include "show.h"
#include <stdio.h>

void ShowStatus(int* health, int* mana, int* hungry, int* poo, int* stress, int* exp, int* rewardgold, char* username, char* damaname)
{
	printf("===================================================\n");
	printf("상태창\n");
	printf("다마고치의 이름은 : %s\n", damaname); // 어차피 배열은 포인터라 &안적어도된다.
	printf("%s의 주인의 이름은 : %s\n", damaname, username); // 어차피 배열은 포인터라 &안적어도된다.
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

void ShowDamage(char* attacker, char* deffender, int damage)
{
	printf("%s가 체력과 공격력을 합친 스킬(총공격력:%d)을 사용했습니다!\n", attacker, damage);
	printf("%s에게 %d의 피해를 입혔습니다!\n", deffender, damage);
}