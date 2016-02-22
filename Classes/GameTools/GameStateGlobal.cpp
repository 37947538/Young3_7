//
//  GameStateGlobal.cpp
//  hero3_2
//
//  Created by jl on 14-9-25.
//
//

#include "GameStateGlobal.h"

GameStateGlobal* GameStateGlobal::instance()
{
    static GameStateGlobal instance;
    return &instance;
}
void GameStateGlobal::enter(GameBLL* aHero)
{
    
}
void GameStateGlobal::execute(GameBLL* aHero)
{
    
}
void GameStateGlobal::exit(GameBLL* aHero)
{
    
}
void GameStateGlobal::executeTime(GameBLL* aHero,float dt)
{
    
}