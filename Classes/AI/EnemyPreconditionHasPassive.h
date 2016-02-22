//
//  EnemyPreconditionHasPassive.h
//  Zombie3_4
//  是否是被动行为
//  Created by jl on 15/7/6.
//
//

#ifndef __Zombie3_4__EnemyPreconditionHasPassive__
#define __Zombie3_4__EnemyPreconditionHasPassive__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"


//是否到达目标
class EnemyPreconditionHasPassive : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};
#endif /* defined(__Zombie3_4__EnemyPreconditionHasPassive__) */
