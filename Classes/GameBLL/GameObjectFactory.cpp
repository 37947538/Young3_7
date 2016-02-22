//
//  GameObjectFactory.cpp
//  Zombie3_4
//
//  Created by jl on 15/8/14.
//
//

#include "GameObjectFactory.h"
#include "EnemyModelBLL.h"
#include "HeroModel.h"
#include "HeroModelBll.h"
#include "GameHeader.h"
#include "HeroBase.h"
#include "HeroMan.h"
#include "HeroBow.h"
#include "HeroAssassin.h"
#include "EnemyBow.h"
#include "EnemyCannon.h"
#include "EnemyBoss.h"
#include "HeroKnight.h"

//获取敌兵
EnemyBase* GameObjectFactory::getEnemy(int enemyIndex, int enemyLv)
{
    //enemyIndex=3;
    EnemyBase *enemy=nullptr;
    EnemyModelBLL *emb=EnemyModelBLL::create(kModelWritablePath);
    auto pEnemyModel=&(emb->modelData[enemyIndex]);
    pEnemyModel->LV=enemyLv;
    switch (pEnemyModel->EnemyType) {
        case 1: //远程发子弹攻击
        {
            //炸弹手子弹抛物线攻击
            if (enemyIndex==11) {
                enemy=new EnemyCannon();
            }else{
                enemy=new EnemyBow();
            }
        } break;
        case 2: //Boss
        {
            enemy=new EnemyBoss();
        } break;
        default: //默认是近身攻击
        {
            enemy=new EnemyBase();
        } break;
    }
    if (enemy) {
        enemy->loadData(pEnemyModel);
        enemy->autorelease();
    }
    
    return enemy;
}

//获取英雄
HeroBase* GameObjectFactory::getHero(int heroIndex)
{
    HeroBase *hero=nullptr;
    HeroModelBLL *hmb=HeroModelBLL::create(kModelWritablePath);
    HeroModel *hm=&(hmb->modelData[heroIndex]);
    switch (heroIndex) {
        case 0:         //战士
        {
            hero=new HeroMan();
            hero->setInitPosition(kHeroPosition);
            hero->loadData(hm);
            hero->autorelease();
        }break;
        case 1:
        {
            hero=new HeroBow();
            hero->setInitPosition(kHeroPosition);
            hero->loadData(hm);
            hero->autorelease();
        }break;
        case 2:
        {
            hero=new HeroAssassin();
            hero->setInitPosition(kHeroPosition);
            hero->loadData(hm);
            hero->autorelease();
        }break;
        case 3:
        {
            hero=new HeroKnight();
            hero->setInitPosition(kHeroPosition);
            hero->loadData(hm);
            hero->autorelease();
        }break;
        default:
            break;
    }
    return hero;
}