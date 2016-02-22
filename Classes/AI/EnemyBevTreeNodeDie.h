//
//  EnemyBevTreeNodeDie.h
//  Zombie3_4
//
//  Created by liuye on 15/8/10.
//
//

#ifndef __Zombie3_4__EnemyBevTreeNodeDie__
#define __Zombie3_4__EnemyBevTreeNodeDie__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  怪物死亡
 */
class EnemyBevTreeNodeDie : public APBevTreeNodeTerminal
{
public:
    EnemyBevTreeNodeDie(APBevTreeNode* parentNode)
    :APBevTreeNodeTerminal(parentNode)
    {}
protected:
    virtual void doEnter(const BevNodeInputParam& input);
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
    bool m_isPlayAnimate;     //是否播放动画
    std::string  animateName; //播放动画名称
};

#endif /* defined(__Zombie3_4__EnemyBevTreeNodeDie__) */
