//
//  HeroPrecondition.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/18.
//
//

#include "HeroPrecondition.h"
#include "HeroBevTreeHeader.h"
#include "AnimateTools.h"

#pragma mark - 英雄被攻击
//英雄被攻击
bool HeroPreconditionHasBeAttack::externalCondition(const BevNodeInputParam& input) const
{
//    //dfgfdg
//    const HeroBevTreeInputData&  inputData	= input.getRealDataType<HeroBevTreeInputData>();
//    //判断是否有敌兵在攻击范围
//    Vec2 curPosition2D = inputData.m_Owner->getPosition();
//    Vec2 mainHeroPos=inputData.m_MainHeroPosition;
//    Vec2 dir = mainHeroPos - curPosition2D;
//    if(fabsf(dir.x)  > 200)
//    {
//        return true;
//    }
//    return false;
}


#pragma mark - Npc是否跟随主英雄
//Npc是否攻击英雄
bool HeroPreconditionNpcFollow::externalCondition(const BevNodeInputParam& input) const
{
    const HeroBevTreeInputData&  inputData	= input.getRealDataType<HeroBevTreeInputData>();
    //判断是否有敌兵在攻击范围
    Vec2 curPosition2D = inputData.m_Owner->getPosition();
    Vec2 mainHeroPos=inputData.m_MainHeroPosition;
    Vec2 dir = mainHeroPos - curPosition2D;
    if(fabsf(dir.x)  > 200)
    {
        return true;
    }
    return false;
}

#pragma mark - Npc是否攻击
//Npc是否攻击英雄
bool HeroPreconditionNpcAttackMonster::externalCondition(const BevNodeInputParam& input) const
{
    const HeroBevTreeInputData&  inputData	= input.getRealDataType<HeroBevTreeInputData>();
    //判断是否有敌兵在攻击范围
    Vec2 curPosition2D = inputData.m_Owner->getPosition();
    for (int i=0; i< inputData.m_EnemyList->size(); i++) {
        auto enemy= inputData.m_EnemyList->at(i);
        Vec2 dir = enemy->getPosition() - curPosition2D;
        if(fabsf(dir.x)  < inputData.m_iAttackDist)
        {
            return true;
        }
    }
    return false;
}


#pragma mark - 是否Npc攻击中
//是否玩家控制
bool HeroPreconditionNpcAttacking::externalCondition(const BevNodeInputParam& input) const
{
    const HeroBevTreeInputData&  inputData	= input.getRealDataType<HeroBevTreeInputData>();
    if (AnimateTools::isSkillAnimatePlaying(inputData.m_Owner) ||
        AnimateTools::isAttackAnimatePlaying(inputData.m_Owner)) {
        return true;
    }
    
    return false;
}

#pragma mark - 是否玩家控制技能
//是否玩家控制
bool HeroPreconditionControllSkill::externalCondition(const BevNodeInputParam& input) const
{
    const HeroBevTreeInputData&  inputData	= input.getRealDataType<HeroBevTreeInputData>();
    if (inputData.m_PlayerControl->isSkillButtonPress()) {
        return true;
    }
    //是否有技能在播放
    if (AnimateTools::isSkillAnimatePlaying(inputData.m_Owner)) {
        return true;
    }

    return false;
}

#pragma mark - 是否玩家控制攻击
//是否玩家控制
bool HeroPreconditionControllAtt::externalCondition(const BevNodeInputParam& input) const
{
    const HeroBevTreeInputData&  inputData	= input.getRealDataType<HeroBevTreeInputData>();
    
    //是否按下攻击按钮
    if (inputData.m_PlayerControl->isAttackButtonPress()) {
        return true;
    }
    
    //是否有连击在播放
    if (AnimateTools::isAttackAnimatePlaying(inputData.m_Owner)) {
        return true;
    }
    
    
    return false;
}
#pragma mark - 是否玩家控制
//是否玩家控制
bool HeroPreconditionPlayerControll::externalCondition(const BevNodeInputParam& input) const
{
    const HeroBevTreeInputData&  inputData	= input.getRealDataType<HeroBevTreeInputData>();
    if (inputData.m_PlayerControl==nullptr) {
        return false;
    }
    
    return true;
}

#pragma mark - 是否玩家控制移动
//是否玩家控制
bool HeroPreconditionControllMove::externalCondition(const BevNodeInputParam& input) const
{
    const HeroBevTreeInputData&  inputData	= input.getRealDataType<HeroBevTreeInputData>();
    if (inputData.m_PlayerControl->isMoveButtonPress()) {
        return true;
    }
    return false;
}


//死亡条件
bool HeroPreconditionHasDie::externalCondition(const BevNodeInputParam& input) const
{
    const HeroBevTreeInputData&  inputData	= input.getRealDataType<HeroBevTreeInputData>();
    
    if (inputData.m_Owner->getHpPercent() > 0.01) {
        return false;
    }
    
    return true;
}

#pragma mark - 条件判定

bool HeroPreconditionHasTarget::externalCondition(const BevNodeInputParam& input) const
{
    /*
    const EnemyBevInputData&  inputData	= input.getRealDataType<EnemyBevInputData>();
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    Vec2 curPosition2D = inputData.m_Owner->getPosition();
    Vec2 dir = targetPoint2D - curPosition2D;
    if(fabsf(dir.x)  > 0.1f)
    {
        return true;
    }
    return false;
     */
}

#pragma mark - 怪攻击英雄条件判定
bool HeroPreconditionEnemyAttHero::externalCondition(const BevNodeInputParam& input) const
{
    /*
    const EnemyBevInputData&  inputData	= input.getRealDataType<EnemyBevInputData>();
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    Vec2 curPosition2D = inputData.m_Owner->getPosition();
    Vec2 dir = targetPoint2D - curPosition2D;
    if(fabsf(dir.x)  < inputData.m_iAttackDist)
    {
        return true;
    }
    return false;
     */
}



