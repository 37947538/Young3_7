//
//  EnemyPreconditionHasBeAttack.h
//  Zombie3_4
//  被攻击
//  Created by jl on 15/6/29.
//
//

#ifndef __Zombie3_4__EnemyPreconditionHasBeAttack__
#define __Zombie3_4__EnemyPreconditionHasBeAttack__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"


//是否被打
class EnemyPreconditionHasBeAttack : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};


#endif /* defined(__Zombie3_4__EnemyPreconditionHasBeAttack__) */
