#ifndef __MyProjectName_HeroStateIdle_H__
#define __MyProjectName_HeroStateIdle_H__

#include "GameHeader.h"
#include "State.h"
#include "HeroBase.h"
/**
 k_ClassDes
 */

class HeroStateIdle : public State<HeroBase>
{
public:
    static HeroStateIdle* Instance();    //英雄空闲状态
    virtual void enter(HeroBase*  arg1);    //英雄空闲状态
    virtual void execute(HeroBase*  arg1);    //英雄空闲状态
    virtual void executeTime(HeroBase*  arg1,float arg2);    //英雄空闲状态
    virtual void exit(HeroBase*  arg1);    //英雄空闲状态
private:
};

#endif 

