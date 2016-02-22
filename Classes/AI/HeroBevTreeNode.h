//
//  HeroBevTreeNode.h
//  Zombie3_4
//  英雄行为树节点
//  Created by jl on 15/8/19.
//
//

#ifndef __Zombie3_4__HeroBevTreeNode__
#define __Zombie3_4__HeroBevTreeNode__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  英雄待机
 */
class HeroBevTreeNodeIdle : public APBevTreeNodeTerminal
{
public:
    HeroBevTreeNodeIdle(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    std::string animateName;                //将要播放待机动画名称
};

/**
 *  英雄左右移动
 */
class HeroBevTreeNodeMove : public APBevTreeNodeTerminal
{
public:
    HeroBevTreeNodeMove(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    std::string animateName;                //将要播放待机动画名称
};

/**
 *  英雄普通攻击
 */
class HeroBevTreeNodeAtt : public APBevTreeNodeTerminal
{
public:
    HeroBevTreeNodeAtt(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    std::string animateName;                //将要播放待机动画名称
};

/**
 *  英雄技能攻击
 */
class HeroBevTreeNodeSkill : public APBevTreeNodeTerminal
{
public:
    HeroBevTreeNodeSkill(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    bool m_isPlayAnimate;
    std::string animateName;                //将要播放待机动画名称
};

/**
 *  Npc攻击
 */
class HeroBevTreeNPCAttack : public APBevTreeNodeTerminal
{
public:
    HeroBevTreeNPCAttack(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    bool m_isPlayAnimate;
    std::string animateName;                //将要播放待机动画名称
};

/**
 *  Npc跟随 主英雄
 */
class HeroBevTreeNPCFollow : public APBevTreeNodeTerminal
{
public:
    HeroBevTreeNPCFollow(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    bool m_isPlayAnimate;
    std::string animateName;                //将要播放待机动画名称
};

/**
 *  英雄被攻击
 */
class HeroBevTreeBeAttack : public APBevTreeNodeTerminal
{
public:
    HeroBevTreeBeAttack(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    bool m_isPlayAnimate;
    std::string animateName;                //将要播放待机动画名称
};

#endif /* defined(__Zombie3_4__HeroBevTreeNode__) */
