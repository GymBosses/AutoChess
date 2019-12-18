#ifndef __SPELL__
#define __SPELL__
#include "Player.h"
#include "Hero.h"

class Ability
{
	//Double strike ability
	void doubleAttack(Hero* attacked_pl, int attack_vl, int num_attacked);
	//A strike on all the heroes of the enemy
	void AttackAllHeroes(Hero* attacked_pl, int attack_vl);
	//To heal all friendly heroes
	void HealAllFriend(Hero* attacking_pl, int health_vl);
	//DeBuffs all heroes of the enemy
	void DeBuffs(Hero* attacked_pl);
public:
	//attacked - атакуемый игрок(я хз что по переводу)
	//attacking - атакующий игрок
	//The hero uses the ability
	void SpellAbility(Hero* attacked_pl, Hero* attacking_pl, int numb_attacked, int num_attacking);
};

#endif