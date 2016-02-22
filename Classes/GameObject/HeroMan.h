//
//  HeroMan.h
//  Zombie3_4
//  战士英雄
//  Created by jl on 15/8/17.
//
//

#ifndef __Zombie3_4__HeroMan__
#define __Zombie3_4__HeroMan__

#include <stdio.h>
#include "HeroBase.h"

class HeroMan : public HeroBase
{
public:
    ~HeroMan();     //稀构函数
    HeroMan();      //英雄基础类
    virtual std::string commonAttack();             //普通攻击
    virtual void skillA();                          //技能A动画
    virtual void skillB();                          //技能B动画
    virtual void skillC();                          //技能c动画
    virtual void skillD();                          //技能d动画
    virtual void playAnimate(const std::string& animateName);   //播放动画
protected:
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    virtual void frameEvent(Bone *bone, const std::string& fn, int oi, int ci); //事件回调
    AttackObject* createAttackObject();
};

#endif /* defined(__Zombie3_4__HeroMan__) */
