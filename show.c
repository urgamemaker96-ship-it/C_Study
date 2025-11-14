#include "show.h"
#include <stdio.h>
#include "Struct.h"
#include "util.h"

void ShowStatus(damagochi* selected)
{
	printf("===================================================\n");
	printf("상태창\n");
	printf("다마고치의 이름은 : %s\n", selected->damaname); // 어차피 배열은 포인터라 &안적어도된다.
	printf("%s의 주인의 이름은 : %s\n", selected->damaname, selected->mastername); // 어차피 배열은 포인터라 &안적어도된다.
	printf("체력: %d\n", selected->health);
	printf("마나: %d\n", selected->mana);
	printf("공격력: %d\n", selected->gochiattack);
	printf("특수공격력(스킬): %d\n", selected->specialattack);
	printf("포만감: %d\n", selected->hungry);
	printf("화장실: %d\n", selected->poo);
	printf("스트레스: %d\n", selected->stress);
	printf("경험치: %d\n", selected->exp);
	printf("현재골드: %d\n", selected->rewardgold);
	printf("===================================================\n");
}
void ShowChoice()
{
	printf("\n=======================================================================================\n");
	printf("1.잠자기 2.응가하기 3.밥주기 4.산책하기 5.터그놀이 6.상점 7.다마고치 가이드라인 8.스킬강화 9.스킬정보\n");
	printf("=======================================================================================\n");
}
void ShowBattle(int enemyhealth, damagochi* selected)// 적 체력은 윗 블록에 지역변수로 이미 들어가 있으나 나머지 체력, 마나 변수들은 그러지 못해 포인터 타입으로 만들어줌
{
	printf("\n----- 전투 -----\n");
	printf("적 체력: %d\n", enemyhealth);
	printf("내 체력: %d\n", selected->health);
	printf("내 마나: %d\n", selected->mana);
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

void ShowSkillInfo(damagochi* type) //구조체에서 그냥 긁어옴
{
    printf("\n=== 스킬 정보 ===\n");

    if (strcmp(type->damaname, "이상해씨") == 0)
	{
        damaskill* skill = &type->skill_isanghaessi; // 구조체 에서 이상해씨 스킬 주소값을 skill포인터 타입 변수에 저장함
        int current_damage = CountSkillDamage(type,1, false);
        int next_damage = CountSkillDamage(type, 1, true);

        printf("스킬명: %s (Lv.%d)\n", skill->name, skill->level);
        printf("마나 소모량: %d\n", skill->mana_cost);
        printf("현재 데미지: %d\n", current_damage);
        printf("다음 레벨 데미지: %d (+%d)\n", next_damage, next_damage - current_damage);
        printf("효과: 최대체력의 %.0f%% 추가 데미지\n", skill->bonus_ratio * 100);
    }
    else if (strcmp(type->damaname, "파이리") == 0)
	{
        damaskill* skill = &type->skill_paili;
        int current_damage = CountSkillDamage(type, 2, false);
        int next_damage = CountSkillDamage(type, 2, true);

        printf("스킬명: %s (Lv.%d)\n", skill->name, skill->level);
        printf("마나 소모량: %d\n", skill->mana_cost);
        printf("현재 데미지: %d\n", current_damage);
        printf("다음 레벨 데미지: %d (+%d)\n", next_damage, next_damage - current_damage);
        printf("효과: 공격력의 %.0f%% 추가 데미지\n", skill->bonus_ratio * 100);
    }
    else if (strcmp(type->damaname, "꼬북이") == 0)
	{
        damaskill* skill = &type->skill_kkobugi;
        int current_damage = CountSkillDamage(type, 3, false);
        int next_damage = CountSkillDamage(type, 3, true);

        printf("스킬명: %s (Lv.%d)\n", skill->name, skill->level);
        printf("마나 소모량: %d\n", skill->mana_cost);
        printf("현재 데미지: %d\n", current_damage);
        printf("다음 레벨 데미지: %d (+%d)\n", next_damage, next_damage - current_damage);
        printf("효과: 현재 마나의 %.0f%% 추가 데미지\n", skill->bonus_ratio * 100);
    }
  
    printf("==================\n");
}