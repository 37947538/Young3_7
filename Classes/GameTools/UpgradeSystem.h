//
//  UpgradeSystem.h
//  Zombie3_4
//  游戏角色成长系统
//  Created by jl on 15/9/2.
//
//

#ifndef __Zombie3_4__UpgradeSystem__
#define __Zombie3_4__UpgradeSystem__

#include <stdio.h>
#include "HeroModel.h"
#include "EnemyModel.h"
#include "SkillModel.h"

class UpgradeSystem
{
public:
    static bool addHeroExp(int exp, HeroModel *lb);                                     //增加英雄经验
    static bool setEnemyLv(int exp, EnemyModel *em);                                    //设置怪等级
    static int getHeroLvExp(int iLv);                                                   //根据等级获取经验
    static bool calculationHeroData(HeroModel *model);                                  //计算英雄数据
    static bool calculationHeroPower(HeroModel *model, SkillModel* skills);             //计算英雄战力
};

#endif /* defined(__Zombie3_4__UpgradeSystem__) */
