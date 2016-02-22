//
//  AttackObject.h
//  Zombie3_4
//  攻击对象
//  Created by jl on 15/8/9.
//
//

#ifndef __Zombie3_4__AttackObject__
#define __Zombie3_4__AttackObject__

#include <stdio.h>
#include "GameHeader.h"
#include "GameBaseObject.h"

class AttackObject : public GameBaseObject
{
public:
    ~AttackObject();
    AttackObject();
    CREATE_FUNC(AttackObject);
    virtual bool init() { return true; };
    CC_SYNTHESIZE_RETAIN(GameBaseObject*, m_AttackObject, AttackObject);    //攻击对象
    CC_SYNTHESIZE(bool, m_isSubBoold, IsSubBoold);                          //是否已经扣血
    CC_SYNTHESIZE(bool, m_isHitDown, IsHitDown);                            //是否被击倒
    CC_PROPERTY(Rect, m_attRange, AttRange);                                //攻击范围
    CC_SYNTHESIZE(int, m_Attack, Attack);                                   //攻击力
    CC_SYNTHESIZE(float, m_RepelPower, RepelPower);                         //击退力量
    virtual AttackObject* clone();                                          //克隆对象
    virtual APOBB* getOBB();                                                //获取碰撞矩形
};

#endif /* defined(__Zombie3_4__AttackObject__) */
