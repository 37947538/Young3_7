#ifndef __MyProjectName_HeroStateBeAttack_H__
#define __MyProjectName_HeroStateBeAttack_H__

#include "GameHeader.h"
#include "State.h"
#include "HeroBase.h"
/**
 k_ClassDes
 */

class HeroStateBeAttack : public State<HeroBase>
{
public:
    static HeroStateBeAttack* Instance();    //英雄被打状态
    virtual void enter(HeroBase*  arg1);    //英雄被打状态
    virtual void execute(HeroBase*  arg1);    //英雄被打状态
    virtual void executeTime(HeroBase*  arg1,float arg2);    //英雄被打状态
    virtual void exit(HeroBase*  arg1);    //英雄被打状态


private:


};

#endif 

