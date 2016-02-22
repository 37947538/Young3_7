//
//  EnemyBevTreeNodeAttack.h
//  Zombie3_4
//
//  Created by jl on 15/6/26.
//
//

#ifndef __Zombie3_4__EnemyBevTreeNodeAttack__
#define __Zombie3_4__EnemyBevTreeNodeAttack__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  怪攻击英雄指定位置
 */
class EnemyBevTreeNodeAttack : public APBevTreeNodeTerminal
{
public:
    EnemyBevTreeNodeAttack(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    bool m_EnemyRunState;
    bool m_isPlayAnimate;
    std::string animateName;
};


#endif /* defined(__Zombie3_4__EnemyBevTreeNodeAttack__) */
