//
//  EnemyPrecondition.h
//  Zombie3_4
//  行为节点进入条件
//  Created by jl on 15/8/10.
//
//

#ifndef __Zombie3_4__EnemyPrecondition__
#define __Zombie3_4__EnemyPrecondition__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

//是否死亡
class EnemyPreconditionHasDie : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//是否到达目标
class EnemyPreconditionHasTarget : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//怪攻击英雄条件
class EnemyPreconditionEnemyAttHero : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};



#endif /* defined(__Zombie3_4__EnemyPrecondition__) */
