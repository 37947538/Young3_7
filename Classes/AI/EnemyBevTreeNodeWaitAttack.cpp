//
//  EnemyBevTreeNodeWaitAttack.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/21.
//
//

#include "EnemyBevTreeNodeWaitAttack.h"

#pragma mark - 等待攻击条件
bool EnemyPrecondWaitAttack::externalCondition(const BevNodeInputParam& input) const
{
    //如果待机时间长即可攻击
    return true;
}