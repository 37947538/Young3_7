//
//  RewardEquipBLL.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/28.
//
//

#include "RewardEquipBLL.h"
#include "EnemyBase.h"
#include "GameBLL.h"
#include "GameLayer.h"
#include "APScatterAction.h"
#include "DropGold.h"
#include "DropObject.h"
#include "DropEquip.h"
#include "EnemyModel.h"
#include "EquipmentLocalBLL.h"

bool RewardEquipBLL::init()
{
    return true;
}

//奖励掉落装备更新
void RewardEquipBLL::update(float arg1)
{
    //做英雄与金币物理碰撞
    auto mainHero=GameBLL::instance()->m_MainHero;
    //获取碰撞的区域
    auto herobb=mainHero->getOBB();
    
    //遍历怪是否攻击
    std::vector<DropObject*> waitRemove;
    for (auto &g : m_dropObjects) {
        //循环遍历怪，判断攻击距离到达后攻击怪
        auto gobb=g->getOBB();
        
        if (gobb->isCollidWithAPOBB(herobb)) {
            //英雄碰撞到金币
            waitRemove.push_back(g);
        }
    }
    
    //影响碰撞对象
    for (auto &dobj : waitRemove) {
        mainHero->getDropObject(dobj);
        removeEquip(dobj);
    }
    
    waitRemove.clear();
}

//随机掉落
void RewardEquipBLL::randDrop(EnemyBase* eb)
{
    Vec2 vPos=eb->getPosition();

    float fRand=CCRANDOM_0_1();
    if (fRand > 0.7) {
        //掉落金币数量 为 random（3，ROUNDDOWN((怪物权值+怪物等级/2)/5)+4）
        auto model=eb->getEnemyModel();
        int iMax=(model->DropValue + model->LV / 2) / 5 + 4;
        int iCount=APTools::getRand(3, iMax);
        for (int i=0; i<iCount; i++) {
            addOneGold(vPos);
        }
    }
    //掉落概率
    float dropRate=CCRANDOM_0_1() * 100.0;
    dropOneEquip(eb, dropRate);
}

//掉落一个装备
void RewardEquipBLL::dropOneEquip(EnemyBase* eb, float dropRate)
{
    Vec2 vPos=eb->getPosition();
    auto enemyModel=eb->getEnemyModel();
    //掉落权值
    int dropValue=enemyModel->DropValue;
    std::vector<Weapon*> equipVector;
    auto eBLL=EquipmentLocalBLL::create();
    eBLL->getDropEquipment(equipVector, dropValue, dropRate);
    
    int dropEquipCount=(int)equipVector.size();
    if (dropEquipCount>0) {
        int randIndex=APTools::getRand(0, dropEquipCount - 1);
        auto equip=equipVector.at(randIndex);
        int dropEquipIndex=equip->WeaponID - 1;
        addOneEquip(vPos, dropEquipIndex);
    }
}

//增加金币
void RewardEquipBLL::addOneGold(const Vec2& goldPos)
{
    auto callFunc= CallFuncN::create(CC_CALLBACK_1(RewardEquipBLL::removeEquip,this));
    //加金币
    float height = APTools::getRandFloat(200,650);
    auto gold = DropGold::create();
    gold->setPosition(goldPos);
    auto apscatt = APScatterAction::create(height, 0.2); //APScatterAction::createWithRotation(0.2);
    auto blink = Blink::create(1, 3);
    auto blink2 = Blink::create(1.3, 4);
    auto sqe = Sequence::create(apscatt,DelayTime::create(1.5f),blink,blink2,callFunc, NULL);
    gold->runAction(sqe);
    
    auto gamelayer=GameBLL::instance()->m_GameLayer;
    gamelayer->addGameObject(gold);
    m_dropObjects.pushBack(gold);
}

//增加一个装备
void RewardEquipBLL::addOneEquip(const Vec2& ePos, int weaponIndex)
{
    auto callFunc=CallFuncN::create(CC_CALLBACK_1(RewardEquipBLL::removeEquip,this));

    //加装备
    float height = APTools::getRandFloat(200,350);
    auto equip = DropEquip::create(weaponIndex);
    equip->setPosition(ePos);
    auto apscatt = APScatterAction::create(height);
    auto blink = Blink::create(1, 3);
    auto blink2 = Blink::create(1.3, 4);
    auto sqe = Sequence::create(apscatt,DelayTime::create(1.5f),blink,blink2,callFunc, NULL);
    equip->runAction(sqe);
    
    auto gamelayer=GameBLL::instance()->m_GameLayer;
    gamelayer->addGameObject(equip);
    m_dropObjects.pushBack(equip);
}

//删除装备
void RewardEquipBLL::removeEquip(Node* gold)
{
    auto obj=dynamic_cast<DropObject*>(gold);
    m_dropObjects.eraseObject(obj);
    obj->removeFromParentAndCleanup(true);
}

