#pragma once

//구조체 안에 구조체를 사용할때, 반드시 구조체안에 사용할 구조체를 먼저 선언해야 컴파일 오류가 발생안한다.
struct Skill 
{
	char name[20];          // 스킬 이름
	int level;              // 스킬 레벨
	int damage;				// 데미지
	float bonus_ratio;      // 추가 효과 비율 (체력/공격력/마나 등) -> 초기값을 0.2f 로 설정함 레벨업시 1.2배 증가시킬려고
	int mana_cost;          // 마나 소모량


}typedef(damaskill);


struct Damagochi
{
	int mana;
	int Maxhealth;
	int health;
	int hungry;
	int gochiattack;
	int poo;
	int stress;
	int exp;
	int currentlevel;
	char damaname[20];
	char mastername[20];
	int specialattack; //스킬함수 쓸때 받아오는 멤버변순
	int rewardgold; // rewardgold 멤버변수 추가 -> 다른 함수들의 파라메터를 간략하게 하기 위해서(구조체 포인터로 파라메터값 변경함)
	int skillpoint;

	damaskill skill_isanghaessi;  // 이상해씨 스킬 -> 다마고치 구조체가 다마고치 스킬을 가지고 있다는 의미 -> 다마고치 스킬 구조체 멤버변수를 가지고있음
	damaskill skill_paili;        // 파이리 스킬  -> 다마고치 구조체가 다마고치 스킬을 가지고 있다는 의미 -> 다마고치 스킬 구조체 멤버변수를 가지고있음
	damaskill skill_kkobugi;      // 꼬북이 스킬 -> 다마고치 구조체가 다마고치 스킬을 가지고 있다는 의미 -> 다마고치 스킬 구조체 멤버변수를 가지고있음

}typedef(damagochi);



