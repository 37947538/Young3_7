//
//  GameStateFinish.cpp
//  hero3_2
//
//  Created by jl on 14-9-25.
//
//
#include "GameStateFinish.h"
//#include "GameScene.h"

GameStateFinish* GameStateFinish::instance()
{
    static GameStateFinish instance;
    return &instance;
}

void GameStateFinish::enter(GameBLL* gb)
{
    /*
    for (auto& e : gb->gameLayer->vectorEnemy) {
        e->pause();
        e->stopAllActions();
    }
    for (auto & t : gb->gameLayer->vectorTower) {
        t->pause();
        t->stopAllActions();
    }
     */
}

void GameStateFinish::execute(GameBLL* gb)
{
    
}

void GameStateFinish::exit(GameBLL* gb)
{
    
}

void GameStateFinish::executeTime(GameBLL* gb,float dt)
{
    
}