//
//  EnemyBevTreeNode.h
//  Zombie3_4
//
//  Created by jl on 15/8/21.
//
//

#ifndef __Zombie3_4__EnemyBevTreeNode__
#define __Zombie3_4__EnemyBevTreeNode__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  怪攻被击倒条件
 */
class EnemyPreconditionBeDown : public APBevTreePrecondition
{
public:
    virtual bool externalCondition(const BevNodeInputParam& input) const;
};

/**
 *  怪攻被击倒
 */
class EnemyBevTreeNodeBeDown : public APBevTreeNodeTerminal
{
public:
    EnemyBevTreeNodeBeDown(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string  animateName; //播放动画名称
    int iAttDist;             //攻击距离
};


#endif /* defined(__Zombie3_4__EnemyBevTreeNode__) */
