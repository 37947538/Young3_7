//
//  EnemyBevTreeNodeIdle.h
//  Zombie3_4
//  待机
//  Created by jl on 15/6/29.
//
//

#ifndef __Zombie3_4__EnemyBevTreeNodeIdle__
#define __Zombie3_4__EnemyBevTreeNodeIdle__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  怪攻待机
 */
class EnemyBevTreeNodeIdle : public APBevTreeNodeTerminal
{
public:
    EnemyBevTreeNodeIdle(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
    void setWaitingTime(float ftime){ m_WaitingTime=ftime; }    //设置待机时间
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    std::string animateName;                //将要播放待机动画名称
};

//攻击前待机数
class EnemyBevTreeNodeIdleAttackBefore : public EnemyBevTreeNodeIdle
{
public:
    EnemyBevTreeNodeIdleAttackBefore(APBevTreeNode* parentNode)
    :EnemyBevTreeNodeIdle(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
};

//攻击后待机数
class EnemyBevTreeNodeIdleAttackAfter : public EnemyBevTreeNodeIdle
{
public:
    EnemyBevTreeNodeIdleAttackAfter(APBevTreeNode* parentNode)
    :EnemyBevTreeNodeIdle(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
};

//追逐待机数
class EnemyBevTreeNodeIdleCatch : public EnemyBevTreeNodeIdle
{
public:
    EnemyBevTreeNodeIdleCatch(APBevTreeNode* parentNode)
    :EnemyBevTreeNodeIdle(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
};

#endif /* defined(__Zombie3_4__EnemyBevTreeNodeIdle__) */
