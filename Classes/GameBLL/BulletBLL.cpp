//
//  BulletBLL.cpp
//  Zombie3_4
//
//  Created by jl on 15/9/4.
//
//

#include "BulletBLL.h"
#include "GameBLL.h"
#include "GameLayer.h"
#include "GameUILayer.h"

static BulletBLL* sharedBulletBLL = nullptr;

BulletBLL* BulletBLL::getInstance()
{
    if (!sharedBulletBLL) {
        sharedBulletBLL = new (std::nothrow) BulletBLL();
    }
    return sharedBulletBLL;
}

void BulletBLL::destroyInstance()
{
    if(sharedBulletBLL != nullptr)
    {
        CC_SAFE_DELETE(sharedBulletBLL);
    }
}

BulletBLL::~BulletBLL()
{
    
}
BulletBLL::BulletBLL()
{
    
}

//子弹更新
void BulletBLL::update(float arg1)
{
    for (auto & b : vectorBullets) {
        b->update(arg1);
        
        if (!b->getIsCollision()) {
            continue;
        }        
        //获取碰撞的区域
        auto bulletOBB=b->getOBB();
        
        //攻击敌人
        if (b->getAttackType()==1) {
            //碰撞检测
            for (auto &e : GameBLL::instance()->vectorEnemy) {
                auto eObb=e->getOBB();
                if (eObb->isCollidWithAPOBB(bulletOBB) &&
                    e->getBodyState()!=GameEnum::BodyState::Die &&
                    b->isAttack(e))
                {
                    e->beAttack(b);
                    GameBLL::instance()->viewComboCount();
                    if (!b->getPenetrateAttack()) {
                        b->setIsCollision(false);
                        b->setVisible(false);
                        break;
                    }
                }
            }
        }else if (b->getAttackType()==2){  //攻击英雄
            for (auto &hero : GameBLL::instance()->vectorHero) {
                auto heroOBB=hero->getOBB();
                if (heroOBB->isCollidWithAPOBB(bulletOBB)) {
                    hero->beAttack(b);

                    if (!b->getPenetrateAttack()) {
                        b->setIsCollision(false);
                        b->setVisible(false);
                        break;
                    }
                }
            }
        }
    }
    
    //删除子弹
    for (auto &b : waitRemove) {
        removeBullet(b);
    }
    waitRemove.clear();
}

//增加子弹
void BulletBLL::addBullet(BulletObject* bullet)
{
    bullet->m_DoneCallback=CC_CALLBACK_1(BulletBLL::addWaitRemove, this);
    vectorBullets.push_back(bullet);
    GameBLL::instance()->m_GameLayer->addGameObject(bullet);
}

void BulletBLL::addWaitRemove(Ref* bullet)
{
    waitRemove.push_back((BulletObject*)bullet);
}

//删除子弹
void BulletBLL::removeBullet(BulletObject* bullet)
{
    auto iter = std::find(vectorBullets.begin(), vectorBullets.end(), bullet);
    if (iter != vectorBullets.end())
        vectorBullets.erase(iter);
    bullet->removeFromParentAndCleanup(true);
}
