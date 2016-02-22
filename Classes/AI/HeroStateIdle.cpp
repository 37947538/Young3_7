/**
 k_ClassDes
 */

#include "HeroStateIdle.h"



//英雄空闲状态
HeroStateIdle* HeroStateIdle::Instance()
{
   static HeroStateIdle instance;    return &instance;
}

//英雄空闲状态
void HeroStateIdle::enter(HeroBase*  arg1)
{
    //arg1->idleAnimate();
}

//英雄空闲状态
void HeroStateIdle::execute(HeroBase*  arg1)
{
   //TODO:
}

//英雄空闲状态
void HeroStateIdle::executeTime(HeroBase*  arg1,float arg2)
{
   //TODO:
}

//英雄空闲状态
void HeroStateIdle::exit(HeroBase*  arg1)
{
   //TODO:
}


