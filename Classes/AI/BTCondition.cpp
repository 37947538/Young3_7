//
//  BTCondition.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/25.
//
//

#include "BTCondition.h"
#include "EnemyBase.h"

APBevTreePrecondition* BTConditionTemp::create(APBevTreeNode* parent)
{
    auto condition=new BTConditionTemp();
    parent->setNodePrecondition(condition);
    return condition;
}

bool BTConditionTemp::externalCondition(const BevNodeInputParam& input) const
{
    //const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    
//    if (inputData.m_Owner->getHpPercent() > 0.01) {
//        return false;
//    }
    
    return true;
}

#pragma mark - 是否玩家控制
APBevTreePrecondition* BTConditionPlayerControl::create(APBevTreeNode* parent)
{
    auto condition=new BTConditionPlayerControl();
    parent->setNodePrecondition(condition);
    return condition;
}

bool BTConditionPlayerControl::externalCondition(const BevNodeInputParam& input) const
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    
    if (inputData.m_PlayerControl==nullptr) {
        return false;
    }
    return true;
}


#pragma mark - 是否玩家控制移动
//是否玩家控制
APBevTreePrecondition* BTConditionPlayerControlMove::create(APBevTreeNode* parent)
{
    auto condition=new BTConditionPlayerControlMove();
    parent->setNodePrecondition(condition);
    return condition;
}

bool BTConditionPlayerControlMove::externalCondition(const BevNodeInputParam& input) const
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    
    if (inputData.m_PlayerControl->isMoveButtonPress()) {
        return true;
    }
    return false;
}

#pragma mark - 主体是否玩家控制攻击
APBevTreePrecondition* BTConditionPlayerControlAtt::create(APBevTreeNode* parent)
{
    auto condition=new BTConditionPlayerControlAtt();
    parent->setNodePrecondition(condition);
    return condition;
}

bool BTConditionPlayerControlAtt::externalCondition(const BevNodeInputParam& input) const
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    
    if (inputData.m_PlayerControl->isAttackButtonPress()) {
        return true;
    }
    return false;
}

#pragma mark - 主体是否玩家控制技能
APBevTreePrecondition* BTConditionPlayerControlSkill::create(APBevTreeNode* parent)
{
    auto condition=new BTConditionPlayerControlSkill();
    parent->setNodePrecondition(condition);
    return condition;
}

bool BTConditionPlayerControlSkill::externalCondition(const BevNodeInputParam& input) const
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    
    if (inputData.m_PlayerControl->isSkillButtonPress() || inputData.m_Owner->getBodyState()==GameEnum::BodyState::Skill) {
        return true;
    }
    return false;
}

#pragma mark - 主体是否被击打
APBevTreePrecondition* BTConditionIsBeAttack::create(APBevTreeNode* parent)
{
    auto condition=new BTConditionIsBeAttack();
    parent->setNodePrecondition(condition);
    return condition;
}

bool BTConditionIsBeAttack::externalCondition(const BevNodeInputParam& input) const
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    
    if(dynamic_cast<EnemyBase*>(inputData.m_Owner))
    {
        //log("BTConditionIsBeAttack::externalCondition%s",typeid(inputData.m_Owner).name());

    }
    if(inputData.m_OwnerState==GameEnum::BodyState::BeAttack || inputData.m_OwnerState==GameEnum::BodyState::Down)
    {
        return true;
    }
    
    return false;
}

#pragma mark - 主体是否被击倒状态
APBevTreePrecondition* BTConditionCurrState::create(APBevTreeNode* parent,GameEnum::BodyState s)
{
    auto condition=new BTConditionCurrState();
    condition->conditionState=s;
    parent->setNodePrecondition(condition);
    return condition;
}

bool BTConditionCurrState::externalCondition(const BevNodeInputParam& input) const
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    
    if (inputData.m_OwnerState==conditionState)
    {
        return true;
    }
    return false;
}

#pragma mark - 主体是否到可攻击距离
APBevTreePrecondition* BTConditionIsAttackDist::create(APBevTreeNode* parent)
{
    auto condition=new BTConditionIsAttackDist();
    parent->setNodePrecondition(condition);
    return condition;
}
bool BTConditionIsAttackDist::externalCondition(const BevNodeInputParam& input) const
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    Vec2 curPosition2D = inputData.m_CurrPosition2D;
    Vec2 dir = targetPoint2D - curPosition2D;
    if(fabsf(dir.x) < inputData.m_iAttackDist && targetPoint2D != curPosition2D)
    {
        return true;
    }
    return false;
}

#pragma mark - 主体是否跟随英雄
APBevTreePrecondition* BTConditionFollowHero::create(APBevTreeNode* parent)
{
    auto condition=new BTConditionFollowHero();
    parent->setNodePrecondition(condition);
    return condition;
}
bool BTConditionFollowHero::externalCondition(const BevNodeInputParam& input) const
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    Vec2 targetPoint2D = inputData.m_CurrPosition2D;//.m_TargetPosition2D;
    Vec2 curPosition2D = inputData.m_MainHeroPosition2D;
    Vec2 dir = targetPoint2D - curPosition2D;
    if(fabsf(dir.x) > 300)
    {
        return true;
    }
    
    return false;
}

#pragma mark - 主体是否比最小攻击距离还小
APBevTreePrecondition* BTConditionIsMinAttackDist::create(APBevTreeNode* parent)
{
    auto condition=new BTConditionIsMinAttackDist();
    parent->setNodePrecondition(condition);
    return condition;
}
bool BTConditionIsMinAttackDist::externalCondition(const BevNodeInputParam& input) const
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    Vec2 curPosition2D = inputData.m_CurrPosition2D;
    int minAttDis = inputData.m_iAttackDistMin;   //最小攻击距离

    if (minAttDis <= 0) {
        return false;
    }
    
    Vec2 dir = targetPoint2D - curPosition2D;
    if(fabsf(dir.x) < minAttDis)
    {
        return true;
    }
    
    return false;
}

#pragma mark - 是否发现敌兵
APBevTreePrecondition* BTConditionIsCatchEnemy::create(APBevTreeNode* parent)
{
    auto condition=new BTConditionIsCatchEnemy();
    parent->setNodePrecondition(condition);
    return condition;
}
bool BTConditionIsCatchEnemy::externalCondition(const BevNodeInputParam& input) const
{
    const BTNodeInputData& inputData = input.getRealDataType<BTNodeInputData>();
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    Vec2 curPosition2D = inputData.m_CurrPosition2D;
    Vec2 mainHeroPosition2D = inputData.m_MainHeroPosition2D;
    int minAttDis = 450;   //搜索距离

    Vec2 dir = targetPoint2D - curPosition2D;
    if(fabsf(dir.x) < minAttDis && targetPoint2D!=curPosition2D && targetPoint2D!=mainHeroPosition2D)
    {
        return true;
    }
    
    return false;
}
