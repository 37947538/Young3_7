//
//  GameObjectFactory.h
//  Zombie3_4
//  游戏对象工厂
//  Created by jl on 15/8/14.
//
//

#ifndef __Zombie3_4__GameObjectFactory__
#define __Zombie3_4__GameObjectFactory__

#include <stdio.h>
#include "EnemyBase.h"

class GameObjectFactory
{
public:
    static EnemyBase* getEnemy(int enemyIndex, int enemyLv=1);     //获取敌兵
    static HeroBase* getHero(int heroIndex);                        //获取英雄
};

#endif /* defined(__Zombie3_4__GameObjectFactory__) */
