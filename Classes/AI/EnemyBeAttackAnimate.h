//
//  EnemyBeAttackAnimate.h
//  Zombie3_4
//
//  Created by jl on 15/7/7.
//
//

#ifndef __Zombie3_4__EnemyBeAttackAnimate__
#define __Zombie3_4__EnemyBeAttackAnimate__

#include <stdio.h>
#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  怪攻待机
 */
class EnemyBeAttackAnimate : public APBevTreeNodeTerminal
{
public:
    EnemyBeAttackAnimate(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
};



#endif /* defined(__Zombie3_4__EnemyBeAttackAnimate__) */
