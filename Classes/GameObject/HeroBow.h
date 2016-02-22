//
//  HeroBow.h
//  Zombie3_4
//  弓箭手
//  Created by jl on 15/8/17.
//
//

#ifndef __Zombie3_4__HeroBow__
#define __Zombie3_4__HeroBow__

#include <stdio.h>
#include "HeroBase.h"

class HeroBow : public HeroBase
{
public:
    ~HeroBow();     //稀构函数
    HeroBow();      //英雄基础类
    virtual std::string commonAttack();                                     //普通攻击
    virtual void playAnimate(const std::string& animateName);               //播放动画
    virtual void skillA();                                                  //技能A动画
    virtual void skillB();                                                  //技能B动画
    virtual void skillC();                                                  //技能c动画
    virtual void skillD();                                                  //技能d动画
protected:
    virtual void frameEvent(Bone *bone, const std::string& fn, int oi, int ci); //事件回调
    virtual AttackObject* createAttackObject();
private:
    Vec2 vShootPos;
    void bulletCallback(Ref* sender);
};

#endif /* defined(__Zombie3_4__HeroBow__) */
