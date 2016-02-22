//
//  GameStateRun.h
//  hero3_2
//  游戏正常运行
//  Created by jl on 14-9-25.
//
//

#ifndef __hero3_2__GameStateRun__
#define __hero3_2__GameStateRun__

#include <iostream>
#include "State.h"
#include "GameBLL.h"

class GameStateRun : public State<GameBLL>
{
public:
    static GameStateRun* instance();
    virtual void enter(GameBLL* aHero);
    virtual void execute(GameBLL* aHero);
    virtual void executeTime(GameBLL* aHero,float dt);
    virtual void exit(GameBLL* aHero);
};

#endif /* defined(__hero3_2__GameStateRun__) */
