#ifndef __MyProjectName_HeroStateJump_H__
#define __MyProjectName_HeroStateJump_H__

#include "GameHeader.h"
#include "State.h"
#include "HeroBase.h"

/**
 k_ClassDes
 */

class HeroStateJump : public State<HeroBase>
{
public:
    static HeroStateJump* Instance();    //英雄跳跃状态
    virtual void enter(HeroBase*  arg1);    //英雄跳跃状态
    virtual void execute(HeroBase*  arg1);    //英雄跳跃状态
    virtual void executeTime(HeroBase*  arg1,float arg2);    //英雄跳跃状态
    virtual void exit(HeroBase*  arg1);    //英雄跳跃状态


private:


};

#endif 

