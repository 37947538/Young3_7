/**
 k_ClassDes
 */

#include "HeroStateRun.h"
#include "GameBLL.h"
#include "GameLayer.h"


//英雄跑动状态
HeroStateRun* HeroStateRun::Instance()
{
   static HeroStateRun instance;    return &instance;
}

//英雄跑动状态
void HeroStateRun::enter(HeroBase*  arg1)
{
   //TODO:
    //arg1->runAnimate();
    log("arg1->runAnimate()");
}

//英雄跑动状态
void HeroStateRun::execute(HeroBase*  arg1)
{
   //TODO:
}

//英雄跑动状态
void HeroStateRun::executeTime(HeroBase*  arg1,float arg2)
{
   
    arg1->updatePosition(arg2);
    
    //更新阴影
    arg1->updateShadow(arg2);
}

//英雄跑动状态
void HeroStateRun::exit(HeroBase*  arg1)
{
   //TODO:
}


