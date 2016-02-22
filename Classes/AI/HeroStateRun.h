#ifndef __MyProjectName_HeroStateRun_H__
#define __MyProjectName_HeroStateRun_H__

#include "GameHeader.h"
#include "State.h"
#include "HeroBase.h"
/**
 k_ClassDes
 */

class HeroStateRun : public State<HeroBase>
{
public:
    static HeroStateRun* Instance();    //英雄跑动状态
    virtual void enter(HeroBase*  arg1);    //英雄跑动状态
    virtual void execute(HeroBase*  arg1);    //英雄跑动状态
    virtual void executeTime(HeroBase*  arg1,float arg2);    //英雄跑动状态
    virtual void exit(HeroBase*  arg1);    //英雄跑动状态


private:


};

#endif 

