//
//  EnemyEventObject.h
//  Zombie3_4
//
//  Created by jl on 15/8/10.
//
//

#ifndef __Zombie3_4__EnemyEventObject__
#define __Zombie3_4__EnemyEventObject__

#include <stdio.h>
#include "GameHeader.h"
#include "GameBaseObject.h"

class EnemyEventObject : public Ref
{
public:
    ~EnemyEventObject();
    EnemyEventObject();
    CREATE_FUNC(EnemyEventObject);
    virtual bool init() { return true; };
    CC_SYNTHESIZE_RETAIN(Ref*, m_EventArg, EventArg);               //敌兵参数
    CC_SYNTHESIZE(GameEnum::EnemyEvent, m_EnemyEvent, EnemyEvent);  //敌兵事件
    std::string playAnimateName;                                    //播放动画名称
};
#endif /* defined(__Zombie3_4__EnemyEventObject__) */
