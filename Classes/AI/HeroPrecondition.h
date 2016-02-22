//
//  HeroPrecondition.h
//  Zombie3_4
//  英雄行为树条件
//  Created by jl on 15/8/18.
//
//

#ifndef __Zombie3_4__HeroPrecondition__
#define __Zombie3_4__HeroPrecondition__

#include <stdio.h>

#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"


//英雄被攻击
class HeroPreconditionHasBeAttack : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//Npc跟随英雄
class HeroPreconditionNpcFollow : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//Npc是否攻击英雄
class HeroPreconditionNpcAttackMonster : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//是否Npc攻击中
class HeroPreconditionNpcAttacking : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//是否玩家控制技能
class HeroPreconditionControllSkill : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//是否玩家控制攻击
class HeroPreconditionControllAtt : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//是否玩家控制
class HeroPreconditionPlayerControll : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//是否玩家控制移动
class HeroPreconditionControllMove : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//是否死亡
class HeroPreconditionHasDie : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//是否到达目标
class HeroPreconditionHasTarget : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

//怪攻击英雄条件
class HeroPreconditionEnemyAttHero : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};


#endif /* defined(__Zombie3_4__HeroPrecondition__) */
