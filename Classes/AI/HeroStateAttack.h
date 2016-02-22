#ifndef __MyProjectName_HeroStateAttack_H__
#define __MyProjectName_HeroStateAttack_H__

#include "GameHeader.h"
#include "State.h"
#include "HeroBase.h"

/**
 k_ClassDes
 */

class HeroStateAttack : public State<HeroBase>
{
public:
    static HeroStateAttack* Instance();    //英雄攻击状态
    virtual void enter(HeroBase*  arg1);    //英雄攻击状态
    virtual void execute(HeroBase*  arg1);    //英雄攻击状态
    virtual void executeTime(HeroBase*  arg1,float arg2);    //英雄攻击状态
    virtual void exit(HeroBase*  arg1);    //英雄攻击状态


private:


};

#endif 

