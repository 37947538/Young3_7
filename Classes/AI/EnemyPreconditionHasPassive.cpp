//
//  EnemyPreconditionHasPassive.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/6.
//
//

#include "EnemyPreconditionHasPassive.h"
#include "EnemyBevTreeData.h"
#include "AnimateTools.h"

bool EnemyPreconditionHasPassive::externalCondition(const BevNodeInputParam& input) const
{
    const EnemyBevInputData&  inputData	= input.getRealDataType<EnemyBevInputData>();
    if(inputData.attackList.size() > 0)
    {
        return true;
    }
    if (AnimateTools::isBeAttackAnimatePlaying(inputData.m_Owner)) {
        return true;
    }
    return false;
}