//
//  EnemyBevTreeNodeFace.h
//  Zombie3_4
//  面对面英雄
//  Created by jl on 15/8/13.
//
//

#ifndef __Zombie3_4__EnemyBevTreeNodeFace__
#define __Zombie3_4__EnemyBevTreeNodeFace__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  面对面英雄
 */
class EnemyBevTreeNodeFace : public APBevTreeNodeTerminal
{
public:
    EnemyBevTreeNodeFace(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    float m_WaitingTime;
    std::string animateName;                //将要播放待机动画名称
};

#endif /* defined(__Zombie3_4__EnemyBevTreeNodeFace__) */
