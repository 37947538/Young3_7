//
//  GameStateGlobal.h
//  hero3_2
//
//  Created by jl on 14-9-25.
//
//

#ifndef __hero3_2__GameStateGlobal__
#define __hero3_2__GameStateGlobal__

#include <iostream>
#include "State.h"
#include "GameBLL.h"

class GameStateGlobal : public State<GameBLL>
{
public:
    static GameStateGlobal* instance();
    virtual void enter(GameBLL* aHero);
    virtual void execute(GameBLL* aHero);
    virtual void executeTime(GameBLL* aHero,float dt);
    virtual void exit(GameBLL* aHero);
};
#endif /* defined(__hero3_2__GameStateGlobal__) */
