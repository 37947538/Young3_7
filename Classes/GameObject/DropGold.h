//
//  DropGold.h
//  Zombie3_4
//  掉落金币
//  Created by jl on 15/7/29.
//
//

#ifndef __Zombie3_4__DropGold__
#define __Zombie3_4__DropGold__

#include <stdio.h>
#include "DropObject.h"

class DropGold : public DropObject
{
public:
    CREATE_FUNC(DropGold);
    bool init();
    virtual DropType getType(){ return DropType::Gold; };        //获取掉落类型
private:
    Sprite *m_goldSpr;
};

#endif /* defined(__Zombie3_4__DropGold__) */
