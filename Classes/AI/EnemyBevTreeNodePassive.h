//
//  EnemyBevTreeNodePassive.h
//  敌兵被动行为节点，被杀，被打
//
//  Created by jl on 15/7/6.
//
//

#ifndef __Zombie3_4__EnemyBevTreeNodePassive__
#define __Zombie3_4__EnemyBevTreeNodePassive__

#include <stdio.h>


#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  怪攻被攻击
 */
class EnemyBevTreeNodePassive : public APBevTreeNodePrioritySelector
{
public:
    EnemyBevTreeNodePassive(APBevTreeNode* parentNode)
    :APBevTreeNodePrioritySelector(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    float m_ShaderTime;
    bool m_EnemyRunState;
};



#endif /* defined(__Zombie3_4__EnemyBevTreeNodePassive__) */
