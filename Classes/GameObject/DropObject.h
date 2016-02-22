//
//  DropObject.h
//  Zombie3_4
//  掉落对象
//  Created by jl on 15/7/29.
//
//

#ifndef __Zombie3_4__DropObject__
#define __Zombie3_4__DropObject__

#include <stdio.h>
#include <GameHeader.h>
#include "GameBaseObject.h"

class DropObject : public GameBaseObject
{
public:
    enum class  DropType
    {
        None=-1,    //空
        Gold=0,     //金币
        Equip,     //装备
    };
    virtual APOBB* getOBB();                            //获取碰撞矩形
    virtual DropType getType()=0;                         //获取掉落类型
};

#endif /* defined(__Zombie3_4__DropObject__) */
