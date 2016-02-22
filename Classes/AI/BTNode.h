//
//  BTNode.h
//  Zombie3_4
//  BaseActionBT 行为节点
//  Created by jl on 15/8/25.
//
//

#ifndef __Zombie3_4__BTNode__
#define __Zombie3_4__BTNode__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"
#include "BevNodeDataHeader.h"

#pragma mark - 主体temp模版
/**
 *  主体temp模版
 */
class BevTreeNodeTemp : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeTemp(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
};


#pragma mark - 主体被击
/**
 *  主体被击
 */
class BevTreeNodeBeAttack : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeBeAttack(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;
    int iAttDist;
};

#pragma mark - 主体攻击
/**
 *  主体攻击
 */
class BevTreeNodeAttack : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeAttack(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;

};

#pragma mark - 主体攻击
/**
 *  主体攻击
 */
class BevTreeNodeEnemyAttack : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeEnemyAttack(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;
    bool isPlay;
    float m_SkillTime=0.0f;
    float m_Time=0.0f;
};

#pragma mark - 主体移动
/**
 *  主体移动
 */
class BevTreeNodeMove : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeMove(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;
};

#pragma mark - 主体技能
/**
 *  主体被击
 */
class BevTreeNodeSkill : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeSkill(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;
};

#pragma mark - 主体待机
/**
 *  主体待机
 */
class BevTreeNodeIdle : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeIdle(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
    float idleTime=5.0;
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;
    float waitTime;
};

#pragma mark - 主体跟随
/**
 *  主体跟随
 */
class BevTreeNodeFollow : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeFollow(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;
};

#pragma mark - 主体转向对面
/**
 *  主体转向对面
 */
class BevTreeNodeFace : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeFace(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);

};

#pragma mark - 主体追逐
/**
 *  主体转向对面
 */
class BevTreeNodeCatch : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeCatch(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
    float maxCatchTime=3.0;
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;
    float currCatchTime=0.0f;
};

#pragma mark - 主体离开对象
/**
 *  主体转向对面
 */
class BevTreeNodeLeave : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeLeave(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;
    
};

#pragma mark - 移动到目标
/**
 *  移动到目标
 */
class BevTreeNodeMoveToTarget : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeMoveToTarget(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;
};

#pragma mark - 敌兵被击
/**
 *  敌兵被击
 */
class BevTreeNodeEnemyBeAttack : public APBevTreeNodeTerminal
{
public:
    BevTreeNodeEnemyBeAttack(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    std::string animateName;
    int iAttDist;
    float m_BeAttackFlyPower;
    float m_ExecuteTime=0;
    bool m_IsUp=true;
    Vec2 m_Ground;
    float m_Power;
};

#endif /* defined(__Zombie3_4__BTNode__) */
