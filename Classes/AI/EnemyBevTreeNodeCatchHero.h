//
//  EnemyBevTreeNodeCatchHero.h
//  Zombie3_4
//
//  Created by jl on 15/6/26.
//
//

#ifndef __Zombie3_4__EnemyBevTreeNodeCatchHero__
#define __Zombie3_4__EnemyBevTreeNodeCatchHero__

#include <stdio.h>
#include "GameHeader.h"
#include "APBevTreeHeader.h"
#include "GameEnum.h"

/**
 *  怪移动英雄指定位置
 */
class EnemyBevTreeNodeCatchHero : public APBevTreeNodeTerminal
{
public:
    EnemyBevTreeNodeCatchHero(APBevTreeNode* _o_ParentNode)
    :APBevTreeNodeTerminal(_o_ParentNode)
    {}
    virtual void doEnter(const BevNodeInputParam& input);
protected:
    virtual BevRunningStatus doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output);
};

#endif /* defined(__Zombie3_4__EnemyBevTreeNodeCatchHero__) */
