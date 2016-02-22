//
//  HeroKnight.h
//  Zombie3_4
//  骑士英雄
//  Created by liuye on 15/9/9.
//
//

#ifndef __Zombie3_4__HeroKnight__
#define __Zombie3_4__HeroKnight__

#include <stdio.h>
#include "HeroBase.h"

class HeroKnight : public HeroBase
{
public:
    ~HeroKnight();     //稀构函数
    HeroKnight();      //英雄基础类
    virtual std::string commonAttack();             //普通攻击
    virtual void skillA();                          //技能A动画
    virtual void skillB();                          //技能B动画
    virtual void skillC();                          //技能c动画
    virtual void skillD();                          //技能d动画
    virtual void playAnimate(const std::string& animateName);   //播放动画
    virtual BTNodeInputData* readBevNodeInputData();            //获取状态数据
protected:
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    virtual void frameEvent(Bone *bone, const std::string& fn, int oi, int ci); //事件回调
    AttackObject* createAttackObject();
};

#endif /* defined(__Zombie3_4__HeroKnight__) */
