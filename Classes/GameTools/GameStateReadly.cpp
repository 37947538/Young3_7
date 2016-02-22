//
//  GameStateReadly.cpp
//  Human3_4
//
//  Created by jl on 15/3/20.
//
//

#include "GameStateReadly.h"

GameStateReadly* GameStateReadly::instance()
{
    static GameStateReadly instance;
    return &instance;
}

void GameStateReadly::enter(GameBLL* aBll)
{
    
}

void GameStateReadly::execute(GameBLL* aBll)
{
    
}

void GameStateReadly::exit(GameBLL* aBll)
{
    
}

void GameStateReadly::executeTime(GameBLL* aBll,float dt)
{
    /*
     //游戏逻辑循环
     gamebll->m_GameLayer->update(dt);
     
     //玩家角色循环
     gamebll->m_PlayRole->update(dt);
     
     //怪循环
     if(gamebll->m_CurrEnemy) gamebll->m_CurrEnemy->update(dt);
     */
}