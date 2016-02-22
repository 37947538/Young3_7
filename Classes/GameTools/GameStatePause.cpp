//
//  GameStatePause.cpp
//  hero3_2
//
//  Created by jl on 14-9-25.
//
//

#include "GameStatePause.h"
#include "BulletObject.h"
#include "BulletBLL.h"

GameStatePause* GameStatePause::instance()
{
    static GameStatePause instance;
    return &instance;
}
void GameStatePause::enter(GameBLL* gb)
{
   
}
void GameStatePause::execute(GameBLL* aHero)
{
    
}
void GameStatePause::exit(GameBLL* gb)
{
    //怪恢复
    for (auto &e : gb->vectorEnemy) {
        e->getArmature()->resume();
        e->resume();
    }
    //子弹恢复
    for (auto &b : BulletBLL::getInstance()->vectorBullets) {
        b->resume();
    }
    //英雄恢复
    for (auto &t : gb->vectorHero) {
        t->getArmature()->resume();
        t->resume();
    }
}
void GameStatePause::executeTime(GameBLL* gb,float dt)
{
    //怪暂停
    for (auto &e : gb->vectorEnemy) {
        e->getArmature()->pause();
        e->pause();
    }
    //子弹暂停
    for (auto &b : BulletBLL::getInstance()->vectorBullets) {
        b->pause();
    }
    //英雄暂停
    for (auto &t : gb->vectorHero) {
        t->getArmature()->pause();
        t->pause();
    }
}