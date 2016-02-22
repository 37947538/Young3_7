//
//  GameStateFinish.h
//  hero3_2
//  游戏结束
//  Created by jl on 14-9-25.
//
//

#ifndef __hero3_2__GameStateFinish__
#define __hero3_2__GameStateFinish__

#include <iostream>
#include "State.h"
#include "GameBLL.h"

class GameStateFinish : public State<GameBLL>
{
public:
    static GameStateFinish* instance();
    virtual void enter(GameBLL* aHero);
    virtual void execute(GameBLL* aHero);
    virtual void executeTime(GameBLL* aHero,float dt);
    virtual void exit(GameBLL* aHero);
};
#endif /* defined(__hero3_2__GameStateFinish__) */
