//
//  BTCondition.h
//  Zombie3_4
//
//  Created by jl on 15/8/25.
//
//

#ifndef __Zombie3_4__BTCondition__
#define __Zombie3_4__BTCondition__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"
#include "BevNodeDataHeader.h"

#pragma mark - 主体temp模版
//主体temp模版

class BTConditionTemp : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#pragma mark - 主体是否玩家控制
class BTConditionPlayerControl : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#pragma mark - 主体是否玩家控制移动
class BTConditionPlayerControlMove : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#pragma mark - 主体是否玩家控制攻击
class BTConditionPlayerControlAtt : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#pragma mark - 主体是否玩家控制技能
class BTConditionPlayerControlSkill : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#pragma mark - 主体是否被击打
class BTConditionIsBeAttack : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#pragma mark - 主体是否为条件状态
class BTConditionCurrState : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent,GameEnum::BodyState s);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
    GameEnum::BodyState conditionState;
};

#pragma mark - 主体是否到可攻击距离
class BTConditionIsAttackDist : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#pragma mark - 主体是否跟随英雄
class BTConditionFollowHero : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#pragma mark - 主体是否到最小攻击距离
class BTConditionIsMinAttackDist : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#pragma mark - 是否发现敌兵
class BTConditionIsCatchEnemy : public APBevTreePrecondition
{
public:
    static APBevTreePrecondition* create(APBevTreeNode* parent);
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#endif /* defined(__Zombie3_4__BTCondition__) */
