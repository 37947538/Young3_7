//
//  EnemyBevTreeNodeInverseMove.h
//  Zombie3_4
//
//  Created by jl on 15/6/29.
//
//

#ifndef __Zombie3_4__EnemyBevTreeNodeInverseMove__
#define __Zombie3_4__EnemyBevTreeNodeInverseMove__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  怪攻被攻击
 */
class EnemyBevTreeNodeInverseMove : public APBevTreeNodeTerminal
{
public:
    EnemyBevTreeNodeInverseMove(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    bool m_EnemyRunState;
};
#endif /* defined(__Zombie3_4__EnemyBevTreeNodeInverseMove__) */
