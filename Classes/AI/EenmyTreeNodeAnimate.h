//
//  EenmyTreeNodeAnimate.h
//  Zombie3_4
//  敌兵播放动画行为树节点(发送宿主消息播放动画,监听动画完成)
//  Created by jl on 15/8/9.
//
//

#ifndef __Zombie3_4__EenmyTreeNodeAnimate__
#define __Zombie3_4__EenmyTreeNodeAnimate__

#include <stdio.h>


#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  怪攻被攻击
 */
class EenmyTreeNodeAnimate : public APBevTreeNodeTerminal
{
public:
    EenmyTreeNodeAnimate(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    float m_ShaderTime;
    bool m_EnemyRunState;
    bool m_isPlayAnimate;     //是否播放动画
};


#endif /* defined(__Zombie3_4__EenmyTreeNodeAnimate__) */
