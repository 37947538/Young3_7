//
//  HeroStateSkill.h
//  Zombie3_4
//  英雄技能状态
//  Created by jl on 15/7/16.
//
//

#ifndef __Zombie3_4__HeroStateSkill__
#define __Zombie3_4__HeroStateSkill__

#include <stdio.h>


#include "GameHeader.h"
#include "State.h"
#include "HeroBase.h"

/**
 k_ClassDes
 */

class HeroStateSkill : public State<HeroBase>
{
public:
    static HeroStateSkill* Instance();                          //英雄技能状态
    bool canChangeState(State<HeroBase>* aState);               //是否可以切换状态
    virtual void enter(HeroBase*  arg1);                        //英雄技能状态
    virtual void execute(HeroBase*  arg1);                      //英雄技能状态
    virtual void executeTime(HeroBase*  arg1,float arg2);       //英雄技能状态
    virtual void exit(HeroBase*  arg1);                         //英雄技能状态
    void setSkillID(int sID);                                   //设置技能ID
private:
    int iAttackID;
    
};


#endif /* defined(__Zombie3_4__HeroStateSkill__) */
