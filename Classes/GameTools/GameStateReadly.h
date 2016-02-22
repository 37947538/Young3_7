//
//  GameStateReadly.h
//  Human3_4
//  游戏逻辑准备状态 
//  Created by jl on 15/3/20.
//
//

#ifndef __Human3_4__GameStateReadly__
#define __Human3_4__GameStateReadly__

#include <stdio.h>
#include "State.h"
#include "GameBLL.h"

class GameStateReadly : public State<GameBLL>
{
public:
    static GameStateReadly* instance();
    virtual void enter(GameBLL* abll);
    virtual void execute(GameBLL* abll);
    virtual void executeTime(GameBLL* abll,float dt);
    virtual void exit(GameBLL* abll);
};
#endif /* defined(__Human3_4__GameStateReadly__) */
