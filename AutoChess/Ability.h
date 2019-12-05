#ifndef __SPELL__
#define __SPELL__
#include "Player.h"
#include "Hero.h"

class Ability
{
	void doubleAttack(Hero* attacked_pl, int attack_vl, int num_attacked);
	void AttackAllHeroes(Hero* attacked_pl, int attack_vl);
	void HealAllFriend(Hero* attacking_pl, int health_vl);
	void DeBuffs(Hero* attacked_pl);
public:
	void SpellAbility(Hero* attacked_pl, Hero* attacking_pl, int numb_attacked, int num_attacking);
};

#endif