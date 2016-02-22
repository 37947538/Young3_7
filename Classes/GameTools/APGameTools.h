//
//  APGameTools.h
//  Zombie3_4
//  游戏工具类,帮助游戏计算经验值
//  Created by jl on 15/7/24.
//
//

#ifndef __Zombie3_4__APGameTools__
#define __Zombie3_4__APGameTools__

#include <stdio.h>
#include "cocos2d.h"
#include "HeroModel.h"

using namespace cocos2d;

class APGameTools{
public:
    static int getLvExp(int iLV);           //获取玩家当前等级所需要的经验,返回经验,iLv:等级
    static int getPower(HeroModel* pmodel); //获取某角色战斗力的算法
};
#endif /* defined(__Zombie3_4__APGameTools__) */
