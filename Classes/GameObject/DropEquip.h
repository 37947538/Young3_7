//
//  DropEquip.h
//  Zombie3_4
//  掉落装备
//  Created by jl on 15/7/29.
//
//

#ifndef __Zombie3_4__DropEquip__
#define __Zombie3_4__DropEquip__

#include <stdio.h>
#include "DropObject.h"

class DropEquip : public DropObject
{
public:
    DropEquip();
    ~DropEquip();
    static DropEquip* create(int weaponIndex);
    CC_SYNTHESIZE(int, m_WeaponIndex, WeaponIndex);
    bool init(int weaponIndex);
    bool init(Sprite* spr,Sprite* sprbg,Sprite* clip);
    virtual DropType getType(){ return DropType::Equip; };        //获取掉落类型
    DropEquip* clone();                                           //克隆
private:
    Sprite* spr;                                                  //保存组合数据
    Sprite* sprbg;
    Sprite* clip;
};

#endif /* defined(__Zombie3_4__DropEquip__) */
