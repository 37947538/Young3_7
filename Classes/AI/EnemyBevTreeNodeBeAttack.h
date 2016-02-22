//
//  EnemyBevTreeNodeBeAttack.h
//  Zombie3_4
//  被攻击播放动画
//  Created by jl on 15/6/29.
//
//

#ifndef __Zombie3_4__EnemyBevTreeNodeBeAttack__
#define __Zombie3_4__EnemyBevTreeNodeBeAttack__

#include <stdio.h>

#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  怪攻被攻击
 */
class EnemyBevTreeNodeBeAttack : public APBevTreeNodeTerminal
{
public:
    EnemyBevTreeNodeBeAttack(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string  animateName; //播放动画名称
    int iAttDist;             //攻击距离
};


#endif /* defined(__Zombie3_4__EnemyBevTreeNodeBeAttack__) */
