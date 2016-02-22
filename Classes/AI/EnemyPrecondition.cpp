//
//  EnemyPrecondition.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/10.
//
//

#include "EnemyPrecondition.h"
#include "EnemyBevTreeData.h"

//死亡条件
bool EnemyPreconditionHasDie::externalCondition(const BevNodeInputParam& input) const
{
    const EnemyBevInputData&  inputData	= input.getRealDataType<EnemyBevInputData>();
    
    if (inputData.m_Owner->getHpPercent() > 0.01) {
        return false;
    }
    
    return true;
}

#pragma mark - 条件判定

bool EnemyPreconditionHasTarget::externalCondition(const BevNodeInputParam& input) const
{
    const EnemyBevInputData&  inputData	= input.getRealDataType<EnemyBevInputData>();
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    Vec2 curPosition2D = inputData.m_Owner->getPosition();
    Vec2 dir = targetPoint2D - curPosition2D;
    if(fabsf(dir.x)  > 0.1f)
    {
        return true;
    }
    return false;
}

#pragma mark - 怪攻击英雄条件判定
bool EnemyPreconditionEnemyAttHero::externalCondition(const BevNodeInputParam& input) const
{
    const EnemyBevInputData&  inputData	= input.getRealDataType<EnemyBevInputData>();
    Vec2 targetPoint2D = inputData.m_TargetPosition2D;
    Vec2 curPosition2D = inputData.m_Owner->getPosition();
    Vec2 dir = targetPoint2D - curPosition2D;
    if(fabsf(dir.x)  < inputData.m_iAttackDist)
    {
        return true;
    }
    return false;
}
