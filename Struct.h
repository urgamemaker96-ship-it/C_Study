#pragma once
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
}typedef(damagochi);