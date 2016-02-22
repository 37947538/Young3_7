//
//  EnemyBevTreeNodeWaitAttack.h
//  Zombie3_4
//  敌兵节点等待攻击
//  Created by jl on 15/7/21.
//
//

#ifndef __Zombie3_4__EnemyBevTreeNodeWaitAttack__
#define __Zombie3_4__EnemyBevTreeNodeWaitAttack__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"
#include "APBevTreePrecondition.h"

class EnemyBevTreeNodeWaitAttack : public APBevTreeNodeParallel
{
public:
    
};


//是否准备攻击
class EnemyPrecondWaitAttack : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

#endif /* defined(__Zombie3_4__EnemyBevTreeNodeWaitAttack__) */


