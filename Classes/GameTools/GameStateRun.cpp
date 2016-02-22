//
//  GameStateRun.cpp
//  hero3_2
//
//  Created by jl on 14-9-25.
//
//

#include "GameStateRun.h"
#include "GameLayer.h"
#include "HeroBase.h"
#include "EnemyBase.h"
#include "RewardEquipBLL.h"



GameStateRun* GameStateRun::instance()
{
    static GameStateRun instance;
    return &instance;
}

void GameStateRun::enter(GameBLL* abll)
{
    
}

void GameStateRun::execute(GameBLL* abll)
{
    
}
void GameStateRun::exit(GameBLL* abll)
{
    
}
void GameStateRun::executeTime(GameBLL* abll,float dt)
{
    //更新敌兵对象逻辑
    abll->m_GameLayer->scroolViewScree();
    //abll->m_MainHero->update(dt);
    
    for (auto & h : abll->vectorHero) {
        h->update(dt);
    }
    
    //敌兵业务逻辑更新
    for (auto & e : abll->vectorEnemy) {
        e->update(dt);
    }
    
    //子弹业务
    abll->updateBullets(dt);
    
    
    //奖励掉落装备更新
    abll->m_rewardEquipBll->update(dt);
    
    //更新关卡逻辑碰撞
    abll->updateLevelCollision(dt);
    /*
    //判断没有敌兵
    if (abll->vectorEnemy.size()==0) {
        //增加敌兵
        EnemyBase *eb=EnemyFactory::getEnemy(0);
        this->addEnemy(eb);
        m_GameUILayer->setGOTips(Vec2(800.f, 400.f),4.0f);
        //change
    }
     */
    
    /*
    abll->gameRun(dt);
    abll->collision(dt);
    abll->enemyUpdate(dt);
    abll->towerUpdate(dt);
    abll->reZOrderObject();
    
    TodoBLL::getInstance()->update(dt);
     */
}
