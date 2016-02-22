//
//  HeroStateSkill.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/16.
//
//

#include "HeroStateSkill.h"
#include "HeroStateBeAttack.h"
#include "HeroStateRun.h"

//英雄攻击状态
HeroStateSkill* HeroStateSkill::Instance()
{
    static HeroStateSkill instance;
    return &instance;
}

//是否可以跳转当前状态
bool HeroStateSkill::canChangeState(State<HeroBase>* aState)
{
    //技能状态无法进入本身
    if (typeid(*aState) == typeid(*(HeroStateSkill::Instance()))) return false;
    
    //技能状态无法进入被打状态
    if (typeid(*aState) == typeid(*(HeroStateBeAttack::Instance()))) return false;
    
    //技能状态无法进入跑状态
    if (typeid(*aState) == typeid(*(HeroStateRun::Instance()))) return false;
    
    return true;
}

//设置技能ID
void HeroStateSkill::setSkillID(int sID)
{
    iAttackID=sID;
}

//英雄攻击状态
void HeroStateSkill::enter(HeroBase*  arg1)
{
    //修改移动速度
    //arg1->m_vVelocity*=0.1;
    
    //Vec2 diff=Vec2::ZERO;
    auto m_Armature=arg1->getArmature();
    m_Armature->getAnimation()->stop();
    
    //技能1
    if (iAttackID==1) {
        arg1->skillA();
    }else if(iAttackID==2)
    {
         arg1->skillB();
    }else if(iAttackID==3)
    {
        arg1->skillC();
    }else if(iAttackID==4)
    {
        arg1->skillD();
    }
   
}

//英雄攻击状态
void HeroStateSkill::execute(HeroBase*  arg1)
{
    //TODO:
}

//英雄攻击状态
void HeroStateSkill::executeTime(HeroBase*  arg1,float arg2)
{
    if (iAttackID==2) {
        arg1->updatePosition(arg2);
    }
    
    //更新阴影
    //arg1->updateShadow(arg2);
}

//英雄攻击状态
void HeroStateSkill::exit(HeroBase*  arg1)
{
    
}

